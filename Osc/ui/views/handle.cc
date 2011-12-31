#include "Osc/ui/views/handle.h"

#include "Osc/ui/views/handle_bar.h"

using namespace views;

// model config is set by the handleBar
Handle::Handle(HandleBar* bar)
  : TextButton(NULL, L"")
  , mouse_offset_(-1)
  , bar_(bar) {
  DCHECK(bar_) << "the Handle need HandleBar object.";
}

bool Handle::OnMousePressed(const views::MouseEvent& event) {
  bool ret = TextButton::OnMousePressed(event);
  mouse_offset_ = bar_->IsHorizontal() ? event.x() : event.y();
  bar_->ActiveHandle(tag());
  return ret;
}

bool Handle::OnMouseDragged(const MouseEvent& event) {
  // notify the bar_ to move the handle. the bar_ calculate the handle represent
  // offset and set the model, model set the offset by it's rule(for example only odd)
  // model notify the handleBar to update, finish the handle be moved.
  if (bar_->IsHorizontal()) {
    int handle_x = x() + event.x() - mouse_offset_;
    bar_->MoveHandle(tag(), handle_x);
  } else {
    int handle_y = y() + event.y() - mouse_offset_;
    bar_->MoveHandle(tag(), handle_y);
  }
  return true;
}
