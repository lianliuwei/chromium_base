#include "Osc/sample/example_view.h"

#include "views/widget/widget.h"
#include "views/widget/widget_delegate.h"
#include "Osc/ui/views/line_data_wave_view.h"

void ExampleView::Init() {
    DCHECK(contents_ == NULL) << "Run called more than once.";
    LineDataWaveView* wave_view = new LineDataWaveView;
    wave_view->set_dot_color(SkColorSetRGB(0, 0, 255));
    wave_view->set_wave_color(SkColorSetRGB(0, 255, 255));
    ui::Transform transform;
    transform.SetScale(2, 20);
    wave_view->set_logic_to_real_transform(transform);
    LineDataWaveView::LineData line_data;
    line_data.begin = 100;
    line_data.end = 200;
    LineDataWaveView::DataBuffer* buffer = new LineDataWaveView::DataBuffer;
    wave_view->set_show_style(LineDataWaveView::KLineAndAutoDot);
    buffer->reserve(100);
    for (int i = 0; i < 100; i++)
      buffer->push_back(4);
    line_data.buffer = buffer;
    wave_view->set_line_data(line_data);
    contents_ = wave_view;
    contents_->set_background(
        views::Background::CreateSolidBackground(SkColorSetRGB(40, 0, 0)));
    views::Widget* window =
        views::Widget::CreateWindowWithBounds(this, gfx::Rect(0, 0, 850, 400));

    window->Show();
}

ExampleView* ExampleView::CreateInstance() {
    return new ExampleView();
}