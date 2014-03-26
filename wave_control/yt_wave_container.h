#pragma once

#include "wave_control/wave_container.h"

class YTWaveContainer : public WaveContainer {
public:
  // implement WaveContainer
  virtual YTWaveContainer* AsYTWaveContainer() { return this; }

  // show option
  void ShowGrid();
  void ToggleGrid();
  bool IsShowGrid() const;
  
  void SelectWave(Wave* wave);
  Wave* GetSelectWave();

};