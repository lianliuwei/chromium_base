#pragma once

#include <vector>

#include "wave_control/wave.h"

enum DigitNodeType {
  kEmpty,
  kLink,  
};

struct DigitNode {
  DigitNodeType type;
  string16 name;
  SkColor color;
  string16 data;
  SkBitmap icon;
  double length;
};

class SimpleDigitWaveData {
 public:
  WaveRange range();

  DigitNode& GetNode(double offset) const;
  std::vector<DigitNode*> GetRangeNode(double start, double offset) const;
  std::vector<DigitNode*> FindNode(string16 key);
  
 private:
   std::vector<DigitNode> nodes_;  
};

class SimpleDigitWave : public Wave {
public:
  virtual SimpleDigitWave* AsSimpleDigitWave() OVERRIDE { return this; }

  SimpleDigitWaveData& GetData();

private:

};
