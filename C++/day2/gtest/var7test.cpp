#include <gtest/gtest.h>
#include </home/naka/MEPhI/C++/day2/var7.h>

TEST(CardioidConstructor, DefaultConstructor) {
    kali::cardioid c;
    ASSERT_EQ(0, c.get_a());
}

TEST(CardioidMethods, DefaultConstructor) {
    kali::cardioid c;
    ASSERT_EQ(0, c.distance_to_centre(1));
    ASSERT_EQ(0, c.radius_of_curvature(1));
    ASSERT_EQ(0, c.area());
    ASSERT_EQ(0, c.arc_length(1, 1));
    c.set_a(2.3);
    ASSERT_EQ(2.3, c.get_a());
}

TEST(CardioidConstructor, InitConstructor) {
    kali::cardioid c(2.3);
    ASSERT_EQ(2.3, c.get_a());
}

TEST(CardioidMethods, InitConstructor) {
    kali::cardioid c(2.3);
    const double err = 0.00001;
    ASSERT_NEAR(9.13011, c.distance_to_centre(10), err);
    ASSERT_NEAR(6.10999, c.radius_of_curvature(10), err);
    ASSERT_NEAR(24.92853, c.area(), err);
    ASSERT_EQ(0, c.arc_length(10, 10));
    ASSERT_ANY_THROW(c.set_a(-2.3));
}

TEST(CardioidConstructor, Exceptions) {
    ASSERT_ANY_THROW(kali::cardioid(0));
    ASSERT_ANY_THROW(kali::cardioid(-2.3));
    ASSERT_ANY_THROW(kali::cardioid(-10));
}

TEST(CardioidMethods, Exceptions) {
    kali::cardioid c(1.1);
    ASSERT_ANY_THROW(c.set_a(0));
    ASSERT_ANY_THROW(c.set_a(-1));
    ASSERT_ANY_THROW(c.set_a(-10));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
