#include <gtest/gtest.h>
#include </home/naka/MEPhI/C++/day4/var1.cpp>

TEST(constructor_BigDecimal, DefaultConstructor) {
    kali::BigDecimal a;
    ASSERT_EQ(1, a.get_N());
    ASSERT_EQ(0, a.get_Sign());
    ASSERT_EQ("0", a.get_Str());
}

TEST(constructor_BigDecimal, InitConstructor) {
    kali::BigDecimal a(-100);
    ASSERT_EQ(3, a.get_N());
    ASSERT_EQ(1, a.get_Sign());
    ASSERT_EQ("100", a.get_Str());
    kali::BigDecimal b("-100200300400500");
    ASSERT_EQ(15, a.get_N());
    ASSERT_EQ(1, a.get_Sign());
    ASSERT_EQ("100200300400500", a.get_Str());
}

TEST(constructor_BigDecimal, CopyConstructor) {
    kali::BigDecimal a(100), b(a);
    ASSERT_EQ(3, b.get_N());
    ASSERT_EQ(0, b.get_Sign());
    ASSERT_EQ("100", b.get_Str());
}

TEST(constructor_BigDecimal, Exception) {
    ASSERT_ANY_THROW(kali::BigDecimal("--00zwe234"));
}

TEST(methods_BigDecimal, Methods) {
    kali::BigDecimal a(100), b(10);
    a.div10();
    ASSERT_EQ(2, a.get_N());
    ASSERT_EQ(0, a.get_Sign());
    ASSERT_EQ("10", a.get_Str());
    b.mult10();
    ASSERT_EQ(3, b.get_N());
    ASSERT_EQ(0, b.get_Sign());
    ASSERT_EQ("100", b.get_Str());
}

TEST(methods_BigDecimal, OverloadedOperators) {
    kali::BigDecimal b; 
    b++;
    ASSERT_EQ(1, b.get_N());
    ASSERT_EQ(0, b.get_Sign());
    ASSERT_EQ("0", b.get_Str());
    b += 10;
    ASSERT_EQ(2, b.get_N());
    ASSERT_EQ(0, b.get_Sign());
    ASSERT_EQ("11", b.get_Str());
    b = 20 - 10;
    ASSERT_EQ(2, b.get_N());
    ASSERT_EQ(0, b.get_Sign());
    ASSERT_EQ("10", b.get_Str());
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}
