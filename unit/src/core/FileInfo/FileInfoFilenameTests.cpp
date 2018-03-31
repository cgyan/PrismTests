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
        const std::string getPath() const { return GetParam(); }
        const std::string expectedFilename() const { return m_expectedFilename; }
private:
        std::string m_expectedFilename{"file.txt"};
};

INSTANTIATE_TEST_CASE_P(
        ,
        FileInfoFilenameParamTests,
        ValuesIn(pathsForFilenameTests)
);

TEST_P(FileInfoFilenameParamTests, ShouldExtractFilenameFromPath)
{
        std::string filePath = getPath();
        cut.setFile(filePath);
        EXPECT_EQ(expectedFilename(), cut.filename());
}
//======================================================================================================================
// FileInfoFilenameTests
//======================================================================================================================
class FileInfoFilenameTests : public Test {
public:
        FileInfo cut;
};

TEST_F(FileInfoFilenameTests, ShouldReturnEmptyStringWhenFilenameIsEmpty)
{
        cut.setFile("");
        EXPECT_EQ("", cut.filename());
}

TEST_F(FileInfoFilenameTests, ShouldReturnBasenameAndAllSuffixesWhenFilenameContainsMultipleSuffixes)
{
        const std::string filenameContainingMultipleSuffixes = "files/compressed/file.tar.gz";
        cut.setFile(filenameContainingMultipleSuffixes);
        const std::string expected = "file.tar.gz";
        EXPECT_EQ(expected, cut.filename());
}

TEST_F(FileInfoFilenameTests, ShouldReturnSuffixWhenFilenameHasNoBasename)
{
        const std::string filenameWithoutBasename = ".txt";
        cut.setFile(filenameWithoutBasename);
        EXPECT_EQ(filenameWithoutBasename, cut.filename());
}

TEST_F(FileInfoFilenameTests,  ShouldReturnBasenameWhenFilenameHasNoSuffix)
{
        const std::string filenameWithoutSuffix = "file";
        cut.setFile(filenameWithoutSuffix);
        EXPECT_EQ(filenameWithoutSuffix, cut.filename());
}

PRISM_END_TEST_NAMESPACE
PRISM_END_NAMESPACE
