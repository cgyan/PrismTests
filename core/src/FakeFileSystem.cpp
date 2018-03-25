#include <prism/global>
#include <prism/FakeFileSystem>
#include <cstring>

PRISM_BEGIN_NAMESPACE

AbstractFileSystem *
FakeFileSystem::create()
{
        static FakeFileSystem instance;
        return &instance;
}

void
FakeFileSystem::createFile(const char * filename)
{
        using FilePair = std::pair<const char *, unsigned int>;
        const unsigned int defaultFileSize = 0;
        m_createdFiles.insert(FilePair(filename, defaultFileSize));
}

const bool
FakeFileSystem::exists(const char * filename) const
{
        std::map<const char *, unsigned int>::const_iterator it = m_createdFiles.find(filename);
        if (it == m_createdFiles.cend())
                return false;
        return true;
}

void
FakeFileSystem::setFileSize(const char * filename, const unsigned int fileSize) {
        m_createdFiles[filename] = fileSize;
}

const unsigned int
FakeFileSystem::fileSizeInBytes(const char * filename) const {
        if (exists(filename)) return m_createdFiles.at(filename);
        else return 0;
}

void
FakeFileSystem::deleteAllFiles() {
        m_createdFiles.clear();
}

PRISM_END_NAMESPACE
