#include "PolygonWithHoles2.h"
#include "Polygon2.h"
#include "cgal_args.h"

using namespace v8;
using namespace node;
using namespace std;


const char *PolygonWithHoles2::Name = "PolygonWithHoles2";


void PolygonWithHoles2::RegisterMethods()
{
    SetPrototypeMethod(sConstructorTemplate, "isEqual", IsEqual);
    SetPrototypeMethod(sConstructorTemplate, "outer", Outer);
    SetPrototypeMethod(sConstructorTemplate, "holes", Holes);
    SetPrototypeMethod(sConstructorTemplate, "isUnbounded", IsUnbounded);
}


bool PolygonWithHoles2::ParseArg(Local<Value> arg, Polygon_with_holes_2 &receiver)
{
    if (sConstructorTemplate->HasInstance(arg)) {
        receiver = ExtractWrapped(Local<Object>::Cast(arg));
        return true;
    }

    if (arg->IsObject()) {
        Local<Object> inits = Local<Object>::Cast(arg);

        Polygon_2 outer;
        vector<Polygon_2> holes;

        if (Polygon2::ParseArg(inits->Get(String::NewSymbol("outer")), outer) &&
            Polygon2::ParseSeqArg(inits->Get(String::NewSymbol("holes")), back_inserter(holes)))
        {
            receiver = Polygon_with_holes_2(outer, holes.begin(), holes.end());
            return true;
        }

        if (Polygon2::ParseArg(arg, outer)) {
            receiver = Polygon_with_holes_2(outer);
            return true;
        }

    }

    return false;
}


Handle<Value> PolygonWithHoles2::ToPOD(const Polygon_with_holes_2 &poly, bool precise)
{
    HandleScope scope;
    Local<Object> obj = Object::New();
    obj->Set(String::NewSymbol("outer"), Polygon2::ToPOD(poly.outer_boundary(), precise));
    obj->Set(String::NewSymbol("holes"), Polygon2::SeqToPOD(poly.holes_begin(), poly.holes_end(), precise));
    return scope.Close(obj);
}


Handle<Value> PolygonWithHoles2::IsEqual(const Arguments &args)
{
    HandleScope scope;
    try {
        Polygon_with_holes_2 &thisPoly = ExtractWrapped(args.This());
        ARGS_ASSERT(args.Length() == 1);
        ARGS_PARSE_LOCAL(PolygonWithHoles2::ParseArg, Polygon_with_holes_2, otherPoly, args[0]);
        return scope.Close(Boolean::New(thisPoly == otherPoly));
    }
    catch (const exception &e) {
        return ThrowException(String::New(e.what()));
    }
}


Handle<Value> PolygonWithHoles2::Outer(const Arguments &args)
{
    HandleScope scope;
    try {
        Polygon_with_holes_2 &poly = ExtractWrapped(args.This());
        return scope.Close(Polygon2::New(poly.outer_boundary()));
    }
    catch (const exception &e) {
        return ThrowException(String::New(e.what()));
    }
}


Handle<Value> PolygonWithHoles2::Holes(const Arguments &args)
{
    HandleScope scope;
    try {
        Polygon_with_holes_2 &poly = ExtractWrapped(args.This());
        Local<Array> array = Array::New();
        uint32_t i;
        Polygon_with_holes_2::Hole_const_iterator it;
        for(it=poly.holes_begin(),i=0; it!=poly.holes_end(); ++it,++i) {
            array->Set(i, Polygon2::New(*it));
        }
        return scope.Close(array);
    }
    catch (const exception &e) {
        return ThrowException(String::New(e.what()));
    }
}


Handle<Value> PolygonWithHoles2::IsUnbounded(const Arguments &args)
{
    HandleScope scope;
    try {
        Polygon_with_holes_2 &poly = ExtractWrapped(args.This());
        return scope.Close(Boolean::New(poly.is_unbounded()));
    }
    catch (const exception &e) {
        return ThrowException(String::New(e.what()));
    }
}
