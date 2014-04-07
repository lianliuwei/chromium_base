#pragma once

class WaveRange {
public:
  double start;
  double end;

  // offset is in start end coord
  void MoveCenter(double offset);
};
