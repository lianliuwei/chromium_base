#pragma once

#include "wave_control/views/wave_control_view.h"
#include "wave_control/views/yt_wave_container_view.h"

// use visitor need template for call the right CreateImpl(), and
// NOTREACHED() for no match. this is complex. just use switch case
class WaveControlViewFactory  {
public:
  static WaveControlViewFactory* GetInstance();

  // first create or notify add create all call these method
  WaveControlView* Create(WaveControl* wave_control);

  views::View* Create(WaveContainer* wave_container, 
                      WaveControlView* wave_control_view);

  views::View* Create(Wave* wave, YTWaveContainerView* wave_container_view);


private:
  WaveControlView* CreateImpl(WaveControl* wave_control);

  YTWaveContainerView* CreateImpl(YTWaveContainer* wave_container, 
                                  WaveControlView* wave_control_view);

  OscWaveView* CreateImpl(OscWave* wave, 
                          YTWaveContainerView* yt_wave_container_view);

  SimpleAnaWaveView* CreateImpl(SimpleAnaWave* wave, 
                                YTWaveContainerView* yt_wave_container_view);

};