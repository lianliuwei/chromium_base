#include "wave_control/wave_range.h"

void WaveRange::MoveCenter(double offset) {
  double old_offset = (start + end) / 2;
  start = start + (offset - old_offset);
  end = end + (offset - old_offset);
}
