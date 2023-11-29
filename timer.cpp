#include <cstdio>
#include <iostream>
#include <ctime>
using namespace std;

int main()
{

    int delay;
    cout << "Enter the time in seconds to be delayed:" << flush;

    cin >> delay;
    delay *= CLOCKS_PER_SEC;

    clock_t now = clock();

    while (clock() - now < delay)
        ;

    cout << "Message Show after delay that you entered" << endl;

    return 0;
}