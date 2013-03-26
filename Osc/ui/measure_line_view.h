// MeasureLineView can take care the delete of the Measureline.
class MeasureLineView {
public:
  Show();
  Hide();
  IsShow();
  
  // Notify to fetch data for MeasureLine.
  PropertyChanged();
  RangeChanged();

  NeedDelete();
  NeedDeleteWithModel();
protected:

private:

};
