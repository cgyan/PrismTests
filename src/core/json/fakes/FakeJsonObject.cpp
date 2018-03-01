#include <prism/global>
#include <prism/AbstractJsonObjectImpl>
#include <prism/FakeJsonObject>
#include <prism/FakeJsonValue>
#include <prism/JsonArray>
#include <map>
#include <iostream>

PRISM_BEGIN_NAMESPACE

class FakeJsonObjectImpl : public AbstractJsonObjectImpl {
public:
    FakeJsonObjectImpl* clone() const override {
        return new FakeJsonObjectImpl(*this);
    }

    const int numMembers() const override {
        return map.size();
    }

    const bool equals(AbstractJsonObjectImpl * rhs) const override {
        FakeJsonObjectImpl * rhsImpl = dynamic_cast<FakeJsonObjectImpl*>(rhs);
        return this->map == rhsImpl->map;
    }

    void insertNewMember(const std::string& key, const JsonValue& value) override {
        map[key] = value;
    }

    JsonObject::iterator begin() override {
        return map.begin();
    }

    JsonObject::iterator end() override {
        return map.end();
    }
public:
    std::map<std::string, JsonValue> map;
};

JsonObject
make_fake_json_object() {
    FakeJsonObjectImpl * fakeImpl = new FakeJsonObjectImpl;
    return JsonObject(fakeImpl);
}

JsonObject
make_fake_json_object(const std::string& key, const JsonValue& fakeValue) {
    FakeJsonObjectImpl * fakeImpl = new FakeJsonObjectImpl;
    fakeImpl->map[key] = fakeValue;
    return JsonObject(fakeImpl);
}

PRISM_END_NAMESPACE
