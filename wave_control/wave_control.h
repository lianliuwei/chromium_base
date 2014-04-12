#pragma once

#include "wave_control/list_model.h"

#include "wave_control/wave_container.h"

class WaveControlVisitor;

// no sub class now
class WaveControl : public ui::ListModel<WaveContainer> {
public:
  int WaveContainerAt(WaveContainer* container);
  bool HasWaveContainer(WaveContainer* container);
  void AddContainer(WaveContainer* container);
  void RemoveContainer(WaveContainer* container);

  // auto layout wave
  virtual void AddWave(Wave* wave) = 0;
  virtual void RemoveWave(Wave* wave) = 0;

  virtual void Accept(WaveControlVisitor* visitor);

  virtual void ShowInfo() = 0;
  virtual void ToggleInfo() = 0;
  virtual void IsShowInfo() const = 0;

private:

};
