#include "wave_control/examples/example_view.h"
#include "wave_control/views/wave_control_view_factory.h"
#include "wave_control/wave_control.h"
#include "wave_control/examples/test_osc_wave.h"

namespace {
class TestWaveControl : public WaveControl {
public:
  virtual void AddWave(Wave* wave);
  virtual void RemoveWave(Wave* wave)  {
    DCHECK(item_count() == 1);
    GetItemAt(0)->RemoveWave(wave);
  }
  virtual void ShowInfo()  {
    NOTREACHED();
  }
  virtual void ToggleInfo()  {
    NOTREACHED();
  }
  virtual void IsShowInfo() const {
    NOTREACHED();
  }

};

class TestWaveContainer : public YTWaveContainer {
public:
  virtual void ShowGrid()  {
    NOTREACHED();
  }
  virtual void ToggleGrid()  {
    NOTREACHED();
  }
  virtual bool IsShowGrid() const {
    NOTREACHED();
    return true;
  }

};

void TestWaveControl::AddWave(Wave* wave) {
  if (item_count() == 0) {
    Add(new TestWaveContainer());
  }
  GetItemAt(0)->Add(wave);
}

}

WaveControl* CreateWaveControl() {
  TestWaveControl* wave_control = new TestWaveControl();
  std::vector<TestOscWave*> waves  = CreateWaves();
  for (size_t i = 0; i < waves.size(); ++i) {
    wave_control->AddWave(waves[i]);
  }
}

void ExampleView::Init() {
  DCHECK(contents_ == NULL) << "Run called more than once.";
  WaveControl* wave_control = CreateWaveControl();
  contents_ = WaveControlViewFactory::GetInstance()->Create(wave_control);
  views::Widget* window =
    views::Widget::CreateWindowWithBounds(this, gfx::Rect(0, 0, 850, 400));

  window->Show();
}

ExampleView* ExampleView::CreateInstance() {
  return new ExampleView();
}