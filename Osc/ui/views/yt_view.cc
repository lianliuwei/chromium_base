#include "Osc/ui/views/yt_view.h"
#include "views/border.h"

namespace {

const SkColor kBackground = SkColorSetRGB(10, 10, 10);

const SkColor kAxisLine = SkColorSetRGB(170, 170, 170);

const int kLineWidth = 5;

const SkColor kAxisGrid = SkColorSetRGB(51, 51, 51);

const int kVGridDiv = 5;

const int kHGridDiv = 5;

const SkColor kFrame = SkColorSetRGB(107, 107, 107);

const int kFrameWidth = 1;
}

using namespace views;

YTView::YTView() 
    : v_grid_(0)
    , h_grid_(0) {
        set_border(Border::CreateSolidBorder(kFrameWidth, kFrame));
}

YTView::~YTView() {}

bool YTView::NormalSize(gfx::Size& size) {
    // keep space for the border
    size.Enlarge(-GetInsets().width(), -GetInsets().height());
    if (get_axis_background()->NormalSize(size)) {
        size.Enlarge(GetInsets().width(), GetInsets().height());
        return true;
    }
    return false;
}

gfx::Size YTView::GetMinimumSize() {
    gfx::Size size = get_axis_background()->GetMinimumSize();
    size.Enlarge(GetInsets().width(), GetInsets().height());
    return size;
}

AxisBackground* YTView::get_axis_background()
{
    Background* bg = background();
    CHECK(bg) << "no background exist";
    return static_cast<AxisBackground*>(bg);
}

void YTView::SetGrid( int v_grid, int h_grid ) {
    int real_v = v_grid == 0 ? v_grid_ : v_grid;
    int real_h = h_grid == 0 ? h_grid_ : h_grid;
    if (real_v != v_grid_ || real_h != h_grid) {
        v_grid_ = real_v;
        h_grid_ = real_h;
        set_background(new AxisBackground(kBackground, 
            kAxisLine, kLineWidth, 
            kAxisGrid, v_grid, kVGridDiv, h_grid, kHGridDiv));
        SchedulePaint();
    }
}

