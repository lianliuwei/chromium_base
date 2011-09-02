#ifndef FOOMOCK_H_
#define FOOMOCK_H_

#include <string>

#include "gmock/gmock.h"
#include "FooInterface.h"

namespace seamless {

class MockFoo : public FooInterface {
public:
    MOCK_METHOD0(getArbitraryString, std::string());
    MOCK_METHOD1(setValue, void(std::string& value));
    MOCK_METHOD2(setDoubleValues, void(int x, int y));
};

} //namespace sealess
#endif //FOOMOCK_H_