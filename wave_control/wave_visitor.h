#pragma once

#include "wave_control/wave.h"

class OscWave;
class SimpleAnaWave;
class SimpleDigitWave;

class WaveVisitor {
public:
  WaveVisitor() {}

  virtual void VisitOscWave(OscWave* wave) = 0;
  virtual void VisitSimpleAnaWave(SimpleAnaWave* wave) = 0;
  virtual void VisitSimpleDigitWave(SimpleDigitWave* wave) = 0;

protected:
  virtual ~WaveVisitor() {}

};