#include <gmock/gmock.h>
using namespace ::testing;
#include <prism/FileInfo>
#include <prism/tests/MockFileSystem>
#include <memory>

PRISM_BEGIN_NAMESPACE
PRISM_BEGIN_TEST_NAMESPACE

GROUP_TEST(Unit, FileInfoCreationDateTests, ShouldReturnEmptyStringWhenFilenameIsEmpty)
{
        auto mfs = std::make_shared<MockFileSystem>();
        EXPECT_CALL(*mfs, creationDate("")).WillOnce(Return(""));

        FileInfo cut("", mfs);
        cut.creationDate();
}

GROUP_TEST(Unit, FileInfoCreationDateTests, ShouldReturnEmptyStringWhenFileDoesNotExist)
{
        const std::string file = "path/to/file/that/does/not/exist";
        auto mfs = std::make_shared<MockFileSystem>();
        EXPECT_CALL(*mfs, creationDate(file)).WillOnce(Return(""));

        FileInfo cut(file, mfs);
        cut.creationDate();
}

GROUP_TEST(Unit, FileInfoCreationDateTests, ShouldReturnDateWhenFileIsCreatedOn1stJan2018)
{
        const std::string file = "file.txt";
        const std::string expectedDate = "2018-01-01";

        auto mfs = std::make_shared<MockFileSystem>();
        EXPECT_CALL(*mfs, creationDate(file)).WillOnce(Return(expectedDate));

        FileInfo cut(file, mfs);
        cut.creationDate();
}

PRISM_END_TEST_NAMESPACE
PRISM_END_NAMESPACE
