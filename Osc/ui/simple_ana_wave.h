struct PeakValue {
  double start;
  double end;
  double max;
  double min;
};

class SimpleWaveData {
public:
  Range data_range;
  vector<double> data;

  // offset is in logic coord.
  double GetValue(double offset);
  PeakValue GetRangePeak(double start, double offset);
  MaxY();
  MinY();
  MaxX();
  MinX();
};
class SimpleWaveDelegate {
public:

};

enum AnaWaveShowStyle {
  
};

class SimpleAnaWave : public Wave {
public:
  SimpleWaveData& Data();

  // command
  // for do FFT.
  DoRangeCommand(int command_id, Range range);
 
  DoCommand(int command_id);

  AsSimpleAnaWave() OVERRIDE;

  
protected:

private:

};
