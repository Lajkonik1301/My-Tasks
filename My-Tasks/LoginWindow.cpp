#include "LoginWindow.h"
#include "MainWindow.h"
#include "DatabaseManager.h"

enum {
    ID_LOGIN = 1,
    ID_REGISTER
};

wxBEGIN_EVENT_TABLE(LoginWindow, wxFrame)
EVT_BUTTON(ID_LOGIN, LoginWindow::OnLogin)
EVT_BUTTON(ID_REGISTER, LoginWindow::OnRegister)
wxEND_EVENT_TABLE()

LoginWindow::LoginWindow() : wxFrame(nullptr, wxID_ANY, "My Tasks", wxDefaultPosition, wxSize(280, 340)) {

    wxFont headlineFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);

    wxPanel* panel = new wxPanel(this);

    wxStaticText* headlineText = new wxStaticText(panel, wxID_ANY, "My Tasks");
    headlineText->SetFont(headlineFont);

    wxStaticText* usernameLabel = new wxStaticText(panel, wxID_ANY, "Login:");
    wxTextCtrl* usernameCtrl = new wxTextCtrl(panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(150, -1));

    wxStaticText* passwordLabel = new wxStaticText(panel, wxID_ANY, "Hasło:");
    wxTextCtrl* passwordCtrl = new wxTextCtrl(panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(150, -1), wxTE_PASSWORD);

    wxButton* loginBtn = new wxButton(panel, ID_LOGIN, "Zaloguj się", wxDefaultPosition, wxSize(150, -1));
    wxButton* registerBtn = new wxButton(panel, ID_REGISTER, "Zarejestruj się", wxDefaultPosition, wxSize(150, -1));

    usernameCtrl->SetFocus();

    // Układ
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    mainSizer->Add(headlineText, wxSizerFlags().CenterHorizontal());
    mainSizer->AddSpacer(15);

    wxBoxSizer* usernameSizer = new wxBoxSizer(wxVERTICAL);
    usernameSizer->Add(usernameLabel, wxSizerFlags().Align(wxALIGN_LEFT));
    usernameSizer->AddSpacer(4);
    usernameSizer->Add(usernameCtrl, wxSizerFlags().CenterHorizontal());
    mainSizer->Add(usernameSizer, wxSizerFlags().CenterHorizontal());
    mainSizer->AddSpacer(15);

    wxBoxSizer* passwordSizer = new wxBoxSizer(wxVERTICAL);
    passwordSizer->Add(passwordLabel, wxSizerFlags().Align(wxALIGN_LEFT));
    passwordSizer->AddSpacer(4);
    passwordSizer->Add(passwordCtrl, wxSizerFlags().CenterHorizontal());
    mainSizer->Add(passwordSizer, wxSizerFlags().CenterHorizontal());
    mainSizer->AddSpacer(15);

    mainSizer->Add(loginBtn, wxSizerFlags().CenterHorizontal());
    mainSizer->AddSpacer(5);
    mainSizer->Add(registerBtn, wxSizerFlags().CenterHorizontal());

    wxGridSizer* outerSizer = new wxGridSizer(1);
    outerSizer->Add(mainSizer, wxSizerFlags().Border(wxALL, 25).Expand());

    panel->SetSizer(outerSizer);
    Centre();
}

void LoginWindow::ShowError(const wxString& message, const wxString& title) {
    wxMessageBox(message, title, wxICON_ERROR);
}

void LoginWindow::ShowInfo(const wxString& message, const wxString& title) {
    wxMessageBox(message, title, wxICON_INFORMATION);
}

void LoginWindow::OnLogin(wxCommandEvent&) {
    std::string login = loginCtrl->GetValue().ToStdString();
    std::string pass = passCtrl->GetValue().ToStdString();

    if (DatabaseManager::GetInstance().ValidateUser(login, pass)) {
        MainWindow* main = new MainWindow(login);
        main->Show();
        Close();
    }
    else {
        ShowError("Błędna nazwa użytkownika lub hasło.", "Błąd logowania");
    }
}

void LoginWindow::OnRegister(wxCommandEvent&) {
    std::string login = loginCtrl->GetValue().ToStdString();
    std::string pass = passCtrl->GetValue().ToStdString();

    if (login.empty() || pass.empty()) {
        ShowError("Login lub hasło nie może być puste!", "Błąd rejestracji");
        return;
    }

    if (DatabaseManager::GetInstance().RegisterUser(login, pass)) {
        ShowInfo("Zarejestrowano!", "Udana rejestracja");
    }
    else {
        ShowError("Użytkownik o podanym loginie istnieje!", "Błąd rejestracji");
    }
}
