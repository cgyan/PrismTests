#include <gmock/gmock.h>
using namespace ::testing;
#include <prism/tests/global>
#include <prism/FileInfo>
#include <prism/tests/MockFileSystem>

PRISM_BEGIN_NAMESPACE
PRISM_BEGIN_TEST_NAMESPACE

class UNIT_TEST_CLASS(FileInfoAbsolutePathParamTests) : public TestWithParam<std::string>
{
public:
        void SetUp()
        {
                mockFileSystem = std::make_shared<MockFileSystem>();
                cut = FileInfo(GetParam(), mockFileSystem);
        }
public:
        FileInfo cut;
        std::shared_ptr<MockFileSystem> mockFileSystem;
};

UNIT_INSTANTIATE_TEST_CASE_P(
        ,
        UNIT_TEST_CLASS(FileInfoAbsolutePathParamTests),
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

UNIT_TEST_P(FileInfoAbsolutePathParamTests, ShouldReturnAbsolutePathWhenFilenameIsNotEmpty)
{
        const std::string expectedPath = "/rootfolder";
        EXPECT_CALL(*mockFileSystem, absolutePath(GetParam())).WillOnce(Return(expectedPath));
        EXPECT_THAT(cut.absolutePath(), Eq(expectedPath));
}

UNIT_TEST(FileInfoAbsolutePathTests, ShouldReturnEmptyStringWhenFilenameIsEmpty)
{
        FileInfo cut;
        EXPECT_THAT(cut.absolutePath(), Eq(""));
}

UNIT_TEST(FileInfoAbsolutePathTests, ShouldReturnEmptyStringWhenFileDoesNotExist)
{
        const std::string path = "path/to/file/that/does/not/exist";
        auto mfs = std::make_shared<MockFileSystem>();
        EXPECT_CALL(*mfs, absolutePath(path)).WillOnce(Return(""));
        FileInfo cut(path, mfs);
        EXPECT_THAT(cut.absolutePath(), Eq(""));
}

PRISM_END_TEST_NAMESPACE
PRISM_END_NAMESPACE
