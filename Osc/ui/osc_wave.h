class OscWaveDelegate {
};

// impl details.
// TODO move to impl, no in interface head file.
struct OscRange : public RefCounted<OscRange> {
  Range range;
  int div;
  String name;
  Range offset_range;
  double offset;
};

class Trigger : public RefCounted<Trigger> {
public:
  Color color();

  Range offset_range();
  double offset();
  bool show();
  // Relate to Y or no.
  bool IsRelate();
};


// used ptr to find if two option is the some.
// TODO whether compare() can replace trigger and Osc Range.
class OscWave : public Wave {
public:
  // map to osc hardware operate.
  MoveToX();
  MoveToY();
  ZoomInX();
  ZoomOutX();
  ZoomInY();
  ZoomOutY();

  // hardware property.

  bool IsSameTrigger(OscWave* osc_wave);
  Range trigger_offset_range();
  double trigger_offset();
  bool trigger_show();
  bool trigger_is_relate();

  bool IsSameVertical(OscWave* osc_wave);
  Range vertical_range();
  Range vertical_offset_range();
  double vertical_offset();

  bool IsSameHorizonal(OscWave* osc_wave);
  OscRange* horizonal_property();
  OscRange horizonal_range();
  Range horizonal_offset_range();
  double horizon_offset();
  
  // using this to optimize the wave draw.
  enum UpdateType {
    kTrigger,
    kAll,
  };
  DataUpdate();
  PropertyChange();

  // command
  // for do FFT.
  DoRangeCommand(int command_id, Range range);

  DoCommand(int command_id);

  OscWave* AsOscWave() OVERRIDE;


private:

};
