#include <gmock/gmock.h>
using namespace ::testing;
#include <prism/tests/global>
#include <prism/FileInfo>
#include <prism/tests/SystemTempDir>
#include <ctime>
#include <stdio.h>

PRISM_BEGIN_NAMESPACE
PRISM_BEGIN_TEST_NAMESPACE

const std::string
todaysDate()
{
        time_t t = time(0);   // get time now
        struct tm * now = localtime( & t );

        std::string year = std::to_string(now->tm_year + 1900);
        std::string month = std::to_string(now->tm_mon + 1);
        std::string day = std::to_string(now->tm_mday);

        if (month.length() == 1) month = std::string("0").append(month);
        if (day.length() == 1) day = std::string("0").append(day);

        return year + "-" + month + "-" + day;
}

GROUP_TEST(Integration, FileInfoCreationDateTests, ShouldReturnEmptyStringWhenFileDoesNotExist)
{
        FileInfo cut("path/to/file/that/does/not/exist");
        EXPECT_THAT(cut.creationDate(), Eq(""));
}

GROUP_TEST(Integration, FileInfoCreationDateTests, ShouldReturnTodaysDateWhenFileIsCreatedToday)
{
        const std::string today = todaysDate();
        const std::string filename = "file.txt";
        if (SystemTempDir::newFileWithContent(filename, ""))
        {
                FileInfo cut(SystemTempDir::path() + "/" + filename);
                EXPECT_THAT(cut.creationDate(), Eq(today));
                SystemTempDir::deleteFile(filename);
        }
        else ADD_FAILURE_AT(__FILE__, __LINE__)
                << "Could not create file in temp dir for test";
}

PRISM_END_TEST_NAMESPACE
PRISM_END_NAMESPACE
