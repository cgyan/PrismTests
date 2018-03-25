#include <gmock/gmock.h>
using namespace ::testing;
#include <prism/global>
#include <prism/FileInfo>
#include <fstream>
#include <cstdio>
#include <cassert>

PRISM_BEGIN_NAMESPACE
PRISM_BEGIN_TEST_NAMESPACE
//==============================================================================
// test setup
//==============================================================================
class FileInfoIntegrationTests : public Test {
public:
        void SetUp();
        void TearDown();
        void setFile(const char * filename);
        const char * testFilename() const;
private:
        const bool createAndOpenFile();
        void closeFile();
        const bool deleteFile();
private:
        const char * m_filename{"file.txt"};
        std::fstream m_fstream;
public:
        FileInfo testSubject{m_filename};
};

void
FileInfoIntegrationTests::SetUp()
{
        assert(createAndOpenFile());
}

void
FileInfoIntegrationTests::TearDown()
{
        closeFile();
        assert(deleteFile());
}

const char *
FileInfoIntegrationTests::testFilename() const {
        return m_filename;
}

const bool
FileInfoIntegrationTests::createAndOpenFile()
{
        m_fstream.open(m_filename, std::fstream::out);
        return m_fstream.is_open();
}

void
FileInfoIntegrationTests::closeFile()
{
        m_fstream.close();
}

const bool
FileInfoIntegrationTests::deleteFile()
{
        return std::remove(m_filename) == 0;
}
//==============================================================================
// tests
//==============================================================================
TEST_F(FileInfoIntegrationTests, WhenFilenameRefersToFileOnDiskExpectFileToExist)
{
        EXPECT_TRUE(testSubject.exists());
}

TEST_F(FileInfoIntegrationTests, WhenFilenameRefersToNonExistentFileExpectFileNotToExist)
{
        testSubject.setFile("path/to/file/that/does/not/exist");
        EXPECT_FALSE(testSubject.exists());
}

PRISM_END_TEST_NAMESPACE
PRISM_END_NAMESPACE
