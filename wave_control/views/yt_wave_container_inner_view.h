#pragma once

#include "views/view.h"

#include "wave_control/wave_container.h"
#include "wave_control/list_model_observer.h"
#include "wave_control/views/axis_background.h"
#include "wave_control/views/handle_bar_model.h"
#include "wave_control/views/handle_bar_observer.h"

class HandleBarDelegate : public HandleBarModel
                        , public HandleBarObserver {
public:
  HandleBarDelegate() {}

protected:
  virtual ~HandleBarDelegate() {}

  DISALLOW_COPY_AND_ASSIGN(HandleBarDelegate);
};

// real YTWaveContainer show view, the YTWaveContainerView
// just frame
class YTWaveContainerInnerView : public views::View
                               , public ui::ListModelObserver {
public:
  YTWaveContainerInnerView(YTWaveContainer* container);

  // get the HandleBarDelegate for move wave and select wave. the YTViewContainer 
  // use this delegate to create handlebar. and it control the Bar
  // show or no and where it show. YTView control how many handle show, and
  // where it show, how it show. the HorizOffsetBar and TriggerBar is the same
  HandleBarDelegate* GetWaveBarDelegate();
  HandleBarDelegate* GetHorizOffsetBarDelegate();
  HandleBarDelegate* GetTriggerBarDelegate();

private:
  // implement ui::ListModelObserver
  virtual void ListItemsAdded(size_t start, size_t count);
  virtual void ListItemsRemoved(size_t start, size_t count);
  virtual void ListItemMoved(size_t index, size_t target_index);
  virtual void ListItemsChanged(size_t start, size_t count);

  AxisBackground* get_axis_background();

  scoped_ptr<OscWaveGroup> wave_group_;
};