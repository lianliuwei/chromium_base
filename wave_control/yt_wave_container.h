#pragma once

#include "wave_control/wave_container.h"

class YTWaveContainer : public WaveContainer {
public:
  // implement WaveContainer
  virtual YTWaveContainer* AsYTWaveContainer() { return this; }

  // show option
  virtual void ShowGrid() = 0;
  virtual void ToggleGrid() = 0;
  virtual bool IsShowGrid() const = 0;
  
  virtual void SelectWave(Wave* wave) = 0;
  virtual Wave* GetSelectWave() = 0;
};