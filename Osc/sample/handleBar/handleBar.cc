#include "Osc/sample/example_view.h"

#include "Osc/ui/views/handle_bar.h"
#include "Osc/ui/views/handle_bar_model.h"
#include "Osc/ui/views/handle_bar_observer.h"
#include "ui/base/resource/resource_bundle.h"
#include "grit/ui_resources.h"
#include "views/controls/separator.h"

enum handleID {
  text = 0,
  icon,
  limit,
  ID_COUNT,
};

class HandleBarTestModel : public HandleBarModel
                         , public HandleBarObserver
                         , public views::View {

public:
  HandleBarTestModel()
    : observer_(NULL)
    , has_active_(false)
    , active_id_(-1)
    , offset_(100) {
    for (int i = 0; i < ID_COUNT; i++) {
      offsets_.push_back(i*10);
      // add separator to index the show the offsets
      indexs_.push_back(new views::Separator());
      this->AddChildView(indexs_[i]);
    }
  }

  virtual void Layout() {
      if (observer_) {
          observer_->SetBoundsRect(bounds());
      }
    for (int i = 0; i < ID_COUNT; i++) {
      indexs_[i]->SetBounds(x(), offsets_[i] + GetHandleBarOffset(), width(), 1);
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
    observer_ = static_cast<HandleBar*>(observer);
    this->AddChildView(observer_);
  }


  virtual void OnHandleMove(int ID, int offset) {
    CHECK(ID >= 0 && ID < ID_COUNT);
    // format limit value
    if (ID == limit)
      offset = offset / 20 * 20; // only can move in 20th
    offsets_[ID] = offset;
    // set the assis separator
    indexs_[ID]->SetBounds(x(), offsets_[ID]+ GetHandleBarOffset(), width(), 1);
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

  int GetHandleBarOffset() { return offset_;}

private:
  HandleBar* observer_;
  int active_id_;
  int has_active_;
  std::vector<int> offsets_;
  std::vector<views::Separator*> indexs_;
  int offset_;
};

void ExampleView::Init() {
  DCHECK(contents_ == NULL) << "Run called more than once.";
  // is also a views so the sys auto delete it.
  HandleBarTestModel* model = new HandleBarTestModel; 
  ResourceBundle& rb = ResourceBundle::GetSharedInstance();
  HandleBar* handle = new HandleBar(model, false,
                                    rb.GetFont(ResourceBundle::MediumFont),
                                    model->GetHandleBarOffset(),
                                    model->GetHandleBarOffset() + 300);
  // for horizon handlebar
  //contents_ = new HandleBar(&model_, true,
  //                          rb.GetFont(ResourceBundle::MediumFont),
  //                          0, 300);
  handle->SetObserver(model);
  contents_ = model;
  contents_->set_background(
      views::Background::CreateSolidBackground(SkColorSetRGB(0, 0, 40)));
  views::Widget* window =
    views::Widget::CreateWindowWithBounds(this, gfx::Rect(0, 0, 450, 400));

  window->Show();
}

ExampleView* ExampleView::CreateInstance() {
  return new ExampleView();
}