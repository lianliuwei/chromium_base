#include "Osc/sample/example_view.h"

#include "views/widget/widget.h"
#include "views/widget/widget_delegate.h"
#include "Osc/ui/views/yt_view.h"
#include "Osc/ui/views/yt_view_container.h"
#include "Osc/ui/views/handle_bar.h"
#include "views/background.h"
#include "ui/base/resource/resource_bundle.h"
#include "grit/ui_resources.h"
#include "third_party/skia/include/core/SkBitmap.h"

enum handleID {
    text = 0,
    icon,
    limit,
    ID_COUNT,
};

class HandleBarTestDelegate : public HandleBarDelegate
{

public:
    HandleBarTestDelegate()
        : observer_(NULL)
        , has_active_(false)
        , active_id_(-1)
        , offset_(100) {
            for (int i = 0; i < ID_COUNT; i++) {
                offsets_.push_back(i*10);
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

    int GetHandleBarOffset() { return offset_;}

private:
    HandleBarModelObserver* observer_;
    int active_id_;
    int has_active_;
    std::vector<int> offsets_;
    int offset_;
};

HandleBarTestDelegate* gWaveBarDelegate = NULL;

HandleBarTestDelegate* gHorizBarDelegate = NULL;

HandleBarTestDelegate* gTriggerBarDelegate = NULL;


HandleBarDelegate* YTView::GetWaveBarDelegate()
{
    return gWaveBarDelegate;
}

HandleBarDelegate* YTView::GetHorizOffsetBarDelegate()
{
    return gHorizBarDelegate;
}

HandleBarDelegate* YTView::GetTriggerBarDelegate()
{
    return gTriggerBarDelegate;
}
void SetChildBoard(views::View* const parent) {
    views::View::Views::const_iterator it;
    for (it = parent->children_begin();
    it != parent->children_end(); ++it) {
        (*it)->set_border(
            views::Border::CreateSolidBorder(1, SkColorSetRGB(255, 255, 255)));
    }
}

void ExampleView::Init() {
    DCHECK(contents_ == NULL) << "Run called more than once.";
    gWaveBarDelegate = new HandleBarTestDelegate;
    gHorizBarDelegate = new HandleBarTestDelegate;
    gTriggerBarDelegate = new HandleBarTestDelegate;
    YTView* yt = new YTView();
    yt->SetGrid(6, 4);
    contents_ = new YTViewContainer(yt);
    SetChildBoard(contents_);
    contents_->set_background(
        views::Background::CreateSolidBackground(SkColorSetRGB(40, 0, 0)));
    views::Widget* window =
        views::Widget::CreateWindowWithBounds(this, gfx::Rect(0, 0, 850, 400));

    window->Show();
}

ExampleView* ExampleView::CreateInstance() {
    return new ExampleView();
}