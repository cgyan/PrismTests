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
        m_createdFile = filename;
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
FakeFileSystem::clear() {
        m_createdFile = "";
        m_createdFileSize = -1;
}

PRISM_END_NAMESPACE
