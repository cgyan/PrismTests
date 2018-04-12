#include <gmock/gmock.h>
using namespace ::testing;
#include <prism/tests/global>
#include <prism/FileInfo>

PRISM_BEGIN_NAMESPACE
PRISM_BEGIN_TEST_NAMESPACE

class UNIT_TEST(FileInfoEntireSuffixParamTests) : public TestWithParam<std::string>
{
public:
        FileInfo cut;
};

GROUP_INSTANTIATE_TEST_CASE_P(
        ,
        UNIT_TEST(FileInfoEntireSuffixParamTests),
        Values(
                ".tar.gz",
                "file.tar.gz",
                "./file.tar.gz",
                "../file.tar.gz",
                "data/./files/../file.tar.gz",
                "/files/file.tar.gz",
                "c:/file.tar.gz"
        )
);

GROUP_TEST_P(Unit, FileInfoEntireSuffixParamTests, ShouldReturnEntireSuffixWhenFilenameIsNotEmpty)
{
        const std::string filename = GetParam();
        cut.setFile(filename);
        EXPECT_THAT(cut.entireSuffix(), Eq("tar.gz"));
}

GROUP_TEST(Unit, FileInfoEntireSuffixTests, ShouldReturnEmptyStringWhenFilenameIsEmpty)
{
        FileInfo cut;
        EXPECT_THAT(cut.entireSuffix(), Eq(""));
}

GROUP_TEST(Unit, FileInfoEntireSuffixTests, ShouldReturnEmptyStringWhenFilenameContainsNoSuffixs)
{
        const std::string filenameWithNoSuffixes = "file";
        FileInfo cut(filenameWithNoSuffixes);
        EXPECT_THAT(cut.entireSuffix(), Eq(""));
}

GROUP_TEST(Unit, FileInfoEntireSuffixTests, ShouldReturnAllSuffixesWhenFilenameContainsMultipleSuffixes)
{
        const std::string filenameWithMultipleSuffixes = "file.tar.gz";
        FileInfo cut(filenameWithMultipleSuffixes);
        EXPECT_THAT(cut.entireSuffix(), Eq("tar.gz"));
}

PRISM_END_TEST_NAMESPACE
PRISM_END_NAMESPACE
