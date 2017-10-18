#include <iostream>
#include <cmath>
#include <string>

namespace luv {

	double PI = 3.14159265359;

	class Diocle {
	private:
		double a;
	public:
		Diocle(const double = 1);
		//Diocle(const Diocle &) {};
		//~Diocle() {}
		double getA() const {
			return a;
		}
		double setA(double);
		double points(const double) const;
		double dist(double phi) const;
		double asymptote() const {
			return (2.0 * a);
		}
		double area() const {
			return (3.0 * PI * a * a);
		}
		double volume() const {
			return (2.0 * PI * PI * a * a * a);
		}
		double coef() const {
			return (4.0 * a);
		}
		std::string frm();
	};
	template <class T>
	bool GetNum(T &a) {
		std::cin >> a;
		if (!std::cin.good())
			return false;
		else return true;
	}
	void dial(Diocle &);
}
