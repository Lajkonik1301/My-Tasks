#pragma once
#include<wx/wx.h>
#include "MainFrame.h"
#include "UserManager.h"
#include "User.h"

class MainFrame;

class LoginPage : public wxPanel {
public:
	LoginPage(MainFrame* mainFrame);
private:
	MainFrame* mainFrame;
	UserManager* userManager;

	wxPanel* panel;
	wxStaticText* loginHeadlineText;
	wxStaticText* usernameText;
	wxStaticText* passwordText;
	wxTextCtrl* username;
	wxTextCtrl* password;
	wxButton* loginButton;
	wxButton* registerButton;

	wxBoxSizer* mainSizer;
	wxBoxSizer* usernameSizer;
	wxBoxSizer* passwordSizer;
	wxGridSizer* outerSizer;

	void ClearLoginPageInputs();
	void ClearPanel();

	void OnLoginButtonClicked(wxCommandEvent& evt);
	void OnRegisterButtonClicked(wxCommandEvent& evt);
	void RegistrationStatusLog(RegistrationStatus status);
};

