#pragma once
#include <wx/wx.h>
#include <string>

class MainWindow;

class ManageUserWindow : public wxFrame {
public:
    ManageUserWindow(MainWindow* parent, const std::string& currentLogin);

private:
    MainWindow* parentWindow;
    std::string originalLogin;

    wxTextCtrl* newLoginCtrl;
    wxTextCtrl* oldPassCtrl;
    wxTextCtrl* newPassCtrl;
    wxTextCtrl* confirmPassCtrl;

    void OnSubmit(wxCommandEvent& event);
    void OnDeleteAccount(wxCommandEvent& event);
    void CreateLayout();
};
