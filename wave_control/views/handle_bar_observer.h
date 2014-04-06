#pragma once

// HandleBarObserver is notified about the HandleBar change.
class HandleBarObserver {
public:
  // Invoked when the Handle is be draged and move.
  virtual void OnHandleMove(int ID, int offset) = 0;

  // Invoked when the Handle be clicked.
  virtual void OnHandleActive(int ID) = 0;

protected:
  virtual ~HandleBarObserver() {}
};
