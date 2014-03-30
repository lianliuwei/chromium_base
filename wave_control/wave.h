#pragma once

#include "wave_control/supports_user_data.h"

class WaveVisitor;
class OscWave;
class SimpleAnaWave;
class SimpleDigitWave;

class Wave : public base::SupportsUserData {
public:
  // parent
  WaveControl* wave_control();
  WaveContainer* wave_container();

  enum Type {
    kOsc,
    kSimpleAna,
    kSimpleDigit,
  };

  virtual Type type_id() const = 0;

  // RTTI
  virtual OscWave* AsOscWave() { return NULL; }
  virtual SimpleAnaWave* AsSimpleAnaWave() { return NULL; }
  virtual SimpleDigitWave* AsSimpleDigitWave() { return NULL; }

  virtual void Accept(WaveVisitor* visitor) = 0;

  virtual string16 name() = 0;
  virtual SkColor color() = 0;
  virtual SkBitmap icon() = 0;


  // Wave can by own by the WaveView, for animation, for Drag&Drop 
  void NeedDelete();
  bool OwnByWaveView();
};