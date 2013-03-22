class WaveViewViews : public WaveView {
 public:
  
 protected:
  
 private:
  
};

class WaveContainerViews  {
 public:
   AddViews(WaveViewViews* view) {

   }

   CreateWaveView() {
     WaveContainer::WaveIterator it;
     for (it = container_->begin(); it != container_->end(), ++it) {
       // cast to Views Platform root class
       AddViews(static_cast<WaveViewViews*> it->CreateView(container_));
     }
   }
 protected:
  
 private:
  WaveContainer* container_;
};

void Init (WaveContainer* container,  CWnd* wnd ){
  WaveContainerViews* container_view = new WaveContainerViews(container, wnd);
}