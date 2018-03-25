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
public:
        const char * m_filename{"file.txt"};
        FileInfo testSubject{m_filename};
};

void
FileInfoUnitTests::SetUp() {

}

void
FileInfoUnitTests::TearDown() {

}

const char *
FileInfoUnitTests::testFilename() const {
        return m_filename;
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
        FileSystemFactory::get()->setFileSystem(&FakeFileSystem::create);
        AbstractFileSystem * fakeFileSystem = FileSystemFactory::get()->getFileSystem();
        fakeFileSystem->createFile(this->testFilename());
        testSubject.setFile(this->testFilename());
        EXPECT_TRUE(testSubject.exists());
}

PRISM_END_TEST_NAMESPACE
PRISM_END_NAMESPACE
