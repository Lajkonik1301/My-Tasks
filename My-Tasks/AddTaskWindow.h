#pragma once
#include <wx/wx.h>
#include <string>

class MainWindow;

class AddTaskWindow : public wxFrame {
public:
    AddTaskWindow(MainWindow* parent, const std::string& user);
    AddTaskWindow(MainWindow* parent, const std::string& user, int taskIndex, const std::string& name, const std::string& description);

private:
    bool isEditMode = false;
    int editingIndex = -1;

    MainWindow* parentWindow;
    std::string currentUser;

    wxTextCtrl* nameCtrl;
    wxTextCtrl* descCtrl;

    void OnSubmit(wxCommandEvent& event);
};
