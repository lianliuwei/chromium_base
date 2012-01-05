#ifndef OSC_UI_VIEW_HANDLE_BAR_H_
#define OSC_UI_VIEW_HANDLE_BAR_H_
#pragma once

#include <vector>
#include "Osc/ui/views/handle_bar_model_observer.h"
#include "Osc/ui/views/handle.h"

class HandleBarModel;
class HandleBarObserver;

// have n Handle, the user can drag and move handle. the HandleBar notify the 
// HandleBarModel when the handle pos change. now the middle of the handle 
// represent the offset.
class HandleBar : public views::View
                , public HandleBarModelObserver {
public:
  HandleBar(HandleBarModel* model, bool is_horiz, gfx::Font font,
            SkColor color, int start, int end);
  // the views delete handle auto
  virtual ~HandleBar() {};

  bool IsHorizontal() const;

  void SetModel(HandleBarModel* model);
  HandleBarModel* model() const {
    return model_;
  }

  void SetObserver(HandleBarObserver* observer) {
    observer_ = observer;
  }
  HandleBarObserver* observer() const {
    return observer_;
  }

  // put the Active Handle on the Top
  void ActiveHandle(int ID);

  // the Handle call this method to set it's offset. the handle must no set
  // the offset by itself, the model may be restrict the offset for some 
  // reason.
  // dest is the x or y the Handle need to be.
  void MoveHandle(int ID, int dest);

  // HandleBarModelObserver methods.
  virtual void OnModelChanged();
  virtual void OnHandleChanged(int ID);
  virtual void OnHandleMoved(int ID);

  // set the move range of the Handle if Handle outside of the Range show
  // indicate. 
  void SetMoveRange(int start, int end);

  void SetFont(const gfx::Font& font);
  // Return the font used by this button.
  gfx::Font font() const {
    return font_;
  }

  void SetColor(SkColor color);
  SkColor color() const {
    return color_;
  }

protected:
  // reset the HandleBar and using the model to create Handles.
  virtual void UpdateFromModel();

  // subclass can use for replace the default Create Handle method
  virtual void UpdateHandle(int ID);

  // only reset the pos of the handle
  virtual void UpdateHandlePos(int ID);

  virtual Handle* GetHandle(int ID) const;

  // ui:views methods
  virtual void OnPaint(gfx::Canvas* canvas) OVERRIDE;

  // from the handle dest arg to the offset set to model
  virtual int CalculateOffset(int dest, int width) const;

  // from the offset to the pos of Handle
  virtual int CalculateDest(int offset, int width) const;

private:
  // set the handle correct, the handle is subclass from the textBotton, need to 
  // set the three type icon, any many color.
  void SetHandle(Handle* handle, int ID);

  void SetHandlePos(Handle* handle, int ID);

private:
  const bool is_horiz_;

  std::vector<Handle*> handles_;

  HandleBarObserver* observer_;

  HandleBarModel* model_;

  gfx::Font font_;

  SkColor color_;

  // the start_ and end_ is set by the SetMoveRange. the start_ is less than the
  // end_ the start_ is the point of the offset zero. start_ is using to calculate
  // the offset.
  int start_;

  int end_;

  DISALLOW_COPY_AND_ASSIGN(HandleBar);
};

#endif // OSC_UI_VIEW_HANDLE_BAR_H_
