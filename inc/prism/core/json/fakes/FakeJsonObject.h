#ifndef PRISM_FAKE_JSON_OBJECT_H_
#define PRISM_FAKE_JSON_OBJECT_H_

#include <prism/global>
#include <prism/JsonObject>

PRISM_BEGIN_NAMESPACE

class JsonArray;
class JsonValue;

JsonObject make_fake_json_object();
JsonObject make_fake_json_object(const std::string& key, const JsonValue& fakeValue);

PRISM_END_NAMESPACE

#endif
