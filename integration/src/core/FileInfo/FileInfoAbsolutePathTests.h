#include <gmock/gmock.h>
using namespace ::testing;
#include <prism/tests/global>
#include <prism/FileInfo>
#include <prism/tests/SystemTempDir>
#include <prism/algorithm>
#include <string>

PRISM_BEGIN_NAMESPACE
PRISM_BEGIN_TEST_NAMESPACE

const std::string normalizePath(const std::string& path)
{
        std::string ret = path;
        prism::replace(ret.begin(), ret.end(), '\\', '/');
        return ret;
}

INTEGRATION_TEST(FileInfoAbsolutePathTests, ShouldReturnAbsolutePathOfTempDirWhenFileIsLocatedThere)
{
        if (SystemTempDir::newFileWithContent("file.tmp", "some temp content..."))
        {
                FileInfo cut(SystemTempDir::path() + "/file.tmp");
                EXPECT_THAT(cut.absolutePath(), Eq(SystemTempDir::path()));
                SystemTempDir::deleteFile("file.tmp");
        }
        else ADD_FAILURE_AT(__FILE__, __LINE__)
                << "Could not create file in temp dir for test";
}

INTEGRATION_TEST(FileInfoAbsolutePathTests, ShouldReturnEmptyStringWhenFilenameIsEmpty)
{
        FileInfo cut("");
        EXPECT_THAT(cut.absolutePath(), Eq(""));
}

INTEGRATION_TEST(FileInfoAbsolutePathTests, ShouldReturnEmptyStringWhenFileDoesNotExist)
{
        FileInfo cut("path/to/file/that/does/not/exist");
        EXPECT_THAT(cut.absolutePath(), Eq(""));
}
//==============================================================================
//==============================================================================
INTEGRATION_TEST(FileInfoAbsolutePathWithFilenameTests, ShouldReturnEmptyStringWhenFilenameIsEmpty)
{
        FileInfo cut;
        EXPECT_THAT(cut.absolutePathWithFilename(), Eq(""));
}

INTEGRATION_TEST(FileInfoAbsolutePathWithFilenameTests, ShouldReturnEmptyStringWhenFileDoesNotExist)
{
        FileInfo cut("path/to/file/that/does/not/exist");
        EXPECT_THAT(cut.absolutePathWithFilename(), Eq(""));
}

INTEGRATION_TEST(FileInfoAbsolutePathWithFilenameTests,
ShouldReturnAbsolutePathOfTempDirAndFilenameWhenFileIsLocatedThere)
{
        if (SystemTempDir::newFileWithContent("file.tmp", "some temp content..."))
        {
                FileInfo cut(SystemTempDir::path() + "\\file.tmp");
                const std::string expected = normalizePath(SystemTempDir::path() + "/file.tmp");
                EXPECT_THAT(cut.absolutePathWithFilename(), Eq(expected));
                SystemTempDir::deleteFile("file.tmp");
        }
        else ADD_FAILURE_AT(__FILE__, __LINE__)
                << "Could not create file in temp dir for test";
}

PRISM_END_TEST_NAMESPACE
PRISM_END_NAMESPACE
