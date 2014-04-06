#pragma once

#include "wave_control/wave_group/wave_group.h"

class CommonWaveGroup;

class RefTriggerPart : public base::RefCounted<RefTriggerPart>
                     , public TriggerPart {
public:
  RefTriggerPart(OscWave* osc_wave, CommonWaveGroup* wave_group);

  // implement TriggerPart
  virtual SkColor color();
  virtual bool show();
  virtual WaveRange offset_range();
  virtual double offset();
  virtual void set_offset(double offset);
  virtual bool IsRelate();


private:
  ~RefTriggerPart();

  OscWave* osc_wave_;

  // notify delete
  CommonWaveGroup* wave_group_;
};

class RefHorizontalPart : public base::RefCounted<RefHorizontalPart>
                        , public HorizontalPart {
public:
  RefHorizontalPart(OscWave* osc_wave, CommonWaveGroup* wave_group);

  // implement HorizontalPart
  virtual SkColor color();
  virtual bool show();
  virtual WaveRange range();
  virtual WaveRange offset_range();
  virtual double offset();
  virtual int div();
  virtual int window_size();

private:
  ~RefHorizontalPart();

  OscWave* osc_wave_;

  // notify delete
  CommonWaveGroup* wave_group_;
};

class RefVerticalPart : public base::RefCounted<RefVerticalPart>
                      , public VerticalPart {
public:
  RefVerticalPart(OscWave* osc_wave, CommonWaveGroup* wave_group);

  // implement VerticalPart
  virtual SkColor color();
  virtual bool show();
  virtual WaveRange range();
  virtual WaveRange offset_range();
  virtual double offset();
  virtual int div();
  virtual int window_size();

private:
  ~RefVerticalPart();

  OscWave* osc_wave_;

  // notify delete
  CommonWaveGroup* wave_group_;  
};

class SimpleVerticalPart : public VerticalPart {
public:
  SimpleVerticalPart(SimpleAnaWave* ana_wave);

  // implement VerticalPart
  virtual SkColor color();
  virtual bool show();
  virtual WaveRange range();
  virtual WaveRange offset_range();
  virtual double offset();
  virtual bool has_div();
  virtual int div();
  virtual int window_size();
 
private:
  SimpleAnaWave* ana_wave_;
};

struct OscWaveRecord {
  OscWave* wave;
  scoped_refptr<RefTriggerPart> trigger;
  scoped_refptr<RefHorizontalPart> horizontal;
  scoped_refptr<RefVerticalPart> vertical;
};

// SimpleAnaWave only have vertical part to select and move wave
struct SimpleAnaWaveRecord {
  SimpleAnaWave* wave;
  SimpleVerticalPart* vertical;
};

class CommonWaveGroup : public WaveGroup
                      , public OscWaveObserver {
public:
  // implement WaveGroup
  virtual void AddOscWave(OscWave* osc_wave);
  virtual void RemoveOscWave(OscWave* osc_wave);
  virtual bool HasOscWave(OscWave* osc_wave);

  virtual void AddSimpleAnaWave(SimpleAnaWave* ana_wave);
  virtual void RemoveSimpleAnaWave(SimpleAnaWave* ana_wave);

private:
  friend class RefTriggerPart;
  friend class RefHorizontalPart;
  friend class RefVerticalPart;

  // implement OscWaveObserver
  virtual void OnOscWaveChanged(OscWave* osc_wave, int change_set);

  void OnTriggerDelete(TriggerPart* tirgger);
  void OnHorizontalDelete(HorizontalPart* horizontal);
  void OnVerticalDelete(VerticalPart* vertical);

  OscWaveRecord& GetOscWaveRecord(OscWave* osc_wave);
  
  int TriggerIndex(TriggerPart* part);
  int HorizontalIndex(HorizontalPart* part);
  int VerticalIndex(VerticalPart* part);

  std::vector<OscWaveRecord> osc_waves_;
  std::vector<SimpleAnaWaveRecord> simple_ana_waves_;

  bool trigger_changed_;
  bool horizontal_changed_;
  bool vertical_changed_;
};