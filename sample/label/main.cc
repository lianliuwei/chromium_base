#include "base/at_exit.h"
#include "base/command_line.h"
#include "base/process_util.h"
#include "base/stringprintf.h"
#include "ui/base/resource/resource_bundle.h"
#include "ui/base/ui_base_paths.h"
#include "ui/gfx/canvas_skia.h"
#include "views/focus/accelerator_handler.h"
#include "views/layout/fill_layout.h"
#include "views/widget/widget.h"
#include "views/widget/widget_delegate.h"
#include "views/controls/label.h"
#include "ui/base/keycodes/keyboard_codes.h"

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

class MessageView : public views::View {
public:
    MessageView();
    virtual ~MessageView() {};
    virtual gfx::Size GetPreferredSize();
    virtual bool OnMousePressed(const views::MouseEvent& event);
    virtual void OnMouseMoved(const views::MouseEvent& event);
    virtual bool OnKeyPressed(const views::KeyEvent& event);

private:
    int count_;
    views::Label* label_;
};

MessageView::MessageView() 
    : count_(0) {
    set_focusable(true);
    label_ = new views::Label();
    label_->SetColor(SkColorSetRGB(255, 255, 255));
    label_->SetLayoutManager(new views::FillLayout());
    AddChildView(label_);
    label_->set_border(views::Border::CreateEmptyBorder(10, 10, 10, 10));
    set_background(
        views::Background::CreateSolidBackground(SkColorSetRGB(0, 0, 0)));
    set_border(views::Border::CreateSolidBorder(10, SkColorSetRGB(125, 125, 125)));
}

bool MessageView::OnMousePressed(const views::MouseEvent& event){
    count_++;
    string16 str;
    base::StringAppendF(&str, L"blackView count: %d", count_);
    label_->SetText(str);
    // trigger the label mouse over background change
    label_->OnMouseMoved(event);

    return true;
}

void MessageView::OnMouseMoved(const views::MouseEvent& event){
    label_->OnMouseMoved(event);
}

bool MessageView::OnKeyPressed(const views::KeyEvent& event){
    switch (event.key_code())
    {
    case ui::VKEY_B:
        label_->SetMouseOverBackground(
            views::Background::CreateVerticalGradientBackground(
                SkColorSetRGB(255,255,0), SkColorSetRGB(120, 120, 0)));
    	return true;
    }
    return false;
}

gfx::Size MessageView::GetPreferredSize() {
    return gfx::Size(200, 200);
}
ExampleView::ExampleView() : contents_(NULL) {}

void ExampleView::Init() {
    DCHECK(contents_ == NULL) << "Run called more than once.";
    MessageView* view;
    contents_ = view = new MessageView();
    views::FillLayout* layout = new views::FillLayout();
    contents_->SetLayoutManager(layout);
    views::Widget* window =
        views::Widget::CreateWindowWithBounds(this, gfx::Rect(0, 0, 850, 300));
    // init focus the MessageView so you can use keyboard to input
    view->RequestFocus();
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
