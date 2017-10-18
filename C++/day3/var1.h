#include <iostream>
#include <limits>

namespace kali {

    static const int SZ = 20;
    
    class BigDecimal {
        private:
            int n;
            char str[SZ + 1];
            bool is_SignedMagnitude(const char*) const;
            bool is_Num(const char*) const;
            void make_SignedMagnitude(const char*);
            void make_SignedMagnitudeForLong(const long);
            void make_SignedMagnitudeForChar(const char*);
            void change_Code();
            char get_Sign() const {
                return str[SZ - 1];
            }
            void set_Sign(bool bl) {
                if (bl)
                    str[SZ - 1] = '1';
                else str[SZ - 1] = '0';
            }
            void find_N() {
                n = SZ - 1;
                while (str[--n] == '0');
                n++;
            }
        public:
            BigDecimal(const long l = 0) {
                make_SignedMagnitudeForLong(l);
            }
            BigDecimal(const char* c) {
                if (is_SignedMagnitude(c))
                    make_SignedMagnitude(c);
                else if (is_Num(c))
                    make_SignedMagnitudeForChar(c);
                else throw std::runtime_error("wrong data");
            }
            void input();
            void output() {
                if (n == -1)
                    find_N();
                std::cout << "Number of digits: " << n << std::endl << "Number: ";
                if (str[SZ - 1] == '1')
                    std::cout << '-';
                for (int i = n - 1; i >= 0; --i)
                    std::cout << str[i];
            }
            BigDecimal plus_BigDecimal(BigDecimal&); 
            BigDecimal minus_BigDecimal(BigDecimal&);
            BigDecimal mult10(); 
            BigDecimal div10();
    };

    int menu_TestBigDecimal();
}
