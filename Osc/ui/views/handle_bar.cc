#include "Osc/ui/views/handle_bar.h"

#include "base/stl_util.h"
#include "Osc/ui/views/handle_bar_model.h"
#include "Osc/ui/views/handle_bar_observer.h"

using namespace base;
using namespace views;

HandleBar::HandleBar(HandleBarModel* model, 
                     bool is_horiz, 
                     gfx::Font font, SkColor color, 
                     int start, int end)
                     : model_(model)
                     , is_horiz_(is_horiz)
                     , font_(font)
                     , color_(color) {
                         SetMoveRange(start, end);
                         UpdateFromModel();

}

void HandleBar::OnModelChanged()
{
    UpdateFromModel();
}

void HandleBar::OnHandleChanged( int ID )
{
    UpdateHandle(ID);
}

void HandleBar::OnHandleMoved(int ID)
{
    UpdateHandlePos(ID);
}

bool HandleBar::IsHorizontal() const
{
    return is_horiz_;
}

void HandleBar::SetModel( HandleBarModel* model )
{
    if (model == model_)
        return;

    if (model_)
        model_->SetObserver(NULL);
    model_ = model;
    if(model_)
        model_->SetObserver(this);
    UpdateFromModel();
}

void HandleBar::ActiveHandle( int ID )
{
    Handle* handle = GetHandle(ID);
    // move the handle to 0 so it's draw first, look like it's on top.
    ReorderChildView(handle, 0);
    // draw the handle to show the on top effect.
    handle->SchedulePaint();
    // notify the observer the ID handle is active.
    observer_->OnHandleActive(true, ID);
}

void HandleBar::MoveHandle( int ID, int dest )
{
    Handle* handle = GetHandle(ID);
    DCHECK(handle) << "can not find the handle from ID: " << ID;
    if (observer_)
    {
        observer_->OnHandleMove(ID, CalculateOffset(dest, handle->width()));
    }
    
}

void HandleBar::UpdateFromModel() {
    for (std::vector<Handle*>::iterator it = handles_.begin();
        it != handles_.end();
        it++) {
        RemoveChildView(*it);
        delete *it;
    }
    handles_.clear();
    // may be no model
    if (model_) {
        for (int i = 0; i < model_->Count(); i++) {
            Handle* handle = new Handle(this);
            SetHandle(handle, model_->GetID(i));
            AddChildView(handle);
            handles_.push_back(handle);
        }
    }
}

void HandleBar::UpdateHandle(int ID) {
    Handle* handle = GetHandle(ID);
    SetHandle(handle, ID);
    SetHandlePos(handle, ID);
    UpdateHandlePos(ID);
}

void HandleBar::UpdateHandlePos(int ID) {
    Handle* handle = GetHandle(ID);
    SetHandlePos(handle, ID);
}

// offset = dest + width / 2 - start_
int HandleBar::CalculateOffset(int dest, int width) const {
    // now the middle of the handle control is the offset value
    return dest + width / 2 - start_;
}

int HandleBar::CalculateDest(int offset, int width) const {
    // from the middle calcuate the handle x or y
    return offset - width / 2 + start_;
}

void HandleBar::SetHandle( Handle* handle, int ID )
{
    handle->SetVisible(model_->IsVisible(ID));
    handle->SetEnabled(model_->IsEnable(ID));
    handle->SetFont(font_);
    handle->SetEnabledColor(color_);
    handle->SetDisabledColor(color_);
    handle->SetHighlightColor(color_);
    handle->SetHoverColor(color_);
    handle->SetTextHaloColor(color_);
    handle->ClearMaxTextSize(); // so can be small
    handle->SetText(model_->GetText(ID));
    handle->SetIcon(model_->GetIcon(ID));
    handle->SetHoverIcon(model_->GetIcon(ID));
    handle->SetPushedIcon(model_->GetIcon(ID));
    handle->set_tag(ID);
    handle->set_icon_placement(TextButton::ICON_ON_LEFT);
    handle->set_alignment(TextButton::ALIGN_CENTER);
}

void HandleBar::SetHandlePos( Handle* handle, int ID )
{
    int width = IsHorizontal() ? handle->width() : handle->height();
    int dest = CalculateDest(model_->GetOffset(ID), width);
    IsHorizontal() ? handle->SetX(dest) : handle->SetY(dest);
}

void HandleBar::SetMoveRange( int start, int end )
{
    CHECK(start < end);
    start_ = start;
    end_ = end;
}
