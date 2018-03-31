#include <gmock/gmock.h>
using namespace ::testing;
#include <prism/global>
#include <prism/FileInfo>

PRISM_BEGIN_NAMESPACE
PRISM_BEGIN_TEST_NAMESPACE

class FileInfoBasenameParamTests : public TestWithParam<std::string> {
public:
        FileInfo cut;
        const std::string expectedBasename() { return m_expectedBasename; }
private:
        std::string m_expectedBasename{"file"};
};

INSTANTIATE_TEST_CASE_P(
        ,
        FileInfoBasenameParamTests,
        ValuesIn(
                "file",
                "file.txt",
                "./file.txt",
                "../file.txt",
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
        EXPECT_EQ(expectedBasename(), cut.basename());
}

TEST(FileInfoBasenameTests, ShouldReturnEmptyStringWhenFilenameOnlyContainsSuffix)
{
        const std::string filenameContainingOnlySuffix = ".bat";
        FileInfo cut(filenameContainingOnlySuffix);
        const std::string expectedBasename = "";
        EXPECT_EQ(expectedBasename, cut.basename());
}

PRISM_END_TEST_NAMESPACE
PRISM_END_NAMESPACE
