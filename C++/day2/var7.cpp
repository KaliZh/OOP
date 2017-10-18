#include <iostream>
#include "var7.h"

namespace kali {

    int menu(cardioid &c) {
        std::cout << "\n1) Parameter of cardioid;\n2) Distance to centre;\n3) Radius of curvature;\n"
            "4) Area of cardioid;\n5) Arc length;\n6) Set parameter of cardioid;\n0) Exit.\n";
        int a, t;
        if (!input_num("Enter command (0 - 6): ", a, 0, 6))
            return -1;
        if (a == 1) {
            std::cout << "Parameter of cardioid: " << c.get_a() << std::endl;
        } else if (a == 2) {
            if (!input_num("Enter angle phi: ", t, -360, 360))
                return -1;
            std::cout << "Distance to centre: " << c.distance_to_centre(t) << std::endl;
        } else if (a == 3) {
            if (!input_num("Enter angle phi: ", t, -360, 360))
                return -1;
            std::cout << "Radius of curvature: " << c.radius_of_curvature(t) << std::endl;
        } else if (a == 4) {
            std::cout << "Area of cardioid: " << c.area() << std::endl;
        } else if (a == 5) {
            if (!input_num("Enter angle phi (-pi <= phi <= pi): ", t, -180, 180))
                return -1;
            int t2;
            if (!input_num("Enter angle phi2 (phi <= phi2 <= pi): ", t2, t, 180))
                return -1;
            std::cout << "Arc length between two angles: " << c.arc_length(t, t2) << std::endl;
        } else if (a == 6) {
            if (!input_num("Enter new parameter of cardioid 'a' (a > 0): ", t, 1, 10000))
                return -1;
            c.set_a(t);
            std::cout << "Parameter of cardioid has changed to: " << t << std::endl;
        } else {
            std::cout << "Bye!\n";
            return 0;
        }
        return 1;
    }

}
