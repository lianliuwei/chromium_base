#include <iostream>
#include "base/basictypes.h"

int main(int argc, char** argv)
{
    using namespace std;
    int64 int64Array[] = {1L, 2L, 3L, 4L, 5L};

    cout << "int64Array Size: " << arraysize(int64Array) << endl;
    cout << "int64Array unsafe array Size: " << ARRAYSIZE_UNSAFE(int64Array) 
        << endl;

    return 0;
}