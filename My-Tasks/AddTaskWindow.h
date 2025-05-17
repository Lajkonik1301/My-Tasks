#pragma once
#include <wx/wx.h>
#include <string>

class MainWindow;

class AddTaskWindow : public wxFrame {
public:
    AddTaskWindow(MainWindow* parent, const std::string& user);

private:
    MainWindow* parentWindow;
    std::string currentUser;

    wxTextCtrl* nameCtrl;
    wxTextCtrl* descCtrl;

    void OnSubmit(wxCommandEvent& event);
};
