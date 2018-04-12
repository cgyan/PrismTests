#include <gmock/gmock.h>
using namespace ::testing;
#include <prism/tests/global>
#include <prism/FileInfo>
#include <prism/tests/SystemTempDir>

PRISM_BEGIN_NAMESPACE
PRISM_BEGIN_TEST_NAMESPACE

GROUP_TEST(Integration, FileInfoExistsTests, ShouldReturnTrueWhenFileExists)
{
        if (SystemTempDir::newFileWithContent("file.tmp", ""))
        {
                FileInfo cut(SystemTempDir::path() + "/file.tmp");
                EXPECT_THAT(cut.exists(), Eq(true));
                SystemTempDir::deleteFile("file.tmp");
        }
        else ADD_FAILURE_AT(__FILE__, __LINE__)
                << "Could not create file in temp dir for test";
}

GROUP_TEST(Integration, FileInfoExistsTests, ShouldReturnFalseWhenFileDoesNotExist)
{
        FileInfo cut("path/to/file/that/does/not/exist");
        EXPECT_THAT(cut.exists(), Eq(false));
}

PRISM_END_TEST_NAMESPACE
PRISM_END_NAMESPACE
