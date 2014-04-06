#include "wave_control/wave_group/common_wave_group.h"

namespace {

bool IsSet(int set, int test) {
  return (set & test) != 0;
}

}

void CommonWaveGroup::AddOscWave(OscWave* osc_wave) {
  DCHECK(osc_wave);

  bool create_trigger = true;
  bool create_horizontal = true;
  bool create_vertical = true;
  OscWaveRecord target_record;
  target_record.wave = osc_wave;

  for (size_t i = 0; i < osc_waves_.size(); ++i) {
    OscWaveRecord& record = osc_waves_[i];
    if (record.wave == osc_wave) {
      NOTREACHED();
    }
    if (target_record.trigger.get() == NULL) {
      if (record.wave->IsSameTrigger(osc_wave)) {
        create_trigger = false;
        target_record.trigger = record.trigger;
      }
    }
    if (target_record.horizontal.get() == NULL) {
      if (record.wave->IsSameHorizontal(osc_wave)) {
        create_horizontal = false;
        target_record.horizontal = record.horizontal;
      }
    }
    if (target_record.vertical.get() == NULL) {
      if (record.wave->IsSameVertical(osc_wave)) {
        create_vertical = false;
        target_record.vertical = record.vertical;
      }
    }
  }
 
  if (create_trigger) {
    RefTriggerPart* trigger = new RefTriggerPart(osc_wave, this);
    triggers_.push_back(trigger);
    target_record.trigger = trigger;
  }
  if (create_horizontal) {
    RefHorizontalPart* horizontal = new RefHorizontalPart(osc_wave, this);
    horizontals_.push_back(horizontal);
    target_record.horizontal = horizontal;
  }
  if (create_vertical) {
    RefVerticalPart* vertical = new RefVerticalPart(osc_wave, this);
    verticals_.push_back(vertical);
    target_record.vertical = vertical;
  }

  osc_wave->AddObserver(this);
  osc_waves_.push_back(target_record);

  if (create_trigger) {
    NotifyTriggerGroupChanged();
  }
  if (create_horizontal) {
    NotifyHorizontalGroupChanged();
  }
  if (create_vertical) {
    NotifyVerticalGroupChanged();
  }
}

void CommonWaveGroup::RemoveOscWave(OscWave* osc_wave) {
  DCHECK(osc_wave);
  trigger_changed_ = false;
  horizontal_changed_ = false;
  vertical_changed_ = false;
  for (size_t i = 0; i < osc_waves_.size(); ++i) {
    OscWaveRecord& record = osc_waves_[i];
    if (record.wave == osc_wave) {
      osc_wave->RemoveObserver(this);
      osc_waves_.erase(osc_waves_.begin() + i);
      break;
    }
    if (i == osc_waves_.size() - 1) {
      NOTREACHED();
    }
  }
  if (trigger_changed_) {
    NotifyTriggerGroupChanged();
  }
  if (horizontal_changed_) {
    NotifyHorizontalGroupChanged();
  }
  if (vertical_changed_) {
    NotifyVerticalGroupChanged();
  }
}

bool CommonWaveGroup::HasOscWave(OscWave* osc_wave) {
  for (size_t i = 0; i < osc_waves_.size(); ++i) {
    OscWaveRecord& record = osc_waves_[i];
    if (record.wave == osc_wave) {
      return true;
    }
  }
  return false;
}

void CommonWaveGroup::OnTriggerDelete(TriggerPart* tirgger) {
  Triggers::iterator it = find(triggers_.begin(), triggers_.end(), trigger);
  DCHECK(it != triggers_.end());
  triggers_.erase(it);
  trigger_changed_ = true;
}

void CommonWaveGroup::AddSimpleAnaWave(SimpleAnaWave* ana_wave) {
  DCHECK(ana_wave);

  for (size_t i = 0; i < simple_ana_waves_.size(); ++i) {
    SimpleAnaWaveRecord& record = simple_ana_waves_[i];
    if (record.wave == ana_wave) {
      NOTREACHED();
    }
  }
  SimpleVerticalPart* vertical = new SimpleVerticalPart();
  SimpleAnaWaveRecord record;
  record.wave = ana_wave;
  record.vertical = vertical;

  simple_ana_waves_.push_back(record);
  verticals_.push_back(vertical);
  
  NotifyHorizontalGroupChanged();
}

void CommonWaveGroup::RemoveSimpleAnaWave(SimpleAnaWave* ana_wave) {
  DCHECK(ana_wave);

  SimpleAnaWaveRecord record;
  for (size_t i = 0; i < simple_ana_waves_.size(); ++i) {
    record = simple_ana_waves_[i];
    if (record.wave == ana_wave) {
      simple_ana_waves_.erase(simple_ana_waves_.begin() + i);
      break;
    }
    if (i == simple_ana_waves_.size() -1) {
      NOTREACHED();
    }
  }
  Verticals::iterator it = find(verticals_.begin(), verticals_.end(), record.vertical);
  DCHECK(it != verticals_.end());
  verticals_.erase(it);
  delete record.vertical;

  NotifyVerticalGroupChanged();
}

