#include "wave_control/views/yt_wave_container_inner_view.h"

#include "wave_control/wave_visitor.h"
#include "wave_control/yt_wave_container.h"
#include "wave_control/views/transform_util.h"
#include "wave_control/views/wave_control_view_factory.h"
#include "wave_control/views/wave_control_views_constants.h"

using namespace ui;
using namespace std;
using namespace views;

namespace {
class HorizOffsetBar : public HandleBarDelegate
                     , public OscWaveGroupObserver {
public:
  HorizOffsetBar(OscWaveGroup* wave_group, YTWaveContainerInnerView* view);
  virtual ~HorizOffsetBar();

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
  YTWaveContainerInnerView* view_;

  DISALLOW_COPY_AND_ASSIGN(HorizOffsetBar);
};

HorizOffsetBar::HorizOffsetBar(OscWaveGroup* wave_group, 
                               YTWaveContainerInnerView* view)
    : wave_group_(wave_group)
    , view_(view) {
  wave_group->AddHorizontalObserver(this);        
}

HorizOffsetBar::~HorizOffsetBar() {
  wave_group_->RemoveHorizontalObserver(this);
}

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
  ui::Transform transform = view_->OscWaveTransform(wave);
  return TransformX(transform, 0);
}

bool HorizOffsetBar::IsVisible(int ID) {
  return wave_group_->horizontal_at(ID)->show();
}

void HorizOffsetBar::OnHandleMove(int ID, int offset) {
  OscWave* wave = wave_group_->horizontal_at(ID)->osc_wave();
  ui::Transform transform = view_->OscWaveTransform(wave);
  int logic_offset = TransformReverseX(transform, offset);
  double old_offset = wave->horizontal_offset();
  wave->MoveToX(YTWaveContainerInnerView::ToOscOffset(old_offset, logic_offset));
}

void HorizOffsetBar::OnHandleActive(int ID) {
  OscWave* wave = wave_group_->horizontal_at(ID)->osc_wave();
  view_->SelectWave(wave);  
}

class TriggerBar : public HandleBarDelegate
                 , public OscWaveGroupObserver {
public:
  TriggerBar(OscWaveGroup* wave_group, YTWaveContainerInnerView* view);
  virtual ~TriggerBar();

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
  public:
    VerticalOffsetObserver(TriggerBar* trigger_bar);
    virtual ~VerticalOffsetObserver();

    // implement OscWaveGroupObserver
    virtual void OnPartGroupChanged() {}
    virtual void OnPartChanged(int id);
    virtual void OnPartMoved(int id);

  private:
    TriggerBar* trigger_bar_;
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
  YTWaveContainerInnerView* view_;
  VerticalOffsetObserver vertical_observer_;

  DISALLOW_COPY_AND_ASSIGN(TriggerBar);
};

TriggerBar::VerticalOffsetObserver::VerticalOffsetObserver(TriggerBar* trigger_bar)
    : trigger_bar_(trigger_bar) {
  trigger_bar->wave_group_->AddVerticalObserver(this);
}

TriggerBar::VerticalOffsetObserver::~VerticalOffsetObserver() {
  trigger_bar_->wave_group_->RemoveVerticalObserver(this);
}

void TriggerBar::VerticalOffsetObserver::OnPartChanged(int id) {
  OscWave* wave = trigger_bar_->wave_group_->vertical_at(id)->osc_wave();
  trigger_bar_->OnOscWaveVerticalMoved(wave);
}

void TriggerBar::VerticalOffsetObserver::OnPartMoved(int id) {
  OscWave* wave = trigger_bar_->wave_group_->vertical_at(id)->osc_wave();
  trigger_bar_->OnOscWaveVerticalMoved(wave);
}

TriggerBar::TriggerBar(OscWaveGroup* wave_group, 
                       YTWaveContainerInnerView* view)
    : wave_group_(wave_group)
    , view_(view)
    , vertical_observer_(this) {
  wave_group->AddTriggerObserver(this);
}

TriggerBar::~TriggerBar() {
  wave_group_->RemoveTriggerObserver(this);
}

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
  ui::Transform transform = view_->OscWaveTransform(trigger_wave);
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
  ui::Transform transform = view_->OscWaveTransform(trigger_wave);
  double new_offset = TransformReverseY(transform, offset);
  trigger_wave->MoveTrigger(new_offset - base_y);
}

void TriggerBar::OnHandleActive(int ID) {
  TriggerPart* trigger = wave_group_->trigger_at(ID);
  view_->SelectWave(trigger->trigger_wave());
}

