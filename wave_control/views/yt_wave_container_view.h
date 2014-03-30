#pragma once

#include "views/view.h"

#include "wave_control/wave_container.h"
#include "wave_control/list_model_observer.h"

class YTWaveContainerView : public views::View
                          , public ui::ListModelObserver {
public:
protected:
private:
  views::View::Views wave_views_;
};