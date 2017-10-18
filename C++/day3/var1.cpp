#include <iostream>
#include <limits>
#include <string.h>
#include <cmath>
#include "var1.h"

namespace kali {

    template <class T>
        bool get_Num(T &a) {
            std::cin >> a;
            if (!std::cin.good())
                return false;
            else return true;
        }

    template <class T>
        bool input_Num(const char *msg, T &a, T minn, T maxx) {
            do { 
                std::cout << msg;
                if (!get_Num(a))
                    return false;
                msg = "You are wrong, repeat please!\n";
                if (std::cin.peek() == '\n')
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            } while (a < minn || a > maxx);
            return true;
        }

    bool BigDecimal::is_SignedMagnitude(const char *c) const {
        unsigned sz = strlen(c);
        if (sz != SZ || (c[sz - 1] != '1' && c[sz - 1] != '0'))
            return false;
        for (unsigned i = 0; i < sz; i++)
            if ((int)c[i] < 48 || (int)c[i] > 57)
                return false;
        return true;
    }

    bool BigDecimal::is_Num(const char *c) const {
        unsigned sz = strlen(c);
        if (c[0] == '-')
            --sz;
        if (sz >= SZ)
            return false;
        bool bl = false;
        for (unsigned i = 0; i < sz; i++) {
            if (c[i] == '-' && i)
                return false;
            else if (c[i] != '-' && ((int)c[i] < 48 || (int)c[i] > 57))
                return false;
            else if (c[i] != '0')
                bl = true;
            else if (!bl)
                return false;
        }
        return true;
    }

    void BigDecimal::make_SignedMagnitude(const char *c) {
        n = -1;
        for (int i = SZ - 1; i >= 0; --i)
            str[i] = c[i];
        str[SZ] = '\0';
    }
    
    void BigDecimal::make_SignedMagnitudeForLong(const long l) {
        long ll = l;
        if (l < 0)
            ll *= -1;
        n = 0;
        for (; ll; ll /= 10)
            str[n++] = char((ll % 10) + 48);
        for (int i = n; i < SZ; i++)
            str[i] = '0';
        if (l < 0) 
            str[SZ - 1] = '1';
        else str[SZ - 1] = '0';
        str[SZ] = '\0';
        if (!n)
            n = 1;
    }

    void BigDecimal::make_SignedMagnitudeForChar(const char *c) {
        n = 0;
        for (int i = strlen(c) - 1; i >= 0; --i)
            str[n++] = c[i];
        if (c[0] == '-')
            str[--n] = '0';
        for (int i = n; i < SZ; i++)
            str[i] = '0';
        if (c[0] == '-')
            str[SZ - 1] = '1';
        else str[SZ - 1] = '0';
        str[SZ] = '\0';
    }

    void BigDecimal::change_Code() {
        if (get_Sign() == '1') {
            int n = 1, c;
            for (int i = 0; i < SZ - 1; i++) {
                c = 9 - ((int)str[i] - 48) + n;
                if (c > 9)
                    n = 1;
                else n = 0;
                str[i] = char((c % 10) + 48);
            }
        }
    }

    BigDecimal BigDecimal::plus_BigDecimal(BigDecimal &b) {
        if (get_Sign() == b.get_Sign() && n + b.n >= SZ)
            throw std::runtime_error("too big data");
        char c[SZ];
        change_Code();
        b.change_Code();
        int n = 0, m;
        for (int i = 0; i < SZ; i++) {
            m = ((int)str[i] - 48) + ((int)b.str[i] - 48) + n;
            if (m > 9)
                n = 1;
            else n = 0;
            c[i] = char((m % 10) + 48);
        }
        c[SZ - 1] = char((((int)c[SZ - 1] - 48) % 2) + 48);
        BigDecimal temp(c);
        change_Code();
        b.change_Code();
        temp.change_Code();
        return temp;
    }

    BigDecimal BigDecimal::minus_BigDecimal(BigDecimal &b){
        if (get_Sign() != b.get_Sign() && n + b.n >= SZ)
            throw std::runtime_error("too big data");
        char c[SZ];
        change_Code();
        if (b.get_Sign() == '1')
            b.set_Sign(0);
        else b.set_Sign(1);
        b.change_Code();
        int n = 0, m;
        for (int i = 0; i < SZ; i++) {
            m = ((int)str[i] - 48) + ((int)b.str[i] - 48) + n;
            if (m > 9)
                n = 1;
            else n = 0;
            c[i] = char((m % 10) + 48);
        }
        c[SZ - 1] = char((((int)c[SZ - 1] - 48) % 2) + 48);
        BigDecimal temp(c);
        change_Code();
        b.change_Code();
        if (b.get_Sign() == '1')
            b.set_Sign(0);
        else b.set_Sign(1);
        temp.change_Code();
        return temp;
    }

