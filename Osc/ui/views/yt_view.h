#ifndef OSC_UI_VIEWS_YT_VIEW_H_
#define OSC_UI_VIEWS_YT_VIEW_H_
#pragma once

#include "views/view.h"
#include "Osc/ui/views/axis_background.h"
#include "Osc/ui/views/handle_bar_model.h"
#include "Osc/ui/views/handle_bar_observer.h"

class HandleBarDelegate : public HandleBarModel
                        , public HandleBarObserver
{
    HandleBarDelegate() {}
protected:
    virtual ~HandleBarDelegate() {}

    DISALLOW_COPY_AND_ASSIGN(HandleBarDelegate);
};

// this view is to show chnl(Analog or Digital) wave, math wave, FFT wave
class YTView : public views::View
{
public:
    YTView();
    virtual ~YTView();
    
    // TODO change to * for output see google code guide
    // see commit in axis_painter.h
    bool NormalSize(gfx::Size& size);

    // see commit in axis_painter.h
    gfx::Size GetMinimumSize();

    // set grid of the Axis. the range is div by the 2*grid and Axis is draw in
    // middle. set grid to 0 to keep the old value
    void SetGrid(int v_grid, int h_grid);

    // now assert the border width are all the same, it user for the container
    // to layout the assist handlebar.
    int GetBorderWidth();

    // get the HandleBarDelegate for move wave and select wave. the yt view 
    // container use this delegate to create handlebar. and it control the Bar
    // show or no and where it show. YTView control how many handle show, and
    // where it show, how it show. the HorizOffsetBar and TriggerBar is the same
    HandleBarDelegate* GetWaveBarDelegate();

    HandleBarDelegate* GetHorizOffsetBarDelegate();

    HandleBarDelegate* GetTriggerBarDelegate();

protected:
private:
    AxisBackground* get_axis_background();

    int v_grid_;

    int h_grid_;

    DISALLOW_COPY_AND_ASSIGN(YTView);
};

#endif // OSC_UI_VIEWS_YT_VIEW_H_