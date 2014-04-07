#include "wave_control/wave_range.h"

void WaveRange::MoveCenter(double offset) {
  double old_offset = (begin + end) / 2;
  begin = begin + (offset - old_offset);
  end = end + (offset - old_offset);
}
