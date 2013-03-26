class WaveViewFactory {
 public:
  // create view
  virtual WaveView* CreateView(OscWave* osc_wave);
  virtual WaveView* CreateView(SimpleAnaWave* osc_wave);
  virtual WaveView* CreateView(SimpleDigitWave* osc_wave);
 protected:
  
 private:
  WaveContainer* container;
};
