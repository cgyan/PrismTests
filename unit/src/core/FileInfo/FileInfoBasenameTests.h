#include <gmock/gmock.h>
using namespace ::testing;
#include <prism/tests/global>
#include <prism/FileInfo>

PRISM_BEGIN_NAMESPACE
PRISM_BEGIN_TEST_NAMESPACE

class UNIT_TEST(FileInfoBasenameParamTests) : public TestWithParam<std::string> {
public:
        FileInfo cut;
};

GROUP_INSTANTIATE_TEST_CASE_P(
        ,
        UNIT_TEST(FileInfoBasenameParamTests),
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

GROUP_TEST_P(Unit, FileInfoBasenameParamTests, ShouldReturnBasenameComponentFromFilePath)
{
        std::string testFilePath = GetParam();
        cut.setFile(testFilePath);
        EXPECT_THAT(cut.basename(), Eq("file"));
}

GROUP_TEST(Unit, FileInfoBasenameTests, ShouldReturnEmptyStringWhenFilenameOnlyContainsSuffix)
{
        const std::string filenameContainingOnlySuffix = ".bat";
        FileInfo cut(filenameContainingOnlySuffix);
        EXPECT_THAT(cut.basename(), Eq(""));
}

PRISM_END_TEST_NAMESPACE
PRISM_END_NAMESPACE
