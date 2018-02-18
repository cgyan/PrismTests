#ifndef PRISM_FAKE_JSON_ARRAY_IMPL_H_
#define PRISM_FAKE_JSON_ARRAY_IMPL_H_

#include <prism/global>
#include <prism/AbstractJsonArrayImpl>
#include <prism/Vector>

PRISM_BEGIN_NAMESPACE

class FakeJsonArrayImpl : public AbstractJsonArrayImpl {
public:
    Vector<double> vec;
};

JsonArray make_fake_json_array(std::initializer_list<double> il);

PRISM_END_NAMESPACE

#endif
