#pragma once

// Observer of a HandleBarModel. Anytime the model changes, it must notify its
// observer.
class HandleBarModelObserver {
public:
  // Invoked when the model has been completely changed. need to read all handle
  // information.
  virtual void OnModelChanged() = 0;

  // Invoked when a handle has changed. need to read the text, icon, offset.
  virtual void OnHandleChanged(int ID) = 0;

  // Invoked When a handle move position. only need to read the offset.
  virtual void OnHandleMoved(int ID) = 0;

protected:
  virtual ~HandleBarModelObserver() {}
};

