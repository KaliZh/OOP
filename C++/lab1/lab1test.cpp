#include <gtest/gtest.h>
#include </home/naka/MEPhI/C++/lab1/lab1.cpp>

TEST(Sequence, ArraySequence) {
    adt::ArraySequence<int> a;
    ASSERT_EQ(0, a.get_Length());
    a.append(23);
    ASSERT_EQ(1, a.get_Length());
    ASSERT_EQ(23, a.get_First());
    ASSERT_EQ(23, a.get_Last());
    ASSERT_EQ(23, a.get(0));
    ASSERT_ANY_THROW(a.get(-1));
    ASSERT_ANY_THROW(a.get(1));
    a.append(43);
    ASSERT_EQ(2, a.get_Length());
    ASSERT_EQ(23, a.get_First());
    ASSERT_EQ(43, a.get_Last());
    ASSERT_EQ(23, a.get(0));
    ASSERT_EQ(43, a.get(1));
    ASSERT_ANY_THROW(a.get(-1));
    ASSERT_ANY_THROW(a.get(2));
    a.prepend(53);
    ASSERT_EQ(3, a.get_Length());
    ASSERT_EQ(53, a.get_First());
    ASSERT_EQ(43, a.get_Last());
    ASSERT_EQ(53, a.get(0));
    ASSERT_EQ(23, a.get(1));
    ASSERT_EQ(43, a.get(2));
    ASSERT_ANY_THROW(a.get(-1));
    ASSERT_ANY_THROW(a.get(3));
    adt::ArraySequence<int> b = a.get_Subsequence(1, 1);
    ASSERT_EQ(1, b.get_Length());
    ASSERT_EQ(23, b.get_First());
    ASSERT_EQ(23, b.get_Last());
    ASSERT_EQ(23, b.get(0));
    ASSERT_ANY_THROW(b.get(-1));
    ASSERT_ANY_THROW(b.get(1));
}

TEST(Sequence, ListSequence) {
    adt::ListSequence<int> a;
    ASSERT_EQ(0, a.get_Length());
    a.append(23);
    ASSERT_EQ(1, a.get_Length());
    ASSERT_EQ(23, a.get_First());
    ASSERT_EQ(23, a.get_Last());
    ASSERT_EQ(23, a.get(0));
    ASSERT_ANY_THROW(a.get(-1));
    ASSERT_ANY_THROW(a.get(1));
    a.append(43);
    ASSERT_EQ(2, a.get_Length());
    ASSERT_EQ(23, a.get_First());
    ASSERT_EQ(43, a.get_Last());
    ASSERT_EQ(23, a.get(0));
    ASSERT_EQ(43, a.get(1));
    ASSERT_ANY_THROW(a.get(-1));
    ASSERT_ANY_THROW(a.get(2));
    a.prepend(53);
    ASSERT_EQ(3, a.get_Length());
    ASSERT_EQ(53, a.get_First());
    ASSERT_EQ(43, a.get_Last());
    ASSERT_EQ(53, a.get(0));
    ASSERT_EQ(23, a.get(1));
    ASSERT_EQ(43, a.get(2));
    ASSERT_ANY_THROW(a.get(-1));
    ASSERT_ANY_THROW(a.get(3));
    adt::ListSequence<int> b = a.get_Subsequence(1, 1);
    ASSERT_EQ(1, b.get_Length());
    ASSERT_EQ(23, b.get_First());
    ASSERT_EQ(23, b.get_Last());
    ASSERT_EQ(23, b.get(0));
    ASSERT_ANY_THROW(b.get(-1));
    ASSERT_ANY_THROW(b.get(1));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}
