#include <gmock/gmock.h>
using namespace ::testing;
#include <prism/tests/global>
#include <prism/FileInfo>

PRISM_BEGIN_NAMESPACE
PRISM_BEGIN_TEST_NAMESPACE

class UNIT_TEST_CLASS(FileInfoEntireBasenameParamTests) : public TestWithParam<std::string>
{
public:
        FileInfo cut;
};

UNIT_INSTANTIATE_TEST_CASE_P(
        ,
        UNIT_TEST_CLASS(FileInfoEntireBasenameParamTests),
        Values(
                "file.tar.gz",
                "./file.tar.gz",
                "../file.tar.gz",
                "data/./files/../file.tar.gz",
                "/files/file.tar.gz",
                "C:/file.tar.gz"
        )
);

UNIT_TEST_P(FileInfoEntireBasenameParamTests, ShouldReturnBasenameAndAllSuffixesExpectLastSuffixWhenFilenameContainsMultipleSuffixes)
{
        const std::string filepath = GetParam();
        cut.setFile(filepath);
        EXPECT_THAT(cut.entireBasename(), Eq("file.tar"));
}

UNIT_TEST(FileInfoEntireBasenameTests, ShouldReturnEmptyStringWhenFilenameIsEmpty)
{
        FileInfo cut;
        EXPECT_THAT(cut.entireBasename(), Eq(""));
}

UNIT_TEST(FileInfoEntireBasenameTests, ShouldReturnEmptyStringWhenFilenameContainsNoBasenameAndOnlyOneSuffix)
{
        const std::string filenameWithNoBasenameAndOnlyOneSuffix = ".txt";
        FileInfo cut(filenameWithNoBasenameAndOnlyOneSuffix);
        EXPECT_THAT(cut.entireBasename(), Eq(""));
}

UNIT_TEST(FileInfoEntireBasenameTests, ShouldReturnBasenameWhenFilenameContainsNoSuffixes)
{
        const std::string filenameWithBasenameAndNoSuffixes = "file";
        FileInfo cut(filenameWithBasenameAndNoSuffixes);
        EXPECT_THAT(cut.entireBasename(), Eq("file"));
}

UNIT_TEST(FileInfoEntireBasenameTests, ShouldReturnBasenameWhenFilenameContainsBasenameAndOneSuffix)
{
        const std::string filenameWithBasenameAndOneSuffix = "file.txt";
        FileInfo cut(filenameWithBasenameAndOneSuffix);
        EXPECT_THAT(cut.entireBasename(), "file");
}

PRISM_END_TEST_NAMESPACE
PRISM_END_NAMESPACE
