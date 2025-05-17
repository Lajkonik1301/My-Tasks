#pragma once
#include <wx/wx.h>
#include <string>

class MainWindow : public wxFrame {
public:
    MainWindow(const std::string& user);

private:
    std::string currentUser;

    wxListBox* taskList;
    wxTextCtrl* nameCtrl;
    wxTextCtrl* descCtrl;

    void RefreshTasks();
    void OnAdd(wxCommandEvent& event);
    void OnDelete(wxCommandEvent& event);
    void OnMarkDone(wxCommandEvent& event);
    void OnLogout(wxCommandEvent& event);

    wxDECLARE_EVENT_TABLE();
};
