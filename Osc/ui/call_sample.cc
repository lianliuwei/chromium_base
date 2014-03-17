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

// Views Init.
void Init (WaveContainer* container,  CWnd* wnd ){
  WaveContainerViews* container_view = new WaveContainerViews(container, wnd);
}

// create single measure line.
{
    views* add_views = NULL;
    WaveContainer* container = NULL;
    SingleLine* line = new SingleLine();
    container->AddMeasureLine(line, add_views);
    
    // get the data
    double data = add_views->GetData(line->pos());
    // create task for async measure.
    // show all measure result.
    ChannelManager->UpdateMeasureTable();
}

// idea for chrome WebContents.
// need WaveUserData same as WebContentsUserData
class CANalyzerWaveHelper : public WaveUserData<CANalyzerWaveHelper> {
 public:
   
 protected:
  
 private:
  
};

// extern the Wave object.
{ 
  Wave* wave = NULL;
  // SupportsUserData
  CANalyzerWaveHelper* wave_helper = CANalyzerWaveHelper::FromWave(wave);
  DCHECK(wave_helper) << "need CANAalyzerWave.";
  DisplayType display = wave_helper->display();
  string display = wave_helper->message();
}