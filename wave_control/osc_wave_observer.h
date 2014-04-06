#pragma once

class OscWaveObserver {
public:
  virtual void OnOscWaveChanged(OscWave* osc_wave, int change_set) = 0;

protected:
  OscWaveObserver() {}
  virtual ~OscWaveObserver() {}
};