#include "MainFrame.h"

MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title) {

    userManager = new UserManager();
	DrawLoginPage();
}

void MainFrame::ClearPanel() {
    panel->DestroyChildren();
}

void MainFrame::DrawLoginPage(){
	wxFont headlineFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));

	//place items
	panel = new wxPanel(this);

	loginHeadlineText = new wxStaticText(panel, wxID_ANY, "My Tasks");
	loginHeadlineText->SetFont(headlineFont);

	usernameText = new wxStaticText(panel, wxID_ANY, "Login: ");
	username = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(150, -1));

	passwordText = new wxStaticText(panel, wxID_ANY, "Has³o: ");
	password = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(150, -1), wxTE_PASSWORD);

	loginButton = new wxButton(panel, wxID_ANY, "Zaloguj siê", wxDefaultPosition, wxSize(150, -1));
	registerButton = new wxButton(panel, wxID_ANY, "Zarejestruj siê", wxDefaultPosition, wxSize(150, -1));

	username->SetFocus();
	//place items


	//setup sizers

	wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
	mainSizer->Add(loginHeadlineText, wxSizerFlags().CenterHorizontal());

	mainSizer->AddSpacer(15);

	wxBoxSizer* usernameSizer = new wxBoxSizer(wxHORIZONTAL);
	usernameSizer->Add(usernameText, wxSizerFlags().CenterVertical());;
	usernameSizer->Add(username, wxSizerFlags().CenterHorizontal());
	mainSizer->Add(usernameSizer, wxSizerFlags().CenterHorizontal());

	mainSizer->AddSpacer(15);

	wxBoxSizer* passwordSizer = new wxBoxSizer(wxHORIZONTAL);
	passwordSizer->Add(passwordText, wxSizerFlags().CenterVertical());;
	passwordSizer->Add(password, wxSizerFlags().CenterHorizontal());
	mainSizer->Add(passwordSizer, wxSizerFlags().CenterHorizontal());

	mainSizer->AddSpacer(15);

	mainSizer->Add(loginButton, wxSizerFlags().CenterHorizontal());
	mainSizer->AddSpacer(5);
	mainSizer->Add(registerButton, wxSizerFlags().CenterHorizontal());

	wxGridSizer* outerSizer = new wxGridSizer(1);
	outerSizer->Add(mainSizer, wxSizerFlags().Border(wxALL, 25).Expand());

	panel->SetSizer(outerSizer);
	outerSizer->SetSizeHints(this);
	//setup sizers

	//binding buttons
	loginButton->Bind(wxEVT_BUTTON, &MainFrame::OnLoginButtonClicked, this);
	registerButton->Bind(wxEVT_BUTTON, &MainFrame::OnRegisterButtonClicked, this);
	//binding buttons

}

void MainFrame::OnLoginButtonClicked(wxCommandEvent& evt){
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

void MainFrame::OnRegisterButtonClicked(wxCommandEvent& evt){
	wxString usrName = username->GetValue();
	wxString pwd = password->GetValue();

	RegistrationStatus status = userManager->registerUser(usrName.ToStdString(), pwd.ToStdString());
	RegistrationStatusLog(status);
}

void MainFrame::RegistrationStatusLog(RegistrationStatus status){
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