#include "view.h"

#include "views/layout/box_layout.h"
#include "ui/gfx/canvas_skia.h"

class focusView : public views::View {
public:
    focusView();
    virtual ~focusView() {};
    virtual void OnPaint(gfx::Canvas* canvas);
    virtual bool OnMousePressed(const views::MouseEvent& event);
    virtual gfx::Size GetPreferredSize();
};

focusView::focusView() {
    set_focusable(true);
}

void focusView::OnPaint(gfx::Canvas* canvas){
    SkColor color = HasFocus() ? SkColorSetRGB(255, 0, 0) 
        : SkColorSetRGB(0, 255, 0);
    canvas->FillRectInt(color, 2, 2, width() - 4 , height() - 4);
    View::OnPaint(canvas);
}

gfx::Size focusView::GetPreferredSize(){
    return gfx::Size(100, 100);
}

bool focusView::OnMousePressed(const views::MouseEvent& event) {
    RequestFocus();
    return true;
}

ExampleView::ExampleView() : contents_(NULL) {}

void ExampleView::Init(gfx::NativeWindow parent) {
    using namespace views;
    DCHECK(contents_ == NULL) << "Run called more than once.";
    focusView* view;
    contents_ = new views::View();
    contents_->set_background(
        views::Background::CreateSolidBackground(25, 25, 25));
    for (int i = 0; i < 5; i++)
    {
        views::View* hcontent =new views::View();
        contents_->AddChildView(hcontent);
        for (int i = 0; i < 5; i++)
        {
            view = new focusView();
            hcontent->AddChildView(view);
        }
        hcontent->SetLayoutManager(new views::BoxLayout(
            views::BoxLayout::kHorizontal, 10, 10, 10));
    }

    contents_->SetLayoutManager(new views::BoxLayout(
        views::BoxLayout::kVertical, 10, 10, 10));
    Widget* widget = new Widget;
    AttachToNativeWindow(parent, widget);
    widget->SetSize(contents_->GetPreferredSize());
    widget->Show();
}

bool ExampleView::CanResize() const {
    return false;
}

bool ExampleView::CanMaximize() const {
    return true;
}

std::wstring ExampleView::GetWindowTitle() const {
    return L"";
}

views::View* ExampleView::GetContentsView() {
    return contents_;
}

void ExampleView::WindowClosing() {
}

views::Widget* ExampleView::GetWidget() {
    return contents_->GetWidget();
}

const views::Widget* ExampleView::GetWidget() const {
    return contents_->GetWidget();
}

views::NonClientFrameView* ExampleView::CreateNonClientFrameView(){
    return NULL;
}

void ExampleView::AttachToNativeWindow( gfx::NativeWindow parent, views::Widget* widget )
{
    views::Widget::InitParams params;
    params.delegate = this;
    params.parent = parent;
    params.child = true;
    params.top_level = true; // need to find the topmost focusmanager
    params.type = views::Widget::InitParams::TYPE_CONTROL; // only this type can be add as child View
    widget->Init(params);
    widget->SetContentsView(contents_); // must after Init because it use root_view
}
