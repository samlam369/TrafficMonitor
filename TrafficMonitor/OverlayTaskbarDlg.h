#pragma once
#include "TaskBarDlg.h"

// Edge placement without reserving space in the shell's task-list container.
class COverlayTaskbarDlg : public CTaskBarDlg
{
public:
    static bool IsAvailable(const TaskBarSettingData& data, bool* horizontal = nullptr);
    static bool IsEnabled(const TaskBarSettingData& data);

private:
    void InitTaskbarWnd() override;
    void AdjustTaskbarWndPos(bool force_adjust) override;
    void ResetTaskbarPos() override;
    void CheckTaskbarOnTopOrBottom() override;
    HWND GetParentHwnd() override;
};
