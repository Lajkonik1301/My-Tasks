#include "AddTaskWindow.h"
#include "DatabaseManager.h"
#include "MainWindow.h"

AddTaskWindow::AddTaskWindow(MainWindow* parent, const std::string& user)
    : wxFrame(nullptr, wxID_ANY, "Dodaj zadanie", wxDefaultPosition, wxSize(300, 200)),
    parentWindow(parent), currentUser(user)
{
    wxPanel* panel = new wxPanel(this);

    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

    nameCtrl = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(250, -1));
    descCtrl = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(250, -1));

    wxButton* submitBtn = new wxButton(panel, wxID_ANY, "Dodaj");

    sizer->Add(new wxStaticText(panel, wxID_ANY, "Nazwa:"), 0, wxALL, 5);
    sizer->Add(nameCtrl, 0, wxALL, 5);
    sizer->Add(new wxStaticText(panel, wxID_ANY, "Opis:"), 0, wxALL, 5);
    sizer->Add(descCtrl, 0, wxALL, 5);
    sizer->Add(submitBtn, 0, wxALL | wxALIGN_CENTER, 10);

    panel->SetSizer(sizer);

    submitBtn->Bind(wxEVT_BUTTON, &AddTaskWindow::OnSubmit, this);
}

void AddTaskWindow::OnSubmit(wxCommandEvent&) {
    std::string name = nameCtrl->GetValue().ToStdString();
    std::string desc = descCtrl->GetValue().ToStdString();

    if (name.empty()) {
        wxMessageBox("WprowadŸ nazwê zadania.", "B³¹d", wxOK | wxICON_ERROR);
        return;
    }

    DatabaseManager::GetInstance().AddTask(currentUser, name, desc);
    parentWindow->RefreshTasks();
    Close();
}
