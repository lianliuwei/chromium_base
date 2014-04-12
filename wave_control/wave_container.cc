#include "wave_control/wave_container.h"

int WaveContainer::WaveAt(Wave* wave) {
  for (size_t i = 0; i < item_count(); ++i) {
    if (GetItemAt(i) == wave) {
      return i;
    }
  }
  NOTREACHED();
  return 0;
}

bool WaveContainer::HasWave(Wave* wave) {
  for (size_t i = 0; i < item_count(); ++i) {
    if (GetItemAt(i) == wave) {
      return true;
    }
  }
  return false;
}

bool WaveContainer::AddWave(Wave* wave) {
  Add(wave);
}

bool WaveContainer::RemoveWave(Wave* wave) {
  size_t i = WaveAt(wave);
  RemoveAt(i);
}

