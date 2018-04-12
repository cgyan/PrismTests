#include <gmock/gmock.h>
using namespace ::testing;
#include <prism/global>
#include <prism/FileInfo>

PRISM_BEGIN_NAMESPACE
PRISM_BEGIN_TEST_NAMESPACE

class FileInfoBasenameParamTests : public TestWithParam<std::string> {
public:
        FileInfo cut;
};

INSTANTIATE_TEST_CASE_P(
        ,
        FileInfoBasenameParamTests,
        Values(
                "file",
                "file.txt",
                "./file.txt",
                "../file.txt",
                "data/./files/../file.txt",
                "files/file.txt",
                "c:\\file.txt",
                "/usr/file.txt",
                "file.tar.gz"
        )
);

TEST_P(FileInfoBasenameParamTests, ShouldReturnBasenameComponentFromFilePath)
{
        std::string testFilePath = GetParam();
        cut.setFile(testFilePath);
        EXPECT_THAT(cut.basename(), Eq("file"));
}

TEST(FileInfoBasenameTests, ShouldReturnEmptyStringWhenFilenameOnlyContainsSuffix)
{
        const std::string filenameContainingOnlySuffix = ".bat";
        FileInfo cut(filenameContainingOnlySuffix);
        EXPECT_THAT(cut.basename(), Eq(""));
}

PRISM_END_TEST_NAMESPACE
PRISM_END_NAMESPACE
