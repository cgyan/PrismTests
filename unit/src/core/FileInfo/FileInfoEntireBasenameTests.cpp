#include <gmock/gmock.h>
using namespace ::testing;
#include <prism/FileInfo>

PRISM_BEGIN_NAMESPACE
PRISM_BEGIN_TEST_NAMESPACE

class FileInfoEntireBasenameParamTests : public TestWithParam<std::string>
{
public:
        FileInfo testSubject;
};

INSTANTIATE_TEST_CASE_P(
        ,
        FileInfoEntireBasenameParamTests,
        Values(
                "file.tar.gz",
                "./file.tar.gz",
                "../file.tar.gz",
                "/files/file.tar.gz",
                "C:/file.tar.gz"
        )
);

TEST_P(FileInfoEntireBasenameParamTests, ShouldReturnBasenameAndAllSuffixesExpectLastSuffixWhenFilenameContainsMultipleSuffixes)
{
        const std::string filepath = GetParam();
        testSubject.setFile(filepath);
        EXPECT_THAT(testSubject.entireBasename(), Eq("file.tar"));
}

TEST(FileInfoEntireBasenameTests, ShouldReturnEmptyStringWhenFilenameIsEmpty)
{
        const std::string emptyFilename = "";
        FileInfo testSubject(emptyFilename);
        EXPECT_THAT(testSubject.entireBasename(), Eq(""));
}

TEST(FileInfoEntireBasenameTests, ShouldReturnEmptyStringWhenFilenameContainsNoBasenameAndOnlyOneSuffix)
{
        const std::string filenameWithNoBasenameAndOnlyOneSuffix = ".txt";
        FileInfo testSubject(filenameWithNoBasenameAndOnlyOneSuffix);
        EXPECT_THAT(testSubject.entireBasename(), Eq(""));
}

TEST(FileInfoEntireBasenameTests, ShouldReturnBasenameWhenFilenameContainsNoSuffixes)
{
        const std::string filenameWithBasenameAndNoSuffixes = "file";
        FileInfo testSubject(filenameWithBasenameAndNoSuffixes);
        EXPECT_THAT(testSubject.entireBasename(), Eq("file"));
}

TEST(FileInfoEntireBasenameTests, ShouldReturnBasenameWhenFilenameContainsBasenameAndOneSuffix)
{
        const std::string filenameWithBasenameAndOneSuffix = "file.txt";
        FileInfo testSubject(filenameWithBasenameAndOneSuffix);
        EXPECT_THAT(testSubject.entireBasename(), "file");
}

PRISM_END_TEST_NAMESPACE
PRISM_END_NAMESPACE
