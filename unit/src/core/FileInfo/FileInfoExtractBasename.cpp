#include <gmock/gmock.h>
using namespace ::testing;
#include <prism/global>
#include <prism/FileInfo>

PRISM_BEGIN_NAMESPACE
PRISM_BEGIN_TEST_NAMESPACE

class FileInfoExtractBasename : public Test {
public:
        FileInfo testSubject;
};

TEST_F(FileInfoExtractBasename, WhenFilenameContainsBasenameAndSuffixExpectBasenameReturned)
{
        const std::string filenameContainingBasenameAndSuffix = "file.txt";
        testSubject.setFile(filenameContainingBasenameAndSuffix);
        const std::string expected = "file";
        EXPECT_EQ(expected, testSubject.basename());
}

PRISM_END_TEST_NAMESPACE
PRISM_END_NAMESPACE
