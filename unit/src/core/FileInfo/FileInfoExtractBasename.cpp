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

TEST_F(FileInfoBasenameTest, ShouldReturnBasenameWhenFilenameIsLocatedInThisDirectory)
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



PRISM_END_TEST_NAMESPACE
PRISM_END_NAMESPACE
