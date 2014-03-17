class MeasureLinePart {
public:
  bool moveable();
  string name();
  color();
  line_style();
  pos();
  set_pos();
protected:

private:

};

class MeasureLineObserver {
 public:
  virtual PosChanged() = 0;  
  virtual WaveChanged() = 0;
  virtual WillDelete() = 0;
 protected:
  
 private:
  
};

class MeasureLine {
public:
  // RTTI
  SingleLine* AsSingleLine(); 
  DualLine* AsDualLine();
  set_wave(Wave* wave);

  virtual CreateView(MeasureLineViewFactory* factory);

  bool valid();
  name();
  bool is_horiz();

protected:

private:

};

// for point measure
// value get from the subclass of wave.
class SingleLine : public MeasureLine {
 public:
  MeasureLinePart& Get();
  double pos();
  void set_pos(double pos);

 protected:
  
 private:
  
};

// for range measure
class DualLine : public MeasureLine {
public:
  MeasureLinePart& From();
  MeasureLinePart& To();
  range();
  From_pos();
  to_pos();
  set_from_pos();
  set_to_pos();

};
