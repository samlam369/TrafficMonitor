#include "../TrafficMonitor/TaskbarLayout.h"
#include "../TrafficMonitor/OverlayLayout.h"
#include <cassert>
#include <iostream>
int main()
{
    long cases = 0;
    for (int height = 1; height <= 160; ++height)
        for (int font = 1; font <= 64; ++font)
            for (int gap : { -4, 0, 1, 2, 5, 100 })
            {
                const auto r = TaskbarLayout::CalculateTwoRows(height, gap, font);
                if (gap >= 0)
                {
                    assert(r.upper_bottom >= 0 && r.lower_top <= height);
                    assert(r.upper_bottom <= r.lower_top);
                    if (height >= 2 * font)
                        assert(r.upper_bottom >= font && height - r.lower_top >= font);
                }
                else
                {
                    assert(r.upper_bottom == (height - gap) / 2);
                    assert(r.lower_top == (height + gap) / 2);
                }
                ++cases;
            }
    for (int count : { 0, 1, 2, 3, 4, 8 })
        for (int mask = 0; mask < (1 << count); ++mask)
            for (int dpi : { 96, 120, 144, 192 })
                for (int height : { 20, 32, 40, 48, 60, 80, 120 })
                    for (int font : { 0, 9, 13, 16, 24, 40 })
                        for (int margin : { -10, 0, 2, 10, 100 })
                        {
                            const auto scale = [dpi](int n) { return n * dpi / 96; };
                            std::vector<TaskbarLayout::Item> items;
                            for (int i = 0; i < count; ++i)
                                items.push_back({ 26 + i * 5, 19 + i * 2, bool(mask & (1 << i)) });
                            TaskbarLayout::Result r;
                            r.width = 123; r.height = 456;
                            const int available = height - scale(2);
                            const int text = (std::max)(1, font);
                            const bool ok = TaskbarLayout::CalculateThreeRows(items, available,
                                font, scale(16), scale(margin), scale(3), r);
                            assert(ok == (available >= 3 * text));
                            if (!ok)
                            {
                                assert(r.width == 123 && r.height == 456 && r.rectangles.empty());
                                ++cases; continue;
                            }
                            assert(r.height <= available && r.height >= 3 * text);
                            assert(r.rectangles.size() == items.size());
                            int last_left = -1, last_right = 0, last_bottom = 0, row = 0;
                            for (int i = 0; i < count; ++i)
                            {
                                const auto& rect = r.rectangles[i];
                                assert(rect.top >= 0 && rect.bottom <= r.height);
                                assert(rect.bottom - rect.top >= text);
                                assert(rect.stacked == items[i].exclusive);
                                if (rect.left != last_left)
                                {
                                    assert(rect.left == (i == 0 ? scale(3) : last_right + scale(3)));
                                    assert(rect.top == 0); row = 0;
                                }
                                else
                                {
                                    assert(!rect.stacked && !r.rectangles[i - 1].stacked);
                                    assert(rect.right == last_right && rect.top >= last_bottom);
                                    assert(++row < 3);
                                }
                                if (rect.stacked)
                                    assert(rect.bottom == r.height && rect.right - rect.left == items[i].stacked_width);
                                else
                                    assert(rect.right - rect.left >= items[i].total_width);
                                last_left = rect.left; last_right = rect.right; last_bottom = rect.bottom;
                            }
                            assert(r.width == (count == 0 ? scale(3) : last_right + scale(3)));
                            ++cases;
                        }
    TaskbarLayout::Result r;
    assert(TaskbarLayout::CalculateThreeRows({ {30,20,false}, {50,25,false},
        {80,40,true}, {60,30,false} }, 50, 13, 16, 2, 3, r));
    assert(r.width == 162 && r.height == 49);
    assert(r.rectangles[0].right == 53 && r.rectangles[1].top == 17);
    assert(r.rectangles[2].left == 56 && r.rectangles[2].bottom == 49);
    assert(r.rectangles[3].left == 99 && r.rectangles[3].bottom == 15);
    for (int width : {48, 80, 1920})
        for (int height : {48, 80, 1080})
            for (int window_width : {32, 100, 2200})
                for (int window_height : {32, 64, 1200})
                    for (int offset : {-10, 0, 8, 100})
                    {
                        auto p = OverlayLayout::Calculate(width, height, window_width, window_height, offset, offset);
                        if (width >= height)
                        {
                            assert(p.x == offset && p.y == (std::max)(0, (height - window_height) / 2));
                            auto other = OverlayLayout::Calculate(width, height, window_width, window_height, offset, 999);
                            assert(p.x == other.x && p.y == other.y);
                        }
                        else
                        {
                            assert(p.y == offset && p.x == (std::max)(0, (width - window_width) / 2));
                            auto other = OverlayLayout::Calculate(width, height, window_width, window_height, 999, offset);
                            assert(p.x == other.x && p.y == other.y);
                        }
                        ++cases;
                    }
    std::cout << "PASS " << cases << " layout cases and explicit column regression\n";
}
