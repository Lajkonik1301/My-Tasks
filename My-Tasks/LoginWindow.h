#pragma once
#include <wx/wx.h>
#include "MainFrame.h"
#include "DatabaseManager.h"
#include "User.h"

class MainFrame;

class LoginWindow : public wxPanel {
public:
	LoginWindow(MainFrame* mainFrame, DatabaseManager* databaseManager);
private:
	MainFrame* mainFrame;
	DatabaseManager* databaseManager;

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

	void OnLoginButtonClicked(wxCommandEvent& evt);
	void OnRegisterButtonClicked(wxCommandEvent& evt);
	void RegistrationStatusLog(RegistrationStatus status);
};

