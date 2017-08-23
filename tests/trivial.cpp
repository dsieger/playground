#include "gtest/gtest.h"

#include "test.h"

TEST(square, square)
{
    ASSERT_EQ(square(3),9);
}

TEST(twice, twice)
{
    ASSERT_EQ(twice(2),4);

#if defined _MSC_VER
    ASSERT_NE(getSize(),0);
#endif
}
