#include "a.hpp"  // first line should be include of hpp with solutions!
// this is driver code for a problem
#include <iostream>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    int a, b;
    std::cin >> a >> b;
    int c = a::solve(a, b);
    std::cout << c << '\n';
}
