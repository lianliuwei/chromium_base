#pragma once

class WaveRange {
public:
  double begin;
  double end;

  // offset is in start end coord
  void MoveCenter(double offset);
};
