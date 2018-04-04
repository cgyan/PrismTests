#include <gmock/gmock.h>
using namespace ::testing;
#include <prism/global>
#include <prism/FileInfo>
#include <fstream>
#include <cstdio>

PRISM_BEGIN_NAMESPACE
PRISM_BEGIN_TEST_NAMESPACE

TEST(FileInfoExistsIntegrationTests, ShouldReturnTrueWhenFileExists)
{
        const std::string filename = "file.txt";

        std::fstream fs(filename, std::fstream::out);
        if (!fs.is_open())
                ADD_FAILURE_AT(
                        "Could not create file for integration test: "
                        "FileInfoExistsIntegrationTests.ShouldReturnTrueWhenFileExists",
                        __LINE__
                );

        fs.close();

        FileInfo cut(filename);
        EXPECT_THAT(cut.exists(), Eq(true));
        std::remove(filename.c_str());
}

TEST(FileInfoExistsIntegrationTests, ShouldReturnFalseWhenFileDoesNotExist)
{
        FileInfo cut("path/to/file/that/does/not/exist");
        EXPECT_THAT(cut.exists(), Eq(false));
}

PRISM_END_TEST_NAMESPACE
PRISM_END_NAMESPACE
