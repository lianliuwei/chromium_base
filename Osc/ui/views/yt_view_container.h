#ifndef OSC_UI_VIEW_YT_VIEW_CONTAINER_H_
#define OSC_UI_VIEW_YT_VIEW_CONTAINER_H_
#pragma once

#include "views/view.h"

class YTView;
class HandleBar;
class HandleBarDelegate;

// layout the YTView and it's assistant view
class YTViewContainer : public views::View {
public:
    YTViewContainer(YTView* yt_view);
    virtual ~YTViewContainer() {};

public:
    // Overridden from the views::View
    virtual void Layout() OVERRIDE;

    // waveBar on the left, horizOffset on the top, TriggerBar on the right.
    void ShowWaveBar(bool visible);
    void ShowHorizOffsetBar(bool visible);
    void ShowTriggerBar(bool visible);

private:
    HandleBar* CreateHandleBar(HandleBarDelegate* delegate, bool is_horiz);

private:
    YTView* yt_view_;

    // the handlebars are the container's children. but the YTView manager
    // those.
    HandleBar* wave_bar_;
    HandleBar* Horiz_offset_bar_;
    HandleBar* trigger_bar_;

    bool show_wave_bar_;
    bool show_horiz_offset_bar_;
    bool show_trigger_bar_;

    DISALLOW_COPY_AND_ASSIGN(YTViewContainer);
};

#endif // OSC_UI_VIEW_YT_VIEW_CONTAINER_H_