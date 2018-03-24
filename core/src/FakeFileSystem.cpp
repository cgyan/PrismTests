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
        m_createdFilename = filename;
}

const bool
FakeFileSystem::exists(const char * filename) const {
        if (strcmp(filename, m_createdFilename) == 0)
                return true;
        return false;
}

PRISM_END_NAMESPACE
