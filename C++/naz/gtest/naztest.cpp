#include <gtest/gtest.h>
#include </home/naka/MEPhI/C++/naz/sample.h>

TEST(CissoidConstructor, DefaultConstructor) {
	luv::Diocle a;
	ASSERT_EQ(1, a.getA());
}

TEST(CissoidConstructor, InitConstructor) {
	luv::Diocle a(4.5);
	const double err = 0.00001;
	ASSERT_EQ(4.5, a.getA());
	ASSERT_EQ(18, a.coef());
	ASSERT_NEAR(0.35355, a.points(1), err);
	ASSERT_NEAR(6.36396, a.dist(45), err);
	ASSERT_NEAR(190.851753, a.area(), err);
	ASSERT_NEAR(599.578467, a.volume(), err);
	ASSERT_ANY_THROW(a.setA(-4.5));
}

TEST(CissoidConstructor, Exceptions) {
    	luv::Diocle a;
	ASSERT_ANY_THROW(luv::Diocle(0));
	ASSERT_ANY_THROW(luv::Diocle(-4.5));
    	ASSERT_ANY_THROW(a.points(-20));
    	ASSERT_ANY_THROW(a.dist(180));
}

TEST(CissoidMethods, DefaultConstructor) {
	luv::Diocle a;
	ASSERT_EQ(0, a.points(0));
	ASSERT_EQ(0, a.dist(0));
	ASSERT_EQ(2, a.asymptote());
	ASSERT_EQ(9.42477796077, a.area());
	ASSERT_EQ(19.73920880218132, a.volume());
	ASSERT_EQ(4, a.coef());
}

int main(int argc, char **argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
