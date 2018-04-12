#include <gmock/gmock.h>
using namespace ::testing;
#include <prism/tests/global>
#include <prism/FileInfo>
#include <prism/tests/SystemTempDir>

PRISM_BEGIN_NAMESPACE
PRISM_BEGIN_TEST_NAMESPACE

GROUP_TEST(Integration, FileInfoSizeTests, ShouldReturnSizeOfFileWhenFileExists)
{
        const std::string newFile = "file.tmp";
        const std::string content = "some content...";
        const int numFileBytes = content.length();

        if (SystemTempDir::newFileWithContent(newFile, content))
        {
                const std::string newFileWithPath = SystemTempDir::path() + "/" + newFile;
                FileInfo cut(newFileWithPath);
                EXPECT_THAT(cut.size(), Eq(numFileBytes));
                SystemTempDir::deleteFile(newFile);
        }
        else ADD_FAILURE_AT(__FILE__, __LINE__)
                << "Could not create file in temp dir for test set up";

}

GROUP_TEST(Integration, FileInfoSizeTests, ShouldReturnErrorSizeOfNegOneWhenFileDoesNotExist)
{
        FileInfo cut("path/to/file/that/does/not/exist");
        EXPECT_THAT(cut.size(), Eq(-1));
}

PRISM_END_TEST_NAMESPACE
PRISM_END_NAMESPACE
