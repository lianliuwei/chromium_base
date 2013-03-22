enum DigitNodeType {
  kEmpty;
  kLink;
  
};
struct DigitNode {
  DigitNodeType type;
  string name;
  Color color;
  string data;
  icon;
  double length;
};

class SimpleDigitWaveData {
 public:
  Range range;
  vector<DigitNode> nodes_;
  DigitNode& GetNode(double offset) const;
  vector<DigitNode*> GetRangeNode(double start, double offset) const;
  vector<DigitNode*> FindNode(string key);
 protected:
  
 private:
  
};

class SimpleDigitWave {
public:
  GetData();
protected:

private:

};
