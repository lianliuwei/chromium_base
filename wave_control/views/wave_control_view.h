#pragma once

#include "views/view.h"

#include "wave_control/wave_control.h"
#include "wave_control/list_model_observer.h"

class WaveControlView : public views::View
                      , public ui::ListModelObserver {
public:
  WaveControlView(WaveControl* wave_control);
  virtual ~WaveControlView();

  WaveControl* wave_control() { return wave_control_; }

private:
  friend class WaveControlViewFactory;
  
  // implement ui::ListModelObserver
  virtual void ListItemsAdded(size_t start, size_t count);
  virtual void ListItemsRemoved(size_t start, size_t count);
  virtual void ListItemMoved(size_t index, size_t target_index);
  virtual void ListItemsChanged(size_t start, size_t count);

  WaveControl* wave_control_;
};
