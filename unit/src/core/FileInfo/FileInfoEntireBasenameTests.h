#include <gmock/gmock.h>
using namespace ::testing;
#include <prism/tests/global>
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

GROUP_TEST_P(Unit, FileInfoEntireBasenameParamTests, ShouldReturnBasenameAndAllSuffixesExpectLastSuffixWhenFilenameContainsMultipleSuffixes)
{
        const std::string filepath = GetParam();
        cut.setFile(filepath);
        EXPECT_THAT(cut.entireBasename(), Eq("file.tar"));
}

GROUP_TEST(Unit, FileInfoEntireBasenameTests, ShouldReturnEmptyStringWhenFilenameIsEmpty)
{
        FileInfo cut;
        EXPECT_THAT(cut.entireBasename(), Eq(""));
}

GROUP_TEST(Unit, FileInfoEntireBasenameTests, ShouldReturnEmptyStringWhenFilenameContainsNoBasenameAndOnlyOneSuffix)
{
        const std::string filenameWithNoBasenameAndOnlyOneSuffix = ".txt";
        FileInfo cut(filenameWithNoBasenameAndOnlyOneSuffix);
        EXPECT_THAT(cut.entireBasename(), Eq(""));
}

GROUP_TEST(Unit, FileInfoEntireBasenameTests, ShouldReturnBasenameWhenFilenameContainsNoSuffixes)
{
        const std::string filenameWithBasenameAndNoSuffixes = "file";
        FileInfo cut(filenameWithBasenameAndNoSuffixes);
        EXPECT_THAT(cut.entireBasename(), Eq("file"));
}

GROUP_TEST(Unit, FileInfoEntireBasenameTests, ShouldReturnBasenameWhenFilenameContainsBasenameAndOneSuffix)
{
        const std::string filenameWithBasenameAndOneSuffix = "file.txt";
        FileInfo cut(filenameWithBasenameAndOneSuffix);
        EXPECT_THAT(cut.entireBasename(), "file");
}

PRISM_END_TEST_NAMESPACE
PRISM_END_NAMESPACE
