#ifndef OSC_UI_VIEWS_YT_VIEW_H_
#define OSC_UI_VIEWS_YT_VIEW_H_
#pragma once

#include "views/view.h"
#include "Osc/ui/views/axis_background.h"

// this view is to show chnl, math w
class YTView : public views::View
{
public:
    
protected:
private:
    AxisBackground* get_axis_background();
};
#endif // OSC_UI_VIEWS_YT_VIEW_H_