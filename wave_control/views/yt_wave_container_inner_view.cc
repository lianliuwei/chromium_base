#include "wave_control/views/yt_wave_container_inner_view.h"

#include "wave_control/views/transform_util.h"

using namespace ui;

namespace {
class HorizOffsetBar : public HandleBarDelegate
                     , public OscWaveGroupObserver {
public:
  // implement HandleBarDelegate
  virtual bool is_horiz() { return true; }

  // implement HandleBarModel
  virtual int Count();
  virtual int GetID(int index) { return index; } // index == id
  virtual string16 GetText(int ID);
  virtual SkColor GetColor(int ID);
  virtual SkBitmap GetIcon(int ID);
  virtual int GetOffset(int ID);
  virtual bool IsEnable(int ID) { return true; }
  virtual bool IsVisible(int ID);

private:
  // implement HandleBarObserver
  virtual void OnHandleMove(int ID, int offset);
  virtual void OnHandleActive(int ID);

  // implement OscWaveGroupObserver
  virtual void OnPartGroupChanged() { NotifyModelChanged(); }
  virtual void OnPartChanged(int id) { NotifyHandleChanged(id); }
  virtual void OnPartMoved(int id){ NotifyHandleMoved(id); }

  OscWaveGroup* wave_group_;
  YTWaveContainerInnerView* views_;

  DISALLOW_COPY_AND_ASSIGN(HorizOffsetBar);
};

int HorizOffsetBar::Count() {
  return wave_group_->horizontal_count();
}

string16 HorizOffsetBar::GetText(int ID) {
  return wave_group_->horizontal_at(ID)->text();
}

SkColor HorizOffsetBar::GetColor(int ID) {
  return wave_group_->horizontal_at(ID)->color();
}

SkBitmap HorizOffsetBar::GetIcon(int ID) {
  return wave_group_->horizontal_at(ID)->icon();
}

int HorizOffsetBar::GetOffset(int ID) {
  OscWave* wave = wave_group_->horizontal_at(ID)->osc_wave();
  ui::Transform transform = views_->OscWaveTransform(wave);
  return TransformX(transform, 0);
}

bool HorizOffsetBar::IsVisible(int ID) {
  return wave_group_->horizontal_at(ID)->show();
}

void HorizOffsetBar::OnHandleMove(int ID, int offset) {
  OscWave* wave = wave_group_->horizontal_at(ID)->osc_wave();
  ui::Transform transform = views_->OscWaveTransform(wave);
  int logic_offset = TransformReverseX(transform, offset);
  double old_offset = wave->horizontal_offset();
  wave->MoveToX(YTWaveContainerInnerView::ToOscOffset(old_offset, logic_offset));
}

void HorizOffsetBar::OnHandleActive(int ID) {
  OscWave* wave = wave_group_->horizontal_at(ID)->osc_wave();
  views_->SelectWave(wave);  
}

class TriggerBar : public HandleBarDelegate
                 , public OscWaveGroupObserver {
public:
  // implement HandleBarDelegate
  virtual bool is_horiz() { return false; }

  // implement HandleBarModel
  virtual int Count();
  virtual int GetID(int index) { return index; } // index == id
  virtual string16 GetText(int ID);
  virtual SkColor GetColor(int ID);
  virtual SkBitmap GetIcon(int ID);
  virtual int GetOffset(int ID);
  virtual bool IsEnable(int ID) { return true; }
  virtual bool IsVisible(int ID);

private:
  // trigger need the relate wave vertical move notify.
  class VerticalOffsetObserver : public OscWaveGroupObserver {
  private:
    // implement OscWaveGroupObserver
    virtual void OnPartGroupChanged() {}
    virtual void OnPartChanged(int id);
    virtual void OnPartMoved(int id);
  };

  // implement HandleBarObserver
  virtual void OnHandleMove(int ID, int offset);
  virtual void OnHandleActive(int ID);

  // implement OscWaveGroupObserver
  virtual void OnPartGroupChanged() { NotifyModelChanged(); }
  virtual void OnPartChanged(int id) { NotifyHandleChanged(id); }
  virtual void OnPartMoved(int id){ NotifyHandleMoved(id); }

  void OnOscWaveVerticalMoved(OscWave* osc_wave);

  OscWaveGroup* wave_group_;
  YTWaveContainerInnerView* views_;

  DISALLOW_COPY_AND_ASSIGN(TriggerBar);
};

int TriggerBar::Count() {
  return wave_group_->trigger_count();
}

string16 TriggerBar::GetText(int ID) {
  return wave_group_->trigger_at(ID)->text();
}

SkColor TriggerBar::GetColor(int ID) {
  return wave_group_->trigger_at(ID)->color();
}

SkBitmap TriggerBar::GetIcon(int ID) {
  return wave_group_->trigger_at(ID)->icon();
}

bool TriggerBar::IsVisible(int ID) {
  return wave_group_->trigger_at(ID)->show();
}

int TriggerBar::GetOffset(int ID) {
  TriggerPart* trigger = wave_group_->trigger_at(ID);
  OscWave* wave = trigger->osc_wave();
  bool relate = trigger->IsRelate();
  OscWave* trigger_wave = trigger->trigger_wave();
  double offset = trigger->offset();
  if (relate) {
    offset = trigger_wave->vertical_offset() + offset;
  }
  ui::Transform transform = views_->OscWaveTransform(trigger_wave);
  return TransformY(transform, offset);
}

void TriggerBar::OnHandleMove(int ID, int offset) {
  TriggerPart* trigger = wave_group_->trigger_at(ID);
  OscWave* wave = trigger->osc_wave();
  bool relate = trigger->IsRelate();
  OscWave* trigger_wave = trigger->trigger_wave();
  double base_y = 0;
  if (relate) {
    base_y = trigger_wave->vertical_offset();
  }
  ui::Transform transform = views_->OscWaveTransform(trigger_wave);
  double new_offset = TransformReverseY(transform, offset);
  trigger_wave->MoveTrigger(new_offset - base_y);
}

void TriggerBar::OnHandleActive(int ID) {
  TriggerPart* trigger = wave_group_->trigger_at(ID);
  views_->SelectWave(trigger->trigger_wave());
}

// TODO need add OtherWave observer
class WaveBar : public HandleBarDelegate
              , public OscWaveGroupObserver {
public:
  // implement HandleBarDelegate
  virtual bool is_horiz() { return false; }

  // implement HandleBarModel
  virtual int Count();
  virtual int GetID(int index) { return index; } // index == id
  virtual string16 GetText(int ID);
  virtual SkColor GetColor(int ID);
  virtual SkBitmap GetIcon(int ID);
  virtual int GetOffset(int ID);
  virtual bool IsEnable(int ID) { return true; }
  virtual bool IsVisible(int ID);

private:
  class OtherWaveVisitor : public WaveVisitor {
  public:
    OtherWaveVisitor(Wave* other_wave);
    int GetOffset(YTWaveContainerInnerView* view);
    void MoveToY(YTWaveContainerInnerView* view, int offset);
  };
  
  // implement HandleBarObserver
  virtual void OnHandleMove(int ID, int offset);
  virtual void OnHandleActive(int ID);

  // implement OscWaveGroupObserver
  virtual void OnPartGroupChanged() { NotifyModelChanged(); }
  virtual void OnPartChanged(int id) { NotifyHandleChanged(id); }
  virtual void OnPartMoved(int id){ NotifyHandleMoved(id); }

  friend YTWaveContainerInnerView;

  void AddOtherWave(Wave* wave);
  void RemoveOtherWave(Wave* wave);
  void HasOtherWave(Wave* wave);

  OscWaveGroup* wave_group_;
  YTWaveContainerInnerView* views_;

  std::vector<Wave*> other_wave_;

  DISALLOW_COPY_AND_ASSIGN(WaveBar);
};

int WaveBar::Count() {
  return wave_group_->vertical_count() + other_wave_.size();
}

string16 WaveBar::GetText(int ID) {
  if (ID < wave_group_->vertical_count()) {
    return wave_group_->vertical_at(ID)->text();
  } else {
    int index = ID - wave_group_->vertical_count();
    return other_wave_[index]->name();
  }
}

SkColor WaveBar::GetColor(int ID) {
  if (ID < wave_group_->vertical_count()) {
    return wave_group_->vertical_at(ID)->color();
  } else {
    int index = ID - wave_group_->vertical_count();
    return other_wave_[index]->color();
  }
}

SkBitmap WaveBar::GetIcon(int ID) {
  if (ID < wave_group_->vertical_count()) {
    return wave_group_->vertical_at(ID)->icon();
  } else {
    int index = ID - wave_group_->vertical_count();
    return other_wave_[index]->icon();
  }
}

bool WaveBar::IsVisible(int ID) {
  if (ID < wave_group_->vertical_count()) {
    return wave_group_->vertical_at(ID)->show();
  } else {
    return true;
  }
}

int WaveBar::GetOffset(int ID) {
  if (ID < wave_group_->vertical_count()) {
    OscWave* wave = wave_group_->vertical_at(ID)->osc_wave();
    ui::Transform transform = views_->OscWaveTransform(wave);
    return TransformY(transform, 0);
  } else {
    int index = ID - wave_group_->vertical_count();
    OtherWaveVisitor visitor(other_wave_[index]);
    return visitor.GetOffset(views_);
  }
}

void WaveBar::OnHandleMove(int ID, int offset) {
  if (ID < wave_group_->vertical_count()) {
    OscWave* wave = wave_group_->horizontal_at(ID)->osc_wave();
    ui::Transform transform = views_->OscWaveTransform(wave);
    int logic_offset = TransformReverseY(transform, offset);
    double old_offset = wave->vertical_offset();
    wave->MoveToY(YTWaveContainerInnerView::ToOscOffset(old_offset, logic_offset));
  } else {
    int index = ID - wave_group_->vertical_count();
    OtherWaveVisitor visitor(other_wave_[index]);
    return visitor.MoveToY(views_, offset);
  }
}

void WaveBar::OnHandleActive(int ID) {
  if (ID < wave_group_->vertical_count()) {
    views_->SelectWave(wave_group_->vertical_at(ID)->osc_wave());
  } else {
    int index = ID - wave_group_->vertical_count();
    views_->SelectWave(other_wave_[index]);
  }
}

}

void HandleBarDelegate::AddObserver(HandleBarModelObserver* observer) {
  observer_list_.AddObserver(observer);
}

void HandleBarDelegate::RemoveObserver(HandleBarModelObserver* observer) {
  observer_list_.RemoveObserver(observer);
}

bool HandleBarDelegate::HasObserver(HandleBarModelObserver* observer) {
  return observer_list_.HasObserver(observer);
}

void HandleBarDelegate::NotifyModelChanged() {
  FOR_EACH_OBSERVER(HandleBarModelObserver, observer_list_, OnModelChanged());
}

void HandleBarDelegate::NotifyHandleChanged(int id) {
  FOR_EACH_OBSERVER(HandleBarModelObserver, observer_list_, OnHandleChanged(id));
}

void HandleBarDelegate::NotifyHandleMoved(int id) {
  FOR_EACH_OBSERVER(HandleBarModelObserver, observer_list_, OnHandleMoved(id));
}

double YTWaveContainerInnerView::ToOscOffset(double old_offset, double move_delta) {
  return old_offset + (-move_delta);
}
