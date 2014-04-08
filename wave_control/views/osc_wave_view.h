#pragma once

#include "wave_control/views/line_data_wave_view.h"
#include "wave_control/osc_wave.h"

class OscWaveView : public LineDataWaveView
                  , public OscWaveObserver {
public:
  OscWaveView(OscWave* osc_wave);
  virtual ~OscWaveView();

private:
  // implement OscWaveObserver
  virtual void OnOscWaveChanged(OscWave* osc_wave, int change_set);

  void UpdateTransform();
  void UpdateData();

  OscWave* osc_wave_;
};

