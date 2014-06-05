#include "PolygonSet2.h"
#include "PolygonWithHoles2.h"
#include "Arrangement2.h"
#include "Polygon2.h"
#include "Point2.h"
#include "cgal_args.h"

using namespace v8;
using namespace node;
using namespace std;


const char *PolygonSet2::Name = "PolygonSet2";


void PolygonSet2::RegisterMethods()
{
    SetPrototypeMethod(sConstructorTemplate, "polygonsWithHoles", PolygonsWithHoles);
    SetPrototypeMethod(sConstructorTemplate, "numPolygonsWithHoles", NumPolygonsWithHoles);
    SetPrototypeMethod(sConstructorTemplate, "isEmpty", IsEmpty);
    SetPrototypeMethod(sConstructorTemplate, "isPlane", IsPlane);
    // SetPrototypeMethod(sConstructorTemplate, "arrangement", Arrangement);
    SetPrototypeMethod(sConstructorTemplate, "clear", Clear);
    SetPrototypeMethod(sConstructorTemplate, "complement", Complement);
    SetPrototypeMethod(sConstructorTemplate, "intersection", Intersection);
    SetPrototypeMethod(sConstructorTemplate, "join", Join);
    SetPrototypeMethod(sConstructorTemplate, "difference", Difference);
    SetPrototypeMethod(sConstructorTemplate, "symmetricDifference", SymmetricDifference);
    SetPrototypeMethod(sConstructorTemplate, "intersects", Intersects);
    // SetPrototypeMethod(sConstructorTemplate, "locate", Locate);
    SetPrototypeMethod(sConstructorTemplate, "insert", Insert);
    SetPrototypeMethod(sConstructorTemplate, "orientedSide", OrientedSide);
    SetPrototypeMethod(sConstructorTemplate, "isValid", IsValid);
}


bool PolygonSet2::ParseArg(Local<Value> arg, Polygon_set_2 &receiver)
{
    // This supports e.g.: newset = new CGAL.PolygonSet2(oldset);
    if (sConstructorTemplate->HasInstance(arg)) {
        receiver = ExtractWrapped(Local<Object>::Cast(arg));
        return true;
    }

    // This supports e.g.: newset = new CGAL.PolygonSet2(aPolygon2);
    Polygon_2 poly;
    if (Polygon2::ParseArg(arg, poly)) {
        receiver = Polygon_set_2(poly);
        return true;
    }

    // This supports e.g.: newset = new CGAL.PolygonSet2(aPolygonWithHoles2);
    Polygon_with_holes_2 pwh;
    if (PolygonWithHoles2::ParseArg(arg, pwh)) {
        receiver = Polygon_set_2(pwh);
        return true;
    }

    // no good...
    return false;
}


Handle<Value> PolygonSet2::ToPOD(const Polygon_set_2 &polySet, bool precise)
{
    HandleScope scope;
    vector<Polygon_with_holes_2> pwhs;
    polySet.polygons_with_holes(back_inserter(pwhs));
    return scope.Close(PolygonWithHoles2::SeqToPOD(pwhs.begin(), pwhs.end(), precise));
}


Handle<Value> PolygonSet2::PolygonsWithHoles(const Arguments &args)
{
    HandleScope scope;
    try {
        Polygon_set_2 &polySet = ExtractWrapped(args.This());
        vector<Polygon_with_holes_2> pwhs;
        polySet.polygons_with_holes(back_inserter(pwhs));
        Local<Array> array = Array::New();
        uint32_t i;
        vector<Polygon_with_holes_2>::iterator it;
        for(it=pwhs.begin(),i=0; it!=pwhs.end(); ++it,++i) {
            array->Set(i, PolygonWithHoles2::New(*it));
        }
        return scope.Close(array);
    }
    catch (const exception &e) {
        return ThrowException(String::New(e.what()));
    }
}


Handle<Value> PolygonSet2::NumPolygonsWithHoles(const Arguments &args)
{
    HandleScope scope;
    try {
        Polygon_set_2 &polySet = ExtractWrapped(args.This());
        return scope.Close(Number::New(polySet.number_of_polygons_with_holes()));
    }
    catch (const exception &e) {
        return ThrowException(String::New(e.what()));
    }
}


Handle<Value> PolygonSet2::IsEmpty(const Arguments &args)
{
    HandleScope scope;
    try {
        Polygon_set_2 &polySet = ExtractWrapped(args.This());
        return scope.Close(Boolean::New(polySet.is_empty()));
    }
    catch (const exception &e) {
        return ThrowException(String::New(e.what()));
    }
}


