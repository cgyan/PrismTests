#include <gmock/gmock.h>
using namespace ::testing;
#include <prism/global>
#include <prism/FileInfo>

PRISM_BEGIN_NAMESPACE
PRISM_BEGIN_TEST_NAMESPACE

class FileInfoEntireSuffixParamTests : public TestWithParam<std::string>
{
public:
        FileInfo testSubject;
};

INSTANTIATE_TEST_CASE_P(
        ,
        FileInfoEntireSuffixParamTests,
        Values(
                ".tar.gz",
                "file.tar.gz",
                "./file.tar.gz",
                "../file.tar.gz",
                "/files/file.tar.gz",
                "c:/file.tar.gz"
        )
);

TEST_P(FileInfoEntireSuffixParamTests, ShouldReturnEntireSuffixWhenFilenameIsNotEmpty)
{
        const std::string filename = GetParam();
        testSubject.setFile(filename);
        EXPECT_THAT(testSubject.entireSuffix(), Eq("tar.gz"));
}

TEST(FileInfoEntireSuffixTests, ShouldReturnEmptyStringWhenFilenameIsEmpty)
{
        FileInfo testSubject;
        EXPECT_THAT(testSubject.entireSuffix(), Eq(""));
}

TEST(FileInfoEntireSuffixTests, ShouldReturnEmptyStringWhenFilenameContainsNoSuffixs)
{
        const std::string filenameWithNoSuffixes = "file";
        FileInfo testSubject(filenameWithNoSuffixes);
        EXPECT_THAT(testSubject.entireSuffix(), Eq(""));
}

TEST(FileInfoEntireSuffixTests, ShouldReturnAllSuffixesWhenFilenameContainsMultipleSuffixes)
{
        const std::string filenameWithMultipleSuffixes = "file.tar.gz";
        FileInfo testSubject(filenameWithMultipleSuffixes);
        EXPECT_THAT(testSubject.entireSuffix(), Eq("tar.gz"));
}

PRISM_END_TEST_NAMESPACE
PRISM_END_NAMESPACE
