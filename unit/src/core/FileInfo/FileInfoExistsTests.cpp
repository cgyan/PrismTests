#include <gmock/gmock.h>
using namespace ::testing;
#include <prism/global>
#include <prism/FileInfo>
#include <prism/FileSystemFactory>
#include <prism/MockFileSystem>

PRISM_BEGIN_NAMESPACE
PRISM_BEGIN_TEST_NAMESPACE

class FileInfoExistsTests : public Test
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

TEST_F(FileInfoExistsTests, ShouldReturnFalseWhenFilenameIsEmpty)
{
        const std::string filePath = "";
        EXPECT_CALL(*mockFileSystem, exists(filePath)).WillOnce(Return(false));
        cut.setFile(filePath);
        EXPECT_THAT(cut.exists(), Eq(false));
}

TEST_F(FileInfoExistsTests, ShouldReturnFalseWhenFileDoesNotExist)
{
        const std::string filePath = "path/to/file/that/does/not/exist";
        EXPECT_CALL(*mockFileSystem, exists(filePath)).WillOnce(Return(false));
        cut.setFile(filePath);
        EXPECT_THAT(cut.exists(), Eq(false));
}

TEST_F(FileInfoExistsTests, ShouldReturnTrueWhenFileExists)
{
        const std::string filePath = "file.txt";
        EXPECT_CALL(*mockFileSystem, exists(filePath)).WillOnce(Return(true));
        cut.setFile(filePath);
        EXPECT_THAT(cut.exists(), Eq(true));
}

PRISM_END_TEST_NAMESPACE
PRISM_END_NAMESPACE
