#include <prism/global>
#include <prism/FileSystemFactory>
#include <prism/FakeFileSystem>
#include <prism/algorithm>
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
        std::string s = filename;
        FileSystemFactory::get()->getFileSystem()->convertToUnixSeparators(s);
        m_createdFile = s;
}

const bool
FakeFileSystem::exists(const std::string& filename) const
{
        if (m_createdFile == "") return false;
        if (m_createdFile == filename) return true;
        return false;
}

void
FakeFileSystem::setFileSize(const unsigned int fileSize) {
        m_createdFileSize = fileSize;
}

const int
FakeFileSystem::fileSizeInBytes(const std::string& filename) const {
        return m_createdFileSize;
}

void
FakeFileSystem::deleteAllFiles() {
        m_createdFile = "";
        m_createdFileSize = 0;
}

const std::string
FakeFileSystem::convertToUnixSeparators(const std::string& filename) const {
        std::string ret = filename;
        prism::replace(ret.begin(), ret.end(), '\\', '/');
        return ret;
}

PRISM_END_NAMESPACE
