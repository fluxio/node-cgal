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


void NefPolyhedron2::RegisterMethods(Isolate *isolate)
{
    // HandleScope scope(isolate);
    // Local<FunctionTemplate> constructorTemplate = sConstructorTemplate.Get(isolate);
    // NODE_DEFINE_CONSTANT(constructorTemplate, EXCLUDED);
    // NODE_DEFINE_CONSTANT(constructorTemplate, INCLUDED);
    // NODE_DEFINE_CONSTANT(constructorTemplate, EMPTY);
    // NODE_DEFINE_CONSTANT(constructorTemplate, COMPLETE);
}


bool NefPolyhedron2::ParseArg(v8::Isolate *isolate, Local<Value> arg, Nef_polyhedron_2 &receiver)
{
    if (sConstructorTemplate.Get(isolate)->HasInstance(arg)) {
        receiver = ExtractWrapped(Local<Object>::Cast(arg));
        return true;
    }

    return false;
}


Local<Value> NefPolyhedron2::ToPOD(v8::Isolate *isolate, const Nef_polyhedron_2 &nef, bool precise)
{
    EscapableHandleScope scope(isolate);
    Local<Object> obj = Object::New(isolate);
    return scope.Escape(obj);
}
