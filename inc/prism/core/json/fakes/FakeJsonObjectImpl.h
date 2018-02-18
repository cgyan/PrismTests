#ifndef PRISM_FAKE_JSON_OBJECT_IMPL_H_
#define PRISM_FAKE_JSON_OBJECT_IMPL_H_

#include <prism/global>
#include <prism/AbstractJsonObjectImpl>
#include <map>

PRISM_BEGIN_NAMESPACE

class JsonArray;

class FakeJsonObjectImpl : public AbstractJsonObjectImpl {
public:
    const int numMembers() const override { return 1; }
public:
    std::map<std::string, double> map;
    std::map<std::string, JsonArray> arrayMap;
    std::map<std::string, JsonObject> objMap;
};

JsonObject make_fake_json_object(const std::string& key, const double value);
JsonObject make_fake_json_object(const std::string& key, const JsonArray& value);
JsonObject make_fake_json_object(const std::string& key, const JsonObject& value);

PRISM_END_NAMESPACE

#endif
