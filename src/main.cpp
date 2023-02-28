#include <wx/wx.h>

#include "rectanglecomponent.h"
#include "squigglecomponent.h"

class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};

wxIMPLEMENT_APP(MyApp);

class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString &title, const wxPoint &pos, const wxSize &size);
    ~MyFrame()
    {
        wxLog::SetActiveTarget(nullptr);
        delete logger;
    }

private:
    wxLog *logger;
};

bool MyApp::OnInit()
{
    MyFrame *frame = new MyFrame("Hello World", wxDefaultPosition, wxDefaultSize);
    frame->Show(true);
    return true;
}

MyFrame::MyFrame(const wxString &title, const wxPoint &pos, const wxSize &size)
    : wxFrame(nullptr, wxID_ANY, title, pos, size)
{
    logger = new wxLogWindow(this, "Log", true, false);
    wxLog::SetActiveTarget(logger);

    auto sizer = new wxGridSizer(2, FromDIP(10), FromDIP(10));

    sizer->Add(new RectangleComponent(this), 1, wxEXPAND);
    sizer->Add(new SquiggleComponent(this), 1, wxEXPAND);

    sizer->SetMinSize(FromDIP(wxSize(800, 400)));
    this->SetSizerAndFit(sizer);
}