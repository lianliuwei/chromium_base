#include "wave_control/views/wave_control_view_factory.h"


WaveControlView* WaveControlViewFactory::Create(WaveControl* wave_control) {
  DCHECK(wave_control);
  return CreateImpl(wave_control);
}

views::View* WaveControlViewFactory::Create(WaveContainer* wave_container, 
                                            WaveControlView* wave_control_view) {
  DCHECK(wave_container);
  switch (wave_container->type_id()) {
  case kYT:
    return CreateImpl(wave_container->AsYTWaveContainer(), wave_control_view);

  default:
    NOTREACHED() << "no support WaveContainer";
    return NULL;
  }
}

views::View* WaveControlViewFactory::Create(Wave* wave, 
                                            YTWaveContainerView* wave_container_view) {
  DCHECK(wave);                                      
  switch (wave->type_id()) {
  case kOsc:
    return CreateImpl(wave->AsOscWave(), wave_container_view);
  case kSimpleAna:
    return CreateImpl(wave->AsSimpleAnaWave(), wave_container_view);

  default:
    NOTREACHED() << "no support Wave";
    return NULL;
  }
}

WaveControlView* WaveControlViewFactory::CreateImpl(WaveControl* wave_control) {
  WaveControlView* wave_control_view = new WaveControlView(wave_control);
  return wave_control_view;
}

YTWaveContainerView* WaveControlViewFactory::CreateImpl(YTWaveContainer* wave_container, 
                                                        WaveControlView* wave_control_view) {
  YTWaveContainerView*  yt_wave_container_view 
      = new YTWaveContainerView(wave_container, wave_control_view);
  return yt_wave_container_view;
}
