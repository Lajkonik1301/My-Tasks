﻿#include "MainWindow.h"
#include "LoginWindow.h"
#include "AddTaskWindow.h"
#include "ManageUserWindow.h"
#include "DatabaseManager.h"

enum {
    ID_ADD = 1001,
    ID_MODIFY,
    ID_MARK_DONE,
    ID_DELETE,
    ID_LOGOUT,
    ID_MANAGE,
    ID_FILTER
};

wxBEGIN_EVENT_TABLE(MainWindow, wxFrame)
EVT_BUTTON(ID_ADD, MainWindow::OnAdd)
EVT_BUTTON(ID_MODIFY, MainWindow::OnModify)
EVT_BUTTON(ID_MARK_DONE, MainWindow::OnMarkDone)
EVT_BUTTON(ID_DELETE, MainWindow::OnDelete)
EVT_BUTTON(ID_LOGOUT, MainWindow::OnLogout)
EVT_BUTTON(ID_MANAGE, MainWindow::OnManage)
EVT_CHOICE(ID_FILTER, MainWindow::OnFilterChanged)
EVT_LISTBOX_DCLICK(wxID_ANY, MainWindow::OnTaskSelected)
wxEND_EVENT_TABLE()

MainWindow::MainWindow(const std::string& user) : wxFrame(nullptr, wxID_ANY, "My-Tasks", wxDefaultPosition, wxSize(800, 500)), currentUser(user)
{
    wxPanel* panel = new wxPanel(this);
    wxBoxSizer* rootSizer = new wxBoxSizer(wxHORIZONTAL);

    // lewa kolumna
    wxBoxSizer* leftSizer = new wxBoxSizer(wxVERTICAL);
    const wxSize buttonSize(160, -1);

    addButton = new wxButton(panel, ID_ADD, "Dodaj", wxDefaultPosition, buttonSize);
    modifyButton = new wxButton(panel, ID_MODIFY, "Modyfikuj", wxDefaultPosition, buttonSize);
    markDoneButton = new wxButton(panel, ID_MARK_DONE, "Oznacz jako wykonane", wxDefaultPosition, buttonSize);
    deleteButton = new wxButton(panel, ID_DELETE, "Usuń", wxDefaultPosition, buttonSize);

    wxString choices[] = { "Nie wykonane", "Wykonane" };
    statusFilter = new wxChoice(panel, ID_FILTER, wxDefaultPosition, buttonSize, 2, choices);
    statusFilter->SetSelection(0);

    leftSizer->Add(addButton, 0, wxALL, 5);
    leftSizer->Add(modifyButton, 0, wxALL, 5);
    leftSizer->Add(markDoneButton, 0, wxALL, 5);
    leftSizer->Add(deleteButton, 0, wxALL, 5);
    leftSizer->Add(statusFilter, 0, wxALL, 5);

    // prawa kolumna
    wxBoxSizer* rightSizer = new wxBoxSizer(wxVERTICAL);

    // górny wiersz
    wxBoxSizer* topRow = new wxBoxSizer(wxHORIZONTAL);
    userLabel = new wxStaticText(panel, wxID_ANY, "Zalogowany użytkownik:");
    usernameText = new wxStaticText(panel, wxID_ANY, user);
    manageUserButton = new wxButton(panel, ID_MANAGE, "Zarządzaj");
    logoutButton = new wxButton(panel, ID_LOGOUT, "Wyloguj się");

    topRow->Add(userLabel, 0, wxRIGHT | wxALIGN_CENTER_VERTICAL, 5);
    topRow->Add(usernameText, 1, wxRIGHT | wxALIGN_CENTER_VERTICAL, 10);
    topRow->Add(manageUserButton, 0, wxRIGHT, 5);
    topRow->Add(logoutButton, 0);

    rightSizer->Add(topRow, 0, wxALL | wxEXPAND, 10);

    // dolny wiersz
    wxBoxSizer* bottomRow = new wxBoxSizer(wxHORIZONTAL);

    taskList = new wxListBox(panel, wxID_ANY, wxDefaultPosition, wxSize(260, 200));
    wxBoxSizer* detailsSizer = new wxBoxSizer(wxVERTICAL);
    taskName = new wxStaticText(panel, wxID_ANY, "Nazwa:");
    taskDescription = new wxStaticText(panel, wxID_ANY, "Opis:");

    detailsSizer->Add(taskName, 0, wxBOTTOM, 8);
    detailsSizer->Add(taskDescription, 0);

    bottomRow->Add(taskList, 1, wxALL | wxEXPAND, 10);
    bottomRow->Add(detailsSizer, 1, wxTOP | wxRIGHT | wxBOTTOM | wxEXPAND, 10);

    rightSizer->Add(bottomRow, 1, wxEXPAND);

    // łączenie kolumn
    rootSizer->Add(leftSizer, 0, wxALL | wxEXPAND, 10);
    rootSizer->Add(rightSizer, 1, wxEXPAND);

    // margines zewnętrzny
    wxGridSizer* outerSizer = new wxGridSizer(1);
    outerSizer->Add(rootSizer, wxSizerFlags().Border(wxALL, 15).Expand());

    panel->SetSizer(outerSizer);
    Centre();

    RefreshTasks();
}

