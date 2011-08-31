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