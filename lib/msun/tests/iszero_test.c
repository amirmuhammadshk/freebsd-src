/*-
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <sys/cdefs.h>

#include <float.h>
#include <math.h>

#include "test-utils.h"

#define TEST_ZERO(type, value, expected) do {                           \
        volatile type x = (value);                                      \
        ATF_CHECK_EQ((expected), !!iszero(x));                           \
} while (0)

#define TEST_ALL(value, expected) do {                                   \
        TEST_ZERO(float, value, expected);                               \
        TEST_ZERO(double, value, expected);                              \
        TEST_ZERO(long double, value, expected);                         \
} while (0)

ATF_TC_WITHOUT_HEAD(zero);
ATF_TC_BODY(zero, tc)
{
        TEST_ALL(0.0, 1);
        TEST_ALL(-0.0, 1);
}

ATF_TC_WITHOUT_HEAD(nonzero);
ATF_TC_BODY(nonzero, tc)
{
        TEST_ALL(1.0, 0);
        TEST_ALL(-1.0, 0);
        TEST_ALL(0.5, 0);
        TEST_ALL(INFINITY, 0);
        TEST_ALL(-INFINITY, 0);
        TEST_ALL(NAN, 0);

        TEST_ZERO(float, FLT_TRUE_MIN, 0);
        TEST_ZERO(double, DBL_TRUE_MIN, 0);
        TEST_ZERO(long double, LDBL_TRUE_MIN, 0);
}

ATF_TC_WITHOUT_HEAD(single_evaluation);
ATF_TC_BODY(single_evaluation, tc)
{
        double values[] = { 0.0, 1.0 };
        int i = 0;

        ATF_CHECK(iszero(values[i++]));
        ATF_CHECK_EQ(1, i);
}

ATF_TP_ADD_TCS(tp)
{
        ATF_TP_ADD_TC(tp, zero);
        ATF_TP_ADD_TC(tp, nonzero);
        ATF_TP_ADD_TC(tp, single_evaluation);

        return (atf_no_error());
}
