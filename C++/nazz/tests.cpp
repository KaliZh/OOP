#include "source.cpp"
#include <gtest/gtest.h>

TEST(CissoidConstructor, DefaultConstructor) {
	luv::Diocle a;
	ASSERT_EQ(1, a.getA());
}

TEST(CissoidMethods, DefaultConstructor) {
	luv::Diocle a;
	ASSERT_EQ(0, a.points(0));
	ASSERT_EQ(0, a.dist(0));
	ASSERT_EQ(2, a.asymptote());
	ASSERT_NEAR(9.42478, a.area(), 0.00001);
	ASSERT_EQ(4, a.coef());
}

TEST(CissoidConstructor, InitConstructor) {
	luv::Diocle a(4.5);
	const double err = 0.00001;
	ASSERT_EQ(4.5, a.getA());
	ASSERT_EQ(18, a.coef());
	ASSERT_NEAR(0.35355, a.points(1), err);
	ASSERT_NEAR(6.36396, a.dist(45), err);
	ASSERT_NEAR(190.851753, a.area(), err);
	ASSERT_ANY_THROW(a.setA(-4.5));
}

TEST(CissoidConstructor, Exceptions) {
    luv::Diocle a;
	ASSERT_ANY_THROW(luv::Diocle(0));
	ASSERT_ANY_THROW(luv::Diocle(-4.5));
    ASSERT_ANY_THROW(a.points(-20));
    ASSERT_ANY_THROW(a.dist(180));
}

int _tmain(int argc, char* argv[]) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
