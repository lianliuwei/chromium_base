class WaveViewViews : public WaveView {
 public:
  
 protected:
  
 private:
  
};

// how to create the views map to the wave obj.
class WaveViewFactoryViews : public WaveViewFactory {

};

static WaveViewFactoryViews g_factory;

class WaveContainerViews  {
 public:
   AddViews(WaveViewViews* view) {

   }

   CreateWaveView() {
     WaveContainer::WaveIterator it;
     for (it = container_->begin(); it != container_->end(), ++it) {
       // cast to Views Platform root class
       AddViews(static_cast<WaveViewViews*> it->CreateView(g_factory));
     }
   }
 protected:
  
 private:
  WaveContainer* container_;
};

void Init (WaveContainer* container,  CWnd* wnd ){
  WaveContainerViews* container_view = new WaveContainerViews(container, wnd);
}

// create single measure line.
{
    views* add_views = NULL;
    WaveContainer* container = NULL;
    container->AddMeasureLine(new MeasureSingleLine(add_views));
}