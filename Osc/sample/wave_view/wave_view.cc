#include "Osc/sample/example_view.h"

#include "views/widget/widget.h"
#include "osc/sample/fill_box_layout.h"
#include "views/widget/widget_delegate.h"
#include "Osc/ui/views/line_data_wave_view.h"

using namespace std;

class WaveViewShowView : public views::View {
public:
  WaveViewShowView();
  virtual ~WaveViewShowView() {};

private:
    LineDataWaveView::DataBuffer fix_size_data_;
    LineDataWaveView::DataBuffer auto_size_data_;
    LineDataWaveView::DataBuffer test_sample_data_;
    vector<LineDataWaveView*> wave_views_;
};

WaveViewShowView::WaveViewShowView()
{
  SetLayoutManager(new FillBoxLayout(FillBoxLayout::kVertical, 10, 10, 10));
  LineDataWaveView::DataBuffer* wave_view_data[3] = {&fix_size_data_, 
    &auto_size_data_, &test_sample_data_};
  for (int i = 0; i < arraysize(wave_view_data); i++) {
    LineDataWaveView* wave_view = new LineDataWaveView;
    wave_view->set_dot_color(SkColorSetRGB(0, 0, 255));
    wave_view->set_wave_color(SkColorSetRGB(0, 255, 255));
    wave_view->set_show_style(LineDataWaveView::KLineAndAutoDot);
    wave_views_.push_back(wave_view);
    AddChildView(wave_view);
    wave_view->set_border(
      views::Border::CreateSolidBorder(1, SkColorSetRGB(255, 255, 255)));
  }
  for (int i = 0; i < arraysize(wave_view_data); i++) {  
    // setup data
    LineDataWaveView::LineData line_data;
    line_data.begin = 100;
    line_data.end = 200;
    (wave_view_data[i])->reserve(100);
    for (int j = 0; j < 100; j++)
      (wave_view_data[i])->push_back(4);
    line_data.buffer = wave_view_data[i];
    wave_views_[i]->set_line_data(line_data);
  }
}

void ExampleView::Init() {
    DCHECK(contents_ == NULL) << "Run called more than once.";
    contents_ = new WaveViewShowView;
    contents_->set_background(
        views::Background::CreateSolidBackground(SkColorSetRGB(40, 0, 0)));
    views::Widget* window =
        views::Widget::CreateWindowWithBounds(this, gfx::Rect(0, 0, 850, 400));

    window->Show();
}

ExampleView* ExampleView::CreateInstance() {
    return new ExampleView();
}