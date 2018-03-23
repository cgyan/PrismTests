#ifndef PRISM_FAKE_JSON_VALUE_H_
#define PRISM_FAKE_JSON_VALUE_H_

#include <prism/global>
#include <prism/JsonValue>

PRISM_BEGIN_NAMESPACE

class JsonArray;
class JsonObject;

JsonValue make_fake_json_value();
JsonValue make_fake_json_value(const std::string& value);
JsonValue make_fake_json_value(const double value);
JsonValue make_fake_json_value(const bool value);
JsonValue make_fake_json_value(const JsonArray& value);
JsonValue make_fake_json_value(const JsonObject& value);

PRISM_END_NAMESPACE

#endif
