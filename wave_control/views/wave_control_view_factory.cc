#include "wave_control/views/wave_control_view_factory.h"


WaveControlView* WaveControlViewFactory::Create(WaveControl* wave_control) {
  DCHECK(wave_control);
  return CreateImpl(wave_control);
}

void WaveControlViewFactory::Create(WaveContainer* wave_container, 
                                    WaveControlView* wave_control_view) {
  DCHECK(wave_container);
  switch (wave_container->type_id()) {
  case kYT:
    CreateImpl(wave_container->AsYTWaveContainer(), wave_control_view);
    break;

  default:
    NOTREACHED() << "no support WaveContainer";
  }
}

void WaveControlViewFactory::Create(Wave* wave, 
                                  YTWaveContainerView* wave_container_view) {
  DCHECK(wave);                                      
  switch (wave->type_id()) {
  case kOsc:
    CreateImpl(wave->AsOscWave(), wave_container_view);
    break;
  case kSimpleAna:
    CreateImpl(wave->AsSimpleAnaWave(), wave_container_view);
    break;

  default:
    NOTREACHED() << "no support Wave"£»
  }
}

WaveControlView* WaveControlViewFactory::CreateImpl(WaveControl* wave_control) {
  WaveControlView* wave_control_view = new WaveControlView(wave_control);
  for (size_t i = 0; i < wave_control->item_count(); ++i) {
    Create(wave_control->GetItemAt(i), wave_control_view);
  }
  return wave_control_view;
}

YTWaveContainerView* WaveControlViewFactory::CreateImpl(YTWaveContainer* wave_container, 
                                                        WaveControlView* wave_control_view) {
  YTWaveContainerView*  yt_wave_container_view 
      = new YTWaveContainerView(wave_container, wave_control_view);
  for (size_t i = 0; i < wave_container->item_count(); ++i) {
    Create(wave_container->GetItemAt(i), yt_wave_container_view);
  }
  return yt_wave_container_view;
}
