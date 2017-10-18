#include <iostream>
#include "var7.h"

using namespace kali;

int main() {
    int t;
    try {
        cardioid a(-1);
    } catch(std::bad_alloc &ba) {
        std::cout << ba.what() << "\n";
    }
    if (!input_num("Enter parameter of cardioid 'a' (a > 0): ", t, 1, 10000)) {
        std::cout << "Incorrect data!\n";
        return 1;
    }
    cardioid c(t);
    while ((t = menu(c)))
        if (t < 0) {
            std::cout << "Incorrect data!\n";
            return 1;
        }

	return 0;
}
