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
FakeFileSystem::createFile(const char * filename)
{
        using FilePair = std::pair<std::string, unsigned int>;
        const unsigned int defaultFileSize = 0;
        m_createdFiles.insert(FilePair(std::string(filename), defaultFileSize));
}

const bool
FakeFileSystem::exists(const char * filename) const
{
        FilesMap::const_iterator it = m_createdFiles.find(std::string(filename));
        if (it == m_createdFiles.cend())
                return false;
        return true;
}

void
FakeFileSystem::setFileSize(const char * filename, const unsigned int fileSize) {
        m_createdFiles[std::string(filename)] = fileSize;
}

const unsigned int
FakeFileSystem::fileSizeInBytes(const char * filename) const {
        if (exists(filename)) {
                std::cout << "filesize is " << m_createdFiles.at(std::string(filename)) << std::endl;
                return m_createdFiles.at(std::string(filename));
        }
        std::cout << "filename does not exist " << std::endl;
        return 0;
}

void
FakeFileSystem::deleteAllFiles() {
        m_createdFiles.clear();
}

PRISM_END_NAMESPACE
