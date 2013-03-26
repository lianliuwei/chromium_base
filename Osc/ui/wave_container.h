class WaveContainerObserver {
  WaveAdded();
  WaveRemoved();
};

// TODO using ui/base/list_model.h instead.
// Wave container is a vertical list
class WaveContainer : public ListModel<Wave> {
public:
  // Iterator Wave.
  typedef vector<Wave>::iterator WaveIterator;

  // Wave Manage
  // CreateSimpleWave(string wave_name);
  AddWave(Wave* wave);
  RemoveWave(Wave* wave);
  
  MoveWave(Wave* wave, int index);
  // move Waves, can add some animation here.
  MoveWaves(vector<Wave*> wave, int index);
  
  SelectWave(Wave* wave);
  IsWaveSelect(Wave* wave);

  Wave* Find(String name);

  // Wave show Manage
  enum YAxesShowType {
    kAllYAxes,
    kSeparateYAxes,
    kAlternateYAxes,
  };

  YAxesShowType YAxes();

  FitAllWave();
  FitAllWaveY();

  // move to impl the need.
  //// show option
  //ShowGrid();
  //ToggleGrid();
  //bool IsShowGrid();
  //
  //ShowSample();
  //ToggleSample();
  //bool IsShowSample();

  // menu
  MenuModel& GetMenuModel();
  MenuModel& GetToolBarModel();

  // measure line
  AddMeasureLine(Wave* wave, MeasureLine* measure);
  RemoveMeasureLine();
  vector<MeasureLine*> GetMeasureLineForWave(Wave* wave);
  MoveMeasureLine(Wave* wave);
protected:

private:
  vector<Wave> wave_vector_;

  MeasureLineContainer measure_lines_;
};
