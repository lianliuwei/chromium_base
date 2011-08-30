#include "gtest/gtest.h"

int Foo(int a, int b)
{
    if(a == 0 || b == 0){
        throw "don't do that";
    }
    int c = a % b;
    if (c == 0)
        return b;
    return Foo(b, c);
}

int Add(int a, int b)
{
    return a + b;
}
TEST(FooTest, HandleNoneZeroInput){
    EXPECT_EQ(2, Foo(4, 10));
    EXPECT_EQ(6, Foo(30, 18));
}

TEST(FooTest, HandleZeroInput){
    EXPECT_ANY_THROW(Foo(10, 0));
    EXPECT_THROW(Foo(0, 5), char*);
}

TEST(AddTest, TestOneAddTwo){
    EXPECT_EQ(3, Add(1, 2));
    EXPECT_EQ(4, Add(2, 1));
}

TEST(ArrayTest, TestEqual){
    int x[3] = {1, 2, 3};
    int y[3] = {1, 2, 4};
    for (int i = 0; i < 3; i++){        EXPECT_EQ(x[i], y[i]);    }    for (int i = 0; i < 3; i++){        EXPECT_EQ(x[i], y[i]) << "arrays x and y differ at index "<< i;    }
}

TEST(MacroTest, TestBool){
    EXPECT_FALSE(false);
    EXPECT_TRUE(true);
}

TEST(MacroTest, TestNum){
    EXPECT_EQ(10, 10);
    EXPECT_NE(1, 10);
    EXPECT_LT(1, 10);
    EXPECT_LE(10, 10);
    EXPECT_GT(10, 1);
    EXPECT_GE(100, 10);
    EXPECT_GE(100, 100);
    EXPECT_NEAR(100, 99, 2);
}

TEST(MacroTest, TestString){
    EXPECT_STREQ("i'm", "i'm");
    EXPECT_STRNE("i'm", "you're");
    EXPECT_STRCASEEQ("YOU", "YoU");
    EXPECT_STRCASENE("YOU", "YoX");
    EXPECT_STREQ(L"you", L"you");
    //EXPECT_STRCASEEQ(L"you", L"YOU"); no allow wchar_t
}

TEST(MacroTest, TestFloat){
    float m = 1e7;
    float n = 1e-7;
    EXPECT_FLOAT_EQ(m + n, m);
    EXPECT_PRED_FORMAT2(testing::FloatLE, m, n);
}
TEST(ExplicitTest, Demo){
    //ADD_FAILURE() << "sorry";
    //FAIL();
    //EXPECT_EQ(1, 10) << "reach here";
    GTEST_SUCCEED();
    //EXPECT_EQ(1, 10) << "no reach here";
}

bool MutuallyPrime(int m, int n){
    return Foo(m, n) > 1;
}

TEST(PredicateAssertionTest, Demo){
    int m = 5, n = 6;
    ASSERT_PRED2(MutuallyPrime, m , n);
}

testing::AssertionResult AssertFoo(const char* m_expr, const char* n_expr, const char* k_expr, int m, int n, int k){
    if(Foo(m, n) == k)
        return testing::AssertionSuccess();
    testing::Message msg;
    msg << m_expr << " 和 " << n_expr << " 的最大公约数应该是： " << Foo(m, n) << " 而不是： " << k_expr;
    return testing::AssertionFailure(msg);
}

TEST(AssertFooTest, HandleFail){
    EXPECT_PRED_FORMAT3(AssertFoo, 3, 6, 2);
}

template <typename T> class FooType {
public:
    void Bar() { testing::StaticAssertTypeEq<int, T>(); }
};

TEST(TypeAssertionTest, Demo){
    FooType<bool> fooType;
    //fooType.Bar(); //can not be compiled
}

class FooCalcTest : public testing::Test
{
protected:
    static void SetUpTestCase(){
        testCase_++;
        std::cout << "TestCase " <<testCase_ << " SetUp"  << std::endl;
    }
    static void TearDownTestCase(){
        std::cout << "TestCase " <<testCase_ << " TearDown"  << std::endl;
    }
    virtual void SetUp(){
        test_++;
        std::cout << "Test " <<test_ << " SetUp"  << std::endl;
    }
    virtual void TearDown(){
        std::cout << "Test " <<test_ << " TearDown"  << std::endl;
    }
//using private is wrong. because gtest using inherit to add test fun.
protected:
    static int testCase_;
    static int test_;
};

int FooCalcTest::testCase_ = 0;
int FooCalcTest::test_ = 0;

TEST_F(FooCalcTest, Test1)
{
}
TEST_F(FooCalcTest, Test2)
{
    std::cout << "access test_ = " << test_  << std::endl;
}

bool IsPrime(int n)
{
    if(n < 1) return false;
    if(n % 2 == 0) return n == 2;

    for (int i = 3; ; i += 2){
        if(i > n/i) break;
        if( n % i == 0) return false;
    }
    return true;
}

TEST(IsPrimeTest, HandleTrueReturn)
{
    EXPECT_TRUE(IsPrime(3));
    EXPECT_TRUE(IsPrime(5));
    EXPECT_TRUE(IsPrime(11));
    EXPECT_TRUE(IsPrime(23));
    EXPECT_TRUE(IsPrime(17));
}

class IsPrimeParamTest : public testing::TestWithParam<int>{};

TEST_P(IsPrimeParamTest, HandleTrueReturn)
{
    int n = GetParam();
    EXPECT_TRUE(IsPrime(n));
}

INSTANTIATE_TEST_CASE_P(TrueReturn, IsPrimeParamTest, testing::Values(3, 5, 11, 23, 17));


template <typename T>
class FooTypeTest : public testing::Test {
public:
    static T shared_;
    T value_;
};
template <typename T>
T FooTypeTest<T>::shared_;

typedef testing::Types<char, int, unsigned int> MyTypes;
TYPED_TEST_CASE(FooTypeTest, MyTypes);
TYPED_TEST(FooTypeTest, DoesPrintShared){
    TypeParam n = shared_;
    std::cout << shared_ << std::endl;
}
TYPED_TEST_CASE_P(FooTypeTest);
TYPED_TEST_P(FooTypeTest, DoesPrintValue){
    TypeParam n = value_;
    std::cout << value_ << std::endl;
}
REGISTER_TYPED_TEST_CASE_P(FooTypeTest, DoesPrintValue);
INSTANTIATE_TYPED_TEST_CASE_P(My, FooTypeTest, MyTypes);

void DeathFoo()
{
    int* pInt = 0;
    *pInt = 42;
}

int DieInDebugElse12(int* sideeffect){
    if (sideeffect) *sideeffect = 12;
#ifndef NDEBUG
    GTEST_LOG_(FATAL) << "debug death inside DieInDebugElse12()";
#endif
    return 12;    
}
TEST(DeathTest, FooDeathTest){
    EXPECT_EXIT(_exit(1), testing::ExitedWithCode(1), "");
    EXPECT_DEATH(DeathFoo(), "");
}

TEST(DeathTest, DebugDeathTest){
    int sideeffect = 0;
    EXPECT_DEBUG_DEATH(DieInDebugElse12(&sideeffect), "debug death");
#ifdef NDEBUG
    EXPECT_EQ(12, sideeffect);
#else
    EXPECT_EQ(0, sideeffect);
#endif
}
