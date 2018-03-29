#include <gmock/gmock.h>
using namespace ::testing;
#include <prism/global>
#include <prism/FileInfo>

PRISM_BEGIN_NAMESPACE
PRISM_BEGIN_TEST_NAMESPACE

class FileInfoBasenameParamTest : public TestWithParam<std::string> {
public:
        FileInfo testSubject;
        const std::string expectedBasename() { return m_expectedBasename; }
private:
        std::string m_expectedBasename{"file"};
};

INSTANTIATE_TEST_CASE_P(
        ,
        FileInfoBasenameParamTest,
        Values(
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

TEST_P(FileInfoBasenameParamTest, ShouldExtractBasenameFromFilePath)
{
        std::string testFilePath = GetParam();
        testSubject.setFile(testFilePath);
        EXPECT_EQ(expectedBasename(), testSubject.basename());
}

TEST(FileInfoBasenameTest, ShouldReturnEmptyStringWhenFilenameOnlyContainsSuffix)
{
        const std::string filenameContainingOnlySuffix = ".bat";
        FileInfo testSubject(filenameContainingOnlySuffix);
        const std::string expectedBasename = "";
        EXPECT_EQ(expectedBasename, testSubject.basename());
}

PRISM_END_TEST_NAMESPACE
PRISM_END_NAMESPACE
