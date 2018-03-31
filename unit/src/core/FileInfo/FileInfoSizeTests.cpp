#include <gmock/gmock.h>
using namespace ::testing;
#include <prism/global>
#include <prism/FileInfo>
#include <prism/FileSystemFactory>
#include <prism/MockFileSystem>

PRISM_BEGIN_NAMESPACE
PRISM_BEGIN_TEST_NAMESPACE

class FileInfoSizeTests : public Test
{
public:
        void SetUp()
        {
                FileSystemFactory::get()->setFileSystem(&MockFileSystem::create);
                mockFileSystem = dynamic_cast<MockFileSystem*>(FileSystemFactory::get()->getFileSystem());
        }
public:
        FileInfo cut;
        MockFileSystem * mockFileSystem;
};

TEST_F(FileInfoSizeTests, ShouldReturnNegativeOneWhenFilenameIsEmpty)
{
        EXPECT_CALL(*mockFileSystem, fileSizeInBytes("")).WillOnce(Return(-1));
        cut.setFile("");
        EXPECT_THAT(cut.size(), Eq(-1));
}

TEST_F(FileInfoSizeTests, ShouldReturnSizeOfFileWhenFileIsOnDisk)
{
        EXPECT_CALL(*mockFileSystem, fileSizeInBytes("path/to/file.txt")).WillOnce(Return(200));
        cut.setFile("path/to/file.txt");
        EXPECT_THAT(cut.size(), Eq(200));
}

TEST_F(FileInfoSizeTests, ShouldReturnNegativeOneWhenFileIsNotOnDisk)
{
        EXPECT_CALL(*mockFileSystem, fileSizeInBytes("path/to/file/that/does/not/exist")).WillOnce(Return(-1));
        cut.setFile("path/to/file/that/does/not/exist");
        EXPECT_THAT(cut.size(), Eq(-1));
}

PRISM_END_TEST_NAMESPACE
PRISM_END_NAMESPACE
