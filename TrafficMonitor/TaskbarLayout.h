#pragma once

#include <algorithm>
#include <vector>
#include <utility>

// Pixel geometry shared by the taskbar window and standalone tests.
namespace TaskbarLayout
{
struct TwoRows
{
    int upper_bottom;
    int lower_top;
};

inline TwoRows CalculateTwoRows(int height, int requested_gap, int text_height)
{
    // A positive gap must not consume space needed by the measured font.
    // Oversized fonts still cannot fit the fixed upstream window height.
    const int maximum_gap = (std::max)(0, height - 2 * (std::max)(0, text_height));
    const int gap = (std::min)(requested_gap, maximum_gap);
    return { (height - gap) / 2, (height + gap) / 2 };
}

struct Item
{
    int total_width;
    int stacked_width;
    bool exclusive;
};
struct Rect
{
    int left, top, right, bottom;
    bool stacked;
};
struct Result
{
    int width = 0;
    int height = 0;
    std::vector<Rect> rectangles;
};

inline bool CalculateThreeRows(const std::vector<Item>& items, int available_height,
    int text_height, int preferred_row_height, int requested_gap, int item_space,
    Result& result)
{
    constexpr int rows = 3;
    text_height = (std::max)(1, text_height);
    if (available_height < rows * text_height)
        return false; // Leave the caller's state intact for the two-row fallback.

    const int gap = (std::min)((std::max)(0, requested_gap),
        (available_height - rows * text_height) / (rows - 1));
    const int row_height = (std::min)((std::max)(preferred_row_height, text_height),
        (available_height - (rows - 1) * gap) / rows);
    Result layout;
    layout.height = rows * row_height + (rows - 1) * gap;
    layout.rectangles.resize(items.size());
    int x = item_space;
    std::size_t index = 0;
    while (index < items.size())
    {
        const auto& item = items[index];
        if (item.exclusive)
        {
            layout.rectangles[index++] = { x, 0, x + item.stacked_width, layout.height, true };
            x += item.stacked_width + item_space;
            continue;
        }
        const std::size_t first = index;
        int width = 0;
        while (index < items.size() && index - first < rows && !items[index].exclusive)
            width = (std::max)(width, items[index++].total_width);
        for (std::size_t i = first; i < index; ++i)
        {
            const int top = static_cast<int>(i - first) * (row_height + gap);
            layout.rectangles[i] = { x, top, x + width, top + row_height, false };
        }
        // Incomplete columns keep empty row slots, including a singleton.
        x += width + item_space;
    }
    layout.width = x;
    result = std::move(layout);
    return true;
}
}
