extern "C" {
#include <qq.h>
}

#include <cstdlib>
#include <gtest/gtest.h>

namespace {

TEST(GetVerbose, Valid)
{
    QQVerbose v = qq_get_verbose();
    EXPECT_TRUE(v >= QQ_VERBOSE_MIN && v <= QQ_VERBOSE_MAX)
        << "Verbose level out of range: " << v;
}

TEST(SetVerbose, Valid)
{
    for (int v = QQ_VERBOSE_MIN; v <= QQ_VERBOSE_MAX; v++) {
        qq_set_verbose((QQVerbose)v);
        EXPECT_EQ(v, qq_get_verbose()) << "Verbose level not set: " << v;
    }
}

TEST(SetVerbose, Invalid)
{
    qq_set_verbose((QQVerbose)(QQ_VERBOSE_MAX + 1));
    EXPECT_EQ(QQ_DEFAULT, qq_get_verbose())
        << "Verbose level not set to default " << QQ_DEFAULT
        << " when out of range";
}

char const *_qq_test_verbose = "_QQ_TEST_VERBOSE";

TEST(InitVerbose, Missing)
{
    unsetenv(_qq_test_verbose);
    qq_init_verbose(_qq_test_verbose);
    EXPECT_EQ(QQ_DEFAULT, qq_get_verbose())
        << "Verbose level not set to default " << QQ_DEFAULT
        << " when environment variable is missing";
}

TEST(InitVerbose, Valid)
{
    for (int v = QQ_VERBOSE_MIN; v <= QQ_VERBOSE_MAX; v++) {
        char buf[16];
        snprintf(buf, sizeof(buf), "%d", v);
        setenv(_qq_test_verbose, buf, 1);
        qq_init_verbose(_qq_test_verbose);
        EXPECT_EQ(v, qq_get_verbose())
            << "Verbose level not set to " << v << " when environment is " << v;
    }
}

TEST(IsVerbose, Order)
{
    for (int v = QQ_VERBOSE_MIN; v <= QQ_VERBOSE_MAX; v++) {
        qq_set_verbose((QQVerbose)v);
        for (int i = QQ_VERBOSE_MIN; i <= v; i++) {
            EXPECT_TRUE(qq_is_verbose((QQVerbose)i))
                << "Verbose level " << i << " not available when " << v;
        }
        for (int i = v + 1; i <= QQ_VERBOSE_MAX; i++) {
            EXPECT_FALSE(qq_is_verbose((QQVerbose)i))
                << "Verbose level " << i << " available when " << v;
        }
    }
}

}  // namespace