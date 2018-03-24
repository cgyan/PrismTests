#include <prism/global>
#include <prismtests/FakeJsonValue>
#include <prism/AbstractJsonValueImpl>
#include <prism/JsonObject>
#include <prism/JsonArray>

PRISM_BEGIN_NAMESPACE

class FakeJsonValueImpl : public AbstractJsonValueImpl {
public:
    double toDouble() const override;
    bool toBool() const override;
    JsonArray toArray() const override;
    JsonObject toObject() const override;
    std::string toString() const override;
    JsonValue::Type type() const override;
public:
    double doubleVal{};
    bool boolVal{};
    JsonArray arrayVal{};
    JsonObject objectVal{};
    std::string stringVal;
    JsonValue::Type valType;
};

double
FakeJsonValueImpl::toDouble() const {
    return doubleVal;
}

bool
FakeJsonValueImpl::toBool() const {
    return boolVal;
}

JsonArray
FakeJsonValueImpl::toArray() const {
    return arrayVal;
}

JsonObject
FakeJsonValueImpl::toObject() const {
    return objectVal;
}

std::string
FakeJsonValueImpl::toString() const {
    return stringVal;
}

JsonValue::Type
FakeJsonValueImpl::type() const {
    return valType;
}

JsonValue make_fake_json_value() {
    FakeJsonValueImpl* fakeImpl = new FakeJsonValueImpl;
    fakeImpl->valType = JsonValue::Type::Null;
    return JsonValue(fakeImpl);
}

JsonValue make_fake_json_value(const std::string& value) {
    FakeJsonValueImpl * fakeImpl = new FakeJsonValueImpl;
    fakeImpl->stringVal = value;
    fakeImpl->valType = JsonValue::Type::String;
    return JsonValue(fakeImpl);
}

JsonValue make_fake_json_value(const double value) {
    FakeJsonValueImpl * fakeImpl = new FakeJsonValueImpl;
    fakeImpl->doubleVal = value;
    fakeImpl->valType = JsonValue::Type::Double;
    return JsonValue(fakeImpl);
}

JsonValue make_fake_json_value(const bool value) {
    FakeJsonValueImpl * fakeImpl = new FakeJsonValueImpl;
    fakeImpl->boolVal = value;
    fakeImpl->valType = JsonValue::Type::Bool;
    return JsonValue(fakeImpl);
}

JsonValue make_fake_json_value(const JsonArray& value) {
    FakeJsonValueImpl * fakeImpl = new FakeJsonValueImpl;
    fakeImpl->arrayVal = value;
    fakeImpl->valType = JsonValue::Type::Array;
    return JsonValue(fakeImpl);
}

JsonValue make_fake_json_value(const JsonObject& value) {
    FakeJsonValueImpl * fakeImpl = new FakeJsonValueImpl;
    fakeImpl->objectVal = value;
    fakeImpl->valType = JsonValue::Type::Object;
    return JsonValue(fakeImpl);
}

PRISM_END_NAMESPACE
