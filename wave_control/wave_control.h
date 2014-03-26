#pragma once

#include "wave_control/list_model.h"

#include "wave_control/wave_container.h"

class WaveControlVisitor;

class WaveControl : public ui::ListModel<WaveContainer> {
public:

  // auto layout wave
  void AddWave(Wave* wave);
  void RemoveWave(Wave* wave);

  // Wave show Manage
  enum YAxesShowType {
    kAllYAxes,
    kSeparateYAxes,
    kAlternateYAxes,
  };

  YAxesShowType YAxes();

  void Accept(WaveControlVisitor* visitor);

  void ShowInfo();
  void ToggleInfo();
  void IsShowInfo() const;


private:

};
