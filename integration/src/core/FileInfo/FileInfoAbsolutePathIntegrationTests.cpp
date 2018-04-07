#include <gmock/gmock.h>
using namespace ::testing;
#include <prism/global>
#include <prism/FileInfo>
#include <string>

#if defined _WIN32
#       include <windows.h>
#elif defined __APPLE__
#       include <unistd.h>
#endif

PRISM_BEGIN_NAMESPACE
PRISM_BEGIN_TEST_NAMESPACE

const std::string currentWorkingDirectory()
{
        char cwd[4096];
        bool error{false};

        #if defined _WIN32
                if (GetFullPathName(".", 4096, cwd, NULL) == 0) error = true;
        #elif defined __APPLE__
                if (getwd(cwd) == nullptr) error = true;
                #endif

        if (error) {
                std::cerr << __FILE__ << ":" << __LINE__;
                std::cerr << " could not retrieve absolute path\n";
        }

        return std::string(cwd);
}
//==============================================================================
//==============================================================================
TEST(FileInfoAbsolutePathIntegrationTests, ShouldReturnAbsolutePathWhenFileIsInCurrentWorkingDirectory)
{
        FileInfo cut("Makefile");
        EXPECT_THAT(cut.absolutePath(), Eq(currentWorkingDirectory()));
}

TEST(FileInfoAbsolutePathIntegrationTests, ShouldReturnEmptyStringWhenFilenameIsEmpty)
{
        FileInfo cut("");
        EXPECT_THAT(cut.absolutePath(), Eq(""));
}

TEST(FileInfoAbsolutePathIntegrationTests, ShouldReturnEmptyStringWhenFileDoesNotExist)
{
        FileInfo cut("path/to/file/that/does/not/exist");
        EXPECT_THAT(cut.absolutePath(), Eq(""));
}
//==============================================================================
//==============================================================================
TEST(FileInfoAbsolutePathWithFilenameIntegrationTests, ShouldReturnEmptyStringWhenFilenameIsEmpty)
{
        FileInfo cut;
        EXPECT_THAT(cut.absolutePathWithFilename(), Eq(""));
}

TEST(FileInfoAbsolutePathWithFilenameIntegrationTests, ShouldReturnEmptyStringWhenFileDoesNotExist)
{
        FileInfo cut("path/to/file/that/does/not/exist");
        EXPECT_THAT(cut.absolutePathWithFilename(), Eq(""));
}

TEST(FileInfoAbsolutePathWithFilenameIntegrationTests,
ShouldReturnAbsolutePathAndFilenameWhenFileIsInCurrentWorkingDirectory)
{
        FileInfo cut("Makefile");
        std::string expected = currentWorkingDirectory() + "/Makefile";
        expected = FileInfo::toNormalizedSeparators(expected);
        EXPECT_THAT(cut.absolutePathWithFilename(), Eq(expected));
}

PRISM_END_TEST_NAMESPACE
PRISM_END_NAMESPACE
