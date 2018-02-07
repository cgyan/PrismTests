#ifndef PRISM_JSON_OBJECT_STUB_H_
#define PRISM_JSON_OBJECT_STUB_H_

#include <prism/global>
#include <prism/JsonObject>

PRISM_BEGIN_NAMESPACE
PRISM_BEGIN_TEST_NAMESPACE

class JsonObjectStub : public JsonObject {
public:
    std::string json;
};

PRISM_END_TEST_NAMESPACE
PRISM_END_NAMESPACE

#endif
