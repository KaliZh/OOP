#include "sample.h"
#include <iostream>
#include <cmath>
#include <string>

namespace luv {
	Diocle::Diocle(const double a) {
		if (a <= 0)
			throw std::runtime_error("Wrong data!");
		else Diocle::a = a;
	}
	double Diocle::setA(double a) {
		if (a <= 0)
			throw std::runtime_error("Wrong data!");
		else return Diocle::a = a;
	}
	double Diocle::points(const double x) const {
		if (x < 0 || x >= 2.0 * a)
			throw std::runtime_error("Wrong data!");
		else return std::sqrt((pow(x, 3) / (2.0 * a - x)));
	}
	double Diocle::dist(double phi) const {
		if (phi <= -90 || phi >= 90)
			throw std::runtime_error("Wrong data!");
		else return (2.0 * a * pow((std::sin(phi * PI / 180.0)), 2)) / (std::cos(phi * PI / 180.0));
	}
	std::string Diocle::frm() {
		std::string s = std::to_string(2 * a);
		std::string str = "y^2 = x^3 / (";
		str += s;
		str += " - x)";
		return str;
	}
	void dial(Diocle &d) {
		do {
			std::cout << "1 - Change parameter.\n2 - Show parameter.\n3 - Show function.\n4 - Find 'y' by 'x'.\n"
				"5 - Find distance by given angle.\n6 - Show area.\n7 - Show asymptote.\n"
				"8 - Show volume.\n9 - Show coefficient of parabola.\n0 - Exit.\n";
			int c;
			double a;
			if (!GetNum(c)) {
				std::cout << "Wrong data!\n";
				return;
			}
			if (c == 1) {
				std::cout << "Please enter parameter: ";
				if (!GetNum(a)) {
					std::cout << "Wrong data!\n";
					return;
				}
				try {
					d.setA(a);
					std::cout << "Parameter successfully changed!\n";
				}
				catch (std::exception &ex) {
					std::cout << ex.what() << std::endl;
				}
			}
			else if (c == 2) {
				std::cout << d.getA() << std::endl << std::endl;
			}
			else if (c == 3) {
				std::cout << d.frm() << std::endl;
			}
			else if (c == 4) {
				std::cout << "Please enter x (0; " << 2 * d.getA() << "): ";
				if (!GetNum(a)) {
					std::cout << "Wrong data!\n";
					return;
				}
				try {
					double y = d.points(a);
					if (y)
						std::cout << "y1 = " << y << " y2 = " << -1.0 * y << std::endl << std::endl;
					else std::cout << y << std::endl << std::endl;
				}
				catch (std::exception &ex) {
					std::cout << ex.what() << std::endl;
				}
			}
			else if (c == 5) {
				std::cout << "Please enter angle (-90; 90): ";
				if (!GetNum(a)) {
					std::cout << "Wrong data!\n";
					return;
				}
				try {
					std::cout << d.dist(a) << std::endl << std::endl;
				}
				catch (std::exception &ex) {
					std::cout << ex.what() << std::endl << std::endl;
				}
			}
			else if (c == 6) {
				std::cout << d.area() << std::endl << std::endl;
			}
			else if (c == 7) {
				std::cout << "x = " << d.asymptote() << std::endl << std::endl;
			}
			else if (c == 8) {
				std::cout << d.volume() << std::endl << std::endl;
			}
			else if (c == 9) {
				std::cout << d.coef() << std::endl << std::endl;
			}
			else if (c == 0) {
				return;
			}
			else {
				std::cout << "You are wrong, please enter again!\n";
			}
		} while (true);
	}
}