    BigDecimal BigDecimal::mult10() {
       if (n == -1) 
           find_N();
       if (n == SZ - 1)
           throw std::runtime_error("too big data");
       if (n == 1 && str[0] == '0') {
           *this = BigDecimal();
       } else {
            for (int i = 0; i < n / 2; i++)
                std::swap(str[i], str[n - i - 1]);
            str[n++] = '0';
            for (int i = 0; i < n / 2; i++)
                std::swap(str[i], str[n - i - 1]);
       }
       return *this;
    }

    BigDecimal BigDecimal::div10() {
       if (n == -1) 
           find_N();
       if (n == 1) {
           *this = BigDecimal();
       } else {
            for (int i = 0; i < n / 2; i++)
               std::swap(str[i], str[n - i - 1]);
            str[--n] = '0';
            for (int i = 0; i < n / 2; i++)
                std::swap(str[i], str[n - i - 1]);
       }
       return *this;
    }

    void BigDecimal::input() {
        int n;
        if (!input_Num("Enter number of digits: ", n, 1, 50)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max());
            throw std::runtime_error("wrong data");
        }
        if (n > 9) {
            char c[n + 1];
            const char *msg = "Enter big decimal: ";
            do {
                std::cout << msg;
                if (!std::cin.good()) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
                std::cin.getline(c, n + 1);
                msg = "You are wrong, repeat please!\n";
            } while (!std::cin.good() || (strlen(c) - n) || !is_Num(c));
            make_SignedMagnitudeForChar(c);
        } else {
            long l, maxx = pow(10, n) - 1, minn = pow(10, n - 1);
            if (!input_Num("Enter big decimal: ", l, minn, maxx)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max());
                throw std::runtime_error("wrong data");
            }
            make_SignedMagnitudeForLong(l);
        }
    }

    int menu_TestBigDecimal() {
        std::cout << "\n1) Default Constructor ();\n2) Init Constructor (long);\n3) Init Constructor (char*)\n"
            "4) input/output;\n5) plus/minus;\n6) mult10/div10;\n0) Exit.\n";
        int c;
        if (!input_Num("Enter command (0 - 6): ", c, 0, 9))
            return -1;
        if (c == 1) {
            std::cout << "Default Constructor ():\n";
            try {
                BigDecimal a;
                a.output();
                std::cout << std::endl;
            } catch (std::bad_alloc &ba) {
                std::cout << ba.what() << std::endl;
                return -1;
            }
        } else if (c == 2) {
            long l;
            if (!input_Num("Enter long int: ", l, -1 * std::numeric_limits<long>::max(), std::numeric_limits<long>::max()))
                return -1;
            std::cout << "Init Constructor (" << l << "):\n";
            try {
                BigDecimal a(l);
                a.output();
                std::cout << std::endl;
            } catch (std::bad_alloc &ba) {
                std::cout << ba.what() << std::endl;
                return -1;
            }
        } else if (c == 3) {
            std::cout << "Enter string: ";
            char c[21]; 
            std::cin.getline(c, 21);
            std::cout << "Init Constructor (" << c << "):\n";
            try {
                BigDecimal a(c);
                a.output();
                std::cout << std::endl;
            } catch (std::bad_alloc &ba) {
                std::cout << ba.what() << std::endl;
                return -1;
            }
        } else if (c == 4) {
            BigDecimal a;
            std::cout << "input():\n";
            try {
                a.input();
            } catch (std::bad_alloc &ba) {
                std::cout << ba.what() << std::endl;
                return -1;
            }
            std::cout << "output():\n";
            a.output();
            std::cout << std::endl;
        } else if (c == 5) {
            BigDecimal a, b;
            std::cout << "Enter first BigDecimal:\n";
            try {
                a.input();
            } catch (std::bad_alloc &ba) {
                std::cout << ba.what() << std::endl;
                return -1;
            }
            std::cout << "Enter second BigDecimal:\n";
            try {
                b.input();
            } catch (std::bad_alloc &ba) {
                std::cout << ba.what() << std::endl;
                return -1;
            }
            std::cout << "plus/minus:\n";
            try {
                a.plus_BigDecimal(b).output();
            } catch (std::bad_alloc &ba) {
                std::cout << ba.what() << std::endl;
                return -1;
            }
            std::cout << std::endl;
            try {
                a.minus_BigDecimal(b).output();
            } catch (std::bad_alloc &ba) {
                std::cout << ba.what() << std::endl;
                return -1;
            }
            std::cout << std::endl;
        } else if (c == 6) {
            BigDecimal a, b;
            std::cout << "Enter BigDecimal:\n";
            try {
                a.input();
            } catch (std::bad_alloc &ba) {
                std::cout << ba.what() << std::endl;
                return -1;
            }
            b = a;
            std::cout << "mult10/div10:\n";
            try {
                a.mult10().output();
            } catch (std::bad_alloc &ba) {
                std::cout << ba.what() << std::endl;
                return -1;
            }
            std::cout << std::endl;
            b.div10().output();
            std::cout << std::endl;
        } else {
            std::cout << "Bye!\n";
            return 0;
        }
        return 1;
    }

}
