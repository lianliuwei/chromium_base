#include "wave_control/views/yt_wave_container_view.h"

#include "ui/base/resource/resource_bundle.h"

namespace {

// the Rect::Center change the size if is bigger than the Rect
// this do not change the size
gfx::Rect Center(const gfx::Rect rect, const gfx::Size& size) {
    int new_width = size.width();
    int new_height = size.height();
    int new_x = rect.x() + (rect.width() - new_width) / 2;
    int new_y = rect.y() + (rect.height() - new_height) / 2;
    return gfx::Rect(new_x, new_y, new_width, new_height);
}

static const ResourceBundle::FontStyle kBarFont = ResourceBundle::MediumFont;

// the width or height between the handlebar and the YTView.
static const int kGapSize = 4;
}

void YTWaveContainerView::Layout() {
  int hzbar_height = horiz_offset_bar_->GetPreferredSize().height();
  int wvbar_width = wave_bar_->GetPreferredSize().width();
  int tgbar_width = trigger_bar_->GetPreferredSize().width();

  int hz_mini_half_width = horiz_offset_bar_->GetMinimumSize().width()/2;
  int wv_mini_half_height = wave_bar_->GetMinimumSize().height()/2;
  int tg_mini_half_height = trigger_bar_->GetMinimumSize().height()/2;

  int max_half_height = 0;
  if (show_wave_bar_ && show_trigger_bar_) {
    max_half_height = std::max(wv_mini_half_height, tg_mini_half_height);
  }  else if (show_wave_bar_) {
    max_half_height = wv_mini_half_height;
  } else if (show_trigger_bar_) {
    max_half_height = tg_mini_half_height;
  } else {
    max_half_height = 0;
  }

  int left_need = 0;
  if (show_wave_bar_ && show_horiz_offset_bar_) {
    left_need = std::max(wvbar_width + kGapSize, hz_mini_half_width);
  } else if (show_wave_bar_) {
    left_need = wvbar_width + kGapSize;
  } else if (show_horiz_offset_bar_) {
    left_need = hz_mini_half_width;
  } else {
    left_need = 0;
  }

  int top_need =  show_horiz_offset_bar_ ?
    std::max(hzbar_height + kGapSize, max_half_height) : max_half_height;

  int right_need = 0;
  if (show_trigger_bar_ && show_horiz_offset_bar_) {
    right_need = std::max(tgbar_width + kGapSize, hz_mini_half_width);
  } else if (show_trigger_bar_) {
    right_need = tgbar_width + kGapSize;
  } else if (show_horiz_offset_bar_) {
    right_need = hz_mini_half_width;
  } else {
    right_need = 0;
  }

  int bottom_need = max_half_height;


  gfx::Size mini = yt_view_->GetMinimumSize();
  gfx::Size real = size();

  mini.Enlarge(left_need + right_need, top_need + bottom_need);
  // no show the YTView if the real is to small
  if(mini.width() > real.width() || mini.height() > real.height()) {
    yt_view_->SetVisible(false);
    wave_bar_->SetVisible(false);
    horiz_offset_bar_->SetVisible(false);
    trigger_bar_->SetVisible(false);

  }else {
    gfx::Rect ytview_rect = GetLocalBounds();
    ytview_rect.Inset(left_need, top_need, right_need, bottom_need);
    gfx::Size ytview_size = ytview_rect.size();
    bool ret = yt_view_->NormalSize(ytview_size);
    CHECK(ret) << "the ytview_size can no be normal";
    ytview_rect = Center(ytview_rect, ytview_size);
    yt_view_->SetBoundsRect(ytview_rect);
    yt_view_->SetVisible(true);

    int border_width = yt_view_->BorderThickness();
    if (show_wave_bar_) {
      gfx::Rect wave_bar_rect(
          0, 
          ytview_rect.y() - wv_mini_half_height,
          wvbar_width, 
          ytview_size.height() + wv_mini_half_height * 2);
      wave_bar_->SetBoundsRect(wave_bar_rect);
      wave_bar_->SetMoveRange(wv_mini_half_height + border_width,
          wv_mini_half_height + ytview_size.height() -  border_width);
    }
    wave_bar_->SetVisible(show_wave_bar_);

    if (show_horiz_offset_bar_) {
      gfx::Rect horiz_offset_rect(
          ytview_rect.x() - hz_mini_half_width, 
          0,
          ytview_size.width() + hz_mini_half_width * 2, 
          hzbar_height);
      horiz_offset_bar_->SetBoundsRect(horiz_offset_rect);
      horiz_offset_bar_->SetMoveRange(hz_mini_half_width + border_width,
          hz_mini_half_width + ytview_size.width() -border_width);
    }
    horiz_offset_bar_->SetVisible(show_horiz_offset_bar_);

    if (show_trigger_bar_) {
      gfx::Rect trigger_rect(
          real.width() - tgbar_width, 
          ytview_rect.y() - tg_mini_half_height,
          tgbar_width, 
          ytview_size.height() + tg_mini_half_height * 2);
      trigger_bar_->SetBoundsRect(trigger_rect);
      trigger_bar_->SetMoveRange(tg_mini_half_height + border_width,
          tg_mini_half_height + ytview_size.height() - border_width);
    }
    trigger_bar_->SetVisible(show_trigger_bar_);
  }
}

YTWaveContainerView::YTWaveContainerView(YTWaveContainer* container, 
                                         WaveControlView* wave_control_view) {
  yt_view_ = new YTWaveContainerInnerView(container);
  AddChildView(yt_view_);
  wave_bar_ = CreateHandleBar(yt_view_->GetWaveBarDelegate());
  horiz_offset_bar_ = CreateHandleBar(yt_view_->GetHorizOffsetBarDelegate());
  trigger_bar_ = CreateHandleBar(yt_view_->GetTriggerBarDelegate());
}

HandleBar* YTWaveContainerView::CreateHandleBar(HandleBarDelegate* delegate) {
  ResourceBundle& rb = ResourceBundle::GetSharedInstance();
  HandleBar* bar = new HandleBar(delegate, delegate->is_horiz(), 
      rb.GetFont(kBarFont),
      0, 1);
  bar->SetObserver(delegate);
  AddChildView(bar);
  return bar;
}

YTWaveContainerView::~YTWaveContainerView() {
  wave_bar_->SetObserver(NULL);
  horiz_offset_bar_->SetObserver(NULL);
  trigger_bar_->SetObserver(NULL);
}
