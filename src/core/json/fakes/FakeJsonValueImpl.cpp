#include <prism/global>
#include <prism/FakeJsonValueImpl>

PRISM_BEGIN_NAMESPACE

double
FakeJsonValueImpl::toDouble() const {
    return doubleVal;
}

JsonValue::Type
FakeJsonValueImpl::type() const {
    return JsonValue::Type::Double;
}

JsonValue make_fake_json_value(const double value) {
    FakeJsonValueImpl * fake = new FakeJsonValueImpl;
    fake->doubleVal = value;
    return JsonValue(fake);
}

PRISM_END_NAMESPACE
