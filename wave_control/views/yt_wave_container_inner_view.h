#pragma once

#include "base/observer_list.h"
#include "views/view.h"

#include "wave_control/wave_container.h"
#include "wave_control/list_model_observer.h"
#include "wave_control/osc_wave_group/osc_wave_group.h"
#include "wave_control/views/axis_background.h"
#include "wave_control/views/handle_bar_model.h"
#include "wave_control/views/handle_bar_observer.h"
#include "wave_control/views/handle_bar_model_observer.h"


class HandleBarDelegate : public HandleBarModel
                        , public HandleBarObserver {
public:
  HandleBarDelegate() {}

  virtual bool is_horiz() = 0;

  // implement HandleBarModel
  virtual void AddObserver(HandleBarModelObserver* observer);
  virtual void RemoveObserver(HandleBarModelObserver* observer);
  virtual bool HasObserver(HandleBarModelObserver* observer);

protected:
  virtual ~HandleBarDelegate() {}

  void NotifyModelChanged();
  void NotifyHandleChanged(int id);
  void NotifyHandleMoved(int id);

  ObserverList<HandleBarModelObserver> observer_list_;

  DISALLOW_COPY_AND_ASSIGN(HandleBarDelegate);
};
namespace {
class HorizOffsetBar;
class TriggerBar;
class WaveBar;
class YTWaveVisitor;
}

// real YTWaveContainer show view, the YTWaveContainerView
// just frame
class YTWaveContainerInnerView : public views::View
                               , public ui::ListModelObserver {
public:
  YTWaveContainerInnerView(YTWaveContainer* container);
  virtual ~YTWaveContainerInnerView();

  // get the HandleBarDelegate for move wave and select wave. the YTViewContainer 
  // use this delegate to create handlebar. and it control the Bar
  // show or no and where it show. YTView control how many handle show, and
  // where it show, how it show. the HorizOffsetBar and TriggerBar is the same
  HandleBarDelegate* GetWaveBarDelegate();
  HandleBarDelegate* GetHorizOffsetBarDelegate();
  HandleBarDelegate* GetTriggerBarDelegate();

  // osc coord transform
  ui::Transform OscWaveTransform(OscWave* osc_wave);
  static double ToOscOffset(double old_offset, double move_delta);

  // SimpleAnaWave coord transform
  ui::Transform SimpleAnaWaveTransform(SimpleAnaWave* ana_wave);
  int GetYOffset(SimpleAnaWave* wave);
  void MoveToY(SimpleAnaWave* wave, double offset);

  void SelectWave(Wave* wave);

  // see commit in axis_painter.h
  bool NormalSize(gfx::Size& size);

  // now assert the border width are all the same, it user for the container
  // to layout the assist handlebar.
  int BorderThickness();

  gfx::Size GetMinimumSize();

private:
  // implement ui::ListModelObserver
  virtual void ListItemsAdded(size_t start, size_t count);
  virtual void ListItemsRemoved(size_t start, size_t count);
  virtual void ListItemMoved(size_t index, size_t target_index);
  virtual void ListItemsChanged(size_t start, size_t count);

  AxisBackground* get_axis_background();
  void SetGrid(int v_grid, int h_grid);
  void UpdateAxis();

  friend class YTWaveVisitor;

  scoped_ptr<WaveBar> wave_bar_;
  scoped_ptr<HorizOffsetBar> horiz_offset_bar_;
  scoped_ptr<TriggerBar> trigger_bar_;

  scoped_ptr<OscWaveGroup> wave_group_;
  
  YTWaveContainer* container_;

  // HACK for sync with wave LiistModel, the RemoveWave need Wave ptr.
  std::vector<Wave*> wave_record_;

  DISALLOW_COPY_AND_ASSIGN(YTWaveContainerInnerView);

};