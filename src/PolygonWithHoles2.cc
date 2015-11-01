#include "PolygonWithHoles2.h"
#include "Polygon2.h"
#include "cgal_args.h"

using namespace v8;
using namespace node;
using namespace std;


const char *PolygonWithHoles2::Name = "PolygonWithHoles2";


void PolygonWithHoles2::RegisterMethods(Isolate *isolate)
{
    HandleScope scope(isolate);
    Local<FunctionTemplate> constructorTemplate = sConstructorTemplate.Get(isolate);
    NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "isEqual", IsEqual);
    NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "outer", Outer);
    NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "holes", Holes);
    NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "isUnbounded", IsUnbounded);
}


bool PolygonWithHoles2::ParseArg(Isolate *isolate, Local<Value> arg, Polygon_with_holes_2 &receiver)
{
    HandleScope scope(isolate);

    if (sConstructorTemplate.Get(isolate)->HasInstance(arg)) {
        receiver = ExtractWrapped(Local<Object>::Cast(arg));
        return true;
    }

    if (arg->IsObject()) {
        Local<Object> inits = Local<Object>::Cast(arg);

        Polygon_2 outer;
        vector<Polygon_2> holes;

        if (Polygon2::ParseArg(isolate, inits->Get(SYMBOL(isolate, "outer")), outer) &&
            Polygon2::ParseSeqArg(isolate, inits->Get(SYMBOL(isolate, "holes")), back_inserter(holes)))
        {
            receiver = Polygon_with_holes_2(outer, holes.begin(), holes.end());
            return true;
        }

        if (Polygon2::ParseArg(isolate, arg, outer)) {
            receiver = Polygon_with_holes_2(outer);
            return true;
        }

    }

    return false;
}


Local<Value> PolygonWithHoles2::ToPOD(Isolate *isolate, const Polygon_with_holes_2 &poly, bool precise)
{
    EscapableHandleScope scope(isolate);
    Local<Object> obj = Object::New(isolate);
    obj->Set(SYMBOL(isolate, "outer"), Polygon2::ToPOD(isolate, poly.outer_boundary(), precise));
    obj->Set(SYMBOL(isolate, "holes"), Polygon2::SeqToPOD(isolate, poly.holes_begin(), poly.holes_end(), precise));
    return scope.Escape(obj);
}


void PolygonWithHoles2::IsEqual(const FunctionCallbackInfo<Value> &info)
{
    Isolate *isolate = info.GetIsolate();
    HandleScope scope(isolate);
    try {
        Polygon_with_holes_2 &thisPoly = ExtractWrapped(info.This());
        ARGS_ASSERT(isolate, info.Length() == 1);
        ARGS_PARSE_LOCAL(isolate, PolygonWithHoles2::ParseArg, Polygon_with_holes_2, otherPoly, info[0]);
        info.GetReturnValue().Set(Boolean::New(isolate, thisPoly == otherPoly));
    }
    catch (const exception &e) {
        isolate->ThrowException(String::NewFromUtf8(isolate, e.what()));
    }
}


void PolygonWithHoles2::Outer(const FunctionCallbackInfo<Value> &info)
{
    Isolate *isolate = info.GetIsolate();
    HandleScope scope(isolate);
    try {
        Polygon_with_holes_2 &poly = ExtractWrapped(info.This());
        info.GetReturnValue().Set(Polygon2::New(isolate, poly.outer_boundary()));
    }
    catch (const exception &e) {
        isolate->ThrowException(String::NewFromUtf8(isolate, e.what()));
    }
}


void PolygonWithHoles2::Holes(const FunctionCallbackInfo<Value> &info)
{
    Isolate *isolate = info.GetIsolate();
    HandleScope scope(isolate);
    try {
        Polygon_with_holes_2 &poly = ExtractWrapped(info.This());
        Local<Array> array = Array::New(isolate);
        uint32_t i;
        Polygon_with_holes_2::Hole_const_iterator it;
        for(it=poly.holes_begin(),i=0; it!=poly.holes_end(); ++it,++i) {
            array->Set(i, Polygon2::New(isolate, *it));
        }
        info.GetReturnValue().Set(array);
    }
    catch (const exception &e) {
        isolate->ThrowException(String::NewFromUtf8(isolate, e.what()));
    }
}


void PolygonWithHoles2::IsUnbounded(const FunctionCallbackInfo<Value> &info)
{
    Isolate *isolate = info.GetIsolate();
    HandleScope scope(isolate);
    try {
        Polygon_with_holes_2 &poly = ExtractWrapped(info.This());
        info.GetReturnValue().Set(Boolean::New(isolate, poly.is_unbounded()));
    }
    catch (const exception &e) {
        isolate->ThrowException(String::NewFromUtf8(isolate, e.what()));
    }
}
