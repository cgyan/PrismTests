#include <gmock/gmock.h>
using namespace ::testing;
#include <prism/global>
#include <prism/FileInfo>

PRISM_BEGIN_NAMESPACE
PRISM_BEGIN_TEST_NAMESPACE

class FileInfoBasenameTest : public Test {
public:
        FileInfo testSubject;
};

TEST_F(FileInfoBasenameTest, ShouldReturnBasenameWhenFilenameContainsBasenameAndSuffix)
{
        const std::string filenameContainingBasenameAndSuffix = "file.txt";
        testSubject.setFile(filenameContainingBasenameAndSuffix);
        const std::string expected = "file";
        EXPECT_EQ(expected, testSubject.basename());
}

TEST_F(FileInfoBasenameTest, ShouldReturnEmptyStringWhenFilenameOnlyContainsSuffix)
{
        const std::string filenameContainingSuffix = ".txt";
        testSubject.setFile(filenameContainingSuffix);
        EXPECT_EQ("", testSubject.basename());
}

TEST_F(FileInfoBasenameTest, ShouldReturnBasenameWhenFilenameIsLocatedInCurrentDirectory)
{
        const std::string filenameInThisDirectory = "./file.txt";
        testSubject.setFile(filenameInThisDirectory);
        const std::string expected = "file";
        EXPECT_EQ(expected, testSubject.basename());
}

TEST_F(FileInfoBasenameTest, ShouldReturnBasenameWhenFilenameIsLocatedInParentDirectory)
{
        const std::string filenameInParentDir = "../file.txt";
        testSubject.setFile(filenameInParentDir);
        const std::string expected = "file";
        EXPECT_EQ(expected, testSubject.basename());
}

TEST_F(FileInfoBasenameTest, ShouldReturnBasenameWhenFilenameIsLocatedInSubdirectory)
{
        const std::string filenameInSubdirectory = "files/file.txt";
        testSubject.setFile(filenameInSubdirectory);
        const std::string expected = "file";
        EXPECT_EQ(expected, testSubject.basename());
}

TEST_F(FileInfoBasenameTest, ShouldReturnBasenameWhenWindowsFilenameIsAbsolute)
{
        const std::string filenameAbsolute = "c:\\file.txt";
        testSubject.setFile(filenameAbsolute);
        const std::string expected = "file";
        EXPECT_EQ(expected, testSubject.basename());
}

TEST_F(FileInfoBasenameTest, ShouldReturnBasenameWhenUnixFilenameIsAbsolute)
{
        const std::string filenameAbsolute = "/usr/file.txt";
        testSubject.setFile(filenameAbsolute);
        const std::string expected = "file";
        EXPECT_EQ(expected, testSubject.basename());
}

TEST_F(FileInfoBasenameTest, ShouldReturnBasenameWhenFilenameOnlyContainsBasename)
{
        const std::string filenameWithOnlyBasename = "file";
        testSubject.setFile(filenameWithOnlyBasename);
        EXPECT_EQ(filenameWithOnlyBasename, testSubject.basename());
}

TEST_F(FileInfoBasenameTest, ShouldReturnBasenameWhenFilenameHasMultipleSuffixes)
{
        const std::string filenameWithMultipleSuffixes = "file.tar.gz";
        testSubject.setFile(filenameWithMultipleSuffixes);
        const std::string expected = "file";
        EXPECT_EQ(expected, testSubject.basename());
}

PRISM_END_TEST_NAMESPACE
PRISM_END_NAMESPACE
