#include <prism/global>
#include <prism/FakeJsonArrayImpl>

PRISM_BEGIN_NAMESPACE

JsonArray
make_fake_json_array(std::initializer_list<double> il) {
    FakeJsonArrayImpl * fake = new FakeJsonArrayImpl;
    for (auto it = il.begin(); it != il.end(); ++it) {
        fake->vec.append(*it);
    }
    return JsonArray(fake);
}

PRISM_END_NAMESPACE
