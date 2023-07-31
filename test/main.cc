#include <gtest/gtest.h>

#include "verbose.cc"

int
main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}