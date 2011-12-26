#ifndef OSC_UI_VIEWS_YT_VIEW_H_
#define OSC_UI_VIEWS_YT_VIEW_H_
#pragma once

#include "views/view.h"
#include "Osc/ui/views/axis_background.h"

// this view is to show chnl(Analog or Digital) wave, math wave, FFT wave
class YTView : public views::View
{
public:
    YTView();
    virtual ~YTView();
    
    // see commit in axis_painter.h
    bool NormalSize(gfx::Size& size);

    // see commit in axis_painter.h
    gfx::Size GetMinimumSize();

    // set grid of the Axis. the range is div by the 2*grid and Axis is draw in
    // middle. set grid to 0 to keep the old value
    void SetGrid(int v_grid, int h_grid);
protected:
private:
    AxisBackground* get_axis_background();

    int v_grid_;

    int h_grid_;

    DISALLOW_COPY_AND_ASSIGN(YTView);
};
#endif // OSC_UI_VIEWS_YT_VIEW_H_