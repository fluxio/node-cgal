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

ostream &operator<<(ostream &str, const Polygon_set_2 &polySet)
{
    return str;
}


void PolygonSet2::RegisterMethods(Isolate *isolate)
{
    HandleScope scope(isolate);
    Local<FunctionTemplate> constructorTemplate = sConstructorTemplate.Get(isolate);
    NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "polygonsWithHoles", PolygonsWithHoles);
    NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "numPolygonsWithHoles", NumPolygonsWithHoles);
    NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "isEmpty", IsEmpty);
    NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "isPlane", IsPlane);
    // NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "arrangement", Arrangement);
    NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "clear", Clear);
    NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "complement", Complement);
    NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "intersection", Intersection);
    NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "join", Join);
    NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "difference", Difference);
    NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "symmetricDifference", SymmetricDifference);
    NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "intersects", Intersects);
    // NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "locate", Locate);
    NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "insert", Insert);
    NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "orientedSide", OrientedSide);
    NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "isValid", IsValid);
}


bool PolygonSet2::ParseArg(Isolate *isolate, Local<Value> arg, Polygon_set_2 &receiver)
{
    if (sConstructorTemplate.Get(isolate)->HasInstance(arg)) {
        receiver = ExtractWrapped(Local<Object>::Cast(arg));
        return true;
    }

    Polygon_2 poly;
    if (Polygon2::ParseArg(isolate, arg, poly)) {
        receiver = Polygon_set_2(poly);
        return true;
    }

    Polygon_with_holes_2 pwh;
    if (PolygonWithHoles2::ParseArg(isolate, arg, pwh)) {
        receiver = Polygon_set_2(pwh);
        return true;
    }

    return false;
}


Local<Value> PolygonSet2::ToPOD(Isolate *isolate, const Polygon_set_2 &polySet, bool precise)
{
    EscapableHandleScope scope(isolate);
    vector<Polygon_with_holes_2> pwhs;
    polySet.polygons_with_holes(back_inserter(pwhs));
    return scope.Escape(PolygonWithHoles2::SeqToPOD(isolate, pwhs.begin(), pwhs.end(), precise));
}


void PolygonSet2::PolygonsWithHoles(const FunctionCallbackInfo<Value> &info)
{
    Isolate *isolate = info.GetIsolate();
    HandleScope scope(isolate);
    try {
        Polygon_set_2 &polySet = ExtractWrapped(info.This());
        vector<Polygon_with_holes_2> pwhs;
        polySet.polygons_with_holes(back_inserter(pwhs));
        Local<Array> array = Array::New(isolate);
        uint32_t i;
        vector<Polygon_with_holes_2>::iterator it;
        for(it=pwhs.begin(),i=0; it!=pwhs.end(); ++it,++i) {
            array->Set(i, PolygonWithHoles2::New(isolate, *it));
        }
        info.GetReturnValue().Set(array);
    }
    catch (const exception &e) {
        isolate->ThrowException(String::NewFromUtf8(isolate, e.what()));
    }
}


void PolygonSet2::NumPolygonsWithHoles(const FunctionCallbackInfo<Value> &info)
{
    Isolate *isolate = info.GetIsolate();
    HandleScope scope(isolate);
    try {
        Polygon_set_2 &polySet = ExtractWrapped(info.This());
        info.GetReturnValue().Set(Number::New(isolate, polySet.number_of_polygons_with_holes()));
    }
    catch (const exception &e) {
        isolate->ThrowException(String::NewFromUtf8(isolate, e.what()));
    }
}


void PolygonSet2::IsEmpty(const FunctionCallbackInfo<Value> &info)
{
    Isolate *isolate = info.GetIsolate();
    HandleScope scope(isolate);
    try {
        Polygon_set_2 &polySet = ExtractWrapped(info.This());
        info.GetReturnValue().Set(Boolean::New(isolate, polySet.is_empty()));
    }
    catch (const exception &e) {
        isolate->ThrowException(String::NewFromUtf8(isolate, e.what()));
    }
}


