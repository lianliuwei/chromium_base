#include "wave_control/views/wave_control_view.h"

#include "views/layout/box_layout.h"

#include "wave_control/views/wave_control_view_factory.h"

using namespace views;

// just Vertical Layout the ContainerView
WaveControlView::WaveControlView(WaveControl* wave_control)
    : wave_control_(wave_control) {
  wave_control->AddObserver(this);
  SetLayoutManager(new BoxLayout(BoxLayout::kVertical, 0, 0, 0));
}

WaveControlView::~WaveControlView() {
  wave_control()->RemoveObserver(this);
}

void WaveControlView::ListItemsAdded(size_t start, size_t count) {
  for (size_t i = 0; i < count; ++i) {
    WaveContainer* container = wave_control_->GetItemAt(start + i);
    View* view = WaveControlViewFactory::GetInstance()->Create(container, this);
    this->AddChildViewAt(view, start + i);
  }
}

void WaveControlView::ListItemsRemoved(size_t start, size_t count) {
  View::Views need_remove;
  need_remove.reserve(count);
  for (size_t i = 0; i < count; ++i) {
    need_remove.push_back(this->child_at(start + i));
  }
  for (size_t i = 0; i < need_remove.size(); ++i) {
    this->RemoveChildView(need_remove[i]);
    delete need_remove[i];
  }
}

void WaveControlView::ListItemMoved(size_t index, size_t target_index) {
  this->ReorderChildView(this->child_at(index), target_index);
}

void WaveControlView::ListItemsChanged(size_t start, size_t count) {
  ListItemsRemoved(start, count);
  ListItemsAdded(start, count);
}


