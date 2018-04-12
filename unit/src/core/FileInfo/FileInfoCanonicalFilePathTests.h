#include <gmock/gmock.h>
using namespace ::testing;
#include <prism/tests/global>
#include <prism/FileInfo>

PRISM_BEGIN_NAMESPACE
PRISM_BEGIN_TEST_NAMESPACE

GROUP_TEST(Unit, FileInfoCanonicalFilePathTests, ShouldReturnEmptyStringWhenFilePathIsEmpty)
{
        FileInfo cut;
        EXPECT_THAT(cut.canonicalFilePath(), Eq(std::string{}));
}

GROUP_TEST(Unit, FileInfoCanonicalFilePathTests, ShouldReturnSameWhenFilePathIsAlreadyCanonical)
{
        const std::string filePathAlreadyCanonicalized = "/usr/bin/files/file.txt";
        FileInfo cut(filePathAlreadyCanonicalized);
        EXPECT_THAT(cut.canonicalFilePath(), Eq(filePathAlreadyCanonicalized));
}

GROUP_TEST(Unit, FileInfoCanonicalFilePathTests, ShouldIgnoreDirectoryWhenFilePathContainsSingleDotComponent)
{
        const std::string filePathWithSingleDotComponent = "files/./file.txt";
        FileInfo cut(filePathWithSingleDotComponent);
        EXPECT_THAT(cut.canonicalFilePath(), Eq("files/file.txt"));
}

GROUP_TEST(Unit, FileInfoCanonicalFilePathTests, ShouldIgnorePreviousDirectoryWhenFilePathContainsDoubleDotComponent)
{
        const std::string filePathWithDoubleDotComponent = "/usr/bin/files/../file.txt";
        FileInfo cut (filePathWithDoubleDotComponent);
        EXPECT_THAT(cut.canonicalFilePath(), Eq("/usr/bin/file.txt"));
}

GROUP_TEST(Unit, FileInfoCanonicalFilePathTests, ShouldReturnEmptyStringWhenFilePathContainsDoubleDotComponentAfterRootDirectory)
{
        const std::string filePathWithDoubleDotComponentAfterRootDirectory = "C:/../";
        FileInfo cut(filePathWithDoubleDotComponentAfterRootDirectory);
        EXPECT_THAT(cut.canonicalFilePath(), Eq(""));
}

GROUP_TEST(Unit, ileInfoCanonicalFilePathTests, ShouldReturnEmptyStringWhenThereAreMoreDoubleDotComponentsThanPathComponents)
{
        const std::string filePathThatResolvesToHigherThanRootDirectory = "/usr/../bin../..";
        FileInfo cut(filePathThatResolvesToHigherThanRootDirectory);
        EXPECT_THAT(cut.canonicalFilePath(), Eq(""));
}

PRISM_END_TEST_NAMESPACE
PRISM_END_NAMESPACE
