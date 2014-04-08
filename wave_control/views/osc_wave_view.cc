#include "wave_control/views/osc_wave_view.h"

namespace {
bool IsSet(int set, int test) {
  return (set & test) != 0;
}

}


void OscWaveView::OnOscWaveChanged(OscWave* osc_wave, int change_set) {
  int update_transform = OscWave::kVertical | OscWave::kVerticalOffset 
      | OscWave::kHorizontal | OscWave::kHorizontalOffset;
  if (IsSet(change_set, update_transform)) {
    UpdateTransform();
  } 
  if (IsSet(change_set, OscWave::kData)) {
    UpdateData();
  }
}

void OscWaveView::UpdateTransform() {
  ui::Transform transform;

  int windows_size;
  double data_size;
  double offset;
  {
  offset = osc_wave_->vertical_offset();
  WaveRange wave_range = osc_wave_->vertical_offset_range();
  double div_size = (wave_range.begin - wave_range.end) / osc_wave_->vertical_div();
  data_size = div_size * osc_wave_->vertical_window_size();
  windows_size = GetLocalBounds().height();
  }
  
  transform.SetTranslateY(windows_size / 2);
  transform.SetScaleY(- windows_size / data_size);
  transform.SetTranslateY(-offset);

  {
  offset = osc_wave_->horizontal_offset();
  WaveRange wave_range = osc_wave_->horizontal_offset_range();
  double div_size = (wave_range.begin - wave_range.end) / osc_wave_->horizontal_div();
  data_size = div_size * osc_wave_->horizontal_window_size();
  windows_size = GetLocalBounds().width();
  }

  transform.SetTranslateY(windows_size / 2);
  transform.SetScaleY(windows_size / data_size);
  transform.SetTranslateY(-offset);

  set_data_transform(transform);
}

void OscWaveView::UpdateData() {
  set_line_data(&(osc_wave_->Data()));
}

OscWaveView::OscWaveView(OscWave* osc_wave)
    : osc_wave_(osc_wave) {
  set_wave_color(osc_wave->color());
  // TODO may dist them
  set_dot_color(osc_wave->color());
  set_show_style(KLineAndAutoDot);

  osc_wave->AddObserver(this);
  UpdateTransform();
  UpdateData();
}

OscWaveView::~OscWaveView() {
  osc_wave_->RemoveObserver(this);
}
