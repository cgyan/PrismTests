#include <gmock/gmock.h>
using namespace ::testing;
#include <prism/global>
#include <prism/FileInfo>
#include <prism/FileSystemFactory>
#include <prism/FakeFileSystem>

PRISM_BEGIN_NAMESPACE
PRISM_BEGIN_TEST_NAMESPACE
//==============================================================================
// test class
//==============================================================================
class FileInfoUnitTests : public Test {
public:
        void SetUp();
        void TearDown();
        const char * testFilename() const;
        FakeFileSystem * getFakeFileSystem() const;
private:
        void setFakeFileSystemAsGlobalFileSystem();
public:
        const char * m_filename{"unit_test_file.txt"};
        FileInfo testSubject{m_filename};
};

void
FileInfoUnitTests::SetUp()
{
        setFakeFileSystemAsGlobalFileSystem();
}

void
FileInfoUnitTests::TearDown()
{
        getFakeFileSystem()->clear();
}

const char *
FileInfoUnitTests::testFilename() const {
        return m_filename;
}

void
FileInfoUnitTests::setFakeFileSystemAsGlobalFileSystem() {
        FileSystemFactory::get()->setFileSystem(&FakeFileSystem::create);
}

FakeFileSystem *
FileInfoUnitTests::getFakeFileSystem() const
{
        AbstractFileSystem * fakeFileSystem = FileSystemFactory::get()->getFileSystem();
        return dynamic_cast<FakeFileSystem*>(fakeFileSystem);
}
//==============================================================================
// tests
//==============================================================================
TEST_F(FileInfoUnitTests, WhenFilenameIsEmptyExpectFileNotToExist)
{
        testSubject.setFile("");
        EXPECT_FALSE(testSubject.exists());
}

TEST_F(FileInfoUnitTests, WhenFilenameRefersToNonExistentFileOnDiskExpectFileNotToExist)
{
        testSubject.setFile("path/to/file/that/does/not/exist");
        EXPECT_FALSE(testSubject.exists());
}

TEST_F(FileInfoUnitTests, WhenFilenameRefersToFileOnDiskExpectFileToExist)
{
        FakeFileSystem * fakeFileSystem = getFakeFileSystem();
        fakeFileSystem->createFile(this->testFilename());
        testSubject.setFile(this->testFilename());
        EXPECT_TRUE(testSubject.exists()) << "file with name called " << testFilename() << " should exist";
}

TEST_F(FileInfoUnitTests, WhenFilenameIsEmptyExpectSizeOfNegativeOne)
{
        testSubject.setFile("");
        const int fileDoesNotExist = -1;
        EXPECT_EQ(fileDoesNotExist, testSubject.size());
}

TEST_F(FileInfoUnitTests, WhenFilenameRefersToFileOnDiskExpectSizeOfThatFile)
{
        FakeFileSystem * fakeFileSystem = getFakeFileSystem();
        fakeFileSystem->createFile(this->testFilename());
        testSubject.setFile(this->testFilename());
        const int newFileSize = 200;
        fakeFileSystem->setFileSize(newFileSize);
        const int expectedFileSize = newFileSize;
        EXPECT_EQ(expectedFileSize, testSubject.size());
}

TEST_F(FileInfoUnitTests, WhenFilenameRefersToNonExistentFileExpectSizeOfNegativeOne)
{
        testSubject.setFile("path/to/file/that/does/not/exist");
        const int fileDoesNotExist = -1;
        EXPECT_EQ(fileDoesNotExist, testSubject.size());
}

TEST_F(FileInfoUnitTests, WhenFileThatExistsHasNoContentExpectSizeOfZero)
{
        FakeFileSystem * fakeFileSystem = getFakeFileSystem();
        fakeFileSystem->createFile(this->testFilename());
        const int newFileSize = 0;
        fakeFileSystem->setFileSize(newFileSize);
        testSubject.setFile(this->testFilename());
        const int expectedFileSize = newFileSize;
        EXPECT_EQ(expectedFileSize, testSubject.size());
}

