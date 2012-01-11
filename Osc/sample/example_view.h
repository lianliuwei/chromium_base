#pragma once

#include "views/widget/widget.h"
#include "views/widget/widget_delegate.h"
#include "base/message_loop.h"

class ExampleView : public views::WidgetDelegate {
public:
  ExampleView() : contents_(NULL) {};
  virtual ~ExampleView() {};

  // Creates all the examples and shows the window.
  virtual void Init();

  static ExampleView* CreateInstance();

protected:
  // views::WidgetDelegate implementation:
  virtual bool CanResize() const OVERRIDE {
    return true;
  }

  virtual bool CanMaximize() const OVERRIDE {
    return true;
  }

  virtual std::wstring GetWindowTitle() const OVERRIDE {
    return L"Views Examples";
  }

  virtual views::View* GetContentsView() OVERRIDE {
    return contents_;
  }

  virtual void WindowClosing() OVERRIDE {
    MessageLoopForUI::current()->Quit();
  }

  virtual views::Widget* GetWidget() OVERRIDE {
    return contents_->GetWidget();
  }

  virtual const views::Widget* GetWidget() const OVERRIDE {
    return contents_->GetWidget();
  }


  views::View* contents_;

  DISALLOW_COPY_AND_ASSIGN(ExampleView);
};
