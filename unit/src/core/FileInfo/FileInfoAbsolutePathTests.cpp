#include <gmock/gmock.h>
using namespace ::testing;
#include <prism/global>
#include <prism/FileInfo>
#include <prism/FileSystemFactory>
#include <prism/MockFileSystem>

PRISM_BEGIN_NAMESPACE
PRISM_BEGIN_TEST_NAMESPACE

MockFileSystem *
getMockFileSystem()
{
        FileSystemFactory::get()->setFileSystem(&MockFileSystem::create);
        return dynamic_cast<MockFileSystem*>(FileSystemFactory::get()->getFileSystem());
}

class FileInfoAbsolutePathParamTests : public TestWithParam<std::string>
{
public:
        void SetUp()
        {
                mockFileSystem = getMockFileSystem();
        }
public:
        FileInfo cut;
        MockFileSystem * mockFileSystem;
};

INSTANTIATE_TEST_CASE_P(
        ,
        FileInfoAbsolutePathParamTests,
        Values(
                "file",
                ".txt"
                "file.txt",
                "file.tar.gz",
                "./file.txt",
                "data/./files/../file.txt",
                "/rootfolder/file.txt"
        )
);

TEST_P(FileInfoAbsolutePathParamTests, ShouldReturnAbsolutePathWhenFilenameIsNotEmpty)
{
        const std::string expectedPath = "/rootfolder";
        EXPECT_CALL(*mockFileSystem, absolutePath(GetParam())).WillOnce(Return(expectedPath));
        cut.setFile(GetParam());
        EXPECT_THAT(cut.absolutePath(), Eq(expectedPath));
}

TEST(FileInfoAbsolutePathTests, ShouldReturnEmptyStringWhenFilenameIsEmpty)
{
        FileInfo cut;
        EXPECT_THAT(cut.absolutePath(), Eq(""));
}

TEST(FileInfoAbsolutePathTests, ShouldReturnEmptyStringWhenFileDoesNotExist)
{
        const std::string path = "path/to/file/that/does/not/exist";
        EXPECT_CALL(*getMockFileSystem(), absolutePath(path)).WillOnce(Return(""));
        FileInfo cut(path);
        EXPECT_THAT(cut.absolutePath(), Eq(""));
}

PRISM_END_TEST_NAMESPACE
PRISM_END_NAMESPACE
