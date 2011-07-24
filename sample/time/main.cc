#include "base/time.h"

int main(int argc, char** argv)
{
    using namespace base;
    Time t = Time::Now();
    Time::Exploded ep;
    t.LocalExplode(&ep);
    t.UTCExplode(&ep);
 
    return 0;
}