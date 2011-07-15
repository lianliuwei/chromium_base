#include <iostream>

#include "base/observer_list.h"

using namespace std;

class MyWidget {
public:

class Observer {
 public:
  virtual void OnFoo(MyWidget* w) = 0;
  virtual void OnBar(MyWidget* w, int x, int y) = 0;
};

void AddObserver(Observer* obs) {
  observer_list_.AddObserver(obs);
}

void RemoveObserver(Observer* obs) {
  observer_list_.RemoveObserver(obs);
}

void NotifyFoo() {
  FOR_EACH_OBSERVER(Observer, observer_list_, OnFoo(this));
}

void NotifyBar(int x, int y) {
  FOR_EACH_OBSERVER(Observer, observer_list_, OnBar(this, x, y));
}

private:
ObserverList<Observer> observer_list_;
};

class Obsever1 : public MyWidget::Observer
{
    virtual void OnFoo( MyWidget* w ) 
    {
        cout<<"in observer1.OnFoo"<<endl;
    }

    virtual void OnBar( MyWidget* w, int x, int y ) 
    {
        cout<<"in observer1.OnBar"<<endl;
    }

};

class Observer2 : public MyWidget::Observer
{
public:
    Observer2(){
        observer_ = NULL;
    }
    virtual void OnFoo( MyWidget* w ) 
    {
        cout<<"in observer2.OnFoo"<<endl;
        if (observer_ != NULL)
        {
            cout<<"remove Observer in Iterator"<<endl;
            w->RemoveObserver(observer_);
        }
    }

    virtual void OnBar( MyWidget* w, int x, int y ) 
    {
        cout<<"in observer2.OnBar"<<endl;
    }
    void removeObserverInOnfoo(MyWidget::Observer* observer)
    {
        observer_ = observer;
    }
private:
    MyWidget::Observer* observer_;
};

class Observer3 : public MyWidget::Observer
{
    

    virtual void OnFoo( MyWidget* w ) 
    {
        cout<<"in observer3.OnFoo"<<endl;
        cout<<"Observer3 remove itself"<<endl;
        w->RemoveObserver(this);
    }

    virtual void OnBar( MyWidget* w, int x, int y ) 
    {
        cout<<"in observer3.OnBar"<<endl;
    }

};
int main(int argc, char** argv)
{
    MyWidget widget;
    Obsever1 ob1;
    Observer2 ob2;
    Observer3 ob3;

    widget.AddObserver(&ob1);
    widget.AddObserver(&ob2);
    widget.AddObserver(&ob3);
    widget.NotifyFoo();
    widget.NotifyBar(1, 2);
    ob2.removeObserverInOnfoo(&ob1);
    widget.NotifyFoo();
    widget.NotifyBar(1, 2);

    return 0;
}