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
#include "ui/base/keycodes/keyboard_codes.h"
#include "views/controls/scrollbar/native_scroll_bar.h"

// in theory i include addition manifest in the gyp. but gyp have a bug no 
// generate the right vcxproj. so i add it here.

// if you don't include the Common-Controls you will see no tooltip. but no warm.
// microsoft is sucks. manifest is a nightmare.

#if defined(OS_WIN)
// Add Common Controls to the application manifest because it's required to
// support the default tooltip implementation.
#pragma comment(linker,"/manifestdependency:\"type='win32' \
                                              name='Microsoft.Windows.Common-Controls' \
                                              version='6.0.0.0' \
                                              processorArchitecture='*' \
                                              publicKeyToken='6595b64144ccf1df' \
                                              language='*'\"")
#endif

class ScrollBarView : public views::View
                    , public views::ScrollBarController {
public:
    ScrollBarView();
    virtual ~ScrollBarView() {};

    // overridden from the views::ScrollBarController
    virtual int GetScrollIncrement( views::ScrollBar* source, bool is_page, bool is_positive ) 
    {
        if (!is_page)
            return 1;
        else {
            int width = this->GetLocalBounds().width();
            int height = this->GetLocalBounds().height();
            if (v_scroll_bar_ == source)
                return height / 10;
            else if (h_scroll_bar_ == source)
                return width / 10;
            else
                NOTREACHED();
        }
    }

    virtual void ScrollToPosition( views::ScrollBar* source, int position ) 
    {
    }

    // overridden from views::View
    virtual void OnBoundsChanged(const gfx::Rect& previous_bounds) {
        int width = this->GetLocalBounds().width();
        int height = this->GetLocalBounds().height();
        v_scroll_bar_->Update(height / 10, height, 0);
        h_scroll_bar_->Update(width / 10, width, 0);
    }

    virtual void Layout() {
        static const int scroll_bar_size = 15;
        int width = this->GetLocalBounds().width();
        int height = this->GetLocalBounds().height();
        if (width < scroll_bar_size || height < scroll_bar_size) {
            v_scroll_bar_->SetVisible(false);
            h_scroll_bar_->SetVisible(false);
            return;
        }
        v_scroll_bar_->SetVisible(true);
        h_scroll_bar_->SetVisible(true);
        v_scroll_bar_->SetBounds(width - scroll_bar_size, 0, scroll_bar_size, height - scroll_bar_size);
        h_scroll_bar_->SetBounds(0, height - scroll_bar_size, width - scroll_bar_size, scroll_bar_size);
    }

private:
    views::ScrollBar* v_scroll_bar_;
    views::ScrollBar* h_scroll_bar_;
};

ScrollBarView::ScrollBarView() {
    v_scroll_bar_ = new views::NativeScrollBar(false);
    h_scroll_bar_ = new views::NativeScrollBar(true);
    v_scroll_bar_->set_controller(this);
    h_scroll_bar_->set_controller(this);
    AddChildView(v_scroll_bar_);
    AddChildView(h_scroll_bar_);
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
    ScrollBarView* view;

    contents_ = view = new ScrollBarView();
   
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

    MessageLoopForUI main_message_loop;

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
