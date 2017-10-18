#include "sample.h"
#include <iostream>

using namespace luv;

int main() {
	std::cout << "Cissoid of Diocles\n";
	std::cout << "Please enter parameter: ";
	double a;
	if (!GetNum(a)) {
		std::cout << "Wrong data!";
		return 1;
	}
	try {
		Diocle d(a);
		dial(d);
	}
	catch (std::exception &ex) {
		std::cout << ex.what() << std::endl;
		return 1;
	}
}
