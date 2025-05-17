#include "ManageUserWindow.h"
#include "DatabaseManager.h"
#include "LoginWindow.h"
#include "MainWindow.h"

ManageUserWindow::ManageUserWindow(MainWindow* parent, const std::string& currentLogin)
    : wxFrame(nullptr, wxID_ANY, "Zarządzanie kontem", wxDefaultPosition, wxSize(360, 360)),
    parentWindow(parent), originalLogin(currentLogin)
{
    CreateLayout();
}

void ManageUserWindow::CreateLayout() {
    wxPanel* panel = new wxPanel(this);
    wxBoxSizer* outerSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* formSizer = new wxBoxSizer(wxVERTICAL);

    newLoginCtrl = new wxTextCtrl(panel, wxID_ANY, originalLogin, wxDefaultPosition, wxSize(240, -1));
    oldPassCtrl = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(240, -1), wxTE_PASSWORD);
    newPassCtrl = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(240, -1), wxTE_PASSWORD);
    confirmPassCtrl = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(240, -1), wxTE_PASSWORD);
    wxButton* submitBtn = new wxButton(panel, wxID_ANY, "Zapisz zmiany");
    wxButton* deleteBtn = new wxButton(panel, wxID_ANY, "Usuń konto");

    formSizer->AddSpacer(10);
    formSizer->Add(new wxStaticText(panel, wxID_ANY, "Nowa nazwa użytkownika"), 0, wxBOTTOM, 4);
    formSizer->Add(newLoginCtrl, 0, wxBOTTOM, 8);
    formSizer->Add(new wxStaticText(panel, wxID_ANY, "Stare hasło"), 0, wxBOTTOM, 4);
    formSizer->Add(oldPassCtrl, 0, wxBOTTOM, 8);
    formSizer->Add(new wxStaticText(panel, wxID_ANY, "Nowe hasło"), 0, wxBOTTOM, 4);
    formSizer->Add(newPassCtrl, 0, wxBOTTOM, 8);
    formSizer->Add(new wxStaticText(panel, wxID_ANY, "Powtórz nowe hasło"), 0, wxBOTTOM, 4);
    formSizer->Add(confirmPassCtrl, 0, wxBOTTOM, 12);

    wxBoxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    buttonSizer->Add(submitBtn, 0, wxRIGHT, 10);
    buttonSizer->Add(deleteBtn);
    formSizer->Add(buttonSizer, 0, wxALIGN_CENTER);

    outerSizer->Add(formSizer, 0, wxALIGN_CENTER | wxALL, 15);
    panel->SetSizer(outerSizer);

    submitBtn->Bind(wxEVT_BUTTON, &ManageUserWindow::OnSubmit, this);
    deleteBtn->Bind(wxEVT_BUTTON, &ManageUserWindow::OnDeleteAccount, this);
}

void ManageUserWindow::OnSubmit(wxCommandEvent&) {
    std::string newLogin = newLoginCtrl->GetValue().ToStdString();
    std::string oldPass = oldPassCtrl->GetValue().ToStdString();
    std::string newPass = newPassCtrl->GetValue().ToStdString();
    std::string confirmPass = confirmPassCtrl->GetValue().ToStdString();

    if (newLogin.empty() || oldPass.empty() || newPass.empty() || confirmPass.empty()) {
        wxMessageBox("Wszystkie pola muszą być wypełnione.", "Błąd", wxOK | wxICON_ERROR);
        return;
    }

    if (newPass != confirmPass) {
        wxMessageBox("Nowe hasła nie są takie same.", "Błąd", wxOK | wxICON_ERROR);
        return;
    }

    auto& db = DatabaseManager::GetInstance();
    if (!db.ValidateUser(originalLogin, oldPass)) {
        wxMessageBox("Stare hasło jest nieprawidłowe.", "Błąd", wxOK | wxICON_ERROR);
        return;
    }

    if (newLogin != originalLogin && !db.ValidateUser(newLogin, newPass)) {
        if (!db.RegisterUser(newLogin, newPass)) {
            wxMessageBox("Taka nazwa użytkownika już istnieje.", "Błąd", wxOK | wxICON_ERROR);
            return;
        }
        db.DeleteUser(originalLogin);
    }
    else {
        db.UpdatePassword(originalLogin, newPass);
    }

    wxMessageBox("Dane użytkownika zostały zaktualizowane.", "Sukces", wxOK | wxICON_INFORMATION);
    Close();
}

void ManageUserWindow::OnDeleteAccount(wxCommandEvent&) {
    int confirm = wxMessageBox(
        "Czy na pewno chcesz usunąć konto? Tej operacji nie można cofnąć.",
        "Potwierdź", wxYES_NO | wxICON_WARNING
    );

    if (confirm == wxYES) {
        if (DatabaseManager::GetInstance().DeleteUser(originalLogin)) {
            wxMessageBox("Konto zostało usunięte.", "Sukces", wxOK | wxICON_INFORMATION);
            Close();
            parentWindow->Close();
            LoginWindow* login = new LoginWindow();
            login->Show();
        }
        else {
            wxMessageBox("Wystąpił problem przy usuwaniu konta.", "Błąd", wxOK | wxICON_ERROR);
        }
    }
}
