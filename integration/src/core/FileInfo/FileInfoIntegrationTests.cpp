#include <gmock/gmock.h>
using namespace ::testing;
#include <prism/global>
#include <prism/FileInfo>
#include <prism/FileSystemFactory>
#include <fstream>
#include <cstdio>
#include <cassert>

PRISM_BEGIN_NAMESPACE
PRISM_BEGIN_TEST_NAMESPACE
//==============================================================================
// test setup
//==============================================================================
class FileInfoIntegrationTests : public Test
{
public:
        void SetUp();
        void TearDown();
        void setFile(const char * filename);
        const char * testFilename() const;
        const unsigned int bytesInFile() const;
private:
        void setRealFileSystemAsGlobalFileSystem();
        const bool createAndOpenFile();
        void writeDataToFile();
        void closeFile();
        const bool deleteFile();
private:
        const char * m_filename{"integration_test_file.txt"};
        const char * m_fileContents = "Hello tests!";
        std::fstream m_fstream;
        unsigned int m_fileSize{0};
public:
        FileInfo testSubject{m_filename};
};

void
FileInfoIntegrationTests::SetUp()
{
        setRealFileSystemAsGlobalFileSystem();
        assert(createAndOpenFile());
        writeDataToFile();
        m_fileSize = strlen(m_fileContents);
        closeFile();
}

void
FileInfoIntegrationTests::TearDown()
{
        assert(deleteFile());
}

void
FileInfoIntegrationTests::setRealFileSystemAsGlobalFileSystem()
{
        FileSystemFactory::get()->setFileSystem(&FileSystem::create);
}

const char *
FileInfoIntegrationTests::testFilename() const
{
        return m_filename;
}

const unsigned int
FileInfoIntegrationTests::bytesInFile() const
{
        return m_fileSize;
}

const bool
FileInfoIntegrationTests::createAndOpenFile()
{
        m_fstream.open(m_filename, std::fstream::out);
        return m_fstream.is_open();
}

void
FileInfoIntegrationTests::writeDataToFile()
{
        m_fstream << m_fileContents;
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
TEST_F(FileInfoIntegrationTests, ShouldReturnTrueWhenFileExists)
{
        EXPECT_TRUE(testSubject.exists());
}

TEST_F(FileInfoIntegrationTests, ShouldReturnFalseWhenFileDoesNotExist)
{
        testSubject.setFile("path/to/file/that/does/not/exist");
        EXPECT_FALSE(testSubject.exists());
}



PRISM_END_TEST_NAMESPACE
PRISM_END_NAMESPACE