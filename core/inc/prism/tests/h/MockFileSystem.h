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
        MOCK_CONST_METHOD1(exists, const bool(const std::string&));
        MOCK_CONST_METHOD1(fileSizeInBytes, const int(const std::string&));
        MOCK_CONST_METHOD1(absolutePath, const std::string(const std::string&));
        MOCK_CONST_METHOD1(creationDate, const std::string(const std::string&));
};

PRISM_END_TEST_NAMESPACE
PRISM_END_NAMESPACE

#endif
