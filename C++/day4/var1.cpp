#include <string.h>
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

    bool BigDecimal::is_Num(const char *c) const {
        bool bl = false;
        for (unsigned i = 0; i < strlen(c); i++) {
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
    
    BigDecimal::BigDecimal(const long l) {
        long ll = l;
        char *buf = new char[10];
        if (l < 0)
            ll *= -1;
        n = 0;
        for (; ll; ll /= 10)
            buf[n++] = char((ll % 10) + 48);
        if (l < 0) 
            sign = 1;
        else sign = 0;
        str = new char[n];
        for (int i = 0; i < n; i++)
            str[i] = buf[i];
        delete[] buf;
    }

    BigDecimal::BigDecimal(const char *c) {
        if (!is_Num(c)) {
            throw std::runtime_error("wrong data");
        } else {
            str = new char[strlen(c)];
            n = 0;
            if (c[0] == '-') {
                sign = 1;
                for (int i = strlen(c) - 1; i > 0; --i)
                    str[n++] = c[i];
            } else {
                sign = 0;
                for (int i = strlen(c) - 1; i >= 0; --i)
                    str[n++] = c[i];
            }
        }
    }

    BigDecimal& BigDecimal::operator=(const BigDecimal &a) {
        if (this != &a) {
            n = a.n;
            delete[] str;
            str = new char[n];
            for (int i = 0; i < n; i++)
                str[i] = a.str[i];
            sign = a.sign;
        }
        return *this;
    }

    BigDecimal& BigDecimal::operator=(BigDecimal &&a) {
        n = a.n;
        char *temp = str;
        str = a.str;
        a.str = temp;
        sign = a.sign;
        return *this;
    }

    void BigDecimal::operator()(BigDecimal &a) {
        if(n < a.n) {
            char *temp = str;
            str = new char[a.n + 1];
            for (int i = 0; i < n; i++)
                str[i] = temp[i];
            for (int i = n; i <= a.n; i++)
                str[i] = '0';
            delete[] temp;
            temp = a.str;
            a.str = new char[a.n + 1];
            for (int i = 0; i < a.n; i++)
                a.str[i] = temp[i];
            a.str[a.n] = '0';
            delete[] temp;
            n = ++a.n;
        } else {
            char *temp = a.str;
            a.str = new char[n + 1];
            for (int i = 0; i < a.n; i++)
                a.str[i] = temp[i];
            for (int i = a.n; i <= n; i++)
                a.str[i] = '0';
            delete[] temp;
            temp = str;
            str = new char[n + 1];
            for (int i = 0; i < n; i++)
                str[i] = temp[i];
            str[n] = '0';
            delete[] temp;
            a.n = ++n;
        }
    }

    void BigDecimal::operator!() {
        if (sign) {
            int a = 1, b;
            for (int i = 0; i < n; i++) {
                b = 9 - ((int)str[i] - 48) + a;
                if (b > 9)
                    a = 1;
                else a = 0;
                str[i] = char((b % 10) + 48);
            }
            sign = (sign + a) % 2;
        }
    }

    void BigDecimal::operator~() {
        if (n == 1 || str[n - 1] != '0')
            return;
        char *temp = str;
        while(str[--n] == '0' && n);
        str = new char[++n];
        for (int i = 0; i < n; i++)
            str[i] = temp[i];
        delete[] temp;
    }

    const BigDecimal operator+(const BigDecimal &aa, const BigDecimal &bb) {
        BigDecimal a(aa), b(bb);
        a(b);
        !a;
        !b;
        char *c = new char[a.n];
        int n = 0, m;
        for (int i = 0; i < a.n; i++) {
            m = ((int)a.str[i] - 48) + ((int)b.str[i] - 48) + n;
            if (m > 9)
                n = 1;
            else n = 0;
            c[i] = char((m % 10) + 48);
        }
        BigDecimal temp;
        temp.n = a.n;
        delete[] temp.str;
        temp.str = c;
        temp.sign = (a.sign + b.sign + n) % 2;
        !temp;
        ~temp;
        return temp;
    }

    const BigDecimal operator-(const BigDecimal &aa, const BigDecimal &bb) {
        BigDecimal a(aa), b(bb);
        a(b);
        !a;
        if (b.sign)
            b.sign = 0;
        else b.sign = 1;
        !b;
        char *c = new char[a.n];
        int n = 0, m;
        for (int i = 0; i < a.n; i++) {
            m = ((int)a.str[i] - 48) + ((int)b.str[i] - 48) + n;
            if (m > 9)
                n = 1;
            else n = 0;
            c[i] = char((m % 10) + 48);
        }
        BigDecimal temp;
        temp.n = a.n;
        delete[] temp.str;
        temp.str = c;
        temp.sign = (a.sign + b.sign + n) % 2;
        !temp;
        ~temp;
        return temp;
    }

    /*const BigDecimal BigDecimal::operator+(const BigDecimal &bb) const {
        BigDecimal a(*this), b(bb);
        a(b);
        !a;
        !b;
        char *c = new char[a.n];
        int n = 0, m;
        for (int i = 0; i < a.n; i++) {
            m = ((int)a.str[i] - 48) + ((int)b.str[i] - 48) + n;
            if (m > 9)
                n = 1;
            else n = 0;
            c[i] = char((m % 10) + 48);
        }
        BigDecimal temp;
        temp.n = a.n;
        delete[] temp.str;
        temp.str = c;
        temp.sign = (a.sign + b.sign + n) % 2;
        !temp;
        ~temp;
        return temp;
    }

    const BigDecimal BigDecimal::operator-(const BigDecimal &bb) const {
        BigDecimal a(*this), b(bb);
        a(b);
        !a;
        if (b.sign)
            b.sign = 0;
        else b.sign = 1;
        !b;
        char *c = new char[a.n];
        int n = 0, m;
        for (int i = 0; i < a.n; i++) {
            m = ((int)a.str[i] - 48) + ((int)b.str[i] - 48) + n;
            if (m > 9)
                n = 1;
            else n = 0;
            c[i] = char((m % 10) + 48);
        }
        BigDecimal temp;
        temp.n = a.n;
        delete[] temp.str;
        temp.str = c;
        temp.sign = (a.sign + b.sign + n) % 2;
        !temp;
        ~temp;
        return temp;
    }*/

    BigDecimal& BigDecimal::mult10() {
        ~(*this);
        if (n == 1 && str[0] == '0') {
            return *this;
        } else {
            for (int i = 0; i < n / 2; i++)
                std::swap(str[i], str[n - i - 1]);
            str[n++] = '0';
            for (int i = 0; i < n / 2; i++)
                std::swap(str[i], str[n - i - 1]);
            return *this;
        }
    }

    BigDecimal& BigDecimal::div10() {
        ~(*this);
        if (n == 1) {
            delete[] str;
            str = new char[1];
            str[0] = '0';
        } else {
            for (int i = 0; i < n / 2; i++)
                std::swap(str[i], str[n - i - 1]);
            str[--n] = '0';
            for (int i = 0; i < n / 2; i++)
                std::swap(str[i], str[n - i - 1]);
        }
        return *this;
    }

    std::istream& operator>>(std::istream &s, BigDecimal &a) {
        char buf[256];
        s >> buf;
        if (s.good()) {
            if (!a.is_Num(buf)) {
                s.setstate(std::ios::failbit);
            } else {
                delete[] a.str;
                a.str = new char[strlen(buf)];
                a.n = 0;
                if (buf[0] == '-') {
                    a.sign = 1;
                    for (int i = strlen(buf) - 1; i > 0; --i)
                        a.str[a.n++] = buf[i];
                } else {
                    a.sign = 0;
                    for (int i = strlen(buf) - 1; i >= 0; --i)
                        a.str[a.n++] = buf[i];
                }
            }
        }    
        return s;
    }

    std::ostream& operator<<(std::ostream &s, BigDecimal &a) {
        ~a;
        if (a.sign)
            s << '-';
        for (int i = a.n - 1; i >= 0; --i)
            s << a.str[i];
        return s;
    }

    void TestBigDecimal() {
        BigDecimal a;
        std::cout << "Testing BigDecimal..\n1. BigDecimal a; // default constructor" << std::endl;
        std::cout << "  Result--> a = " << a << std::endl << std::endl;
        BigDecimal b = a++; 
        std::cout << "2. BigDecimal b = a++; // copy constructor and overloaded postfix operator++" << std::endl;
        std::cout << "  Result--> b = " << b << std::endl;
        std::cout << "      a = " << a << std::endl << std::endl;
        a -= 100;
        std::cout << "3. a -= 100; // overloaded operator-= and init constructor" << std::endl;
        std::cout << "  Result--> a = " << a << std::endl << std::endl;
        BigDecimal c = b + a;
        std::cout << "4. BigDecimal c = b + a; // copy constructor and overloaded operator+" << std::endl;
        std::cout << "  Result--> c = " << c << std::endl << std::endl;
        a.div10();
        b.mult10();
        std::cout << std::endl << "5. a.div10(); b.mult10; // class method div10; class method mult10" << std::endl;
        std::cout << "  Result--> a = " << a << std::endl;
        std::cout << "      b = " << b << std::endl << std::endl;
        c = a - b;
        std::cout << "6. c = a - b; // overloaded operator= and overloaded operator-" << std::endl;
        std::cout << "  Result--> c = " << c << std::endl << std::endl;
        BigDecimal d("-100200300400500");
        std::cout << "7. BigDecimal d(-100200300400500)); // init constructor" << std::endl;
        std::cout << "  Result--> d = " << d << std::endl << std::endl;
        a = b.mult10() + d.div10() - ++c;
        std::cout << "8. a = b.mult10() + d.div10() - ++c" << std::endl;
        std::cout << "  Result--> a = " << a << std::endl;
        std::cout << "      b = " << b << std::endl;
        std::cout << "      c = " << c << std::endl;
        std::cout << "      d = " << d << std::endl << std::endl;
        std::cout << "9. cin >> d; // overloaded operator>> please enter BigDecimal" << std::endl;
        std::cin >> d;
        std::cout << "  Result--> d = " << d << std::endl << std::endl;
        std::cout << "10. BigDecimal(--00zwe234); // throw exception" << std::endl;
        BigDecimal("--00zwe234");
    }

    /*void BigDecimal::check() {
        BigDecimal a(234), b(-120), c;
        c = a + b;
        a = c - b - b;
        b = b + a + c;
        c = a + b - 5000;
        std::cout << a.n << " " << a.sign << std::endl;
        for (int i = 0; i < a.n; i++)
            std::cout << a.str[i];
        std::cout << std::endl;
        std::cout << b.n << " " << b.sign << std::endl;
        for (int i = 0; i < b.n; i++)
            std::cout << b.str[i];
        std::cout << std::endl;
        std::cout << c.n << " " << c.sign << std::endl;
        for (int i = 0; i < c.n; i++)
            std::cout << c.str[i];
        std::cout << std::endl;
        a += b;
        b -= 23;
        c += (a += 1);
        std::cout << a.n << " " << a.sign << std::endl;
        for (int i = 0; i < a.n; i++)
            std::cout << a.str[i];
        std::cout << std::endl;
        std::cout << b.n << " " << b.sign << std::endl;
        for (int i = 0; i < b.n; i++)
            std::cout << b.str[i];
        std::cout << std::endl;
        std::cout << c.n << " " << c.sign << std::endl;
        for (int i = 0; i < c.n; i++)
            std::cout << c.str[i];
        std::cout << std::endl;
        a = ++c;
        std::cout << a.n << " " << a.sign << std::endl;
        for (int i = 0; i < a.n; i++)
            std::cout << a.str[i];
        std::cout << std::endl;
        std::cout << c.n << " " << c.sign << std::endl;
        for (int i = 0; i < c.n; i++)
            std::cout << c.str[i];
        std::cout << std::endl;
        b = a--;
        std::cout << b.n << " " << b.sign << std::endl;
        for (int i = 0; i < b.n; i++)
            std::cout << b.str[i];
        std::cout << std::endl;
        std::cout << a.n << " " << a.sign << std::endl;
        for (int i = 0; i < a.n; i++)
            std::cout << a.str[i];
        std::cout << std::endl;
        BigDecimal d;
        a.mult10();
        b.mult10();
        c.mult10();
        d.mult10();
        std::cout << a.n << " " << a.sign << std::endl;
        for (int i = 0; i < a.n; i++)
            std::cout << a.str[i];
        std::cout << std::endl;
        std::cout << b.n << " " << b.sign << std::endl;
        for (int i = 0; i < b.n; i++)
            std::cout << b.str[i];
        std::cout << std::endl;
        std::cout << c.n << " " << c.sign << std::endl;
        for (int i = 0; i < c.n; i++)
            std::cout << c.str[i];
        std::cout << std::endl;
        std::cout << d.n << " " << d.sign << std::endl;
        for (int i = 0; i < d.n; i++)
            std::cout << d.str[i];
        std::cout << std::endl;
        a.div10();
        b.div10();
        c.div10();
        d.div10();
        std::cout << a.n << " " << a.sign << std::endl;
        for (int i = 0; i < a.n; i++)
            std::cout << a.str[i];
        std::cout << std::endl;
        std::cout << b.n << " " << b.sign << std::endl;
        for (int i = 0; i < b.n; i++)
            std::cout << b.str[i];
        std::cout << std::endl;
        std::cout << c.n << " " << c.sign << std::endl;
        for (int i = 0; i < c.n; i++)
            std::cout << c.str[i];
        std::cout << std::endl;
        std::cout << d.n << " " << d.sign << std::endl;
        for (int i = 0; i < d.n; i++)
            std::cout << d.str[i];
        std::cout << std::endl;
        std::cin >> a >> b >> c;
        std::cout << a << " " << b << " " << c << std::endl;
        d = a + b - c;
        std::cout << d << std::endl;
        a = ++b + c.mult10();
        std::cout << a << std::endl;
        std::cout << b << std::endl;
        std::cout << c << std::endl;
        b = c-- - a.div10();
        std::cout << a << std::endl;
        std::cout << b << std::endl;
        std::cout << c << std::endl;
    }*/

}
