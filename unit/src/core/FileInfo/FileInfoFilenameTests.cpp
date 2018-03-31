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
        FileInfo testSubject;
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
        testSubject.setFile(filePath);
        EXPECT_EQ(expectedFilename(), testSubject.filename());
}
//======================================================================================================================
// FileInfoFilenameTests
//======================================================================================================================
class FileInfoFilenameTests : public Test {
public:
        FileInfo testSubject;
};

TEST_F(FileInfoFilenameTests, ShouldReturnEmptyStringWhenFilenameIsEmpty)
{
        testSubject.setFile("");
        EXPECT_EQ("", testSubject.filename());
}

TEST_F(FileInfoFilenameTests, ShouldReturnBasenameAndAllSuffixesWhenFilenameContainsMultipleSuffixes)
{
        const std::string filenameContainingMultipleSuffixes = "files/compressed/file.tar.gz";
        testSubject.setFile(filenameContainingMultipleSuffixes);
        const std::string expected = "file.tar.gz";
        EXPECT_EQ(expected, testSubject.filename());
}

TEST_F(FileInfoFilenameTests, ShouldReturnSuffixWhenFilenameHasNoBasename)
{
        const std::string filenameWithoutBasename = ".txt";
        testSubject.setFile(filenameWithoutBasename);
        EXPECT_EQ(filenameWithoutBasename, testSubject.filename());
}

TEST_F(FileInfoFilenameTests,  ShouldReturnBasenameWhenFilenameHasNoSuffix)
{
        const std::string filenameWithoutSuffix = "file";
        testSubject.setFile(filenameWithoutSuffix);
        EXPECT_EQ(filenameWithoutSuffix, testSubject.filename());
}

PRISM_END_TEST_NAMESPACE
PRISM_END_NAMESPACE
