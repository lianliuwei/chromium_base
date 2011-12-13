#include "Osc/ui/views/yt_view_container.h"
#include "Osc/ui/views/yt_view.h"

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
        rect = rect.Center(real);
        yt_view_->SetBoundsRect(rect);
        yt_view_->SetVisible(true);
    }
}

YTViewContainer::YTViewContainer( YTView* yt_view ) 
    : yt_view_(yt_view) {
    DCHECK(yt_view != NULL);
    AddChildView(yt_view);
}
