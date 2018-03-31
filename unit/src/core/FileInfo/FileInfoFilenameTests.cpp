#include <gmock/gmock.h>
using namespace ::testing;
#include <prism/global>
#include <prism/FileInfo>
#include <prism/FileSystemFactory>
#include <map>

PRISM_BEGIN_NAMESPACE
PRISM_BEGIN_TEST_NAMESPACE
//======================================================================================================================
// FileInfoFilenameParamTests
//======================================================================================================================
std::string pathsForFilenameTests[] = {
        "file.txt",
        "./file.txt",
        "../file.txt",
        "/files/file.txt",
        "c:\\file.txt",
        "/usr/file.txt",
        "..\\file.txt"
};

class FileInfoFilenameParamTests : public TestWithParam<std::string>
{
public:
        FileInfo cut;
};

INSTANTIATE_TEST_CASE_P(
        ,
        FileInfoFilenameParamTests,
        ValuesIn(pathsForFilenameTests)
);

TEST_P(FileInfoFilenameParamTests, ShouldExtractFilenameFromPath)
{
        std::string filePath = GetParam();
        cut.setFile(filePath);
        EXPECT_THAT(cut.filename(), "file.txt");
}

TEST(FileInfoFilenameTests, ShouldReturnEmptyStringWhenFilenameIsEmpty)
{
        FileInfo cut;
        EXPECT_THAT(cut.filename(), Eq(""));
}

TEST(FileInfoFilenameTests, ShouldReturnBasenameAndAllSuffixesWhenFilenameContainsMultipleSuffixes)
{
        const std::string filenameContainingMultipleSuffixes = "files/compressed/file.tar.gz";
        FileInfo cut(filenameContainingMultipleSuffixes);
        EXPECT_THAT(cut.filename(), Eq("file.tar.gz"));
}

TEST(FileInfoFilenameTests, ShouldReturnSuffixWhenFilenameHasNoBasename)
{
        const std::string filenameWithoutBasename = ".txt";
        FileInfo cut(filenameWithoutBasename);
        EXPECT_THAT(cut.filename(), Eq(filenameWithoutBasename));
}

TEST(FileInfoFilenameTests,  ShouldReturnBasenameWhenFilenameHasNoSuffix)
{
        const std::string filenameWithoutSuffix = "file";
        FileInfo cut(filenameWithoutSuffix);
        EXPECT_THAT(cut.filename(), Eq(filenameWithoutSuffix));
}

PRISM_END_TEST_NAMESPACE
PRISM_END_NAMESPACE
