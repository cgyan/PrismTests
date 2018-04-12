#include <gmock/gmock.h>
using namespace ::testing;
#include <prism/tests/global>
#include <prism/FileInfo>
#include <map>

PRISM_BEGIN_NAMESPACE
PRISM_BEGIN_TEST_NAMESPACE

class UNIT_TEST(FileInfoFilenameParamTests) : public TestWithParam<std::string>
{
public:
        FileInfo cut;
};

GROUP_INSTANTIATE_TEST_CASE_P(
        ,
        UNIT_TEST(FileInfoFilenameParamTests),
        Values(
                "file.txt",
                "./file.txt",
                "../file.txt",
                "data/./files/../file.txt",
                "/files/file.txt",
                "c:\\file.txt",
                "/usr/file.txt",
                "..\\file.txt"
        )
);

GROUP_TEST_P(Unit, FileInfoFilenameParamTests, ShouldExtractFilenameFromPath)
{
        std::string filePath = GetParam();
        cut.setFile(filePath);
        EXPECT_THAT(cut.filename(), "file.txt");
}

GROUP_TEST(Unit, FileInfoFilenameTests, ShouldReturnEmptyStringWhenFilenameIsEmpty)
{
        FileInfo cut;
        EXPECT_THAT(cut.filename(), Eq(""));
}

GROUP_TEST(Unit, FileInfoFilenameTests, ShouldReturnBasenameAndAllSuffixesWhenFilenameContainsMultipleSuffixes)
{
        const std::string filenameContainingMultipleSuffixes = "files/compressed/file.tar.gz";
        FileInfo cut(filenameContainingMultipleSuffixes);
        EXPECT_THAT(cut.filename(), Eq("file.tar.gz"));
}

GROUP_TEST(Unit, FileInfoFilenameTests, ShouldReturnSuffixWhenFilenameHasNoBasename)
{
        const std::string filenameWithoutBasename = ".txt";
        FileInfo cut(filenameWithoutBasename);
        EXPECT_THAT(cut.filename(), Eq(filenameWithoutBasename));
}

GROUP_TEST(Unit, FileInfoFilenameTests,  ShouldReturnBasenameWhenFilenameHasNoSuffix)
{
        const std::string filenameWithoutSuffix = "file";
        FileInfo cut(filenameWithoutSuffix);
        EXPECT_THAT(cut.filename(), Eq(filenameWithoutSuffix));
}

PRISM_END_TEST_NAMESPACE
PRISM_END_NAMESPACE