Handle<Value> PolygonSet2::IsPlane(const Arguments &args)
{
    HandleScope scope;
    try {
        Polygon_set_2 &polySet = ExtractWrapped(args.This());
        return scope.Close(Boolean::New(polySet.is_plane()));
    }
    catch (const exception &e) {
        return ThrowException(String::New(e.what()));
    }
}


// Handle<Value> PolygonSet2::Arrangement(const Arguments &args)
// {
//     HandleScope scope;
//     try {
//         Polygon_set_2 &polySet = ExtractWrapped(args.This());
//         return scope.Close(Arrangement2::New(polySet.arrangement()));
//     }
//     catch (const exception &e) {
//         return ThrowException(String::New(e.what()));
//     }
// }


Handle<Value> PolygonSet2::Clear(const Arguments &args)
{
    HandleScope scope;
    try {
        Polygon_set_2 &polySet = ExtractWrapped(args.This());
        polySet.clear();
        return Undefined();
    }
    catch (const exception &e) {
        return ThrowException(String::New(e.what()));
    }
}


Handle<Value> PolygonSet2::Insert(const Arguments &args)
{
    HandleScope scope;
    try {

        Polygon_set_2 &polySet = ExtractWrapped(args.This());

        ARGS_ASSERT(args.Length() == 1);

        Polygon_2 poly;
        if (Polygon2::ParseArg(args[0], poly)) {
            polySet.insert(poly);
            return Undefined();
        }

        Polygon_with_holes_2 pwh;
        if (PolygonWithHoles2::ParseArg(args[0], pwh)) {
            polySet.insert(pwh);
            return Undefined();
        }

        ARGS_ASSERT(false);

    }

    catch (const exception &e) {
        return ThrowException(String::New(e.what()));
    }
}


Handle<Value> PolygonSet2::Complement(const Arguments &args)
{
    HandleScope scope;
    try {
        Polygon_set_2 &polySet = ExtractWrapped(args.This());
        polySet.complement();
        return Undefined();
    }
    catch (const exception &e) {
        return ThrowException(String::New(e.what()));
    }
}


Handle<Value> PolygonSet2::Intersection(const Arguments &args)
{
    HandleScope scope;
    try {

        Polygon_set_2 &polySet = ExtractWrapped(args.This());

        ARGS_ASSERT(args.Length() == 1);

        Polygon_2 poly;
        if (Polygon2::ParseArg(args[0], poly)) {
            polySet.intersection(poly);
            return Undefined();
        }

        Polygon_with_holes_2 pwh;
        if (PolygonWithHoles2::ParseArg(args[0], pwh)) {
            polySet.intersection(pwh);
            return Undefined();
        }

        Polygon_set_2 polySet2;
        if (PolygonSet2::ParseArg(args[0], polySet2)) {
            polySet.intersection(polySet2);
            return Undefined();
        }

        ARGS_ASSERT(false);

    }

    catch (const exception &e) {
        return ThrowException(String::New(e.what()));
    }
}


Handle<Value> PolygonSet2::Join(const Arguments &args)
{
    HandleScope scope;
    try {

        Polygon_set_2 &polySet = ExtractWrapped(args.This());

        ARGS_ASSERT(args.Length() == 1);

        Polygon_2 poly;
        if (Polygon2::ParseArg(args[0], poly)) {
            polySet.join(poly);
            return Undefined();
        }

        Polygon_with_holes_2 pwh;
        if (PolygonWithHoles2::ParseArg(args[0], pwh)) {
            polySet.join(pwh);
            return Undefined();
        }

        Polygon_set_2 polySet2;
        if (PolygonSet2::ParseArg(args[0], polySet2)) {
            polySet.join(polySet2);
            return Undefined();
        }

        ARGS_ASSERT(false);

    }

    catch (const exception &e) {
        return ThrowException(String::New(e.what()));
    }
}


Handle<Value> PolygonSet2::Difference(const Arguments &args)
{
    HandleScope scope;
    try {

        Polygon_set_2 &polySet = ExtractWrapped(args.This());

        ARGS_ASSERT(args.Length() == 1);

        Polygon_2 poly;
        if (Polygon2::ParseArg(args[0], poly)) {
            polySet.difference(poly);
            return Undefined();
        }

        Polygon_with_holes_2 pwh;
        if (PolygonWithHoles2::ParseArg(args[0], pwh)) {
            polySet.difference(pwh);
            return Undefined();
        }

        Polygon_set_2 polySet2;
        if (PolygonSet2::ParseArg(args[0], polySet2)) {
            polySet.difference(polySet2);
            return Undefined();
        }

        ARGS_ASSERT(false);

    }

    catch (const exception &e) {
        return ThrowException(String::New(e.what()));
    }
}


