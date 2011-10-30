#pragma once

#include "views/widget/widget.h"
#include "views/widget/widget_delegate.h"

class ExampleView : public views::WidgetDelegate {
public:
    ExampleView();
    virtual ~ExampleView() {};

    // Creates all the examples and shows the window.
    void Init(gfx::NativeWindow parent);

    void AttachToNativeWindow( gfx::NativeWindow parent, views::Widget* widget );

private:
    // views::WidgetDelegate implementation:
    virtual bool CanResize() const OVERRIDE;
    virtual bool CanMaximize() const OVERRIDE;
    virtual std::wstring GetWindowTitle() const OVERRIDE;
    virtual views::View* GetContentsView() OVERRIDE;
    virtual void WindowClosing() OVERRIDE;
    virtual views::Widget* GetWidget() OVERRIDE;
    virtual const views::Widget* GetWidget() const OVERRIDE;
    virtual views::NonClientFrameView* CreateNonClientFrameView() OVERRIDE;
    views::View* contents_;

    DISALLOW_COPY_AND_ASSIGN(ExampleView);
};
