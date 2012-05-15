#include "Osc/sample/example_view.h"

#include "views/widget/widget.h"
#include "osc/sample/fill_box_layout.h"
#include "views/widget/widget_delegate.h"
#include "Osc/ui/views/line_data_wave_view.h"

#define M_PI       3.14159265358979323846

using namespace std;

class WaveViewShowView : public views::View {
public:
  WaveViewShowView();
  virtual ~WaveViewShowView() {};

  virtual void Layout() OVERRIDE;

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
    wave_view->set_wave_color(SkColorSetRGB(0, 255, 0));
    wave_view->set_show_style(LineDataWaveView::KLineAndAutoDot);
    wave_views_.push_back(wave_view);
    AddChildView(wave_view);
    wave_view->set_border(
      views::Border::CreateSolidBorder(1, SkColorSetRGB(255, 255, 255)));
  }
    // setup data
   // fix size
  LineDataWaveView::LineData line_data;
  {
    line_data.begin = 100;
    line_data.end = 700;
    (wave_view_data[0])->reserve(200);
    for (int j = 0; j < 200; j++)
      (wave_view_data[0])->push_back(sin(j*4*2*M_PI/200));
    line_data.buffer = wave_view_data[0];
    wave_views_[0]->set_line_data(line_data);
    ui::Transform transform;
    transform.SetTranslate(0, 400/3/2);
    transform.SetScaleY(400/3/3);
    wave_views_[0]->set_logic_to_real_transform(transform);
  }

  {
    // auto size
    line_data.begin = 0;
    line_data.end = 1;
    (wave_view_data[1])->reserve(50);
    for (int j = 0; j < 50; j++)
      (wave_view_data[1])->push_back(sin(j*4*2*M_PI/50));
    line_data.buffer = wave_view_data[1];
    wave_views_[1]->set_line_data(line_data);
  }

  {
    // test sample
    line_data.begin = 100;
    line_data.end = 700;
    (wave_view_data[2])->reserve(2400);
    for (int j = 0; j < 2400; j++)
      (wave_view_data[2])->push_back(sin(j*4*2*M_PI/2400));
    (*(wave_view_data[2]))[1200] = 1.0;
    (*(wave_view_data[2]))[1202] = -1.0;
    line_data.buffer = wave_view_data[2];
    wave_views_[2]->set_line_data(line_data);
    ui::Transform transform;
    transform.SetTranslate(0, 400/3/2);
    transform.SetScaleY(400/3/3);
    wave_views_[2]->set_logic_to_real_transform(transform);
    wave_views_[2]->set_show_style(LineDataWaveView::KLineAndAutoDot);
  }
  
}

void WaveViewShowView::Layout()
{
  // using the default to Layout the child view first
  views::View::Layout();

  ui::Transform transform;

  gfx::Size view_size = wave_views_[1]->size();
  transform.SetTranslate(0, view_size.height()/2);
  transform.SetScaleY(view_size.height()/2);
  transform.SetScaleX(view_size.width());
  wave_views_[1]->set_logic_to_real_transform(transform);
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