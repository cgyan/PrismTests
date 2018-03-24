#ifndef PRISM_FAKE_FILE_SYSTEM_H_
#define PRISM_FAKE_FILE_SYSTEM_H_

#include <prism/global>
#include <prism/AbstractFileSystem>

PRISM_BEGIN_NAMESPACE

class FakeFileSystem : public AbstractFileSystem {
public:
        static AbstractFileSystem * create();
        void createFile(const char * filename) override;
        const bool exists(const char * filename) const override;
private:
        const char * m_createdFilename{""};
};

PRISM_END_NAMESPACE

#endif
