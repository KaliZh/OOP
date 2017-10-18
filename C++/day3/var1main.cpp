#include <iostream>
#include "var1.h"

using namespace kali;

/*void test_Plus(BigDecimal a, BigDecimal b) {
    a.output();
    std::cout << " + ";
    b.output();
    std::cout << " = ";
    a.plus_BigDecimal(b).output();
    std::cout << std::endl;
}

void test_Minus(BigDecimal a, BigDecimal b) {
    a.output();
    std::cout << " - ";
    b.output();
    std::cout << " = ";
    a.minus_BigDecimal(b).output();
    std::cout << std::endl;
}*/

int main() {
    /*BigDecimal n, n1(long(-12345)), n2(long(12345)), n3(100), n4(-90);
    BigDecimal n7[3] = {BigDecimal(-350), BigDecimal(-120), BigDecimal(-5)};*/
    
    /*char *c = "09080834", *c1 = "123456778900000", *c2 = "wdeqew1232ewq2333", *c3 = "8-2134";
    char *c4 = "00023214", *c5 = "-12345", *c6 = "--11", *c7 = "123--", *c8 = "-23000011";
    char *cc = "12345678901234567890", *cc1 = "-1234567891234567890", *cc2 = "-12345678901234567890";
    char *a = "12345678901234567892", *a1 = "12345678s01234567890", *a2 = "-2345678901234567891";
    BigDecimal b(c), b1(c1), b2(c2), b3(c3), b4(c4), b5(c5), b6(c6), b7(c7), b8(c8);
    BigDecimal bb(cc), bb1(cc1), bb2(cc2);
    BigDecimal aa(a), aa1(a1), aa2(a2);*/

    //BigDecimal a;
    //a.input();

    /*BigDecimal a(-120), a1(50), a3(120), a4(-50), a5(-5), a6(5), a8(-350), a9(351), b(-950), b1(-120);
    test_Plus(a, a1);
    test_Plus(a, a5);
    test_Plus(a, a6);
    test_Plus(a3, a1);
    test_Plus(a3, a4);
    test_Plus(a3, a5);
    test_Plus(a8, a9);
    test_Plus(b, b1);
    std::cout << std::endl;
    test_Minus(a, a1);
    test_Minus(a, a5);
    test_Minus(a, a6);
    test_Minus(a3, a1);
    test_Minus(a3, a4);
    test_Minus(a3, a5);
    test_Minus(a8, a9);
    test_Minus(b, b1);*/

    /*BigDecimal a(100), a1(-23), a2(9), a3;
    a.output();
    std::cout << " * 10 = "; 
    a.mult10_BigDecimal();
    a.output();
    std::cout << std::endl;
    a1.output();
    std::cout << " * 10 = "; 
    a1.mult10_BigDecimal();
    a1.output();
    std::cout << std::endl;
    a2.output();
    std::cout << " * 10 = "; 
    a2.mult10_BigDecimal();
    a2.output();
    std::cout << std::endl;
    a3.output();
    std::cout << " * 10 = "; 
    a3.mult10_BigDecimal();
    a3.output();
    std::cout << std::endl << std::endl;
    a.output();
    std::cout << " / 10 = "; 
    a.div10_BigDecimal();
    a.output();
    std::cout << std::endl;
    a1.output();
    std::cout << " / 10 = "; 
    a1.div10_BigDecimal();
    a1.output();
    std::cout << std::endl;
    a2.output();
    std::cout << " / 10 = "; 
    a2.div10_BigDecimal();
    a2.output();
    std::cout << std::endl;
    a3.output();
    std::cout << " / 10 = "; 
    a3.div10_BigDecimal();
    a3.output();
    std::cout << std::endl;*/
    int t;
    while ((t = menu_TestBigDecimal()))
        if (t < 0) {
            std::cout << "Something goes wrong..\n";
            return 1;
        }

	return 0;
}
