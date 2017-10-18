#include <cmath>
#include <iostream>

namespace kali {

    const double pi = 3.14159265359;

    class cardioid {
        private:
        double a; // a > 0, phi - radians
        // r = 2a(1 - cos(phi))
        public:
        cardioid() : a(0) {}
        cardioid(const double a) {
            if (a < 1) 
                throw std::runtime_error("incorrect parameter");
            cardioid::a = a;
        }
        cardioid(const cardioid &) {}
        ~cardioid() {}
        void set_a(const double a) {
            if (a < 1)
                throw std::runtime_error("incorrect parameter");
            cardioid::a = a;
        }
        double get_a() const {
            return a;
        }
        double distance_to_centre(int phi) const {
            phi %= 360;
            return (2.0 * a) * (1.0 + std::cos(phi * pi / 180));
        }
        //double long_points() {
        //}
        double radius_of_curvature(int phi) const {
            phi %= 360;
            return (std::pow(2.0, (5.0 / 2.0)) * a * std::pow((1.0 + std::cos(phi * pi / 180.0)), (1.0 / 2.0))) / 3.0;
        }
        double area() const {
            return (3.0 * pi * pow(a, 2.0)) / 2.0;
        }
        double arc_length(int phi, int phi2) const { 
            (phi %= 360) /= 2;
            (phi2 %= 360) /= 2;
            return 8.0 * a * (std::sin(phi2 * pi / 180.0) - std::sin(phi * pi / 180.0));
        }
    };

    int menu(cardioid &);

    template <class T>
        bool get_num(T &a) {
            std::cin>> a;
            if (!std::cin.good())
                return false;
            else return true;
        }

    template <class T>
        bool input_num(const char *msg, T &a, T minn, T maxx) {
            do {
                std::cout << msg;
                if (!get_num(a))
                    return false;
                msg = "You are wrong, repeat please!\n";
            } while (a < minn || a > maxx);
            return true;
        }

}
