#include <gmock/gmock.h>
using namespace ::testing;
#include <prism/global>
#include <prism/FileInfo>
#include <prism/tests/MockFileSystem>

PRISM_BEGIN_NAMESPACE
PRISM_BEGIN_TEST_NAMESPACE

TEST(FileInfoSizeTests, ShouldReturnNegativeOneWhenFilenameIsEmpty)
{
        auto mfs = std::make_shared<MockFileSystem>();
        EXPECT_CALL(*mfs, fileSizeInBytes("")).WillOnce(Return(-1));
        FileInfo cut("", mfs);
        EXPECT_THAT(cut.size(), Eq(-1));
}

TEST(FileInfoSizeTests, ShouldReturnSizeOfFileWhenFileIsOnDisk)
{
        auto mfs = std::make_shared<MockFileSystem>();
        EXPECT_CALL(*mfs, fileSizeInBytes("path/to/file.txt")).WillOnce(Return(200));
        FileInfo cut("path/to/file.txt", mfs);
        EXPECT_THAT(cut.size(), Eq(200));
}

TEST(FileInfoSizeTests, ShouldReturnNegativeOneWhenFileIsNotOnDisk)
{
        auto mfs = std::make_shared<MockFileSystem>();
        EXPECT_CALL(*mfs, fileSizeInBytes("path/to/file/that/does/not/exist")).WillOnce(Return(-1));
        FileInfo cut("path/to/file/that/does/not/exist", mfs);
        EXPECT_THAT(cut.size(), Eq(-1));
}

PRISM_END_TEST_NAMESPACE
PRISM_END_NAMESPACE
