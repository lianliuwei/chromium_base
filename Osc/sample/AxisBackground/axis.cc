#include "Osc/sample/example_view.h"

#include "views/widget/widget.h"
#include "views/widget/widget_delegate.h"
#include "Osc/ui/views/yt_view.h"
#include "Osc/ui/views/yt_view_container.h"
#include "views/background.h"

void ExampleView::Init() {
  DCHECK(contents_ == NULL) << "Run called more than once.";
  YTView* yt = new YTView();
  yt->SetGrid(6, 4);
  contents_ = new YTViewContainer(yt);
  contents_->set_background(
      views::Background::CreateSolidBackground(SkColorSetRGB(40, 0, 0)));
  views::Widget* window =
    views::Widget::CreateWindowWithBounds(this, gfx::Rect(0, 0, 850, 400));

  window->Show();
}

ExampleView* ExampleView::CreateInstance() {
  return new ExampleView();
}