#pragma once

#include <wx/wx.h>
#include <wx/graphics.h>
#include <wx/dcbuffer.h>

#include <deque>

class SquiggleComponent : public wxWindow
{
public:
    SquiggleComponent(wxWindow *parent, wxWindowID id = wxID_ANY, const wxPoint &pos = wxDefaultPosition, const wxSize &size = wxDefaultSize, long style = 0)
        : wxWindow(parent, id, pos, size, wxFULL_REPAINT_ON_RESIZE | style)
    {
        this->SetBackgroundStyle(wxBG_STYLE_PAINT); // needed for windows

        this->Bind(wxEVT_PAINT, &SquiggleComponent::OnPaint, this);
        this->Bind(wxEVT_MOTION, &SquiggleComponent::OnMouseMove, this);
    }

    void OnPaint(wxPaintEvent &evt)
    {
        wxAutoBufferedPaintDC dc(this);
        dc.Clear();

        wxGraphicsContext *gc = wxGraphicsContext::Create(dc);

        if (gc)
        {
            gc->SetPen(wxPen(*wxGREEN, FromDIP(5)));

            for (int i = 1; i < points.size(); i++)
            {
                gc->StrokeLine(points[i - 1].m_x, points[i - 1].m_y, points[i].m_x, points[i].m_y);
            }

            delete gc;
        }
    }

    void OnMouseMove(wxMouseEvent &evt)
    {
        points.push_back(evt.GetPosition());

        if (points.size() > MAX_POINTS)
        {
            points.pop_front();
        }

        this->Refresh();
    }

private:
    const int MAX_POINTS = 30;
    std::deque<wxPoint2DDouble> points{};
};