void TriggerBar::OnOscWaveVerticalMoved(OscWave* osc_wave) {
  for (int i = 0; i < wave_group_->trigger_count(); ++i) {
    TriggerPart* trigger = wave_group_->trigger_at(i);
    if (trigger->trigger_wave() == osc_wave) {
      NotifyHandleMoved(i);
    }
  }
}

// TODO need add OtherWave observer
class WaveBar : public HandleBarDelegate
              , public OscWaveGroupObserver {
public:
  WaveBar(OscWaveGroup* wave_group, YTWaveContainerInnerView* view);
  virtual ~WaveBar();

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

  void AddOtherWave(Wave* wave);
  void RemoveOtherWave(Wave* wave);
  bool HasOtherWave(Wave* wave);

private:
  class OtherWaveVisitor : public WaveVisitor {
  public:
    OtherWaveVisitor(Wave* other_wave, YTWaveContainerInnerView* view);
    virtual ~OtherWaveVisitor() {}

    int GetOffset();
    void MoveToY(int offset);

  private:
    enum VisitorType {
      kOffset,
      kMoveToY,
    };

    // implement WaveVisitor
    virtual void VisitOscWave(OscWave* wave) { NOTREACHED(); }
    virtual void VisitSimpleAnaWave(SimpleAnaWave* wave);
    virtual void VisitSimpleDigitWave(SimpleDigitWave* wave) { NOTREACHED(); }

    VisitorType type_;
    int offset_;
    int ret_offset_;
    Wave* other_wave_;
    YTWaveContainerInnerView* view_;

    DISALLOW_COPY_AND_ASSIGN(OtherWaveVisitor);
  };
  
  // implement HandleBarObserver
  virtual void OnHandleMove(int ID, int offset);
  virtual void OnHandleActive(int ID);

  // implement OscWaveGroupObserver
  virtual void OnPartGroupChanged() { NotifyModelChanged(); }
  virtual void OnPartChanged(int id) { NotifyHandleChanged(id); }
  virtual void OnPartMoved(int id){ NotifyHandleMoved(id); }

  OscWaveGroup* wave_group_;
  YTWaveContainerInnerView* view_;

  std::vector<Wave*> other_wave_;

  DISALLOW_COPY_AND_ASSIGN(WaveBar);
};

WaveBar::OtherWaveVisitor::OtherWaveVisitor(Wave* other_wave, 
                                            YTWaveContainerInnerView* view) 
  : other_wave_(other_wave)
  , view_(view) {

}

void WaveBar::OtherWaveVisitor::VisitSimpleAnaWave(SimpleAnaWave* wave){
  if (type_ == kOffset) {
    ret_offset_ = view_->GetYOffset(wave);
  } else if (type_ == kMoveToY) {
    view_->MoveToY(wave, offset_);
  } else {
    NOTREACHED();
  }
}

int WaveBar::OtherWaveVisitor::GetOffset() {
  type_ = kOffset;
  other_wave_->Accept(this);
  return ret_offset_;
}

void WaveBar::OtherWaveVisitor::MoveToY(int offset) {
  type_ = kMoveToY;
  offset_ = offset;
  other_wave_->Accept(this);
}

WaveBar::WaveBar(OscWaveGroup* wave_group, YTWaveContainerInnerView* view)
    : wave_group_(wave_group)
    , view_(view) {
  wave_group->AddVerticalObserver(this);
}

WaveBar::~WaveBar() {
  wave_group_->RemoveVerticalObserver(this);
}

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
    ui::Transform transform = view_->OscWaveTransform(wave);
    return TransformY(transform, 0);
  } else {
    int index = ID - wave_group_->vertical_count();
    OtherWaveVisitor visitor(other_wave_[index], view_);
    return visitor.GetOffset();
  }
}

void WaveBar::OnHandleMove(int ID, int offset) {
  if (ID < wave_group_->vertical_count()) {
    OscWave* wave = wave_group_->horizontal_at(ID)->osc_wave();
    ui::Transform transform = view_->OscWaveTransform(wave);
    int logic_offset = TransformReverseY(transform, offset);
    double old_offset = wave->vertical_offset();
    wave->MoveToY(YTWaveContainerInnerView::ToOscOffset(old_offset, logic_offset));
  } else {
    int index = ID - wave_group_->vertical_count();
    OtherWaveVisitor visitor(other_wave_[index], view_);
    return visitor.MoveToY(offset);
  }
}

