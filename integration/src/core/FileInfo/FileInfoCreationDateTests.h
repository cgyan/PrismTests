#include <gmock/gmock.h>
using namespace ::testing;
#include <prism/tests/global>
#include <prism/FileInfo>
#include <prism/tests/SystemTempDir>
#include <ctime>
#include <stdio.h>

PRISM_BEGIN_NAMESPACE
PRISM_BEGIN_TEST_NAMESPACE

//==================================================================================================
// NOTE:
// United Kingdom operates on GMT in winter and BST in summer
//==================================================================================================
const std::string
todaysDate()
{
        time_t t = time(0);   // get time now
        struct tm * now = gmtime( & t );

        std::string year = std::to_string(now->tm_year + 1900);
        std::string month = std::to_string(now->tm_mon + 1);
        std::string day = std::to_string(now->tm_mday);

        if (month.length() == 1) month = std::string("0").append(month);
        if (day.length() == 1) day = std::string("0").append(day);

        return year + "-" + month + "-" + day;
}

INTEGRATION_TEST(FileInfoCreationDateTests, ShouldReturnEmptyStringWhenFileDoesNotExist)
{
        FileInfo cut("path/to/file/that/does/not/exist");
        EXPECT_THAT(cut.creationDate(), Eq(""));
}

INTEGRATION_TEST(FileInfoCreationDateTests, ShouldReturnTodaysDateWhenFileIsCreatedToday)
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