Handle<Value> PolygonSet2::SymmetricDifference(const Arguments &args)
{
    HandleScope scope;
    try {

        Polygon_set_2 &polySet = ExtractWrapped(args.This());

        ARGS_ASSERT(args.Length() == 1);

        Polygon_2 poly;
        if (Polygon2::ParseArg(args[0], poly)) {
            polySet.symmetric_difference(poly);
            return Undefined();
        }

        Polygon_with_holes_2 pwh;
        if (PolygonWithHoles2::ParseArg(args[0], pwh)) {
            polySet.symmetric_difference(pwh);
            return Undefined();
        }

        Polygon_set_2 polySet2;
        if (PolygonSet2::ParseArg(args[0], polySet2)) {
            polySet.symmetric_difference(polySet2);
            return Undefined();
        }

        ARGS_ASSERT(false);

    }

    catch (const exception &e) {
        return ThrowException(String::New(e.what()));
    }
}


Handle<Value> PolygonSet2::Intersects(const Arguments &args)
{
    HandleScope scope;
    try {

        Polygon_set_2 &polySet = ExtractWrapped(args.This());

        ARGS_ASSERT(args.Length() == 1);

        Polygon_2 poly;
        if (Polygon2::ParseArg(args[0], poly)) {
            return scope.Close(Boolean::New(polySet.do_intersect(poly)));
        }

        Polygon_with_holes_2 pwh;
        if (PolygonWithHoles2::ParseArg(args[0], pwh)) {
            return scope.Close(Boolean::New(polySet.do_intersect(pwh)));
        }

        Polygon_set_2 polySet2;
        if (PolygonSet2::ParseArg(args[0], polySet2)) {
            return scope.Close(Boolean::New(polySet.do_intersect(polySet2)));
        }

        ARGS_ASSERT(false);

    }

    catch (const exception &e) {
        return ThrowException(String::New(e.what()));
    }
}


// Handle<Value> PolygonSet2::Locate(const Arguments &args)
// {
//     HandleScope scope;
//     try {
//         Polygon_set_2 &polySet = ExtractWrapped(args.This());
//         ARGS_ASSERT(args.Length() == 2);
//         ARGS_PARSE_LOCAL(Point2::ParseArg, Point_2, point, args[0]);
//         ARGS_PARSE_LOCAL(PolygonWithHoles2::ParseArg, Polygon_with_holes_2, pwh, args[1]);
//         return scope.Close(Boolean::New(polySet.locate(point, pwh)));
//     }
//     catch (const exception &e) {
//         return ThrowException(String::New(e.what()));
//     }
// }


Handle<Value> PolygonSet2::OrientedSide(const Arguments &args)
{
    HandleScope scope;
    try {

        Polygon_set_2 &polySet = ExtractWrapped(args.This());

        ARGS_ASSERT(args.Length() == 1);

        Point_2 point;
        if (Point2::ParseArg(args[0], point)) {
            return scope.Close(Number::New(polySet.oriented_side(point)));
        }

        Polygon_2 poly;
        if (Polygon2::ParseArg(args[0], poly)) {
            return scope.Close(Number::New(polySet.oriented_side(poly)));
        }

        Polygon_with_holes_2 pwh;
        if (PolygonWithHoles2::ParseArg(args[0], pwh)) {
            return scope.Close(Number::New(polySet.oriented_side(pwh)));
        }

        Polygon_set_2 polySet2;
        if (PolygonSet2::ParseArg(args[0], polySet2)) {
            return scope.Close(Number::New(polySet.oriented_side(polySet2)));
        }

        ARGS_ASSERT(false);

    }

    catch (const exception &e) {
        return ThrowException(String::New(e.what()));
    }
}


Handle<Value> PolygonSet2::IsValid(const Arguments &args)
{
    HandleScope scope;
    try {
        Polygon_set_2 &polySet = ExtractWrapped(args.This());
        return scope.Close(Boolean::New(polySet.is_valid()));
    }
    catch (const exception &e) {
        return ThrowException(String::New(e.what()));
    }
}
