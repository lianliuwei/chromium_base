#include "wave_control/ana_wave_data.h"

double AnaWaveData::GetValue(double offset) {
  double* data_ptr = data();
  DCHECK(data_ptr);
  ui::Transform transform;
  WaveRange range = data_range();
  double size =  range.end - range.start;
  transform.SetScaleX(size / size() - 1);
  transform.SetTranslateX(range.start);
  int index = TransformReverseX(transform, offset);
  CHECK(index >= 0 && index <= size() - 1);
  return data_ptr[index];
}

double AnaWaveData::MaxY() {
  double* data_ptr = data();
  int data_size = size();
  DCHECK(data_ptr);
  double max = data_ptr[0]; 
  for (int i = 0; i < data_size; ++i) {
    if (data_ptr[i] > max) {
      max = data_ptr[i];
    }
    if (data_ptr[i] < min) {
      min = data_ptr[i];
    }
  }
  return max;
}

double AnaWaveData::MinY() {
  double* data_ptr = data();
  int data_size = size();
  DCHECK(data_ptr);
  double min = data_ptr[0]; 
  for (int i = 0; i < data_size; ++i) {
    if (data_ptr[i] < min) {
      min = data_ptr[i];
    }
  }
  return min;
}
