#pragma once
#include <vector>
struct TaskBarSettingData;
class CTaskbarHelper
{
public:
    // Resolve the actual target, including upstream's primary-display fallback.
    static HWND ResolveTaskbar(const TaskBarSettingData& data, bool& secondary);
    //获取所有副显示器上的任务栏，并确保按显示器的顺序
    static void GetAllSecondaryDisplayTaskbar(std::vector<HWND>& secondary_taskbars);

    //获取显示器数量
    static int GetDisplayNum();

    //获取副显示器任务栏的数量
    static int GetSecondaryTaskbarNum();
};

