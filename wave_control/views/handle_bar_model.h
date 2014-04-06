#pragma once

#include "base/string16.h"

class HandleBarModelObserver;

// the model driving the HandleBar.
class HandleBarModel {
public:
  // number of handle in the model
  virtual int Count() = 0;

  // using the Count() to get the max index and iterate to get each ID
  // the ID is the only way to get the resource of each handle.
  virtual int GetID(int index) = 0;

  // return the value of a particular ID.
  virtual string16 GetText(int ID) = 0;

  // return the Value of a particular ID. to support the runtime change color.
  virtual SkColor GetColor(int ID) = 0;

  // return the Icon that can be displayed in the handleBar. HandleBar have
  // mode of how to displayed the Text and Icon, may be Text only, Icon only,
  // Text and Icon.
  // TODO can using gfx/image replace?
  virtual SkBitmap GetIcon(int ID) = 0;

  // get the offset of the Handle, the handle is to represent the offset of the
  // a specific range in pixel. the Icon and Text offset to the offset is 
  // set by call the HandleBar.
  virtual int GetOffset(int ID) = 0;

  // return if the handle could be move
  virtual bool IsEnable(int ID) = 0;

  // return if the handle could be see
  virtual bool IsVisible(int ID) = 0;

  // set the observer for the model. The HandleBarModel should NOT take ownership
  // of the observer.
  virtual void AddObserver(HandleBarModelObserver* observer) = 0;
  virtual void RemoveObserver(HandleBarModelObserver* observer) = 0;
  virtual bool HasObserver(HandleBarModelObserver* observer) = 0;
  
protected:
  virtual ~HandleBarModel() {};
};