void CommonWaveGroup::OnOscWaveChanged(OscWave* osc_wave, int change_set) {
  OscWaveRecord& record = GetOscWaveRecord(osc_wave);

  if (IsSet(change_set, OscWave::kTrigger)) {
    NotifyTriggerChanged(TriggerIndex(record.trigger.get()));
  }
  if (IsSet(change_set, OscWave::kTriggerOffset)) {
    NotifyTriggerMoved(TriggerIndex(record.trigger.get()));
  }
  if (IsSet(change_set, OscWave::kHorizontal)) {
    NotifyHorizontalChanged(HorizontalIndex(record.horizontal.get()));
  }
  if (IsSet(change_set, OscWave::kHorizontalOffset)) {
    NotifyHorizontalMoved(HorizontalIndex(record.horizontal.get()));
  }
  if (IsSet(change_set, OscWave::kVertical)) {
    NotifyVerticalChanged(VerticalIndex(record.vertical.get()));
  }
  if (IsSet(change_set, OscWave::kVerticalOffset)) {
    NotifyVerticalMoved(VerticalIndex(record.vertical.get()));
  }
}

OscWaveRecord& CommonWaveGroup::GetOscWaveRecord(OscWave* osc_wave) {
  for (size_t i = 0; i < osc_waves_.size(); ++i) {
    OscWaveRecord& record = osc_waves_[i];
    if (record.wave == osc_wave) {
      return record;
    }
  }
  NOTREACHED();
}

int CommonWaveGroup::TriggerIndex(TriggerPart* part) {
  for (size_t i = 0; i < triggers_.size(); ++i) {
    if (triggers_[i] == part) {
      return i;
    }
  }
  NOTREACHED();
}

// RefTriggerPart

SkColor RefTriggerPart::color() {
  return osc_wave_->trigger_color();
}

bool RefTriggerPart::show() {
  return osc_wave_->trigger_show();
}

WaveRange RefTriggerPart::offset_range() {
  return osc_wave_->trigger_offset_range();
}

double RefTriggerPart::offset() {
  return osc_wave_->trigger_offset();
}

void RefTriggerPart::set_offset(double offset) {
  osc_wave_->MoveTrigger(offset);
}

bool RefTriggerPart::IsRelate() {
  return osc_wave_->trigger_is_relate();
}

RefTriggerPart::RefTriggerPart(OscWave* osc_wave, CommonWaveGroup* wave_group)
    : osc_wave_(osc_wave)
    , wave_group_(wave_group) {
  DCHECK(osc_wave);
  DCHECK(wave_group);
}

RefTriggerPart::~RefTriggerPart() {
  wave_group_->OnTriggerDelete(this);
}

// RefHorizontalPart
SkColor RefHorizontalPart::color() {
  return osc_wave_->horizontal_color();
}

bool RefHorizontalPart::show() {
  return osc_wave_->horizontal_show();
}

WaveRange RefHorizontalPart::range() {
  return osc_wave_->horizontal_range();
}

WaveRange RefHorizontalPart::offset_range() {
  return osc_wave_->horizontal_offset_range();
}

double RefHorizontalPart::offset() {
  return osc_wave_->horizontal_offset();
}

int RefHorizontalPart::div() {
  return osc_wave_->horizontal_div();
}

int RefHorizontalPart::window_size() {
  return osc_wave_->horizontal_window_size();
}

RefHorizontalPart::RefHorizontalPart(OscWave* osc_wave, CommonWaveGroup* wave_group)
    : osc_wave_(osc_wave)
    , wave_group_(wave_group) {
  DCHECK(osc_wave);
  DCHECK(wave_group);
}

RefHorizontalPart::~RefHorizontalPart() {
  wave_group_->OnHorizontalDelete(this);
}

// RefVerticalPart
SkColor RefVerticalPart::color() {
  return osc_wave_->vertical_color();
}

bool RefVerticalPart::show() {
  return osc_wave_->vertical_show();
}

WaveRange RefVerticalPart::range() {
  return osc_wave_->vertical_range();
}

WaveRange RefVerticalPart::offset_range() {
  return osc_wave_->vertical_offset_range();
}

double RefVerticalPart::offset() {
  return osc_wave_->vertical_offset();
}

int RefVerticalPart::div() {
  return osc_wave_->vertical_div();
}

int RefVerticalPart::window_size() {
  return osc_wave_->vertical_window_size();
}

RefVerticalPart::RefVerticalPart(OscWave* osc_wave, CommonWaveGroup* wave_group)
    : osc_wave_(osc_wave)
    , wave_group_(wave_group) {
  DCHECK(osc_wave);
  DCHECK(wave_group);
}

RefVerticalPart::~RefVerticalPart() {
  wave_group_->OnVerticalDelete(this);
}

SkColor SimpleVerticalPart::color() {
  return ana_wave_->color();
}

bool SimpleVerticalPart::show() {
  return true;
}

WaveRange SimpleVerticalPart::range() {
  return ana_wave_->vertical_range();
}

WaveRange SimpleVerticalPart::offset_range() {
  return ana_wave_->vertical_range(); 
}

double SimpleVerticalPart::offset() {
  return ana_wave_->vertical_offset();
}


bool SimpleVerticalPart::has_div() {
  return false;
}

int SimpleVerticalPart::div() {
  NOTREACHED();
  return 0;
}

int SimpleVerticalPart::window_size() {
  NOTREACHED();
  return 0;
}
