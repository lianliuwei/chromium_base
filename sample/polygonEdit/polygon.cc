#include "polygonEdit/polygon.h"
#include "base/memory/scoped_ptr.h"

namespace {
    // the size of the Rect to select Point on the Path
    static const int kPointSelectRect = 5;

    // the x and y expand to select line
    static const int kLineSelectWidth = 4;
}

bool Polygon::OnMousePressed( const views::MouseEvent& event ) {
    if (state_ == init) {
        if (event.IsOnlyLeftMouseButton()) // add point to the path
            if (path_.countPoints() == 0)
                path_.moveTo(SkIntToScalar(event.x()), 
                             SkIntToScalar(event.y()));
            else
                path_.lineTo(SkIntToScalar(event.x()), 
                             SkIntToScalar(event.y()));
        else if(event.IsOnlyRightMouseButton()) {// remove point frome the path
            int count = path_.countPoints();
            if(count >= 2) {
                scoped_array<SkPoint> points = new SkPoint[count];
                path_.getPoints(points, count-1); // no need the last point
                path_ = gfx::Path();
                path_.moveTo(points[0]);
                for (int i = 1; i < count-1; i++)
                    path_.lineTo(points[i]);
            } else if (count == 1)
                path_ = gfx::Path(); // start again
        }
    } else if (state_ == init_with_shape) {
        //TODO create different shape here
    } else 
}
