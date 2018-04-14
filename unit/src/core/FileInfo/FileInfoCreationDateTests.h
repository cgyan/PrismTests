#include <gmock/gmock.h>
using namespace ::testing;
#include <prism/FileInfo>
#include <prism/tests/MockFileSystem>
#include <memory>

PRISM_BEGIN_NAMESPACE
PRISM_BEGIN_TEST_NAMESPACE

GROUP_TEST(Unit, FileInfoCreationDateTests, ShouldReturnEmptyStringWhenFilenameIsEmpty)
{
        FileInfo cut;
        EXPECT_THAT(cut.creationDate(), Eq(""));
}

GROUP_TEST(Unit, FileInfoCreationDateTests, ShouldReturnEmptyStringWhenFileDoesNotExist)
{
        auto mfs = std::make_shared<MockFileSystem>();
        const std::string file = "path/to/file/that/does/not/exist";
        EXPECT_CALL(*mfs, exists(file)).WillOnce(Return(false));

        FileInfo cut(file, mfs);
        EXPECT_THAT(cut.creationDate(), Eq(""));
}

GROUP_TEST(Unit, FileInfoCreationDateTests, ShouldReturnMonthWithLeadingZeroWhenMonthIsEarlierThanMonth10)
{
        auto mfs = std::make_shared<MockFileSystem>();
        EXPECT_CALL(*mfs, exists(_)).WillOnce(Return(true));
        EXPECT_CALL(*mfs, creationDate(_)).WillOnce(Return("2018-1-21"));

        FileInfo cut("file.txt", mfs);
        EXPECT_THAT(cut.creationDate(), Eq("2018-01-21"));
}

GROUP_TEST(Unit, FileInfoCreationDateTests, ShouldReturnDayWithLeadingZeroWhenDayIsEarlierThanDay10)
{
        auto mfs = std::make_shared<MockFileSystem>();
        EXPECT_CALL(*mfs, exists(_)).WillOnce(Return(true));
        EXPECT_CALL(*mfs, creationDate(_)).WillOnce(Return("2018-12-1"));

        FileInfo cut("somefile.txt", mfs);
        EXPECT_THAT(cut.creationDate(), Eq("2018-12-01"));
}

GROUP_TEST(Unit, FileInfoCreationDateTests, ShouldReturnChristmasDayWhenFileWasCreatedOnChristmasDay)
{
        auto mfs = std::make_shared<MockFileSystem>();
        EXPECT_CALL(*mfs, exists(_)).WillOnce(Return(true));
        EXPECT_CALL(*mfs, creationDate(_)).WillOnce(Return("2018-12-25"));

        FileInfo cut("christmas_file.txt", mfs);
        EXPECT_THAT(cut.creationDate(), Eq("2018-12-25"));
}

PRISM_END_TEST_NAMESPACE
PRISM_END_NAMESPACE