void PolygonSet2::IsPlane(const FunctionCallbackInfo<Value> &info)
{
    Isolate *isolate = info.GetIsolate();
    HandleScope scope(isolate);
    try {
        Polygon_set_2 &polySet = ExtractWrapped(info.This());
        info.GetReturnValue().Set(Boolean::New(isolate, polySet.is_plane()));
    }
    catch (const exception &e) {
        isolate->ThrowException(String::NewFromUtf8(isolate, e.what()));
    }
}


// void PolygonSet2::Arrangement(const FunctionCallbackInfo<Value> &info)
// {
//     Isolate *isolate = info.GetIsolate();
//     HandleScope scope(isolate);
//     try {
//         Polygon_set_2 &polySet = ExtractWrapped(info.This());
//         info.GetReturnValue().Set(isolate, Arrangement2::New(polySet.arrangement()));
//     }
//     catch (const exception &e) {
//         isolate->ThrowException(String::NewFromUtf8(isolate, e.what()));
//     }
// }


void PolygonSet2::Clear(const FunctionCallbackInfo<Value> &info)
{
    Isolate *isolate = info.GetIsolate();
    HandleScope scope(isolate);
    try {
        Polygon_set_2 &polySet = ExtractWrapped(info.This());
        polySet.clear();
        info.GetReturnValue().SetUndefined();
        return;
    }
    catch (const exception &e) {
        isolate->ThrowException(String::NewFromUtf8(isolate, e.what()));
    }
}


void PolygonSet2::Insert(const FunctionCallbackInfo<Value> &info)
{
    Isolate *isolate = info.GetIsolate();
    HandleScope scope(isolate);
    try {

        Polygon_set_2 &polySet = ExtractWrapped(info.This());

        ARGS_ASSERT(isolate, info.Length() == 1);

        Polygon_2 poly;
        if (Polygon2::ParseArg(isolate, info[0], poly)) {
            polySet.insert(poly);
            info.GetReturnValue().SetUndefined();
            return;
        }

        Polygon_with_holes_2 pwh;
        if (PolygonWithHoles2::ParseArg(isolate, info[0], pwh)) {
            polySet.insert(pwh);
            info.GetReturnValue().SetUndefined();
            return;
        }

        ARGS_ASSERT(isolate, false);

    }

    catch (const exception &e) {
        isolate->ThrowException(String::NewFromUtf8(isolate, e.what()));
    }
}


void PolygonSet2::Complement(const FunctionCallbackInfo<Value> &info)
{
    Isolate *isolate = info.GetIsolate();
    HandleScope scope(isolate);
    try {
        Polygon_set_2 &polySet = ExtractWrapped(info.This());
        polySet.complement();
        info.GetReturnValue().SetUndefined();
        return;
    }
    catch (const exception &e) {
        isolate->ThrowException(String::NewFromUtf8(isolate, e.what()));
    }
}


void PolygonSet2::Intersection(const FunctionCallbackInfo<Value> &info)
{
    Isolate *isolate = info.GetIsolate();
    HandleScope scope(isolate);
    try {

        Polygon_set_2 &polySet = ExtractWrapped(info.This());

        ARGS_ASSERT(isolate, info.Length() == 1);

        Polygon_2 poly;
        if (Polygon2::ParseArg(isolate, info[0], poly)) {
            polySet.intersection(poly);
            info.GetReturnValue().SetUndefined();
            return;
        }

        Polygon_with_holes_2 pwh;
        if (PolygonWithHoles2::ParseArg(isolate, info[0], pwh)) {
            polySet.intersection(pwh);
            info.GetReturnValue().SetUndefined();
            return;
        }

        Polygon_set_2 polySet2;
        if (PolygonSet2::ParseArg(isolate, info[0], polySet2)) {
            polySet.intersection(polySet2);
            info.GetReturnValue().SetUndefined();
            return;
        }

        ARGS_ASSERT(isolate, false);

    }

    catch (const exception &e) {
        isolate->ThrowException(String::NewFromUtf8(isolate, e.what()));
    }
}


