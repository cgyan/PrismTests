#include <gmock/gmock.h>
using namespace ::testing;
#include <prism/global>
#include <prism/FileInfo>
#include <prism/FileSystemFactory>
#include <prism/FakeFileSystem>
#include "FileInfoTests.h"

PRISM_BEGIN_NAMESPACE
PRISM_BEGIN_TEST_NAMESPACE

class FileInfoExistsTests : public FileInfoTests {};

TEST_F(FileInfoExistsTests, ShouldNotExistWhenFilenameIsEmpty)//WhenFilenameIsEmptyExpectFileNotToExist)
{
        testSubject.setFile("");
        EXPECT_FALSE(testSubject.exists());
}

TEST_F(FileInfoExistsTests, ShouldNotExistWhenFileIsNotOnDisk)//WhenFilenameRefersToNonExistentFileOnDiskExpectFileNotToExist)
{
        testSubject.setFile("path/to/file/that/does/not/exist");
        EXPECT_FALSE(testSubject.exists());
}

TEST_F(FileInfoExistsTests, ShouldExistWhenFileIsOnDisk)//WhenFilenameRefersToFileOnDiskExpectFileToExist)
{
        writeFileToDiskWithSize(testFilename(), 0);
        testSubject.setFile(this->testFilename());
        EXPECT_TRUE(testSubject.exists());
}

PRISM_END_TEST_NAMESPACE
PRISM_END_NAMESPACE
