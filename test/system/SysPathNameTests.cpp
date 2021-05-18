#include <gtest/gtest.h>
#include "system/pathname.hpp"

/** * *
 * I decided to pick something "simple" like the pathname stuff to setup Google Test.
 **/

TEST(SysPathNameTests, NoArgsIsUnsetTest) {
    SysPathName noArgsConstructed = SysPathName();

    ASSERT_EQ(false, noArgsConstructed.set());
}
