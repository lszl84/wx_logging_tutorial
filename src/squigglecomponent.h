#pragma once

#include <wx/wx.h>
#include <wx/graphics.h>
#include <wx/dcbuffer.h>

#include <deque>

#undef wxLOG_COMPONENT
#define wxLOG_COMPONENT "main/SquiggleComponent"

class SquiggleComponent : public wxWindow
{
public:
    SquiggleComponent(wxWindow *parent, wxWindowID id = wxID_ANY, const wxPoint &pos = wxDefaultPosition, const wxSize &size = wxDefaultSize, long style = 0)
        : wxWindow(parent, id, pos, size, wxFULL_REPAINT_ON_RESIZE | style)
    {
        this->SetBackgroundStyle(wxBG_STYLE_PAINT); // needed for windows

        this->Bind(wxEVT_PAINT, &SquiggleComponent::OnPaint, this);
        this->Bind(wxEVT_MOTION, &SquiggleComponent::OnMouseMove, this);

        this->Bind(wxEVT_LEAVE_WINDOW, [this](wxMouseEvent &evt)
                   { wxLogDebug("Squiggle: <--- Mouse left window"); });

        this->Bind(wxEVT_ENTER_WINDOW, [this](wxMouseEvent &evt)
                   {
                       wxLogDebug("Squiggle: ---> Mouse entered window");
                       points.clear();
                   });
    }

    void OnPaint(wxPaintEvent &evt)
    {
        wxAutoBufferedPaintDC dc(this);
        dc.Clear();

        wxGraphicsContext *gc = wxGraphicsContext::Create(dc);

        if (gc)
        {
            if (points.size() <= 1)
            {
                wxLogDebug("Squiggle: Not enough points to draw");
                delete gc;
                return;
            }
            else
            {
                wxLogDebug("Squiggle: Drawing %zu points. From (%.2f, %.2f) to (%.2f, %.2f)", points.size(), points[0].m_x, points[0].m_y, points[points.size() - 1].m_x, points[points.size() - 1].m_y);
            }

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
        wxLogDebug("Squiggle: Mouse moved to %d, %d", evt.GetX(), evt.GetY());

        if (points.size() > 0)
        {
            wxLogDebug("Squiggle: Last point was (%.2f, %.2f)", points[points.size() - 1].m_x, points[points.size() - 1].m_y);
        }

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