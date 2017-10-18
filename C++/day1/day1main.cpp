#include <iostream>
#include "day1.h"

using namespace kali;

int main() {
    bigmatrix *a = nullptr;
    a = input();
    if (!a) {
        std::cout << "Incorrect data!\n";
        return 1;
    }
    bigmatrix *b = nullptr, *c = nullptr;
    b = a->map(reversenumber);
    c = a->map(triplenumber);
    if (!b || !c) {
        a->~bigmatrix();
        if (b)
            b->~bigmatrix();
        else c->~bigmatrix();
        return 1;
    }
    std::cout << "\nSource matrix:\n";
    a->p->print();
    std::cout << "\nReverse numbers:\n";
    b->p->print();
    std::cout << "\nTriple numbers:\n";
    c->p->print();
    a->~bigmatrix();
    b->~bigmatrix();
    c->~bigmatrix();

	return 0;
}
