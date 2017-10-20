#include <iostream>
#include <limits>
#include <exception>

namespace kali {

    class BigDecimal {
        friend std::istream& operator>>(std::istream&, BigDecimal&);
        friend std::ostream& operator<<(std::ostream&, BigDecimal&);
        friend const BigDecimal operator+(const BigDecimal&, const BigDecimal&);
        friend const BigDecimal operator-(const BigDecimal&, const BigDecimal&);
        private:
            int n;
            char *str;
            bool sign;
            bool is_Num(const char*) const;
            void operator() (BigDecimal&);
            void operator~();
            void operator!();
        public:
            BigDecimal() : n(1), str(new char[1]), sign(0) {
                str[0] = '0';
            }
            BigDecimal(const long l);
            BigDecimal(const char* c);
            BigDecimal(const BigDecimal &a) : n(a.n), str(new char[a.n]), sign(a.sign) {
                for (int i = 0; i < n; i++)
                    str[i] = a.str[i];
            }
            BigDecimal(BigDecimal &&a) : n(a.n), str(a.str), sign(a.sign) {
                a.str = nullptr;
            }
            ~BigDecimal() {
                delete[] str;
            }
            BigDecimal& operator=(const BigDecimal&);
            BigDecimal& operator=(BigDecimal&&);
            //const BigDecimal operator+(const BigDecimal&) const;
            //const BigDecimal operator-(const BigDecimal&) const;
            BigDecimal& operator+=(const BigDecimal &a) {
                return *this = *this + a;
            }
            BigDecimal& operator-=(const BigDecimal &a) {
                return *this = *this - a;
            }
            BigDecimal& operator++() {
                return *this += 1;
            }
            const BigDecimal operator++(int) {
                BigDecimal temp(*this);
                *this += 1;
                return temp;
            }
            BigDecimal& operator--() {
                return *this -= 1;
            }
            const BigDecimal operator--(int) {
                BigDecimal temp(*this);
                *this -= 1;
                return temp;
            }
            BigDecimal& mult10();
            BigDecimal& div10();
            int get_N() const {
                return n;
            }
            bool get_Sign() const {
                return sign;
            }
            const char* get_Str() const {
                return str;
            }
    };
        
    void TestBigDecimal();

}
