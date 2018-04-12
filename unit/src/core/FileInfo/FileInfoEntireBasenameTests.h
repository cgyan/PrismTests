#include <gmock/gmock.h>
using namespace ::testing;
#include <prism/FileInfo>

PRISM_BEGIN_NAMESPACE
PRISM_BEGIN_TEST_NAMESPACE

class FileInfoEntireBasenameParamTests : public TestWithParam<std::string>
{
public:
        FileInfo cut;
};

INSTANTIATE_TEST_CASE_P(
        ,
        FileInfoEntireBasenameParamTests,
        Values(
                "file.tar.gz",
                "./file.tar.gz",
                "../file.tar.gz",
                "data/./files/../file.tar.gz",
                "/files/file.tar.gz",
                "C:/file.tar.gz"
        )
);

TEST_P(FileInfoEntireBasenameParamTests, ShouldReturnBasenameAndAllSuffixesExpectLastSuffixWhenFilenameContainsMultipleSuffixes)
{
        const std::string filepath = GetParam();
        cut.setFile(filepath);
        EXPECT_THAT(cut.entireBasename(), Eq("file.tar"));
}

TEST(FileInfoEntireBasenameTests, ShouldReturnEmptyStringWhenFilenameIsEmpty)
{
        FileInfo cut;
        EXPECT_THAT(cut.entireBasename(), Eq(""));
}

TEST(FileInfoEntireBasenameTests, ShouldReturnEmptyStringWhenFilenameContainsNoBasenameAndOnlyOneSuffix)
{
        const std::string filenameWithNoBasenameAndOnlyOneSuffix = ".txt";
        FileInfo cut(filenameWithNoBasenameAndOnlyOneSuffix);
        EXPECT_THAT(cut.entireBasename(), Eq(""));
}

TEST(FileInfoEntireBasenameTests, ShouldReturnBasenameWhenFilenameContainsNoSuffixes)
{
        const std::string filenameWithBasenameAndNoSuffixes = "file";
        FileInfo cut(filenameWithBasenameAndNoSuffixes);
        EXPECT_THAT(cut.entireBasename(), Eq("file"));
}

TEST(FileInfoEntireBasenameTests, ShouldReturnBasenameWhenFilenameContainsBasenameAndOneSuffix)
{
        const std::string filenameWithBasenameAndOneSuffix = "file.txt";
        FileInfo cut(filenameWithBasenameAndOneSuffix);
        EXPECT_THAT(cut.entireBasename(), "file");
}

PRISM_END_TEST_NAMESPACE
PRISM_END_NAMESPACE
