#include <gmock/gmock.h>
using namespace ::testing;
#include <prism/tests/global>
#include <prism/FileInfo>
#include "FileInfoAbsolutePathTests.h"
#include "FileInfoBasenameTests.h"
#include "FileInfoCanonicalFilePathTests.h"
#include "FileInfoEntireBasenameTests.h"
#include "FileInfoEntireSuffixTests.h"
#include "FileInfoExistsTests.h"
#include "FileInfoFilenameTests.h"
#include "FileInfoPathSeparatorTests.h"
#include "FileInfoSizeTests.h"
#include "FileInfoSuffixTests.h"
#include "FileInfoCreationDateTests.h"

PRISM_BEGIN_NAMESPACE
PRISM_BEGIN_TEST_NAMESPACE

UNIT_TEST(FileInfoTests, WhenModifyingCopyOfFileInfoExpectOriginalToRetainState)
{
        FileInfo cut("file.txt");
        FileInfo fi = cut;
        fi.setFile("new-file.txt");
        EXPECT_THAT(cut.file(), Eq("file.txt"));
}

UNIT_TEST(FileInfoTests, WhenModifyingCopyAssignedFileInfoExpectOriginalToRetainState)
{
        FileInfo cut("file.txt");
        FileInfo fi;
        fi = cut;
        fi.setFile("new-file.txt");
        EXPECT_THAT(cut.file(), Eq("file.txt"));
}

PRISM_END_TEST_NAMESPACE
PRISM_END_NAMESPACE
