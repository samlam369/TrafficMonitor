#include "stdafx.h"
#include "OverlayTaskbarDlg.h"
#include "OverlayLayout.h"
#include "TaskbarHelper.h"

bool COverlayTaskbarDlg::IsAvailable(const TaskBarSettingData& data, bool* horizontal)
{
    bool secondary = false;
    HWND taskbar = CTaskbarHelper::ResolveTaskbar(data, secondary);
    RECT rect{};
    if (theApp.m_win_version.IsWine() || secondary || taskbar == nullptr
        || ::FindWindowEx(taskbar, nullptr, L"Start", nullptr) == nullptr
        || !::GetWindowRect(taskbar, &rect))
        return false;
    if (horizontal != nullptr)
        *horizontal = rect.right - rect.left >= rect.bottom - rect.top;
    return true;
}

bool COverlayTaskbarDlg::IsEnabled(const TaskBarSettingData& data)
{
    return data.taskbar_left_overlay && data.tbar_wnd_on_left && IsAvailable(data);
}

void COverlayTaskbarDlg::InitTaskbarWnd()
{
    // The outer taskbar is the only parent; no ReBar or task-list mutation.
}

void COverlayTaskbarDlg::AdjustTaskbarWndPos(bool force_adjust)
{
    const auto pos = OverlayLayout::Calculate(m_rcTaskbar.Width(), m_rcTaskbar.Height(),
        m_window_width, m_window_height, DPI(theApp.m_taskbar_data.window_offset_left),
        DPI(theApp.m_taskbar_data.window_offset_top));
    CRect next(pos.x, pos.y, pos.x + m_window_width, pos.y + m_window_height);
    if (force_adjust || next != m_rect)
    {
        m_rect = next;
        MoveWindow(m_rect);
    }
}

void COverlayTaskbarDlg::ResetTaskbarPos()
{
    // Overlay never changes shell geometry, so there is nothing to restore.
}

void COverlayTaskbarDlg::CheckTaskbarOnTopOrBottom()
{
    m_taskbar_on_top_or_bottom = m_rcTaskbar.Width() >= m_rcTaskbar.Height();
}

HWND COverlayTaskbarDlg::GetParentHwnd()
{
    return m_hTaskbar;
}