class FileInfoExtractFilename : public Test {
        void SetUp() {
                FileSystemFactory::get()->setFileSystem(&FileSystem::create);
        }
public:
        FileInfo testSubject;
};

TEST_F(FileInfoExtractFilename, WhenFilenameHasBasenameAndSuffixExpectBasenameAndSuffixReturned)
{
        const std::string filenameWithBaseAndSuffix = "file.txt";
        testSubject.setFile(filenameWithBaseAndSuffix);
        EXPECT_EQ(filenameWithBaseAndSuffix, testSubject.filename());
}

TEST_F(FileInfoExtractFilename, WhenFilenameHasNoBasenameExpectSuffixReturned)
{
        const std::string filenameWithoutBasename = ".txt";
        testSubject.setFile(filenameWithoutBasename);
        EXPECT_EQ(filenameWithoutBasename, testSubject.filename());
}

TEST_F(FileInfoExtractFilename, WhenFilenameHasNoSuffixExpectSuffixReturned)
{
        const std::string filenameWithoutSuffix = "file";
        testSubject.setFile(filenameWithoutSuffix);
        EXPECT_EQ(filenameWithoutSuffix, testSubject.filename());
}

TEST_F(FileInfoExtractFilename, WhenFilenameIsInCurrentDirectoryExpectBasenameAndSuffixReturned)
{
        const std::string filenameInCurrentDirectory = "./file.txt";
        testSubject.setFile(filenameInCurrentDirectory);
        const std::string expected = "file.txt";
        EXPECT_EQ(expected, testSubject.filename());
}

TEST_F(FileInfoExtractFilename, WhenFilenameIsInParentDirectoryExpectBasenameAndSuffixReturned)
{
        const std::string filenameInParentDirectory = "../file.txt";
        testSubject.setFile(filenameInParentDirectory);
        const std::string expected = "file.txt";
        EXPECT_EQ(expected, testSubject.filename());
}

TEST_F(FileInfoExtractFilename, WhenFilenameIsInSubdirectoryExpectBasenameAndSuffixReturned)
{
        const std::string filenameInSubdirectory = "/files/file.txt";
        testSubject.setFile(filenameInSubdirectory);
        const std::string expected = "file.txt";
        EXPECT_EQ(expected, testSubject.filename());
}

TEST_F(FileInfoExtractFilename, WhenWindowsFilenameIsAbsoluteExpectBasenameAndSuffixReturned)
{
        const std::string filenameAbsolutePath = "c:\\file.txt";
        testSubject.setFile(filenameAbsolutePath);
        const std::string expected = "file.txt";
        EXPECT_EQ(expected, testSubject.filename());
}

TEST_F(FileInfoExtractFilename, WhenUnixFilenameIsAbsoluteExpectBasenameAndSuffixReturned)
{
        const std::string filenameAbsolutePath = "/usr/file.txt";
        testSubject.setFile(filenameAbsolutePath);
        const std::string expected = "file.txt";
        EXPECT_EQ(expected, testSubject.filename());
}

TEST_F(FileInfoExtractFilename, WhenFilenameHasNotBeenSetExpectEmptyStringReturned)
{
        EXPECT_EQ("", testSubject.filename());
}

TEST_F(FileInfoExtractFilename, WhenFilenameUsesBackslashesExpectBasenameAndSuffixReturned)
{
        const std::string filenameWithBackslash = "..\\file.txt";
        testSubject.setFile(filenameWithBackslash);
        const std::string expected = "file.txt";
        EXPECT_EQ(expected, testSubject.filename());
}

TEST_F(FileInfoExtractFilename, WhenFilenameContainsMultipleSuffixesExpectBasenameAndSuffixesReturned)
{
        const std::string filenameContainingMultipleSuffixes = "files/compressed/file.tar.gz";
        testSubject.setFile(filenameContainingMultipleSuffixes);
        const std::string expected = "file.tar.gz";
        EXPECT_EQ(expected, testSubject.filename());
}

PRISM_END_TEST_NAMESPACE
PRISM_END_NAMESPACE
