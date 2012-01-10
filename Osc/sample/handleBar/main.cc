#include "base/at_exit.h"
#include "base/command_line.h"
#include "base/process_util.h"
#include "base/message_loop.h"
#include "ui/base/resource/resource_bundle.h"
#include "ui/base/ui_base_paths.h"
#include "views/focus/accelerator_handler.h"
#include "views/widget/widget.h"
#include "views/widget/widget_delegate.h"
#include "Osc/ui/views/handle_bar.h"
#include "Osc/ui/views/handle_bar_model.h"
#include "Osc/ui/views/handle_bar_observer.h"
#include "grit/ui_resources.h"

enum handleID {
  text = 0,
  icon,
  limit,
  ID_COUNT,
};

class HandleBarTestModel : public HandleBarModel
                         , public HandleBarObserver {

public:
  HandleBarTestModel()
    : observer_(NULL)
    , has_active_(false)
    , active_id_(-1) {
    for (int i = 0; i < ID_COUNT; i++) {
      offsets_.push_back(i);
    }
  }

  virtual int Count() {
    return ID_COUNT;
  }

  virtual int GetID(int index) {
    CHECK(index >=0 && index < ID_COUNT);
    return index; // the same
  }

  virtual string16 GetText(int ID) {
    switch (ID) {
    case text:
      return L"text";
      break;
    case icon:
      return L"";
      break;
    case limit:
      return L"limit";
      break;
        default:
      NOTREACHED();
    }
  }
  virtual SkColor GetColor( int ID) {
      switch (ID) {
    case text:
        return SkColorSetRGB(255, 0, 0);
        break;
    case icon:
        return SkColorSetRGB(0, 255, 0);
        break;
    case limit:
        return SkColorSetRGB(0, 0, 255);
        break;
    default:
        NOTREACHED();
      }
  }

  virtual SkBitmap GetIcon(int ID) {
    switch (ID) {
    case text:
      return SkBitmap();
      break;
    case icon:
      {
        ResourceBundle& rb = ResourceBundle::GetSharedInstance();
        return *(rb.GetBitmapNamed(IDR_CLOSE_SA_H));
      }
    case limit:
      return SkBitmap();
      break;
        default:
      NOTREACHED();
    }
  }

  virtual int GetOffset(int ID) {
    CHECK(ID >= 0 && ID < ID_COUNT);
    return offsets_[ID]; // the same
  }

  virtual bool IsEnable(int ID) {
    CHECK(ID >= 0 && ID < ID_COUNT);
    return true; // the same
  }

  virtual bool IsVisible(int ID) {
    CHECK(ID >= 0 && ID < ID_COUNT);
    return true; // the same
  }

  virtual void SetObserver(HandleBarModelObserver* observer) {
    CHECK(observer != NULL);
    observer_ = observer;
  }


  virtual void OnHandleMove(int ID, int offset) {
    CHECK(ID >= 0 && ID < ID_COUNT);
    // format limit value
    if (ID == limit)
      offset = offset / 20 * 20; // only can move in 20th
    offsets_[ID] = offset;
    // notify
    observer_->OnHandleMoved(ID);
  }

  virtual void OnHandleActive(int ID) {
    CHECK(ID >= 0 && ID < ID_COUNT);
    has_active_ = true;
    active_id_ = ID;
    LOG(INFO) <<
    "Handle " << ID << " be actived";
  }


private:
  HandleBarModelObserver* observer_;
  int active_id_;
  int has_active_;
  std::vector<int> offsets_;
};

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

  HandleBar* contents_;
  HandleBarTestModel model_;

  DISALLOW_COPY_AND_ASSIGN(ExampleView);
};

ExampleView::ExampleView()
  : contents_(NULL) {}

void ExampleView::Init() {
  DCHECK(contents_ == NULL) << "Run called more than once.";
  ResourceBundle& rb = ResourceBundle::GetSharedInstance();
  contents_ = new HandleBar(&model_, false,
                            rb.GetFont(ResourceBundle::MediumFont),
                            0, 300);
  contents_->SetObserver(&model_);
  contents_->set_background(
      views::Background::CreateSolidBackground(SkColorSetRGB(0, 0, 40)));
  views::Widget* window =
    views::Widget::CreateWindowWithBounds(this, gfx::Rect(0, 0, 850, 400));

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
  views::Widget::SetPureViews(CommandLine::ForCurrentProcess()->
                              HasSwitch("use-pure-views"));

  ExampleView view;
  view.Init();

  views::AcceleratorHandler accelerator_handler;
  MessageLoopForUI::current()->Run(&accelerator_handler);

#if defined(OS_WIN)
    OleUninitialize();
#endif
    return 0;
}