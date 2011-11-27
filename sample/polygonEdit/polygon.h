#ifndef POLYGONEDIT_POLYGON_H_
#define POLYGONEDIT_POLYGON_H_

#include "views/view.h"
#include "ui/gfx/path.h"

// this View support using mouse to draw a Polygon
// add edit the Polygon.
class Polygon : public views::View
{
public:
    
private:
    enum {
        // left button click add a point, left button double
        // clicks done the draw, right button click remove the last point
        init,

        // zoom in or out the shape to create the path, left button double
        // clicks done the draw.
        init_with_shape,

        // left click inside the ploygon to select this object, and drag to
        // move.
        select_ploygon,

        // left click on the edge. and drag to create a new point in side the
        // select line.
        select_line,

        // left click on the point. and drag to move the point. 
        select_point,

        // click outside the polygon. the polygon is no select.
        no_select,
    } State;

    // views::View
    // in init draw: left button click add a point, left button double
    // clicks done the draw, right button click remove the last point
    // right button double click cancel this draw.
    // in edit: left button click on the point and drag can move the point
    // click on the edge can add a point and drag to move the create point
    // click inside on the Polygon and drag can move the Polygon
    virtual bool OnMousePressed(const views::MouseEvent& event) OVERRIDE;
    
    virtual void OnMouseReleased(const views::MouseEvent& event) OVERRIDE;
    
    virtual void OnMouseCaptureLost() OVERRIDE;
    
    virtual void OnMouseMoved(const views::MouseEvent& event) OVERRIDE;
    
    virtual bool OnMouseDragged(const views::MouseEvent& event) OVERRIDE;

    // three part three Cursor
    // inside the Polygon the move Cursor
    // on the Point cross locate Cursor
    // on the edge the create point Cursor
    virtual gfx::NativeCursor GetCursor(const MouseEvent& event) OVERRIDE;

    virtual bool HitTest(const gfx::Point& l) const OVERRIDE;


private:
    State state_;

    // in select_point state select_ is the point
    // in select_line state select_ is the create point
    gfx::Point select_;

    // in the select line state start_ end_ is the line's end points
    gfx::Point start_;

    gfx::Point end_;

    // 
    gfx::Path path_;
};

#endif // POLYGONEDIT_POLYGON_H_