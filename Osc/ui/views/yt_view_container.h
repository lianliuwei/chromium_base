#ifndef OSC_UI_VIEW_YT_VIEW_CONTAINER_H_
#define OSC_UI_VIEW_YT_VIEW_CONTAINER_H_
#pragma once

#include "views/view.h"

class YTView;

// layout the YTView and it's assistant view
class YTViewContainer : public views::View {
public:
    YTViewContainer(YTView* yt_view);
    virtual ~YTViewContainer() {};

public:
    // Overridden from the views::View
    virtual void Layout() OVERRIDE;

private:
    YTView* yt_view_;

    DISALLOW_COPY_AND_ASSIGN(YTViewContainer);
};

#endif // OSC_UI_VIEW_YT_VIEW_CONTAINER_H_