#include <gmock/gmock.h>
using namespace ::testing;
#include <prism/global>
#include <prism/FileInfo>
#include <prism/algorithm>
#include <string>
#include <fstream>
#include <cstdio>

#if defined _WIN32
#       include <windows.h>
#elif defined __APPLE__
#       include <unistd.h>
#endif

PRISM_BEGIN_NAMESPACE
PRISM_BEGIN_TEST_NAMESPACE

const std::string normalizePath(const std::string& path)
{
        std::string ret = path;
        prism::replace(ret.begin(), ret.end(), '\\', '/');
        return ret;
}

class SystemTempDir
{
public:
        static const std::string path()
        {
                #if defined _WIN32
                        return std::string(getenv("TMP"));
                #elif defined __APPLE__
                        return std::string(getenv("TMPDIR"));
                #endif
        }

        static const bool newFileWithContent(const std::string& filename, const std::string& content)
        {
                bool success{false};
                const std::string pathFilename = SystemTempDir::path() + "\\" + filename;

                std::fstream fs(pathFilename, std::fstream::out);
                if (fs.is_open())
                {
                        fs << content;
                        success = true;
                }
                else success = false;

                fs.close();
                return success;
        }

        static const bool deleteFile(const std::string& filename)
        {
                const std::string pathFilename = SystemTempDir::path() + "\\" + filename;
                std::remove(pathFilename.c_str());
        }
};

TEST(FileInfoAbsolutePathIntegrationTests, ShouldReturnAbsolutePathOfTempDirWhenFileIsLocatedThere)
{
        if (SystemTempDir::newFileWithContent("file.tmp", "some temp content..."))
        {
                FileInfo cut(SystemTempDir::path() + "\\file.tmp");
                EXPECT_THAT(cut.absolutePath(), Eq(SystemTempDir::path()));
                SystemTempDir::deleteFile("file.tmp");
        }
        else ADD_FAILURE_AT(__FILE__, __LINE__)
                << "Could not create file in temp dir for test";
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
ShouldReturnAbsolutePathOfTempDirAndFilenameWhenFileIsLocatedThere)
{
        if (SystemTempDir::newFileWithContent("file.tmp", "some temp content..."))
        {
                FileInfo cut(SystemTempDir::path() + "\\file.tmp");
                const std::string expected = normalizePath(SystemTempDir::path() + "/file.tmp");
                EXPECT_THAT(cut.absolutePathWithFilename(), Eq(expected));
                SystemTempDir::deleteFile("file.tmp");
        }
        else ADD_FAILURE_AT(__FILE__, __LINE__)
                << "Could not create file in temp dir for test";
}

PRISM_END_TEST_NAMESPACE
PRISM_END_NAMESPACE
