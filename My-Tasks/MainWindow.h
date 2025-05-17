#pragma once
#include <wx/wx.h>
#include <wx/choice.h>
#include <string>

class AddTaskWindow;

class MainWindow : public wxFrame {
public:
    MainWindow(const std::string& user);
    void RefreshTasks();

private:
    std::string currentUser;

    // Lewa kolumna
    wxButton* addButton;
    wxButton* modifyButton;
    wxButton* markDoneButton;
    wxButton* deleteButton;
    wxChoice* statusFilter;

    // Prawa górna sekcja
    wxStaticText* userLabel;
    wxStaticText* usernameText;
    wxButton* manageUserButton;
    wxButton* logoutButton;

    // Prawa dolna sekcja
    wxListBox* taskList;
    wxStaticText* taskName;
    wxStaticText* taskDescription;

    void OnAdd(wxCommandEvent& event);
    void OnDelete(wxCommandEvent& event);
    void OnMarkDone(wxCommandEvent& event);
    void OnModify(wxCommandEvent& event);
    void OnLogout(wxCommandEvent& event);
    void OnManage(wxCommandEvent& event);
    void OnFilterChanged(wxCommandEvent& event);
    void OnTaskSelected(wxCommandEvent& event);

    wxDECLARE_EVENT_TABLE();
};
