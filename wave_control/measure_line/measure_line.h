#pragma once

class SingleLine;
class DualLine;

class MeasureLine {
public:
  class Part {
  public:
    bool moveable();
    string name();
    SkColor color();
    // line_style();

    double pos();
    void set_pos(double pos);

    bool has_info();
    double info_pos();
    string16 info();

    bool is_horiz();

  private:
  };

  // RTTI
  virtual SingleLine* AsSingleLine() { return NULL; }
  virtual DualLine* AsDualLine() { return NULL; }

  void set_wave(Wave* wave);

  bool valid();
  string16 name();

protected:

private:

};