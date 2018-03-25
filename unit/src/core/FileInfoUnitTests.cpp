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

void
FileInfoUnitTests::setFakeFileSystemAsGlobalFileSystem() {
        FileSystemFactory::get()->setFileSystem(&FakeFileSystem::create);
}

const char *
FileInfoUnitTests::testFilename() const {
        return m_filename;
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
        EXPECT_TRUE(testSubject.exists());
}

TEST_F(FileInfoUnitTests, WhenFilenameIsEmptyExpectSizeOfZero)
{
        testSubject.setFile("");
        EXPECT_EQ(0, testSubject.size());
}

TEST_F(FileInfoUnitTests, WhenFilenameRefersToFileOnDiskExpectSizeOfThatFile)
{
        FakeFileSystem * fakeFileSystem = getFakeFileSystem();
        fakeFileSystem->createFile(this->testFilename());
        testSubject.setFile(this->testFilename());
        const unsigned int newFileSize = 200;
        fakeFileSystem->setFileSize(this->testFilename(), newFileSize);
        const unsigned int expectedFileSize = newFileSize;
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
        const unsigned int newFileSize = 0;
        fakeFileSystem->setFileSize(this->testFilename(), newFileSize);
        testSubject.setFile(this->testFilename());
        const unsigned int expectedFileSize = newFileSize;
        EXPECT_EQ(expectedFileSize, testSubject.size());
}

PRISM_END_TEST_NAMESPACE
PRISM_END_NAMESPACE
