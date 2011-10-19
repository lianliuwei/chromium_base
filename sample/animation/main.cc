#include "base/at_exit.h"
#include "base/command_line.h"
#include "base/process_util.h"
#include "base/stringprintf.h"
#include "ui/base/resource/resource_bundle.h"
#include "ui/base/ui_base_paths.h"
#include "ui/gfx/canvas_skia.h"
#include "views/focus/accelerator_handler.h"
#include "views/layout/fill_layout.h"
#include "views/layout/box_layout.h"
#include "views/widget/widget.h"
#include "views/widget/widget_delegate.h"
#include "views/controls/label.h"
#include "ui/base/keycodes/keyboard_codes.h"
#include "ui/base/animation/animation_delegate.h"
#include "ui/base/animation/slide_animation.h"


class AnimationView : public views::View
                    , public ui::AnimationDelegate {
public:
    AnimationView(ui::Tween::Type type);
    virtual ~AnimationView() {};
    // View
    virtual void OnPaint(gfx::Canvas* canvas);
    virtual void OnMouseEntered(const views::MouseEvent& event);
    virtual void OnMouseExited(const views::MouseEvent& event);
    virtual gfx::Size GetPreferredSize();
    virtual void Layout();
    // AnimationDelegate
    void AnimationProgressed(const ui::Animation* animation);

private:
    scoped_ptr<ui::SlideAnimation> animation_;
    views::View* view_;
};

AnimationView::AnimationView(ui::Tween::Type type) {
    set_focusable(true);
    animation_.reset(new ui::SlideAnimation(this));
    animation_->SetTweenType(type);
    animation_->SetSlideDuration(2000);
    view_ = new views::View();
    view_->set_background(
        views::Background::CreateSolidBackground(255, 0, 0));
    view_->SetBounds(0, 10, 10, 80);
    AddChildView(view_);
}

void AnimationView::OnPaint(gfx::Canvas* canvas){
    SkColor color = HasFocus() ? SkColorSetRGB(255, 0, 0) 
        : SkColorSetRGB(0, 255, 0);
    canvas->FillRectInt(color, 2, 2, width() - 4 , height() - 4);
    View::OnPaint(canvas);
}

gfx::Size AnimationView::GetPreferredSize(){
    return gfx::Size(850, 100);
}

void AnimationView::OnMouseEntered( const views::MouseEvent& event )
{
    animation_->Show();
}

void AnimationView::OnMouseExited( const views::MouseEvent& event )
{
    animation_->Hide();
}

void AnimationView::AnimationProgressed( const ui::Animation* animation )
{
    if (animation == animation_.get()) {
        Layout();
        SchedulePaint();
    } else {
        NOTREACHED();
    }
}

void AnimationView::Layout()
{
    if (animation_->is_animating()) {
        int x = ui::Tween::ValueBetween( animation_->GetCurrentValue(), 0, 850);
        view_->SetBounds(x, 10, 10, 80);
    }
}


class ExampleView : public views::WidgetDelegate {
public:
    ExampleView();
    virtual ~ExampleView() {};

    // Creates all the examples and shows the window.
    void Init();

private:
    // views::WidgetDelegate implementation:
    virtual bool CanResize() const OVERRIDE;
    virtual bool CanMaximize() const OVERRIDE;
    virtual std::wstring GetWindowTitle() const OVERRIDE;
    virtual views::View* GetContentsView() OVERRIDE;
    virtual void WindowClosing() OVERRIDE;
    virtual views::Widget* GetWidget() OVERRIDE;
    virtual const views::Widget* GetWidget() const OVERRIDE;

    views::View* contents_;

    DISALLOW_COPY_AND_ASSIGN(ExampleView);
};

ExampleView::ExampleView() : contents_(NULL) {}

void ExampleView::Init() {
    DCHECK(contents_ == NULL) << "Run called more than once.";
    AnimationView* view;
    contents_ = new views::View();
    contents_->set_background(
        views::Background::CreateSolidBackground(25, 25, 25));
 
    view = new AnimationView(ui::Tween::LINEAR);
    contents_->AddChildView(view);
    view = new AnimationView(ui::Tween::EASE_OUT);
    contents_->AddChildView(view);
    view = new AnimationView(ui::Tween::EASE_IN);
    contents_->AddChildView(view);
    view = new AnimationView(ui::Tween::EASE_IN_OUT);
    contents_->AddChildView(view);
    view = new AnimationView(ui::Tween::FAST_IN_OUT);
    contents_->AddChildView(view);
//     view = new AnimationView(ui::Tween::EASE_OUT_SNAP); // will break because ASSERT
//     contents_->AddChildView(view);
    view = new AnimationView(ui::Tween::ZERO);
    contents_->AddChildView(view);

    contents_->SetLayoutManager(new views::BoxLayout(
        views::BoxLayout::kVertical, 10, 10, 10));
    views::Widget* window =
        views::Widget::CreateWindowWithBounds(this, gfx::Rect(0, 0, 850, 300));

    window->Show();
}

bool ExampleView::CanResize() const {
    return true;
}

bool ExampleView::CanMaximize() const {
    return true;
}

std::wstring ExampleView::GetWindowTitle() const {
    return L"Views Examples";
}

views::View* ExampleView::GetContentsView() {
    return contents_;
}

void ExampleView::WindowClosing() {
    MessageLoopForUI::current()->Quit();
}

views::Widget* ExampleView::GetWidget() {
    return contents_->GetWidget();
}

const views::Widget* ExampleView::GetWidget() const {
    return contents_->GetWidget();
}

int main(int argc, char** argv) {
#if defined(OS_WIN)
    OleInitialize(NULL);
#elif defined(OS_LINUX)
    // Initializes gtk stuff.
    g_thread_init(NULL);
    g_type_init();
    gtk_init(&argc, &argv);
#endif
    CommandLine::Init(argc, argv);

    base::EnableTerminationOnHeapCorruption();

    // The exit manager is in charge of calling the dtors of singleton objects.
    base::AtExitManager exit_manager;

    ui::RegisterPathProvider();
    ui::ResourceBundle::InitSharedInstance("en-US");

    MessageLoop main_message_loop(MessageLoop::TYPE_UI);

    // views::TestViewsDelegate delegate;

    // We do not use this header: chrome/common/chrome_switches.h
    // because that would create a bad dependency back on Chrome.
    views::Widget::SetPureViews(
        CommandLine::ForCurrentProcess()->HasSwitch("use-pure-views"));

    ExampleView view;
    view.Init();

    views::AcceleratorHandler accelerator_handler;
    MessageLoopForUI::current()->Run(&accelerator_handler);

#if defined(OS_WIN)
    OleUninitialize();
#endif
    return 0;
}
