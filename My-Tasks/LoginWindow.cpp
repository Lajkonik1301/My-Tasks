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

LoginWindow::LoginWindow()
    : wxFrame(nullptr, wxID_ANY, "My Tasks", wxDefaultPosition, wxSize(300, 300)) {
    wxPanel* panel = new wxPanel(this);

    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(new wxStaticText(panel, wxID_ANY, "Login:"), 0, wxALL, 5);
    loginCtrl = new wxTextCtrl(panel, wxID_ANY);
    sizer->Add(loginCtrl, 0, wxALL | wxEXPAND, 5);
    sizer->Add(new wxStaticText(panel, wxID_ANY, "Hasło:"), 0, wxALL, 5);
    passCtrl = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_PASSWORD);
    sizer->Add(passCtrl, 0, wxALL | wxEXPAND, 5);

    sizer->Add(new wxButton(panel, ID_LOGIN, "Zaloguj się"), 0, wxALL | wxEXPAND, 5);
    sizer->Add(new wxButton(panel, ID_REGISTER, "Zarejestruj się"), 0, wxALL | wxEXPAND, 5);

    panel->SetSizer(sizer);
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
