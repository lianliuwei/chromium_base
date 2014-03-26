#pragma once

class WaveContainer;
class YTWaveContainer;
class YLWaveContainer;
class XYWaveContainer;

class WaveContainerVisitor {
public:
  WaveContainerVisitor() {}

  void VisitYTWaveContainer(YTWaveContainer* wave_container) = 0;
  void VisitYLWaveContainer(YLWaveContainer* wave_container) = 0;
  void VisitXYWaveContainer(XYWaveContainer* wave_container) = 0;

protected:
  virtual ~WaveContainerVisitor() {}
};