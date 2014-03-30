#pragma once

class WaveGroupObserver {
public:
  // Invoked when the model has been completely changed. need to read all part
  // information.
  virtual void OnPartGroupChanged() = 0;

  // Invoked when a part has changed. need to read the text, icon, offset.
  virtual void OnPartChanged(int ID) = 0;

  // Invoked When a part move position. only need to read the offset.
  virtual void OnPartMoved(int ID) = 0;

protected:
  virtual ~WaveGroupObserver() {}
};

