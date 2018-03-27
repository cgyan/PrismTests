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
        getFakeFileSystem()->deleteAllFiles();
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

TEST_F(FileInfoUnitTests, WhenFilenameIsEmptyExpectSizeOfZero)
{
        testSubject.setFile("");
        EXPECT_EQ(0, testSubject.size());
}

TEST_F(FileInfoUnitTests, WhenFilenameRefersToFileOnDiskExpectSizeOfThatFile)
{
        std::cout << "setting test filename: " << this->testFilename() << std::endl;
        FakeFileSystem * fakeFileSystem = getFakeFileSystem();
        fakeFileSystem->createFile(this->testFilename());
        testSubject.setFile(this->testFilename());
        std::cout << "testSubject.filename = " << testSubject.filename() << std::endl;
        const int newFileSize = 200;
        fakeFileSystem->setFileSize(newFileSize);
        const int expectedFileSize = newFileSize;
        EXPECT_EQ(expectedFileSize, testSubject.size());
}

TEST_F(FileInfoUnitTests, WhenFilenameRefersToNonExistentFileExpectSizeOfZero)
{
        testSubject.setFile("path/to/file/that/does/not/exist");
        EXPECT_EQ(0, testSubject.size());
}

TEST_F(FileInfoUnitTests, WhenFileHasNoContentExpectSizeOfZero)
{
        FakeFileSystem * fakeFileSystem = getFakeFileSystem();
        fakeFileSystem->createFile(this->testFilename());
        const int newFileSize = 0;
        fakeFileSystem->setFileSize(newFileSize);
        testSubject.setFile(this->testFilename());
        const int expectedFileSize = newFileSize;
        EXPECT_EQ(expectedFileSize, testSubject.size());
}

class FileInfoFilenameUnitTests : public Test {
        void SetUp() {
                FileSystemFactory::get()->setFileSystem(&FileSystem::create);
        }
public:
        FileInfo testSubject;
};

TEST_F(FileInfoFilenameUnitTests, WhenFilenameHasBasenameAndSuffixExpectBasenameAndSuffixReturned)
{
        const std::string filenameWithBaseAndSuffix = "file.txt";
        testSubject.setFile(filenameWithBaseAndSuffix);
        EXPECT_EQ(filenameWithBaseAndSuffix, testSubject.filename());
}

TEST_F(FileInfoFilenameUnitTests, WhenFilenameHasNoBasenameExpectSuffixReturned)
{
        const std::string filenameWithoutBasename = ".txt";
        testSubject.setFile(filenameWithoutBasename);
        EXPECT_EQ(filenameWithoutBasename, testSubject.filename());
}

TEST_F(FileInfoFilenameUnitTests, WhenFilenameHasNoSuffixExpectSuffixReturned)
{
        const std::string filenameWithoutSuffix = "file";
        testSubject.setFile(filenameWithoutSuffix);
        EXPECT_EQ(filenameWithoutSuffix, testSubject.filename());
}

TEST_F(FileInfoFilenameUnitTests, WhenFilenameIsInCurrentDirectoryExpectBasenameAndSuffixReturned)
{
        const std::string filenameInCurrentDirectory = "./file.txt";
        testSubject.setFile(filenameInCurrentDirectory);
        const std::string expected = "file.txt";
        EXPECT_EQ(expected, testSubject.filename());
}

TEST_F(FileInfoFilenameUnitTests, WhenFilenameIsInParentDirectoryExpectBasenameAndSuffixReturned)
{
        const std::string filenameInParentDirectory = "../file.txt";
        testSubject.setFile(filenameInParentDirectory);
        const std::string expected = "file.txt";
        EXPECT_EQ(expected, testSubject.filename());
}

TEST_F(FileInfoFilenameUnitTests, WhenFilenameIsInSubdirectoryExpectBasenameAndSuffixReturned)
{
        const std::string filenameInSubdirectory = "/files/file.txt";
        testSubject.setFile(filenameInSubdirectory);
        const std::string expected = "file.txt";
        EXPECT_EQ(expected, testSubject.filename());
}

TEST_F(FileInfoFilenameUnitTests, WhenFilenameIsAbsoluteExpectBasenameAndSuffixReturned)
{
        const std::string filenameAbsolutePath = "c:/file.txt";
        testSubject.setFile(filenameAbsolutePath);
        const std::string expected = "file.txt";
        EXPECT_EQ(expected, testSubject.filename());
}

TEST_F(FileInfoFilenameUnitTests, WhenFilenameHasNotBeenSetExpectEmptyStringReturned)
{
        EXPECT_EQ("", testSubject.filename());
}

TEST_F(FileInfoFilenameUnitTests, WhenFilenameUsesBackslashesExpectBasenameAndSuffixReturned)
{
        const std::string filenameWithBackslash = "c:\\file.txt";
        testSubject.setFile(filenameWithBackslash);
        const std::string expected = "file.txt";
        EXPECT_EQ(expected, testSubject.filename());
}

PRISM_END_TEST_NAMESPACE
PRISM_END_NAMESPACE
