#include <prism/global>
#include <prism/JsonValue>
#include <prism/AbstractJsonValueImpl>
#include <prism/JsonObject>
#include <prism/JsonArray>

PRISM_BEGIN_NAMESPACE

class FakeJsonValueImpl : public AbstractJsonValueImpl {
public:
    double toDouble() const override;
    JsonValue::Type type() const override;
public:
    double doubleVal{};
};

JsonValue make_fake_json_value(const double value);

PRISM_END_NAMESPACE
