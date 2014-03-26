#pragma once

#include "views/view.h"

#include "wave_control/wave_control.h"

class WaveControlView : public views::View {
public:
  WaveControl* wave_control();

};
