#include "AddTaskWindow.h"
#include "DatabaseManager.h"
#include "MainWindow.h"

AddTaskWindow::AddTaskWindow(MainWindow* parent, const std::string& user)
    : wxFrame(nullptr, wxID_ANY, "", wxDefaultPosition, wxDefaultSize),
    parentWindow(parent), currentUser(user)
{
    CreateLayout("Dodaj zadanie", "", "", "Dodaj");
}


AddTaskWindow::AddTaskWindow(MainWindow* parent, const std::string& user, int taskIndex, const std::string& name, const std::string& description)
    : wxFrame(nullptr, wxID_ANY, "", wxDefaultPosition, wxDefaultSize),
    parentWindow(parent), currentUser(user), isEditMode(true), editingIndex(taskIndex)
{
    CreateLayout("Edytuj zadanie", name, description, "Zapisz");
}

void AddTaskWindow::CreateLayout(const std::string& title, const std::string& initialName, const std::string& initialDesc, const wxString& buttonText) {
    SetTitle(title);
    SetSize(wxSize(360, 300));
    wxPanel* panel = new wxPanel(this);

    wxBoxSizer* outerSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* formSizer = new wxBoxSizer(wxVERTICAL);

    nameCtrl = new wxTextCtrl(panel, wxID_ANY, initialName, wxDefaultPosition, wxSize(240, -1));
    descCtrl = new wxTextCtrl(panel, wxID_ANY, initialDesc, wxDefaultPosition, wxSize(240, 80), wxTE_MULTILINE | wxTE_WORDWRAP);
    wxButton* submitBtn = new wxButton(panel, wxID_ANY, buttonText);

    formSizer->AddSpacer(10);
    formSizer->Add(new wxStaticText(panel, wxID_ANY, "Nazwa"), 0, wxALIGN_CENTER_HORIZONTAL | wxBOTTOM, 4);
    formSizer->Add(nameCtrl, 0, wxALIGN_CENTER_HORIZONTAL | wxBOTTOM, 8);

    formSizer->Add(new wxStaticText(panel, wxID_ANY, "Opis"), 0, wxALIGN_CENTER_HORIZONTAL | wxBOTTOM, 4);
    formSizer->Add(descCtrl, 0, wxALIGN_CENTER_HORIZONTAL | wxBOTTOM, 6);

    formSizer->Add(submitBtn, 0, wxALIGN_CENTER_HORIZONTAL | wxBOTTOM, 4);

    outerSizer->Add(formSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxTOP | wxLEFT | wxRIGHT, 15);
    outerSizer->AddStretchSpacer(1);

    panel->SetSizer(outerSizer);
    submitBtn->Bind(wxEVT_BUTTON, &AddTaskWindow::OnSubmit, this);
}

void AddTaskWindow::OnSubmit(wxCommandEvent&) {
    std::string name = nameCtrl->GetValue().ToStdString();
    std::string desc = descCtrl->GetValue().ToStdString();

    if (name.empty()) {
        wxMessageBox("WprowadŸ nazwê zadania.", "B³¹d", wxOK | wxICON_ERROR);
        return;
    }

    if (isEditMode) {
        DatabaseManager::GetInstance().UpdateTask(currentUser, editingIndex, name, desc);
    }
    else {
        DatabaseManager::GetInstance().AddTask(currentUser, name, desc);
    }

    parentWindow->RefreshTasks();
    Close();
}

