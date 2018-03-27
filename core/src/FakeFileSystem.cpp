#include <prism/global>
#include <prism/FakeFileSystem>
#include <cstring>
#include <cassert>
#include <iostream>

PRISM_BEGIN_NAMESPACE

AbstractFileSystem *
FakeFileSystem::create()
{
        static FakeFileSystem instance;
        return &instance;
}

void
FakeFileSystem::createFile(const std::string& filename)
{
        using FilePair = std::pair<std::string, unsigned int>;
        const unsigned int defaultFileSize = 0;
        m_createdFiles.insert(FilePair(filename, defaultFileSize));
}

const bool
FakeFileSystem::exists(const std::string& filename) const
{
        FilesMap::const_iterator it = m_createdFiles.find(filename);
        if (it == m_createdFiles.cend())
                return false;
        return true;
}

void
FakeFileSystem::setFileSize(const std::string& filename, const unsigned int fileSize) {
        m_createdFiles[filename] = fileSize;
}

const int
FakeFileSystem::fileSizeInBytes(const std::string& filename) const {
        if (exists(filename)) {
                return m_createdFiles.at(filename);
        }
        return 0;
}

void
FakeFileSystem::deleteAllFiles() {
        m_createdFiles.clear();
}

const std::string
FakeFileSystem::convertToUnixSeparators(const std::string& filename) const {
        return "";
}

PRISM_END_NAMESPACE
