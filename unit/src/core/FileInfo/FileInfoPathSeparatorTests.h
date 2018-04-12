#include <gmock/gmock.h>
using namespace ::testing;
#include <prism/tests/global>
#include <prism/FileInfo>
#include <vector>
#include <utility>

PRISM_BEGIN_NAMESPACE
PRISM_BEGIN_TEST_NAMESPACE

GROUP_TEST(Unit, FileInfoPathSeparatorTests, ShouldReturnEmptyStringWhenPathIsEmpty)
{
        EXPECT_THAT(
                FileInfo::toNormalizedSeparators(""),
                Eq("")
        );
}

GROUP_TEST(Unit, FileInfoPathSeparatorTests, ShouldConvertBackSlashToForwardSlash)
{
        EXPECT_THAT(
                FileInfo::toNormalizedSeparators(R"(\)"),
                Eq("/")
        );
}

GROUP_TEST(Unit, FileInfoPathSeparatorTests, ShouldConvertAllBackSlashesToForwardSlashesWhenPathIsNativeWindows)
{
        EXPECT_THAT(
                FileInfo::toNormalizedSeparators(R"(C:\windows\system32)"),
                Eq("C:/windows/system32")
        );
}

PRISM_END_TEST_NAMESPACE
PRISM_END_NAMESPACE
