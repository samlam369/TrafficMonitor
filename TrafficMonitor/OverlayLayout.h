#pragma once

// Taskbar-local physical pixels. The caller scales the saved logical offsets.
namespace OverlayLayout
{
    struct Position { int x; int y; };

    inline Position Calculate(int taskbar_width, int taskbar_height,
        int window_width, int window_height, int horizontal_offset, int vertical_offset)
    {
        if (taskbar_width >= taskbar_height)
            return { horizontal_offset, taskbar_height > window_height ? (taskbar_height - window_height) / 2 : 0 };
        return { taskbar_width > window_width ? (taskbar_width - window_width) / 2 : 0, vertical_offset };
    }
}
