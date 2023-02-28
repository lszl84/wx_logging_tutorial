#pragma once

#include <wx/wx.h>
#include <wx/graphics.h>
#include <wx/dcbuffer.h>

#undef wxLOG_COMPONENT
#define wxLOG_COMPONENT "main/RectangleComponent"

class RectangleComponent : public wxWindow
{
public:
    RectangleComponent(wxWindow *parent, wxWindowID id = wxID_ANY, const wxPoint &pos = wxDefaultPosition, const wxSize &size = wxDefaultSize, long style = 0)
        : wxWindow(parent, id, pos, size, wxFULL_REPAINT_ON_RESIZE | style)
    {
        this->SetBackgroundStyle(wxBG_STYLE_PAINT); // needed for windows

        this->Bind(wxEVT_PAINT, &RectangleComponent::OnPaint, this);
        this->Bind(wxEVT_MOTION, &RectangleComponent::OnMouseMove, this);
    }

    void OnPaint(wxPaintEvent &evt)
    {
        wxAutoBufferedPaintDC dc(this);
        dc.Clear();

        wxGraphicsContext *gc = wxGraphicsContext::Create(dc);

        if (gc)
        {
            wxLogDebug("Drawing rectangle at %f, %f", position.m_x, position.m_y);

            gc->SetBrush(*wxRED_BRUSH);

            auto width = gc->FromDIP(100);

            gc->Translate(-width / 2, -width / 2);
            gc->DrawRectangle(position.m_x, position.m_y, width, width);

            delete gc;
        }
    }

    void OnMouseMove(wxMouseEvent &evt)
    {
        wxLogDebug("Rectangle: Mouse moved to %d, %d", evt.GetX(), evt.GetY());
        position = evt.GetPosition();
        this->Refresh();
    }

private:
    wxPoint2DDouble position{};
};