void PolygonSet2::Join(const FunctionCallbackInfo<Value> &info)
{
    Isolate *isolate = info.GetIsolate();
    HandleScope scope(isolate);
    try {

        Polygon_set_2 &polySet = ExtractWrapped(info.This());

        ARGS_ASSERT(isolate, info.Length() == 1);

        Polygon_2 poly;
        if (Polygon2::ParseArg(isolate, info[0], poly)) {
            polySet.join(poly);
            info.GetReturnValue().SetUndefined();
            return;
        }

        Polygon_with_holes_2 pwh;
        if (PolygonWithHoles2::ParseArg(isolate, info[0], pwh)) {
            polySet.join(pwh);
            info.GetReturnValue().SetUndefined();
            return;
        }

        Polygon_set_2 polySet2;
        if (PolygonSet2::ParseArg(isolate, info[0], polySet2)) {
            polySet.join(polySet2);
            info.GetReturnValue().SetUndefined();
            return;
        }

        ARGS_ASSERT(isolate, false);

    }

    catch (const exception &e) {
        isolate->ThrowException(String::NewFromUtf8(isolate, e.what()));
    }
}


void PolygonSet2::Difference(const FunctionCallbackInfo<Value> &info)
{
    Isolate *isolate = info.GetIsolate();
    HandleScope scope(isolate);
    try {

        Polygon_set_2 &polySet = ExtractWrapped(info.This());

        ARGS_ASSERT(isolate, info.Length() == 1);

        Polygon_2 poly;
        if (Polygon2::ParseArg(isolate, info[0], poly)) {
            polySet.difference(poly);
            info.GetReturnValue().SetUndefined();
            return;
        }

        Polygon_with_holes_2 pwh;
        if (PolygonWithHoles2::ParseArg(isolate, info[0], pwh)) {
            polySet.difference(pwh);
            info.GetReturnValue().SetUndefined();
            return;
        }

        Polygon_set_2 polySet2;
        if (PolygonSet2::ParseArg(isolate, info[0], polySet2)) {
            polySet.difference(polySet2);
            info.GetReturnValue().SetUndefined();
            return;
        }

        ARGS_ASSERT(isolate, false);

    }

    catch (const exception &e) {
        isolate->ThrowException(String::NewFromUtf8(isolate, e.what()));
    }
}


void PolygonSet2::SymmetricDifference(const FunctionCallbackInfo<Value> &info)
{
    Isolate *isolate = info.GetIsolate();
    HandleScope scope(isolate);
    try {

        Polygon_set_2 &polySet = ExtractWrapped(info.This());

        ARGS_ASSERT(isolate, info.Length() == 1);

        Polygon_2 poly;
        if (Polygon2::ParseArg(isolate, info[0], poly)) {
            polySet.symmetric_difference(poly);
            info.GetReturnValue().SetUndefined();
            return;
        }

        Polygon_with_holes_2 pwh;
        if (PolygonWithHoles2::ParseArg(isolate, info[0], pwh)) {
            polySet.symmetric_difference(pwh);
            info.GetReturnValue().SetUndefined();
            return;
        }

        Polygon_set_2 polySet2;
        if (PolygonSet2::ParseArg(isolate, info[0], polySet2)) {
            polySet.symmetric_difference(polySet2);
            info.GetReturnValue().SetUndefined();
            return;
        }

        ARGS_ASSERT(isolate, false);

    }

    catch (const exception &e) {
        isolate->ThrowException(String::NewFromUtf8(isolate, e.what()));
    }
}