void MainWindow::RefreshTasks() {
    taskList->Clear();
    auto tasks = DatabaseManager::GetInstance().GetTasks(currentUser);
    int filter = statusFilter->GetSelection(); // 0: niewykonane, 1: wykonane
    for (const auto& task : tasks) {
        if ((int)task.isDone() == filter) {
            taskList->Append(task.getName());
        }
    }
}

void MainWindow::OnAdd(wxCommandEvent&) {
    AddTaskWindow* addWin = new AddTaskWindow(this, currentUser);
    addWin->Show();
}

void MainWindow::OnDelete(wxCommandEvent&) {
    int sel = taskList->GetSelection();
    if (sel == wxNOT_FOUND) {
        wxMessageBox("Najpierw wybierz zadanie do usunięcia.", "Brak wyboru", wxOK | wxICON_WARNING);
        return;
    }

    DatabaseManager::GetInstance().DeleteTask(currentUser, sel);
    taskName->SetLabel("Nazwa:");
    taskDescription->SetLabel("Opis:");
    RefreshTasks();
}

void MainWindow::OnMarkDone(wxCommandEvent&) {
    int sel = taskList->GetSelection();
    if (sel == wxNOT_FOUND) {
        wxMessageBox("Najpierw wybierz zadanie do zmiany statusu.", "Brak wyboru", wxOK | wxICON_WARNING);
        return;
    }

    auto allTasks = DatabaseManager::GetInstance().GetTasks(currentUser);
    int filter = statusFilter->GetSelection(); // 0: niewykonane, 1: wykonane

    int filteredIndex = 0;
    for (int i = 0; i < (int)allTasks.size(); ++i) {
        if ((int)allTasks[i].isDone() == filter) {
            if (filteredIndex == sel) {
                int newStatus = (filter == 0) ? 1 : 0;
                DatabaseManager::GetInstance().UpdateTaskStatus(currentUser, i, newStatus);
                break;
            }
            filteredIndex++;
        }
    }

    taskName->SetLabel("Nazwa:");
    taskDescription->SetLabel("Opis:");
    RefreshTasks();
}

void MainWindow::OnModify(wxCommandEvent&) {
    int sel = taskList->GetSelection();
    if (sel == wxNOT_FOUND) {
        wxMessageBox("Najpierw wybierz zadanie do modyfikacji.", "Brak wyboru", wxOK | wxICON_WARNING);
        return;
    }

    auto allTasks = DatabaseManager::GetInstance().GetTasks(currentUser);
    int filter = statusFilter->GetSelection();
    int filteredIndex = 0;

    for (int i = 0; i < (int)allTasks.size(); ++i) {
        if ((int)allTasks[i].isDone() == filter) {
            if (filteredIndex == sel) {
                const auto& task = allTasks[i];
                AddTaskWindow* editWin = new AddTaskWindow(this, currentUser, i, task.getName(), task.getDescription());
                editWin->Show();
                break;
            }
            filteredIndex++;
        }
    }
}

void MainWindow::OnLogout(wxCommandEvent&) {
    Close();
    LoginWindow* login = new LoginWindow();
    login->Show();
}

void MainWindow::OnManage(wxCommandEvent&) {
    ManageUserWindow* manageWin = new ManageUserWindow(this, currentUser);
    manageWin->Show();
}

void MainWindow::OnFilterChanged(wxCommandEvent&) {
    int filter = statusFilter->GetSelection();
    if (filter == 0) {
        markDoneButton->SetLabel("Oznacz jako wykonane");
    }
    else {
        markDoneButton->SetLabel("Oznacz jako niewykonane");
    }
    RefreshTasks();
}

void MainWindow::OnTaskSelected(wxCommandEvent&) {
    int sel = taskList->GetSelection();
    if (sel != wxNOT_FOUND) {
        auto tasks = DatabaseManager::GetInstance().GetTasks(currentUser);
        int filter = statusFilter->GetSelection();
        int filteredIndex = 0;
        for (const auto& task : tasks) {
            if ((int)task.isDone() == filter) {
                if (filteredIndex == sel) {
                    taskName->SetLabel("Nazwa: " + task.getName());
                    taskDescription->SetLabel("Opis: " + task.getDescription());
                    break;
                }
                filteredIndex++;
            }
        }
    }
}
