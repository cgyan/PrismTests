#include <prism/global>
#include "FileInfoSizeTests.h"

PRISM_BEGIN_NAMESPACE
PRISM_BEGIN_TEST_NAMESPACE


TEST_F(FileInfoSizeTests, ShouldReturnNegativeOneWhenFilenameIsEmpty)
{
        testSubject.setFile("");
        EXPECT_EQ(ERROR_SIZE_NEG_1, testSubject.size());
}

TEST_F(FileInfoSizeTests, ShouldReturnSizeOfFileOnDisk)
{
        writeFileToDiskWithSize(testFilename(), 200);
        testSubject.setFile(testFilename());
        EXPECT_EQ(200, testSubject.size());
}

TEST_F(FileInfoSizeTests, ShouldReturnNegativeOneWhenFileDoesNotExist)
{
        testSubject.setFile("path/to/file/that/does/not/exist");
        EXPECT_EQ(ERROR_SIZE_NEG_1, testSubject.size());
}

TEST_F(FileInfoSizeTests, ShouldReturnZeroWhenFileContainsNoData)
{
        writeFileToDiskWithSize(testFilename(), 0);
        testSubject.setFile(testFilename());
        EXPECT_EQ(0, testSubject.size());
}

PRISM_END_TEST_NAMESPACE
PRISM_END_NAMESPACE
