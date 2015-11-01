#include "Polygon2.h"
#include "Point2.h"
#include "AffTransformation2.h"
#include "cgal_args.h"

using namespace v8;
using namespace node;
using namespace std;


const char *Polygon2::Name = "Polygon2";


void Polygon2::RegisterMethods(Isolate *isolate)
{
    HandleScope scope(isolate);
    Local<FunctionTemplate> constructorTemplate = sConstructorTemplate.Get(isolate);

    NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "isEqual", IsEqual);
    NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "isSimple", IsSimple);
    NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "isConvex", IsConvex);
    NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "orientation", Orientation);
    NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "orientedSide", OrientedSide);
    NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "boundedSide", BoundedSide);
    NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "area", Area);
    NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "coords", Coords);

    NODE_SET_METHOD(constructorTemplate, "transform", Transform);
}


bool Polygon2::ParseArg(Isolate *isolate, Local<Value> arg, Polygon_2 &receiver)
{
    if (sConstructorTemplate.Get(isolate)->HasInstance(arg)) {
        receiver = ExtractWrapped(Local<Object>::Cast(arg));
        return true;
    }

    if (arg->IsArray()) {
        return Point2::ParseSeqArg(isolate, arg, back_inserter(receiver));
    }

    return false;
}


Local<Value> Polygon2::ToPOD(Isolate *isolate, const Polygon_2 &poly, bool precise)
{
    EscapableHandleScope scope(isolate);
    return scope.Escape(Point2::SeqToPOD(isolate, poly.vertices_begin(), poly.vertices_end(), precise));
}


void Polygon2::IsEqual(const FunctionCallbackInfo<Value> &info)
{
    Isolate *isolate = info.GetIsolate();
    HandleScope scope(isolate);
    try {
        Polygon_2 &thisPoly = ExtractWrapped(info.This());
        ARGS_ASSERT(isolate, info.Length() == 1);
        ARGS_PARSE_LOCAL(isolate, Polygon2::ParseArg, Polygon_2, otherPoly, info[0]);
        info.GetReturnValue().Set(Boolean::New(isolate, thisPoly == otherPoly));
    }
    catch (const exception &e) {
        isolate->ThrowException(String::NewFromUtf8(isolate, e.what()));
    }
}


void Polygon2::IsSimple(const FunctionCallbackInfo<Value> &info)
{
    Isolate *isolate = info.GetIsolate();
    HandleScope scope(isolate);
    try {
        Polygon_2 &poly = ExtractWrapped(info.This());
        // NOTE(ocderby): CGAL Segfaults on linux if the polygon has no points in it,
        // so catch that here.
        if (poly.size() == 0) {
            info.GetReturnValue().Set(Boolean::New(isolate, false));
            return;
        }
        info.GetReturnValue().Set(Boolean::New(isolate, poly.is_simple()));
    }
    catch (const exception &e) {
        isolate->ThrowException(String::NewFromUtf8(isolate, e.what()));
    }
}


void Polygon2::IsConvex(const FunctionCallbackInfo<Value> &info)
{
    Isolate *isolate = info.GetIsolate();
    HandleScope scope(isolate);
    try {
        Polygon_2 &poly = ExtractWrapped(info.This());
        info.GetReturnValue().Set(Boolean::New(isolate, poly.is_convex()));
    }
    catch (const exception &e) {
        isolate->ThrowException(String::NewFromUtf8(isolate, e.what()));
    }
}


void Polygon2::Orientation(const FunctionCallbackInfo<Value> &info)
{
    Isolate *isolate = info.GetIsolate();
    HandleScope scope(isolate);
    try {
        Polygon_2 &poly = ExtractWrapped(info.This());
        info.GetReturnValue().Set(Integer::New(isolate, poly.orientation()));
    }
    catch (const exception &e) {
        isolate->ThrowException(String::NewFromUtf8(isolate, e.what()));
    }
}


void Polygon2::OrientedSide(const FunctionCallbackInfo<Value> &info)
{
    Isolate *isolate = info.GetIsolate();
    HandleScope scope(isolate);
    try {
        Polygon_2 &poly = ExtractWrapped(info.This());
        ARGS_ASSERT(isolate, info.Length() == 1);
        ARGS_PARSE_LOCAL(isolate, Point2::ParseArg, Point_2, point, info[0]);
        info.GetReturnValue().Set(Integer::New(isolate, poly.oriented_side(point)));
    }
    catch (const exception &e) {
        isolate->ThrowException(String::NewFromUtf8(isolate, e.what()));
    }
}


void Polygon2::BoundedSide(const FunctionCallbackInfo<Value> &info)
{
    Isolate *isolate = info.GetIsolate();
    HandleScope scope(isolate);
    try {
        Polygon_2 &poly = ExtractWrapped(info.This());
        ARGS_ASSERT(isolate, info.Length() == 1);
        ARGS_PARSE_LOCAL(isolate, Point2::ParseArg, Point_2, point, info[0]);
        info.GetReturnValue().Set(Integer::New(isolate, poly.bounded_side(point)));
    }
    catch (const exception &e) {
        isolate->ThrowException(String::NewFromUtf8(isolate, e.what()));
    }
}


void Polygon2::Area(const FunctionCallbackInfo<Value> &info)
{
    Isolate *isolate = info.GetIsolate();
    HandleScope scope(isolate);
    try {
        Polygon_2 &poly = ExtractWrapped(info.This());
        info.GetReturnValue().Set(Number::New(isolate, CGAL::to_double(poly.area())));
    }
    catch (const exception &e) {
        isolate->ThrowException(String::NewFromUtf8(isolate, e.what()));
    }
}


void Polygon2::Transform(const FunctionCallbackInfo<Value> &info)
{
  Isolate *isolate = info.GetIsolate();
  HandleScope scope(isolate);
  try {
    ARGS_ASSERT(isolate, info.Length() == 2);

    Aff_transformation_2 afft;
    if (!AffTransformation2::ParseArg(isolate, info[0], afft)) {
      ARGS_ASSERT(isolate, false);
    }

    Polygon_2 poly;
    if (!ParseArg(isolate, info[1], poly)) {
      ARGS_ASSERT(isolate, false);
    }

    Polygon_2 xpoly = CGAL::transform(afft, poly);
    info.GetReturnValue().Set(New(isolate, xpoly));
  }
  catch (const exception &e) {
    isolate->ThrowException(String::NewFromUtf8(isolate, e.what()));
  }
}


void Polygon2::Coords(const FunctionCallbackInfo<Value> &info)
{
    Isolate *isolate = info.GetIsolate();
    HandleScope scope(isolate);
    Polygon_2 &poly = ExtractWrapped(info.This());
    Local<Array> array = Array::New(isolate);
    Vertex_iterator it;
    uint32_t i;
    for(it=poly.vertices_begin(),i=0; it!=poly.vertices_end(); ++it,++i) {
        array->Set(i, Point2::New(isolate, *it));
    }
    info.GetReturnValue().Set(array);
}
