#include <gmock/gmock.h>
using namespace ::testing;
#include <prism/global>
#include <prism/FileInfo>

PRISM_BEGIN_NAMESPACE
PRISM_BEGIN_TEST_NAMESPACE

TEST(FileInfoTestss, WhenModifyingCopyOfFileInfoExpectOriginalToRetainState)
{
        FileInfo cut("file.txt");
        FileInfo fi = cut;
        fi.setFile("new-file.txt");
        EXPECT_THAT(cut.file(), Eq("file.txt"));
}

TEST(FileInfoTestss, WhenModifyingCopyAssignedFileInfoExpectOriginalToRetainState)
{
        FileInfo cut("file.txt");
        FileInfo fi;
        fi = cut;
        fi.setFile("new-file.txt");
        EXPECT_THAT(cut.file(), Eq("file.txt"));
}

PRISM_END_TEST_NAMESPACE
PRISM_END_NAMESPACE
