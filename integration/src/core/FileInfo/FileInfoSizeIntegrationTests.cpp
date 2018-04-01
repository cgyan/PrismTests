#include <gmock/gmock.h>
using namespace ::testing;
#include <prism/global>
#include <prism/FileInfo>
#include <prism/FileSystemFactory>
#include <fstream>
#include <cstdio>

PRISM_BEGIN_NAMESPACE
PRISM_BEGIN_TEST_NAMESPACE

TEST(FileInfoSizeIntegrationTests, ShouldReturnSizeOfFileWhenFileExists)
{
        FileSystemFactory::get()->setFileSystem(&FileSystem::create);

        const std::string filename = "file.txt";
        const std::string data = "prism";
        const int expectedFileSize = data.length();

        std::fstream fs(filename, std::fstream::out);
        if (fs.is_open())
                fs << data;
        else ADD_FAILURE_AT(
                "Could not create file for integration test: "
                "FileInfoSizeIntegrationTests.ShouldReturnSizeOfFileWhenFileExists",
                __LINE__
        );
        fs.close();

        FileInfo cut(filename);
        EXPECT_THAT(cut.size(), Eq(expectedFileSize));
        std::remove(filename.c_str());
}

TEST(FileInfoSizeIntegrationTests, ShouldReturnErrorSizeOfNegOneWhenFileDoesNotExist)
{
        FileInfo cut("path/to/file/that/does/not/exist");
        EXPECT_THAT(cut.size(), Eq(-1));
}

PRISM_END_TEST_NAMESPACE
PRISM_END_NAMESPACE
