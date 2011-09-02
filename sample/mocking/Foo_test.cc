#include <gmock/gmock.h>

#include "FooMock.h"

using namespace seamless;
using namespace std;

TEST(FooTest, TestGetArbitraryString)
{
    string value = "Hello World!";
    MockFoo mockFoo;
    EXPECT_CALL(mockFoo, getArbitraryString())
        .Times(1)
        .WillOnce(testing::Return(value));
    string returnValue = mockFoo.getArbitraryString();
    cout << "Return Value: " << returnValue << endl;
}

TEST(FooTest, TestSetValues)
{
    MockFoo mockFoo;
    string value = "Hello World!";
    EXPECT_CALL(mockFoo, setValue(testing::_));
    mockFoo.setValue(value);
}

TEST(FooTest, TestSetDoubleValues)
{
    MockFoo mockFoo;
    EXPECT_CALL(mockFoo, setDoubleValues(testing::Eq(1), testing::Ge(1)));
    mockFoo.setDoubleValues(1, 1);
    //mockFoo.setDoubleValues(1, 0); //error
}