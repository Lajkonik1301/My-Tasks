#include "MainFrame.h"

MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title) {

    Center();

    panel = new wxPanel(this);
    //panel->SetMinSize(wxSize(220, 270));
    userManager = new UserManager();
    loginPage = new LoginPage(panel, userManager);
}

void MainFrame::ClearPanel() {
    panel->DestroyChildren();
}

void MainFrame::MainPage() {
    ClearPanel();
}
