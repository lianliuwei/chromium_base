#pragma once

#include "wave_control/osc_wave_group/osc_wave_group.h"

class CommonOscWaveGroup;

class RefTriggerPart : public base::RefCounted<RefTriggerPart>
                     , public TriggerPart {
public:
  RefTriggerPart(OscWave* osc_wave, CommonOscWaveGroup* wave_group);

  // implement TriggerPart
  virtual SkColor color();
  virtual bool show();
  virtual string16 text();
  virtual SkBitmap icon();
  virtual WaveRange offset_range();
  virtual double offset();
  virtual void set_offset(double offset);
  virtual bool IsRelate();
  virtual OscWave* trigger_wave();
  virtual OscWave* osc_wave() { return osc_wave_; }

private:
  friend class base::RefCounted<RefTriggerPart>;
  ~RefTriggerPart();

  OscWave* osc_wave_;

  // notify delete
  CommonOscWaveGroup* wave_group_;
};

class RefHorizontalPart : public base::RefCounted<RefHorizontalPart>
                        , public HorizontalPart {
public:
  RefHorizontalPart(OscWave* osc_wave, CommonOscWaveGroup* wave_group);

  // implement HorizontalPart
  virtual SkColor color();
  virtual bool show();
  virtual string16 text();
  virtual SkBitmap icon();
  virtual WaveRange range();
  virtual WaveRange offset_range();
  virtual double offset();
  virtual int div();
  virtual int window_size();
  virtual OscWave* osc_wave() { return osc_wave_; }

private:
  friend class base::RefCounted<RefHorizontalPart>;
  ~RefHorizontalPart();

  OscWave* osc_wave_;

  // notify delete
  CommonOscWaveGroup* wave_group_;
};

class RefVerticalPart : public base::RefCounted<RefVerticalPart>
                      , public VerticalPart {
public:
  RefVerticalPart(OscWave* osc_wave, CommonOscWaveGroup* wave_group);

  // implement VerticalPart
  virtual SkColor color();
  virtual bool show();
  virtual string16 text();
  virtual SkBitmap icon();
  virtual WaveRange range();
  virtual WaveRange offset_range();
  virtual double offset();
  virtual int div();
  virtual int window_size();
  virtual OscWave* osc_wave() { return osc_wave_; }

private:
  friend class base::RefCounted<RefVerticalPart>;
  ~RefVerticalPart();

  OscWave* osc_wave_;

  // notify delete
  CommonOscWaveGroup* wave_group_;  
};

struct OscWaveRecord {
  OscWave* wave;
  scoped_refptr<RefTriggerPart> trigger;
  scoped_refptr<RefHorizontalPart> horizontal;
  scoped_refptr<RefVerticalPart> vertical;
};


class CommonOscWaveGroup : public OscWaveGroup
                         , public OscWaveObserver {
public:
  CommonOscWaveGroup();
  virtual ~CommonOscWaveGroup();

  // implement OscWaveGroup
  virtual void AddOscWave(OscWave* osc_wave);
  virtual void RemoveOscWave(OscWave* osc_wave);
  virtual bool HasOscWave(OscWave* osc_wave);

private:
  friend class RefTriggerPart;
  friend class RefHorizontalPart;
  friend class RefVerticalPart;

  // implement OscWaveObserver
  virtual void OnOscWaveChanged(OscWave* osc_wave, int change_set);

  void OnTriggerDelete(TriggerPart* trigger);
  void OnHorizontalDelete(HorizontalPart* horizontal);
  void OnVerticalDelete(VerticalPart* vertical);

  OscWaveRecord& GetOscWaveRecord(OscWave* osc_wave);
  
  int TriggerIndex(TriggerPart* part);
  int HorizontalIndex(HorizontalPart* part);
  int VerticalIndex(VerticalPart* part);

  std::vector<OscWaveRecord> osc_waves_;

  bool trigger_changed_;
  bool horizontal_changed_;
  bool vertical_changed_;
};