void WaveBar::OnHandleActive(int ID) {
  if (ID < wave_group_->vertical_count()) {
    view_->SelectWave(wave_group_->vertical_at(ID)->osc_wave());
  } else {
    int index = ID - wave_group_->vertical_count();
    view_->SelectWave(other_wave_[index]);
  }
}
void WaveBar::AddOtherWave(Wave* wave) {
  DCHECK(!HasOtherWave(wave));
  other_wave_.push_back(wave);
  NotifyModelChanged();
}

void WaveBar::RemoveOtherWave(Wave* wave) {
  vector<Wave*>::iterator it = find(other_wave_.begin(), other_wave_.end(), wave);
  DCHECK(it != other_wave_.end());
  other_wave_.erase(it);
  NotifyModelChanged();
}

bool WaveBar::HasOtherWave(Wave* wave) {
  for (size_t i = 0; i < other_wave_.size(); ++i) {
    if (other_wave_[i] == wave) {
      return true;
    }
  }
  return false;
}

class YTWaveVisitor : public WaveVisitor {
public:
  YTWaveVisitor(YTWaveContainerInnerView* view);
  virtual ~YTWaveVisitor() {}

  void AddWave(Wave* wave);
  void RemoveWave(Wave* wave);
  void SetAxis(Wave* wave);

private:
  enum VisitorType {
    kAddWave,
    kRemoveWave,
    kSetAxis,
  };

  // implement WaveVisitor
  virtual void VisitOscWave(OscWave* wave);
  virtual void VisitSimpleAnaWave(SimpleAnaWave* wave);
  virtual void VisitSimpleDigitWave(SimpleDigitWave* wave) { NOTREACHED(); }

  VisitorType type_;
  YTWaveContainerInnerView* view_;

  DISALLOW_COPY_AND_ASSIGN(YTWaveVisitor);
};

YTWaveVisitor::YTWaveVisitor(YTWaveContainerInnerView* view)
    : view_(view) {

}

void YTWaveVisitor::AddWave(Wave* wave) {
  type_ = kAddWave;
  wave->Accept(this);
}

void YTWaveVisitor::RemoveWave(Wave* wave) {
  type_ = kRemoveWave;
  wave->Accept(this);
}

void YTWaveVisitor::VisitOscWave(OscWave* wave) {
  if (type_ == kAddWave) {
    view_->wave_group_->AddOscWave(wave);
  } else if (type_ == kRemoveWave) {
    view_->wave_group_->RemoveOscWave(wave);
  } else if (type_ == kSetAxis) {
    int v_div = wave->vertical_div() / 2;
    int h_div = wave->horizontal_div() / 2;
    view_->SetGrid(v_div, h_div);
  } else {
    NOTREACHED();
  }
}

