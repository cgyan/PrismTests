#include <prism/global>
#include <prism/FakeJsonArray>
#include <prism/AbstractJsonArrayImpl>
#include <prism/Vector>

PRISM_BEGIN_NAMESPACE

class FakeJsonArrayImpl : public AbstractJsonArrayImpl {
public:
    FakeJsonArrayImpl* clone() const override {
        return new FakeJsonArrayImpl(*this);
    }

    const int numElements() const override {
        return vec.size();
    }

    void insert(JsonArray::const_iterator pos, const JsonValue& value) override
    {}

    void remove(JsonArray::const_iterator pos) override
    {}

    const bool containsElement(const JsonValue& value) const override {
        for (auto it = vec.begin(); it != vec.end(); ++it)
            if (*it == value) return true;
        return false;
    }

    JsonArray::iterator
    begin() override {
        return vec.begin();
    }

    JsonArray::iterator
    end() override {
        return vec.end();
    }
public:
    Vector<JsonValue> vec;
};

JsonArray make_fake_json_array() {
    FakeJsonArrayImpl* fakeImpl = new FakeJsonArrayImpl;
    return JsonArray(fakeImpl);
}

JsonArray
make_fake_json_array(std::initializer_list<JsonValue> il) {
    FakeJsonArrayImpl * fake = new FakeJsonArrayImpl;
    for (auto it = il.begin(); it != il.end(); ++it) {
        fake->vec.append(*it);
    }
    return JsonArray(fake);
}

PRISM_END_NAMESPACE
