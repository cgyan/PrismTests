#include <gmock/gmock.h>
using namespace ::testing;
#include <prism/global>
#include <prism/FileInfo>
#include <prism/FileSystemFactory>
#include <prism/FakeFileSystem>

PRISM_BEGIN_NAMESPACE
PRISM_BEGIN_TEST_NAMESPACE

class FileInfoTests : public Test
{
public:
        void SetUp()
        {
                setFakeFileSystemAsGlobalFileSystem();
        }

        void TearDown()
        {
                getFakeFileSystem()->clear();
        }

        const char * testFilename() const
        {
                return m_filename;
        }

        void writeFileToDiskWithSize(const std::string& filename, const int size)
        {
                getFakeFileSystem()->createFile(filename);
                getFakeFileSystem()->setFileSize(size);
        }
private:
        void setFakeFileSystemAsGlobalFileSystem()
        {
                FileSystemFactory::get()->setFileSystem(&FakeFileSystem::create);
        }

        FakeFileSystem * getFakeFileSystem() const
        {
                AbstractFileSystem * fakeFileSystem = FileSystemFactory::get()->getFileSystem();
                return dynamic_cast<FakeFileSystem*>(fakeFileSystem);
        }
public:
        FileInfo testSubject;
        const char * m_filename{"file.txt"};
        const int ERROR_SIZE_NEG_1 = -1;
};

PRISM_END_TEST_NAMESPACE
PRISM_END_NAMESPACE
