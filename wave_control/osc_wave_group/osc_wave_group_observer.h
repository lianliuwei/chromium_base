#pragma once

class OscWaveGroupObserver {
public:
  // Invoked when the model has been completely changed. need to read all part
  // information.
  virtual void OnPartGroupChanged() = 0;

  // Invoked when a part has changed. need to read the text, icon, offset.
  virtual void OnPartChanged(int id) = 0;

  // Invoked When a part move position. only need to read the offset.
  virtual void OnPartMoved(int id) = 0;

protected:
  virtual ~OscWaveGroupObserver() {}
};