void PolygonSet2::Intersects(const FunctionCallbackInfo<Value> &info)
{
    Isolate *isolate = info.GetIsolate();
    HandleScope scope(isolate);
    try {

        Polygon_set_2 &polySet = ExtractWrapped(info.This());

        ARGS_ASSERT(isolate, info.Length() == 1);

        Polygon_2 poly;
        if (Polygon2::ParseArg(isolate, info[0], poly)) {
            info.GetReturnValue().Set(Boolean::New(isolate, polySet.do_intersect(poly)));
            return;
        }

        Polygon_with_holes_2 pwh;
        if (PolygonWithHoles2::ParseArg(isolate, info[0], pwh)) {
            info.GetReturnValue().Set(Boolean::New(isolate, polySet.do_intersect(pwh)));
            return;
        }

        Polygon_set_2 polySet2;
        if (PolygonSet2::ParseArg(isolate, info[0], polySet2)) {
            info.GetReturnValue().Set(Boolean::New(isolate, polySet.do_intersect(polySet2)));
            return;
        }

        ARGS_ASSERT(isolate, false);

    }

    catch (const exception &e) {
        isolate->ThrowException(String::NewFromUtf8(isolate, e.what()));
    }
}


// void PolygonSet2::Locate(const FunctionCallbackInfo<Value> &info)
// {
//     Isolate *isolate = info.GetIsolate();
//     HandleScope scope(isolate);
//     try {
//         Polygon_set_2 &polySet = ExtractWrapped(info.This());
//         ARGS_ASSERT(isolate, info.Length() == 2);
//         ARGS_PARSE_LOCAL(isolate, Point2::ParseArg, Point_2, point, info[0]);
//         ARGS_PARSE_LOCAL(isolate, PolygonWithHoles2::ParseArg, Polygon_with_holes_2, pwh, info[1]);
//         info.GetReturnValue().Set(Boolean::New(isolate, polySet.locate(point, pwh)));
//     }
//     catch (const exception &e) {
//         isolate->ThrowException(String::NewFromUtf8(isolate, e.what()));
//     }
// }


void PolygonSet2::OrientedSide(const FunctionCallbackInfo<Value> &info)
{
    Isolate *isolate = info.GetIsolate();
    HandleScope scope(isolate);
    try {

        Polygon_set_2 &polySet = ExtractWrapped(info.This());

        ARGS_ASSERT(isolate, info.Length() == 1);

        Point_2 point;
        if (Point2::ParseArg(isolate, info[0], point)) {
            info.GetReturnValue().Set(Number::New(isolate, polySet.oriented_side(point)));
            return;
        }

        Polygon_2 poly;
        if (Polygon2::ParseArg(isolate, info[0], poly)) {
            info.GetReturnValue().Set(Number::New(isolate, polySet.oriented_side(poly)));
            return;
        }

        Polygon_with_holes_2 pwh;
        if (PolygonWithHoles2::ParseArg(isolate, info[0], pwh)) {
            info.GetReturnValue().Set(Number::New(isolate, polySet.oriented_side(pwh)));
            return;
        }

        Polygon_set_2 polySet2;
        if (PolygonSet2::ParseArg(isolate, info[0], polySet2)) {
            info.GetReturnValue().Set(Number::New(isolate, polySet.oriented_side(polySet2)));
            return;
        }

        ARGS_ASSERT(isolate, false);

    }

    catch (const exception &e) {
        isolate->ThrowException(String::NewFromUtf8(isolate, e.what()));
    }
}


void PolygonSet2::IsValid(const FunctionCallbackInfo<Value> &info)
{
    Isolate *isolate = info.GetIsolate();
    HandleScope scope(isolate);
    try {
        Polygon_set_2 &polySet = ExtractWrapped(info.This());
        info.GetReturnValue().Set(Boolean::New(isolate, polySet.is_valid()));
    }
    catch (const exception &e) {
        isolate->ThrowException(String::NewFromUtf8(isolate, e.what()));
    }
}
