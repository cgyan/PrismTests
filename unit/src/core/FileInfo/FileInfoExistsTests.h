#include <gmock/gmock.h>
using namespace ::testing;
#include <prism/tests/global>
#include <prism/FileInfo>
#include <prism/tests/MockFileSystem>

PRISM_BEGIN_NAMESPACE
PRISM_BEGIN_TEST_NAMESPACE

GROUP_TEST(Unit, FileInfoExistsTests, ShouldReturnFalseWhenFilenameIsEmpty)
{
        const std::string filePath = "";
        auto mfs = std::make_shared<MockFileSystem>();
        EXPECT_CALL(*mfs, exists(filePath)).WillOnce(Return(false));
        FileInfo cut(filePath, mfs);
        EXPECT_THAT(cut.exists(), Eq(false));
}

GROUP_TEST(Unit, FileInfoExistsTests, ShouldReturnFalseWhenFileDoesNotExist)
{
        const std::string filePath = "path/to/file/that/does/not/exist";
        auto mfs = std::make_shared<MockFileSystem>();
        EXPECT_CALL(*mfs, exists(filePath)).WillOnce(Return(false));
        FileInfo cut(filePath, mfs);
        EXPECT_THAT(cut.exists(), Eq(false));
}

GROUP_TEST(Unit, FileInfoExistsTests, ShouldReturnTrueWhenFileExists)
{
        const std::string filePath = "file.txt";
        auto mfs = std::make_shared<MockFileSystem>();
        EXPECT_CALL(*mfs, exists(filePath)).WillOnce(Return(true));
        FileInfo cut(filePath, mfs);
        EXPECT_THAT(cut.exists(), Eq(true));
}

PRISM_END_TEST_NAMESPACE
PRISM_END_NAMESPACE
