#include "NefPolyhedron2.h"
#include "cgal_args.h"

using namespace v8;
using namespace node;
using namespace std;

namespace {

    enum {
        EXCLUDED = Nef_polyhedron_2::EXCLUDED,
        INCLUDED = Nef_polyhedron_2::INCLUDED,
        EMPTY = Nef_polyhedron_2::EMPTY,
        COMPLETE = Nef_polyhedron_2::COMPLETE
    };

}

const char *NefPolyhedron2::Name = "NefPolyhedron2";


void NefPolyhedron2::RegisterMethods()
{
    NODE_DEFINE_CONSTANT(sConstructorTemplate, EXCLUDED);
    NODE_DEFINE_CONSTANT(sConstructorTemplate, INCLUDED);
    NODE_DEFINE_CONSTANT(sConstructorTemplate, EMPTY);
    NODE_DEFINE_CONSTANT(sConstructorTemplate, COMPLETE);
}


bool NefPolyhedron2::ParseArg(Local<Value> arg, Nef_polyhedron_2 &receiver)
{
    if (sConstructorTemplate->HasInstance(arg)) {

        // This supports e.g.: newnef = new CGAL.NefPolyhedron2(oldnef);

        receiver = ExtractWrapped(Local<Object>::Cast(arg));
        return true;

    } else {

        return false;

    }
}


Handle<Value> NefPolyhedron2::ToPOD(const Nef_polyhedron_2 &nef, bool precise)
{
    HandleScope scope;
    Local<Object> obj = Object::New();
    return scope.Close(obj);
}
