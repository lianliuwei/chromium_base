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

  Type type_id() const;

  // RTTI
  virtual OscWave* AsOscWave();
  virtual SimpleAnaWave* AsSimpleAnaWave();
  virtual SimpleDigitWave* AsSimpleDigitWave();

  virtual void Accept(WaveVisitor* visitor) = 0;

  string16 name();
  SkColor color();
  SkBitmap icon();

  Range Vercital();
  Range Horizonal();

  // Wave can by own by the WaveView, for animation, for Drag&Drop 
  void NeedDelete();
  bool OwnByWaveView();
};