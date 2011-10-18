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

//FillLayout without border
class FillLayout : public views::LayoutManager {
public:
    FillLayout();
    virtual ~FillLayout();

    // Overridden from LayoutManager:
    virtual void Layout(views::View* host);
    virtual gfx::Size GetPreferredSize(views::View* host);

private:
    DISALLOW_COPY_AND_ASSIGN(FillLayout);
};

FillLayout::FillLayout() {
}

FillLayout::~FillLayout() {
}

void FillLayout::Layout(views::View* host) {
    if (!host->has_children())
        return;

    views::View* frame_view = host->child_at(0);
    gfx::Rect child_area(host->GetLocalBounds());
    child_area.Inset(host->GetInsets());
    frame_view->SetBoundsRect(child_area);
}

gfx::Size FillLayout::GetPreferredSize(views::View* host) {
    DCHECK_EQ(1, host->child_count());
    gfx::Size size = host->child_at(0)->GetPreferredSize();
    gfx::Insets inset = host->GetInsets();
    size.Enlarge(inset.width(), inset.height());
    return size;
}

class LabelView : public views::View {
public:
    LabelView();
    virtual ~LabelView() {};

    static LabelView* CreateLabelViewWithMouseOverBackground();
    static LabelView* CreateRightAlignLabelView();
    static LabelView* CreateLabelViewWithMutliLine();
    static LabelView* CreateLabelViewWithPaintAsFocus();
    virtual void OnMouseMoved(const views::MouseEvent& event);
private:
    views::Label* label_;
};

// static 
LabelView* LabelView::CreateLabelViewWithMouseOverBackground() {
    LabelView* labelView = new LabelView();
    labelView->label_->SetColor(SkColorSetRGB(255, 0, 0));
    labelView->label_->set_border(views::Border::CreateEmptyBorder(10, 10, 10, 10));
    labelView->set_background(
        views::Background::CreateSolidBackground(SkColorSetRGB(0, 0, 0)));
    labelView->label_->SetMouseOverBackground(
        views::Background::CreateVerticalGradientBackground(
        SkColorSetRGB(255,255,0), SkColorSetRGB(120, 120, 0)));
    labelView->label_->SetText(L"Mouse Over Background change. ");
    return labelView;
}

// static 
LabelView* LabelView::CreateRightAlignLabelView() {
    LabelView* labelView = new LabelView();
    labelView->label_->set_focusable(true);
    labelView->label_->SetColor(SkColorSetRGB(0, 255, 0));
    labelView->label_->set_border(views::Border::CreateEmptyBorder(10, 10, 10, 10));
    labelView->set_background(
        views::Background::CreateSolidBackground(SkColorSetRGB(0, 0, 40)));
    labelView->label_->SetHorizontalAlignment(views::Label::ALIGN_RIGHT);
    labelView->label_->SetTooltipText(L"the Align attribute is seet Right.");// no effect
    labelView->label_->SetText(L"String Right Align.");
    return labelView;
}

// static 
LabelView* LabelView::CreateLabelViewWithMutliLine() {
    LabelView* labelView = new LabelView();
    labelView->label_->SetColor(SkColorSetRGB(0, 0, 255));
    labelView->label_->set_border(views::Border::CreateEmptyBorder(10, 10, 10, 10));
    labelView->set_background(
        views::Background::CreateSolidBackground(SkColorSetRGB(0, 40, 0)));
    labelView->label_->SetMultiLine(true);
    labelView->label_->SetText(L"MultiLine label line 1\nline 2\nline 3\nline4");
    return labelView;
}

// static 
LabelView* LabelView::CreateLabelViewWithPaintAsFocus() {
    LabelView* labelView = new LabelView();
    labelView->label_->SetColor(SkColorSetRGB(0, 255, 255));
    labelView->label_->set_border(views::Border::CreateEmptyBorder(10, 10, 10, 10));
    labelView->set_background(
        views::Background::CreateSolidBackground(SkColorSetRGB(40, 0, 0)));
    labelView->label_->set_paint_as_focused(true);
    labelView->label_->SetText(L"LabelView Paint As Focus.");
    return labelView;
}
LabelView::LabelView() {
    set_focusable(true);
    label_ = new views::Label();
    AddChildView(label_);
    SetLayoutManager(new FillLayout());
    set_border(views::Border::CreateEmptyBorder(2,2,2,2));
}

void LabelView::OnMouseMoved(const views::MouseEvent& event) {
    label_->OnMouseMoved(event);
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
    contents_ = new views::View();
    contents_->AddChildView(LabelView::CreateLabelViewWithMouseOverBackground());
    contents_->AddChildView(LabelView::CreateRightAlignLabelView());
    contents_->AddChildView(LabelView::CreateLabelViewWithMutliLine());
    contents_->AddChildView(LabelView::CreateLabelViewWithPaintAsFocus());
    contents_->SetLayoutManager(new views::BoxLayout(
        views::BoxLayout::kVertical, 10, 10, 10));
    contents_->set_background(
        views::Background::CreateSolidBackground(SkColorSetRGB(25, 25, 25)));
    contents_->set_border(
        views::Border::CreateSolidBorder(10, SkColorSetRGB(125, 125, 125)));
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
