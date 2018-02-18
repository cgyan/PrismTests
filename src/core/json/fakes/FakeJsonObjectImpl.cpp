#include <prism/global>
#include <prism/FakeJsonObjectImpl>
#include <prism/JsonArray>

PRISM_BEGIN_NAMESPACE

JsonObject
make_fake_json_object(const std::string& key, const double value) {
    FakeJsonObjectImpl * fake = new FakeJsonObjectImpl;
    fake->map[key] = value;
    return JsonObject(fake);
}

JsonObject
make_fake_json_object(const std::string& key, const JsonArray& value) {
    FakeJsonObjectImpl * fake = new FakeJsonObjectImpl;
    fake->arrayMap[key] = value;
    return JsonObject(fake);
}

JsonObject
make_fake_json_object(const std::string& key, const JsonObject& value) {
    FakeJsonObjectImpl * fake = new FakeJsonObjectImpl;
    fake->objMap[key] = value;
    return JsonObject(fake);
}

PRISM_END_NAMESPACE
