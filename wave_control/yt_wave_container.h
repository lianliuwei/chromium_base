#pragma once

#include "wave_control/wave_container.h"
#include "wave_control/osc_wave_group/osc_wave_group.h"

class YTWaveContainer : public WaveContainer {
public:
  // implement WaveContainer
  virtual YTWaveContainer* AsYTWaveContainer() { return this; }

  // caller take ownership
  virtual OscWaveGroup* CreateOscWaveGroup() = 0;

  // show option
  virtual void ShowGrid() = 0;
  virtual void ToggleGrid() = 0;
  virtual bool IsShowGrid() const = 0;
  
  virtual void SelectWave(Wave* wave) = 0;
  virtual Wave* GetSelectWave() = 0;
};