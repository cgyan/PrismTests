#ifndef PRISM_FAKE_FILE_SYSTEM_H_
#define PRISM_FAKE_FILE_SYSTEM_H_

#include <prism/global>
#include <prism/AbstractFileSystem>
#include <map>

PRISM_BEGIN_NAMESPACE

class FakeFileSystem : public AbstractFileSystem {
public:
        static AbstractFileSystem * create();

        void createFile(const char * filename) override;
        const bool exists(const char * filename) const override;
        void setFileSize(const char * filename, const unsigned int filesize);
        const unsigned int fileSizeInBytes(const char * filename) const override;
        void deleteAllFiles();
private:
        FakeFileSystem() = default;
        FakeFileSystem(const FakeFileSystem& other) = default;
        FakeFileSystem& operator=(const FakeFileSystem& rhs) = default;
private:
        using FilesMap = std::map<const char *, unsigned int>;
        FilesMap m_createdFiles;
};

PRISM_END_NAMESPACE

#endif
