#include <iostream>
#include <algorithm>
int main()
{
    int a[8] = {1,2,3,4,5,6,7,8};

    std::cout << "Beforeswap: ";
    for(int i=0; i<8; ++i)
        std::cout << a[i] << ' ';
    std::cout << '\n';

    std::swap_ranges(a+0, a+2, a+5);

    std::cout << "After swap: ";
    for(int i=0; i<8; ++i)
        std::cout << a[i] << ' ';
    std::cout << '\n';
}
