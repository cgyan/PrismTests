#include <gmock/gmock.h>
using namespace ::testing;
#include <prism/global>
#include <prism/FileInfo>
#include <prism/FileSystemFactory>
#include <string>

#if defined _WIN32
#       include <windows.h>
#elif defined __APPLE__
#       include <unistd.h>
#endif

PRISM_BEGIN_NAMESPACE
PRISM_BEGIN_TEST_NAMESPACE

class FileInfoAbsolutePathIntegrationTests : public Test
{
public:
        void SetUp()
        {
                FileSystemFactory::get()->setFileSystem(&FileSystem::create);
        }

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
public:
        FileInfo cut;
};

TEST_F(FileInfoAbsolutePathIntegrationTests, ShouldReturnAbsolutePathWhenFileIsInCurrentWorkingDirectory)
{
        cut.setFile("Makefile");
        EXPECT_THAT(cut.absolutePath(), Eq(currentWorkingDirectory()));
}

TEST_F(FileInfoAbsolutePathIntegrationTests, ShouldReturnEmptyStringWhenFilenameIsEmpty)
{
        cut.setFile("");
        EXPECT_THAT(cut.absolutePath(), Eq(""));
}

TEST_F(FileInfoAbsolutePathIntegrationTests, ShouldReturnEmptyStringWhenFileDoesNotExist)
{
        cut.setFile("path/to/file/that/does/not/exist");
        EXPECT_THAT(cut.absolutePath(), Eq(""));
}

PRISM_END_TEST_NAMESPACE
PRISM_END_NAMESPACE
