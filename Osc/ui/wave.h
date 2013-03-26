class Wave {
public:
  name();
  color();
  icon();

  string x_unit();
  string y_unit();

  enum CoordinateType {
    kYT, // Y , time
    kYL, // Y , log X
    kXY,
  };
  CoordinateType Coordinate();
  Range Vercital();
  Range Horizonal();

  // Fix In Screen.
  Fix();
  FixY();
  FixX();

  // RTTI
  OscWave* AsOscWave();
  SimpleAnaWave* AsSimpleAnaWave();
  SimpleDigitWave* AsSimpleDigitWave();

  // create view
  virtual WaveView* CreateView(WaveViewFactory* factory);
  
  // Wave can by own by the WaveView, for animation, for Drag&Drop 
  void NeedDelete();
  bool OwnByWaveView();

  // TODO figure out if necessary for Drag&Drop
  clone();

  // measure line support
  bool SupportXMeasure();
  bool SupportYMeasure();
  // for X measure
  double GetValue(double offset);
protected:

private:

};