void YTWaveVisitor::VisitSimpleAnaWave(SimpleAnaWave* wave) {
  if (type_ == kAddWave) {
    view_->wave_bar_->AddOtherWave(wave);
  } else if (type_ == kRemoveWave) {
    view_->wave_bar_->RemoveOtherWave(wave);
  } else if (type_ == kSetAxis) {
    // use last axis config.
  } else {
    NOTREACHED();
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

YTWaveContainerInnerView::YTWaveContainerInnerView(YTWaveContainer* container)
    : container_(container) {
  wave_group_.reset(container_->CreateOscWaveGroup());
  wave_bar_.reset(new WaveBar(wave_group_.get(), this));
  horiz_offset_bar_.reset(new HorizOffsetBar(wave_group_.get(), this));
  trigger_bar_.reset(new TriggerBar(wave_group_.get(), this));

  container->AddObserver(this);
  // fetch Wave
  ListItemsAdded(0, container->item_count());

  set_border(Border::CreateSolidBorder(kBorderThickness, kBorderColor));
  SetGrid(kDefaultVDiv, kDefaultHDiv);
}

YTWaveContainerInnerView::~YTWaveContainerInnerView() {
  container_->RemoveObserver(this);

  trigger_bar_.reset();
  horiz_offset_bar_.reset();
  wave_bar_.reset();
  wave_group_.reset();
}

// static
double YTWaveContainerInnerView::ToOscOffset(double old_offset, double move_delta) {
  return old_offset + (-move_delta);
}

int YTWaveContainerInnerView::GetYOffset(SimpleAnaWave* wave) {
  WaveRange range = wave->vertical_range();
  Transform transform = SimpleAnaWaveTransform(wave);
  return TransformY(transform, (range.begin + range.end) / 2);
}

void YTWaveContainerInnerView::MoveToY(SimpleAnaWave* wave, double offset) {
  Transform transform = SimpleAnaWaveTransform(wave);
  int logic_offset = TransformReverseY(transform, offset);
  WaveRange range = wave->vertical_range();
  range.MoveCenter(logic_offset);
  wave->set_vertical_offset(offset);
}

void YTWaveContainerInnerView::ListItemsAdded(size_t start, size_t count) {
  YTWaveVisitor visitor(this);

  wave_record_.reserve(container_->item_count());
  for (size_t i = 0; i < count; ++i) {
    Wave* wave = container_->GetItemAt(start + i);
    View* view = WaveControlViewFactory::GetInstance()->Create(wave, 
        static_cast<YTWaveContainerView*>(this->parent()));
    this->AddChildViewAt(view, start + i);
    wave_record_.insert(wave_record_.begin() + start + i, wave);

    // notify add wave
    visitor.AddWave(wave);
  }
  if (start == 0) {
    UpdateAxis();
  }
}

void YTWaveContainerInnerView::ListItemsRemoved(size_t start, size_t count) {
  YTWaveVisitor visitor(this);
  vector<Wave*> need_remove_wave;
  View::Views need_remove;
  need_remove.reserve(count);
  for (size_t i = 0; i < count; ++i) {
    need_remove.push_back(this->child_at(start + i));
    need_remove_wave.push_back(wave_record_[start]);
    wave_record_.erase(wave_record_.begin() + start);
  }
  for (size_t i = 0; i < need_remove.size(); ++i) {
    this->RemoveChildView(need_remove[i]);
    // notify remove wave
    visitor.RemoveWave(need_remove_wave[i]);  
    delete need_remove[i];
  }
  if (start == 0) {
    UpdateAxis();
  }
}

void YTWaveContainerInnerView::ListItemMoved(size_t index, size_t target_index) {
  this->ReorderChildView(this->child_at(index), target_index);
  Wave* wave = wave_record_[index];
  wave_record_.erase(wave_record_.begin() + index);
  wave_record_.insert(wave_record_.begin() + target_index, wave);

  if (target_index == 0 || index == 0) {
    UpdateAxis();
  }
}

void YTWaveContainerInnerView::ListItemsChanged(size_t start, size_t count) {
  ListItemsRemoved(start, count);
  ListItemsAdded(start, count);

  if (start == 0) {
    UpdateAxis();
  }
}

ui::Transform YTWaveContainerInnerView::OscWaveTransform(OscWave* osc_wave) {
  int id = container_->WaveAt(osc_wave);
  OscWaveView* wave_view = static_cast<OscWaveView*>(child_at(id));
  return wave_view->data_transform();
}

HandleBarDelegate* YTWaveContainerInnerView::GetWaveBarDelegate() {
  return wave_bar_.get();
}

HandleBarDelegate* YTWaveContainerInnerView::GetHorizOffsetBarDelegate() {
  return horiz_offset_bar_.get();
}

HandleBarDelegate* YTWaveContainerInnerView::GetTriggerBarDelegate() {
  return trigger_bar_.get();
}

bool YTWaveContainerInnerView::NormalSize(gfx::Size& size) {
  // keep space for the border
  size.Enlarge(-GetInsets().width(), -GetInsets().height());
  if (get_axis_background()->NormalSize(size)) {
    size.Enlarge(GetInsets().width(), GetInsets().height());
    return true;
  }
  return false;
}

int YTWaveContainerInnerView::BorderThickness() {
  return kBorderThickness;
}

AxisBackground* YTWaveContainerInnerView::get_axis_background() {
  Background* bg = background();
  DCHECK(bg) << "no background exist";
  return static_cast<AxisBackground*>(bg);
}

gfx::Size YTWaveContainerInnerView::GetMinimumSize() {
  gfx::Size size = get_axis_background()->GetMinimumSize();
  size.Enlarge(GetInsets().width(), GetInsets().height());
  return size;
}

void YTWaveContainerInnerView::SetGrid(int v_grid, int h_grid) {
  set_background(
    new AxisBackground(kWaveViewBackgroundColor, kAxisLineColor, 
                       kLineWidth, 
                       kAxisGridColor, 
                       v_grid, kVGridDiv, 
                       h_grid, kHGridDiv));
  SchedulePaint();
}

void YTWaveContainerInnerView::UpdateAxis() {
  Wave* wave = container_->GetSelectWave();
  YTWaveVisitor visitor(this);
  visitor.SetAxis(wave);
}

