#include "Osc/ui/views/yt_view_container.h"
#include "Osc/ui/views/yt_view.h"

namespace {

// the Rect::Center change the size if is bigger than the Rect
// this do not change the size
gfx::Rect Center(const gfx::Rect rect, const gfx::Size& size) {
    int new_width = size.width();
    int new_height = size.height();
    int new_x = rect.x() + (rect.width() - new_width) / 2;
    int new_y = rect.y() + (rect.height() - new_height) / 2;
    return gfx::Rect(new_x, new_y, new_width, new_height);
}

}

//TODO the container must controll the YTView and it's assistant view visible
// because the use may only want to show some of them.
void YTViewContainer::Layout() {
    gfx::Size mini = yt_view_->GetMinimumSize();
    gfx::Size real = size();
    // no show the YTView if the real is to small
    if(mini.width() > real.width() || mini.height() > real.height()) {
        yt_view_->SetVisible(false);
    }else {
        gfx::Rect rect = GetLocalBounds();
        bool ret = yt_view_->NormalSize(real);
        CHECK(ret) << "the real can no be normal";
        rect = Center(rect, real);
        yt_view_->SetBoundsRect(rect);
        yt_view_->SetVisible(true);
    }
}

YTViewContainer::YTViewContainer( YTView* yt_view ) 
    : yt_view_(yt_view) {
    DCHECK(yt_view != NULL);
    AddChildView(yt_view);
}
