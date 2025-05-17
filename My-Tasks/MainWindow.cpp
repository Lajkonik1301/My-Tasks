#include "MainWindow.h"
#include "LoginWindow.h"
#include "DatabaseManager.h"

enum {
    ID_ADD = 101,
    ID_DELETE,
    ID_MARK_DONE,
    ID_LOGOUT
};

wxBEGIN_EVENT_TABLE(MainWindow, wxFrame)
EVT_BUTTON(ID_ADD, MainWindow::OnAdd)
EVT_BUTTON(ID_DELETE, MainWindow::OnDelete)
EVT_BUTTON(ID_MARK_DONE, MainWindow::OnMarkDone)
EVT_BUTTON(ID_LOGOUT, MainWindow::OnLogout)
wxEND_EVENT_TABLE()

MainWindow::MainWindow(const std::string& user)
    : wxFrame(nullptr, wxID_ANY, "My Tasks", wxDefaultPosition, wxSize(500, 400)), currentUser(user) {
    wxPanel* panel = new wxPanel(this);

    wxBoxSizer* mainSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* leftSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* rightSizer = new wxBoxSizer(wxVERTICAL);

    nameCtrl = new wxTextCtrl(panel, wxID_ANY, "Nazwa");
    descCtrl = new wxTextCtrl(panel, wxID_ANY, "Opis");
    taskList = new wxListBox(panel, wxID_ANY);

    leftSizer->Add(nameCtrl, 0, wxALL | wxEXPAND, 5);
    leftSizer->Add(descCtrl, 0, wxALL | wxEXPAND, 5);
    leftSizer->Add(new wxButton(panel, ID_ADD, "Dodaj"), 0, wxALL | wxEXPAND, 5);
    leftSizer->Add(new wxButton(panel, ID_MARK_DONE, "Oznacz jako wykonane"), 0, wxALL | wxEXPAND, 5);
    leftSizer->Add(new wxButton(panel, ID_DELETE, "Usuń"), 0, wxALL | wxEXPAND, 5);
    leftSizer->Add(new wxButton(panel, ID_LOGOUT, "Wyloguj się"), 0, wxALL | wxEXPAND, 5);

    rightSizer->Add(new wxStaticText(panel, wxID_ANY, "Zadania:"), 0, wxALL, 5);
    rightSizer->Add(taskList, 1, wxALL | wxEXPAND, 5);

    mainSizer->Add(leftSizer, 0, wxALL | wxEXPAND, 5);
    mainSizer->Add(rightSizer, 1, wxALL | wxEXPAND, 5);

    panel->SetSizer(mainSizer);

    RefreshTasks();
    Centre();
}

void MainWindow::RefreshTasks() {
    taskList->Clear();
    auto tasks = DatabaseManager::GetInstance().GetTasks(currentUser);
    for (const auto& task : tasks) {
        wxString item = wxString::Format("[%s] %s - %s",
            task.isDone() ? "OK" : " ", task.getName(), task.getDescription());
        taskList->Append(item);
    }
}

void MainWindow::OnAdd(wxCommandEvent&) {
    std::string name = nameCtrl->GetValue().ToStdString();
    std::string desc = descCtrl->GetValue().ToStdString();
    DatabaseManager::GetInstance().AddTask(currentUser, name, desc);
    RefreshTasks();
}

void MainWindow::OnDelete(wxCommandEvent&) {
    int sel = taskList->GetSelection();
    if (sel != wxNOT_FOUND) {
        DatabaseManager::GetInstance().DeleteTask(currentUser, sel);
        RefreshTasks();
    }
}

void MainWindow::OnMarkDone(wxCommandEvent&) {
    int sel = taskList->GetSelection();
    if (sel != wxNOT_FOUND) {
        DatabaseManager::GetInstance().MarkTaskDone(currentUser, sel);
        RefreshTasks();
    }
}

void MainWindow::OnLogout(wxCommandEvent&) {
    Close();
    LoginWindow* login = new LoginWindow();
    login->Show();
}
