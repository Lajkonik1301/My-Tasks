#pragma once
#include "wx/wx.h"
#include "UserManager.h"

class LoginPage : public wxPanel {
public:
	LoginPage(wxWindow* parent, UserManager* userManager);
private:
	void OnLoginButtonClicked(wxCommandEvent& evt);
	void OnRegisterButtonClicked(wxCommandEvent& evt);
	void RegistrationStatusLog(RegistrationStatus status);

	wxBoxSizer* mainLoginPageSizer;
	wxBoxSizer* loginSizer;
	wxBoxSizer* passwordSizer;
	wxGridSizer* outerSizer;

	wxStaticText* loginHeadlineText;
	wxStaticText* usernameText;
	wxStaticText* passwordText;
	wxTextCtrl* username;
	wxTextCtrl* password;
	wxButton* loginButton;
	wxButton* registerButton;

	UserManager* userManager;
};

