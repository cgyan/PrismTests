#include <gmock/gmock.h>
using namespace ::testing;
#include <prism/tests/global>
#include <prism/FileInfo>
#include <vector>
#include <utility>

PRISM_BEGIN_NAMESPACE
PRISM_BEGIN_TEST_NAMESPACE

UNIT_TEST(FileInfoPathSeparatorTests, ShouldReturnEmptyStringWhenPathIsEmpty)
{
        EXPECT_THAT(
                FileInfo::toNormalizedSeparators(""),
                Eq("")
        );
}

UNIT_TEST(FileInfoPathSeparatorTests, ShouldConvertBackSlashToForwardSlash)
{
        EXPECT_THAT(
                FileInfo::toNormalizedSeparators(R"(\)"),
                Eq("/")
        );
}

UNIT_TEST(FileInfoPathSeparatorTests, ShouldConvertAllBackSlashesToForwardSlashesWhenPathIsNativeWindows)
{
        EXPECT_THAT(
                FileInfo::toNormalizedSeparators(R"(C:\windows\system32)"),
                Eq("C:/windows/system32")
        );
}

PRISM_END_TEST_NAMESPACE
PRISM_END_NAMESPACE
