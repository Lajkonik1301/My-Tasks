#pragma once
#include <wx/wx.h>
#include "UserManager.h"
#include "User.h"

class MainFrame : public wxFrame {
public:
	MainFrame(const wxString& title);
private:
	void ClearPanel();

	void DrawLoginPage();
	void OnLoginButtonClicked(wxCommandEvent& evt);
	void OnRegisterButtonClicked(wxCommandEvent& evt);
	void RegistrationStatusLog(RegistrationStatus status);

	void DrawMainPage();

	wxPanel* panel;
	wxStaticText* loginHeadlineText;
	wxStaticText* usernameText;
	wxStaticText* passwordText;
	wxTextCtrl* username;
	wxTextCtrl* password;
	wxButton* loginButton;
	wxButton* registerButton;

	UserManager* userManager;
};