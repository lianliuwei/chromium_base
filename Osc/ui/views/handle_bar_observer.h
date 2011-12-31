#ifndef OSC_UI_VIEW_HANDLE_BAR_OBSERVER_H_
#define OSC_UI_VIEW_HANDLE_BAR_OBSERVER_H_
#pragma once

// HandleBarObserver is notified about the HandleBar change.
class HandleBarObserver {
public:
  // Invoked when the Handle is be draged and move.
  virtual void OnHandleMove(int ID, int offset) = 0;

  // Invoked when the Handle be clicked. if click on handles the in_handles
  // is set to true, and the ID is the click ID. if the click on in any handle
  // the in_handles is false, and the ID is invalid.
  virtual void OnHandleActive(bool in_handles, int ID) = 0;

protected:
  virtual ~HandleBarObserver() {}
};

#endif // OSC_UI_VIEW_HANDLE_BAR_OBSERVER_H_
