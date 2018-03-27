#ifndef PRISM_FAKE_FILE_SYSTEM_H_
#define PRISM_FAKE_FILE_SYSTEM_H_

#include <prism/global>
#include <prism/AbstractFileSystem>
#include <map>
#include <string>

PRISM_BEGIN_NAMESPACE

class FakeFileSystem : public AbstractFileSystem {
public:
        static AbstractFileSystem * create();

        void createFile(const std::string& filename) override;
        const bool exists(const std::string& filename) const override;
        void setFileSize(const unsigned int filesize);
        const int fileSizeInBytes(const std::string& filename) const override;
        const std::string convertToUnixSeparators(const std::string& filename) const override;
        void deleteAllFiles();
private:
        FakeFileSystem() = default;
        FakeFileSystem(const FakeFileSystem& other) = default;
        FakeFileSystem& operator=(const FakeFileSystem& rhs) = default;
private:
        std::string m_createdFile{""};
        unsigned int m_createdFileSize{0};
};

PRISM_END_NAMESPACE

#endif
