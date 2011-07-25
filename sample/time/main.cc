#include "base/time.h"

int main(int argc, char** argv)
{
    using namespace base;
    Time t = Time::Now();
    Time::Exploded ep;
    t.LocalExplode(&ep);
    t.UTCExplode(&ep);
    TimeDelta td = TimeDelta::FromDays(2);
    TimeDelta td1 = TimeDelta::FromDays(1);
    TimeDelta td2 = td - td1;
    int day = td2.InDays();
    return 0;
}