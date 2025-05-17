#include <wx/wx.h>
#include "LoginWindow.h"

class TaskApp : public wxApp {
public:
    virtual bool OnInit() override {
        LoginWindow* login = new LoginWindow();
        login->Show();
        return true;
    }
};

wxIMPLEMENT_APP(TaskApp);
