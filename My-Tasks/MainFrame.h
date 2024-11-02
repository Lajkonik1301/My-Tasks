#pragma once
#include <wx/wx.h>
#include "UserManager.h"
#include "User.h"

class MainFrame : public wxFrame {
public:
	MainFrame(const wxString& title);
private:

	wxPanel* panel;
	wxStaticText* loginHeadlineText;
	wxStaticText* usernameText;
	wxStaticText* passwordText;
	wxTextCtrl* username;
	wxTextCtrl* password;
	wxButton* loginButton;
	wxButton* registerButton;

	UserManager* userManager;

	void ClearLoginPageInputs();
	void ClearPanel();

	void DrawLoginWindow();
	void OnLoginButtonClicked(wxCommandEvent& evt);
	void OnRegisterButtonClicked(wxCommandEvent& evt);
	void RegistrationStatusLog(RegistrationStatus status);

	void DrawMainWindow();
};