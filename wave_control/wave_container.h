#pragma once

#include "wave_control/list_model.h"

#include "wave_control/wave.h"

class WaveControl;
class YTWaveContainer;
class YLWaveContainer;
class XYWaveContainer;
class WaveContainerVisitor;

class WaveContainer : public ui::ListModel<Wave> {
public:
  // parent
  WaveControl* wave_control();

  enum Type {
    kYT, // Y , time
    kYL, // Y , log X
    kXY,
  };

  Type type_id();

  virtual YTWaveContainer* AsYTWaveContainer() { return NULL; }
  virtual YLWaveContainer* AsYLWaveContainer() { return NULL; }
  virtual XYWaveContainer* AsXYWaveContainer() { return NULL; }

  virtual void Accept(WaveContainerVisitor* visitor) = 0;
};
