#pragma once
#include <wx/wx.h>
#include <string>

class LoginWindow : public wxFrame {
public:
    LoginWindow();
private:
    wxTextCtrl* loginCtrl;
    wxTextCtrl* passCtrl;

    void OnLogin(wxCommandEvent& event);
    void OnRegister(wxCommandEvent& event);

    void ShowError(const wxString& message, const wxString& title);
    void ShowInfo(const wxString& message, const wxString& title);

    wxDECLARE_EVENT_TABLE();
};
