#include "Polygon2.h"
#include "Point2.h"
#include "AffTransformation2.h"
#include "cgal_args.h"

using namespace v8;
using namespace node;
using namespace std;


const char *Polygon2::Name = "Polygon2";


void Polygon2::RegisterMethods()
{
    SetPrototypeMethod(sConstructorTemplate, "isEqual", IsEqual);
    SetPrototypeMethod(sConstructorTemplate, "isSimple", IsSimple);
    SetPrototypeMethod(sConstructorTemplate, "isConvex", IsConvex);
    SetPrototypeMethod(sConstructorTemplate, "orientation", Orientation);
    SetPrototypeMethod(sConstructorTemplate, "orientedSide", OrientedSide);
    SetPrototypeMethod(sConstructorTemplate, "boundedSide", BoundedSide);
    SetPrototypeMethod(sConstructorTemplate, "area", Area);
    SetPrototypeMethod(sConstructorTemplate, "coords", Coords);

    SetMethod(sConstructorTemplate, "transform", Transform);
}


bool Polygon2::ParseArg(v8::Local<v8::Value> arg, Polygon_2 &receiver)
{
    if (sConstructorTemplate->HasInstance(arg)) {
        receiver = ExtractWrapped(Local<Object>::Cast(arg));
        return true;
    }

    if (arg->IsArray()) {
        return Point2::ParseSeqArg(arg, back_inserter(receiver));
    }

    return false;
}


Handle<Value> Polygon2::ToPOD(const Polygon_2 &poly, bool precise)
{
    HandleScope scope;
    return scope.Close(Point2::SeqToPOD(poly.vertices_begin(), poly.vertices_end(), precise));
}


Handle<Value> Polygon2::IsEqual(const Arguments &args)
{
    HandleScope scope;
    try {
        Polygon_2 &thisPoly = ExtractWrapped(args.This());
        ARGS_ASSERT(args.Length() == 1);
        ARGS_PARSE_LOCAL(Polygon2::ParseArg, Polygon_2, otherPoly, args[0]);
        return scope.Close(Boolean::New(thisPoly == otherPoly));
    }
    catch (const exception &e) {
        return ThrowException(String::New(e.what()));
    }
}


Handle<Value> Polygon2::IsSimple(const Arguments &args)
{
    HandleScope scope;
    try {
        Polygon_2 &poly = ExtractWrapped(args.This());
        // NOTE(ocderby): CGAL Segfaults on linux if the polygon has no points in it,
        // so catch that here.
        if (poly.size() == 0) {
            return scope.Close(Boolean::New(false));
        }
        return scope.Close(Boolean::New(poly.is_simple()));
    }
    catch (const exception &e) {
        return ThrowException(String::New(e.what()));
    }
}


Handle<Value> Polygon2::IsConvex(const Arguments &args)
{
    HandleScope scope;
    try {
        Polygon_2 &poly = ExtractWrapped(args.This());
        return scope.Close(Boolean::New(poly.is_convex()));
    }
    catch (const exception &e) {
        return ThrowException(String::New(e.what()));
    }
}


Handle<Value> Polygon2::Orientation(const Arguments &args)
{
    HandleScope scope;
    try {
        Polygon_2 &poly = ExtractWrapped(args.This());
        return scope.Close(Integer::New(poly.orientation()));
    }
    catch (const exception &e) {
        return ThrowException(String::New(e.what()));
    }
}


Handle<Value> Polygon2::OrientedSide(const Arguments &args)
{
    HandleScope scope;
    try {
        Polygon_2 &poly = ExtractWrapped(args.This());
        ARGS_ASSERT(args.Length() == 1);
        ARGS_PARSE_LOCAL(Point2::ParseArg, Point_2, point, args[0]);
        return scope.Close(Integer::New(poly.oriented_side(point)));
    }
    catch (const exception &e) {
        return ThrowException(String::New(e.what()));
    }
}


Handle<Value> Polygon2::BoundedSide(const Arguments &args)
{
    HandleScope scope;
    try {
        Polygon_2 &poly = ExtractWrapped(args.This());
        ARGS_ASSERT(args.Length() == 1);
        ARGS_PARSE_LOCAL(Point2::ParseArg, Point_2, point, args[0]);
        return scope.Close(Integer::New(poly.bounded_side(point)));
    }
    catch (const exception &e) {
        return ThrowException(String::New(e.what()));
    }
}


Handle<Value> Polygon2::Area(const Arguments &args)
{
    HandleScope scope;
    try {
        Polygon_2 &poly = ExtractWrapped(args.This());
        return scope.Close(Number::New(CGAL::to_double(poly.area())));
    }
    catch (const exception &e) {
        return ThrowException(String::New(e.what()));
    }
}


Handle<Value> Polygon2::Transform(const Arguments &args)
{
  HandleScope scope;
  try {
    ARGS_ASSERT(args.Length() == 2);

    Aff_transformation_2 afft;
    if (!AffTransformation2::ParseArg(args[0], afft)) {
      ARGS_ASSERT(false);
    }

    Polygon_2 poly;
    if (!ParseArg(args[1], poly)) {
      ARGS_ASSERT(false);
    }

    Polygon_2 xpoly = CGAL::transform(afft, poly);
    return scope.Close(New(xpoly));
  }
  catch (const exception &e) {
    return ThrowException(String::New(e.what()));
  }
}


Handle<Value> Polygon2::Coords(const Arguments &args)
{
    HandleScope scope;
    Polygon_2 &poly = ExtractWrapped(args.This());
    Local<Array> array = Array::New();
    Vertex_iterator it;
    uint32_t i;
    for(it=poly.vertices_begin(),i=0; it!=poly.vertices_end(); ++it,++i) {
        array->Set(i, Point2::New(*it));
    }
    return scope.Close(array);
}
