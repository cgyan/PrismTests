#ifndef PRISM_FAKE_JSON_ARRAY_H_
#define PRISM_FAKE_JSON_ARRAY_H_

#include <prism/global>
#include <prism/JsonArray>
#include <prism/JsonValue>

PRISM_BEGIN_NAMESPACE

JsonArray make_fake_json_array();
JsonArray make_fake_json_array(std::initializer_list<JsonValue> il);

PRISM_END_NAMESPACE

#endif
