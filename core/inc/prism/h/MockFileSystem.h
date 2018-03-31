#ifndef PRISM_MOCK_FILE_SYSTEM_H_
#define PRISM_MOCK_FILE_SYSTEM_H_

#include <gmock/gmock.h>
using namespace ::testing;
#include <prism/AbstractFileSystem>
#include <string>

PRISM_BEGIN_NAMESPACE
PRISM_BEGIN_TEST_NAMESPACE

class MockFileSystem : public AbstractFileSystem
{
public:
        MOCK_METHOD1(createFile, void(const std::string& filename));
        MOCK_CONST_METHOD1(exists, const bool(const std::string& filename));
        MOCK_CONST_METHOD1(fileSizeInBytes, const int(const std::string& filename));

        static AbstractFileSystem * create()
        {
                static MockFileSystem instance;
                return &instance;
        }
};

PRISM_END_TEST_NAMESPACE
PRISM_END_NAMESPACE

#endif
