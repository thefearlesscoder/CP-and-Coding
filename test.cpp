// C++ program to demonstrate the working of copy elision
// via RVO
#include <iostream>
using namespace std;

class GFG {
public:
    GFG() { cout << "GeeksforGeeks"; }
    GFG(const GFG&) // Copy Construcctor
    {
        cout << " GeeksforGeeks Copy Constructor";
    }
};

GFG func()
{
    return GFG(); // RVO example
}

int main()
{
    GFG G = func();
    return 0;
}