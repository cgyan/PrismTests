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

        // overriding methods
        void createFile(const std::string& filename) override;
        const bool exists(const std::string& filename) const override;
        const int fileSizeInBytes(const std::string& filename) const override;

        // helper methods
        void setFileSize(const unsigned int filesize);
        void clear();
private:
        FakeFileSystem() = default;
        FakeFileSystem(const FakeFileSystem& other) = default;
        FakeFileSystem& operator=(const FakeFileSystem& rhs) = default;
private:
        std::string m_createdFile{""};
        int m_createdFileSize{-1};
};

PRISM_END_NAMESPACE

#endif
