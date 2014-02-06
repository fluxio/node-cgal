#include "Polygon2.h"
#include "Point2.h"
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
}


bool Polygon2::ParseArg(v8::Local<v8::Value> arg, Polygon_2 &receiver)
{
    if (sConstructorTemplate->HasInstance(arg)) {

        // This supports e.g.: newPolygon = new CGAL.Polygon2(oldPolygon);
        receiver = ExtractWrapped(Local<Object>::Cast(arg));
        return true;

    } else if (arg->IsArray()) {

        // This supports e.g.: newPolygon = new CGAL.Polygon2([point1, point2, ... ])
        bool parsed = Point2::ParseSeqArg(arg, back_inserter(receiver));

        // We've decided for now that constructing with an empty array, though valid in the CGAL
        // API, is probably an unintentional programming error, so flag as a parse error.  (If in
        // the future this extra seatbelt proves troublesome for algorithmic code, just remove it.)
        if (parsed && (receiver.size() == 0))
            return false;

        return parsed;

    } else {

        return false;

    }
}


Handle<Value> Polygon2::ToPOD(const Polygon_2 &poly)
{
    HandleScope scope;
    return scope.Close(Point2::SeqToPOD(poly.vertices_begin(), poly.vertices_end()));
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
