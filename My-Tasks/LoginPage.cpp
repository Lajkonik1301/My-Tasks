#include "LoginPage.h"

LoginPage::LoginPage(wxWindow* parent, UserManager* userManager) : wxPanel(parent), userManager(userManager) {

	//drawing controls
	loginHeadlineText = new wxStaticText(this, wxID_ANY, "My Tasks", wxDefaultPosition, wxDefaultSize);
	loginHeadlineText->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));

	usernameText = new wxStaticText(this, wxID_ANY, "Login: ");
	username = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxSize(150, -1));

	passwordText = new wxStaticText(this, wxID_ANY, "Has³o: ");
	password = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxSize(150, -1), wxTE_PASSWORD);

	loginButton = new wxButton(this, wxID_ANY, "Zaloguj siê", wxDefaultPosition, wxSize(150, -1));
	registerButton = new wxButton(this, wxID_ANY, "Zarejestruj siê", wxDefaultPosition, wxSize(150, -1));

	username->SetFocus();
	//drawing controls


	//setting up layout
	//sizers
	mainLoginPageSizer = new wxBoxSizer(wxVERTICAL);
	loginSizer = new wxBoxSizer(wxVERTICAL);
	passwordSizer = new wxBoxSizer(wxVERTICAL);
	outerSizer = new wxGridSizer(1);


	//headline
	mainLoginPageSizer->Add(loginHeadlineText, wxSizerFlags().CenterHorizontal());
	mainLoginPageSizer->AddSpacer(15);


	//login
	loginSizer->Add(usernameText);
	loginSizer->Add(username, wxSizerFlags().CenterHorizontal());
	mainLoginPageSizer->Add(loginSizer, wxSizerFlags().CenterHorizontal());

	mainLoginPageSizer->AddSpacer(15);


	//password
	passwordSizer->Add(passwordText);
	passwordSizer->Add(password, wxSizerFlags().CenterHorizontal());
	mainLoginPageSizer->Add(passwordSizer, wxSizerFlags().CenterHorizontal());

	mainLoginPageSizer->AddSpacer(15);


	//buttons
	mainLoginPageSizer->Add(loginButton, wxSizerFlags().CenterHorizontal());
	mainLoginPageSizer->AddSpacer(5);
	mainLoginPageSizer->Add(registerButton, wxSizerFlags().CenterHorizontal());

	outerSizer->Add(mainLoginPageSizer, wxSizerFlags().Border(wxALL, 35).Expand());
	this->SetSizer(outerSizer);
	outerSizer->SetSizeHints(this);
	//setting up layout


	//binding buttons
	loginButton->Bind(wxEVT_BUTTON, &LoginPage::OnLoginButtonClicked, this);
	registerButton->Bind(wxEVT_BUTTON, &LoginPage::OnRegisterButtonClicked, this);
	//binding buttons
}

void LoginPage::OnLoginButtonClicked(wxCommandEvent& evt) {
	wxString usrName = username->GetValue();
	wxString pwd = password->GetValue();

	User* user = userManager->loginUser(usrName.ToStdString(), pwd.ToStdString());
	if (user == nullptr) {
		wxMessageBox("B³êdna nazwa u¿ytkownika lub has³o.", "B³¹d logowania", wxOK | wxICON_ERROR);
		password->Clear();
		return;
	}

	wxMessageBox("Zalogowano pomyœlnie!", "Sukces", wxOK | wxICON_INFORMATION);

	//TODO: logged-in user

	delete user;
}

void LoginPage::OnRegisterButtonClicked(wxCommandEvent& evt) {
	wxString usrName = username->GetValue();
	wxString pwd = password->GetValue();

	RegistrationStatus status = userManager->registerUser(usrName.ToStdString(), pwd.ToStdString());
	RegistrationStatusLog(status);
}

void LoginPage::RegistrationStatusLog(RegistrationStatus status) {
	switch (status)
	{
	case RegistrationStatus::Success:
		wxMessageBox("Zarejestrowano!", "Udana rejestracja", wxOK | wxICON_INFORMATION);
		break;
	case RegistrationStatus::UsernameAlreadyExists:
		wxMessageBox("U¿ytkownik o podanym loginie istnieje!", "B³¹d rejestracji", wxOK | wxICON_ERROR);
		break;
	case RegistrationStatus::EmptyUsernameOrPassword:
		wxMessageBox("Login lub ha³o nie mo¿e byæ puste!", "B³¹d rejestracji", wxOK | wxICON_ERROR);
		break;
	case RegistrationStatus::DatabaseError:
		wxMessageBox("B³¹d bazy danych!", "B³¹d rejestracji", wxOK | wxICON_ERROR);
		break;
	default:
		break;
	}
}