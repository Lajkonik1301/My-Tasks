#include "LoginWindow.h"

LoginWindow::LoginWindow(MainFrame* mainFrame){
	this->mainFrame = mainFrame;

	userManager = new UserManager();

	wxFont headlianeFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));

	//place items
	panel = new wxPanel(mainFrame);

	loginHeadlineText = new wxStaticText(panel, wxID_ANY, "My Tasks");
	loginHeadlineText->SetFont(headlianeFont);

	usernameText = new wxStaticText(panel, wxID_ANY, "Login:");
	username = new wxTextCtrl(panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(150, -1));

	passwordText = new wxStaticText(panel, wxID_ANY, "Has³o:");
	password = new wxTextCtrl(panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(150, -1), wxTE_PASSWORD);

	loginButton = new wxButton(panel, wxID_ANY, "Zaloguj siê", wxDefaultPosition, wxSize(150, -1));
	registerButton = new wxButton(panel, wxID_ANY, "Zarejestruj siê", wxDefaultPosition, wxSize(150, -1));

	username->SetFocus();
	//place items


	//setup sizers
	mainSizer = new wxBoxSizer(wxVERTICAL);
	mainSizer->Add(loginHeadlineText, wxSizerFlags().CenterHorizontal());

	mainSizer->AddSpacer(15);

	usernameSizer = new wxBoxSizer(wxVERTICAL);
	usernameSizer->Add(usernameText, wxSizerFlags().Align(wxALIGN_LEFT));
	usernameSizer->AddSpacer(4);
	usernameSizer->Add(username, wxSizerFlags().CenterHorizontal());
	mainSizer->Add(usernameSizer, wxSizerFlags().CenterHorizontal());

	mainSizer->AddSpacer(15);

	passwordSizer = new wxBoxSizer(wxVERTICAL);
	passwordSizer->Add(passwordText, wxSizerFlags().Align(wxALIGN_LEFT));
	passwordSizer->AddSpacer(4);
	passwordSizer->Add(password, wxSizerFlags().CenterHorizontal());
	mainSizer->Add(passwordSizer, wxSizerFlags().CenterHorizontal());

	mainSizer->AddSpacer(15);

	mainSizer->Add(loginButton, wxSizerFlags().CenterHorizontal());
	mainSizer->AddSpacer(5);
	mainSizer->Add(registerButton, wxSizerFlags().CenterHorizontal());

	outerSizer = new wxGridSizer(1);
	outerSizer->Add(mainSizer, wxSizerFlags().Border(wxALL, 25).Expand());

	panel->SetSizer(outerSizer);
	outerSizer->SetSizeHints(mainFrame);
	//setup sizers

	//binding buttons
	loginButton->Bind(wxEVT_BUTTON, &LoginWindow::OnLoginButtonClicked, this);
	registerButton->Bind(wxEVT_BUTTON, &LoginWindow::OnRegisterButtonClicked, this);
	//binding buttons

	//window min-size setup
	wxSize size = mainFrame->GetSize();
	int minWidth = size.GetWidth() + size.GetWidth() * 0.25;
	int minHeight = size.GetHeight() + size.GetHeight() * 0.25;

	mainFrame->SetMinSize(wxSize(minWidth, minHeight));
}

void LoginWindow::ClearLoginPageInputs(){
	username->Clear();
	password->Clear();
}

void LoginWindow::OnLoginButtonClicked(wxCommandEvent& evt){
	wxString usrName = username->GetValue();
	wxString pwd = password->GetValue();

	User* user = userManager->loginUser(usrName.ToStdString(), pwd.ToStdString());
	if (user == nullptr) {
		wxMessageBox("B³êdna nazwa u¿ytkownika lub has³o.", "B³¹d logowania", wxOK | wxICON_ERROR);
		ClearLoginPageInputs();
		return;
	}

	wxMessageBox("Zalogowano pomyœlnie!", "Sukces", wxOK | wxICON_INFORMATION);

	mainFrame->SetLoggedInUser(user->getId(), user->getUsername());

	//TODO: logged-in user

	delete user;
}

void LoginWindow::OnRegisterButtonClicked(wxCommandEvent& evt){
	wxString usrName = username->GetValue();
	wxString pwd = password->GetValue();

	RegistrationStatus status = userManager->registerUser(usrName.ToStdString(), pwd.ToStdString());

	RegistrationStatusLog(status);
}

void LoginWindow::RegistrationStatusLog(RegistrationStatus status){
	switch (status)
	{
	case RegistrationStatus::Success:
		wxMessageBox("Zarejestrowano!", "Udana rejestracja", wxOK | wxICON_INFORMATION);
		break;
	case RegistrationStatus::UsernameAlreadyExists:
		wxMessageBox("U¿ytkownik o podanym loginie istnieje!", "B³¹d rejestracji", wxOK | wxICON_ERROR);
		ClearLoginPageInputs();
		break;
	case RegistrationStatus::EmptyUsernameOrPassword:
		wxMessageBox("Login lub ha³o nie mo¿e byæ puste!", "B³¹d rejestracji", wxOK | wxICON_ERROR);
		ClearLoginPageInputs();
		break;
	case RegistrationStatus::DatabaseError:
		wxMessageBox("B³¹d bazy danych!", "B³¹d rejestracji", wxOK | wxICON_ERROR);
		ClearLoginPageInputs();
		break;
	default:
		break;
	}
}