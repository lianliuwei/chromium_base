class WaveView {
 public:
  
  // Wave state observer
  DataChanged();
  // notify property change. wave fetch change.
  PropertyChanged(int id);

  // WaveView need to delete itself. in Drag&Drop may delete later.
  // using for 
  NeedDelete();

  // respond to Delete itself and wave. for 
  NeedDeleteWithWave();
 protected:
   // 
   Wave* wave_;
 private:
   
};
