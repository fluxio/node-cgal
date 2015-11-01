#include "Ray2.h"
#include "Point2.h"
#include "Line2.h"
#include "Direction2.h"
#include "Vector2.h"
#include "cgal_args.h"

using namespace v8;
using namespace node;
using namespace std;


const char *Ray2::Name = "Ray2";


void Ray2::RegisterMethods(Isolate *isolate)
{
    HandleScope scope(isolate);
    Local<FunctionTemplate> constructorTemplate = sConstructorTemplate.Get(isolate);
    NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "isEqual", IsEqual);
    NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "source", Source);
    NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "point", Point);
    NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "direction", Direction);
    NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "toVector", ToVector);
    NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "supportingLine", SupportingLine);
    NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "opposite", Opposite);
    NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "isDegenerate", IsDegenerate);
    NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "isHorizontal", IsHorizontal);
    NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "isVertical", IsVertical);
    NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "hasOn", HasOn);
    NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "collinearHasOn", CollinearHasOn);
}


bool Ray2::ParseArg(Isolate *isolate, Local<Value> arg, Ray_2 &receiver)
{
    HandleScope scope(isolate);

    if (sConstructorTemplate.Get(isolate)->HasInstance(arg)) {
        receiver = ExtractWrapped(Local<Object>::Cast(arg));
        return true;
    }

    if (arg->IsObject()) {
        Local<Object> inits = Local<Object>::Cast(arg);

        Point_2 p;
        Direction_2 d;
        if (Point2::ParseArg(isolate, inits->Get(SYMBOL(isolate, "p")), p) &&
            Direction2::ParseArg(isolate, inits->Get(SYMBOL(isolate, "d")), d))
        {
            receiver = Ray_2(p, d);
            return true;
        }

        Point_2 q;
        if (Point2::ParseArg(isolate, inits->Get(SYMBOL(isolate, "p")), p) &&
            Point2::ParseArg(isolate, inits->Get(SYMBOL(isolate, "q")), q))
        {
            receiver = Ray_2(p, q);
            return true;
        }

        Line_2 l;
        if (Point2::ParseArg(isolate, inits->Get(SYMBOL(isolate, "p")), p) &&
            Line2::ParseArg(isolate, inits->Get(SYMBOL(isolate, "l")), l))
        {
            receiver = Ray_2(p, l);
            return true;
        }

        Vector_2 v;
        if (Point2::ParseArg(isolate, inits->Get(SYMBOL(isolate, "p")), p) &&
            Vector2::ParseArg(isolate, inits->Get(SYMBOL(isolate, "v")), v))
        {
            receiver = Ray_2(p, v);
            return true;
        }

    }

    return false;
}


Local<Value> Ray2::ToPOD(Isolate *isolate, const Ray_2 &ray, bool precise)
{
    EscapableHandleScope scope(isolate);
    Local<Object> obj = Object::New(isolate);
    obj->Set(SYMBOL(isolate, "p"), Point2::ToPOD(isolate, ray.source(), precise));
    obj->Set(SYMBOL(isolate, "d"), Direction2::ToPOD(isolate, ray.direction(), precise));
    return scope.Escape(obj);
}


void Ray2::IsEqual(const FunctionCallbackInfo<Value> &info)
{
    Isolate *isolate = info.GetIsolate();
    HandleScope scope(isolate);
    try {
        Ray_2 &thisRay = ExtractWrapped(info.This());
        ARGS_ASSERT(isolate, info.Length() == 1);
        ARGS_PARSE_LOCAL(isolate, Ray2::ParseArg, Ray_2, otherRay, info[0]);
        info.GetReturnValue().Set(Boolean::New(isolate, thisRay == otherRay));
    }
    catch (const exception &e) {
        isolate->ThrowException(String::NewFromUtf8(isolate, e.what()));
    }
}


void Ray2::Source(const FunctionCallbackInfo<Value> &info)
{
    Isolate *isolate = info.GetIsolate();
    HandleScope scope(isolate);
    try {
        Ray_2 &ray = ExtractWrapped(info.This());
        info.GetReturnValue().Set(Point2::New(isolate, ray.source()));
    }
    catch (const exception &e) {
        isolate->ThrowException(String::NewFromUtf8(isolate, e.what()));
    }
}


void Ray2::Point(const FunctionCallbackInfo<Value> &info)
{
    Isolate *isolate = info.GetIsolate();
    HandleScope scope(isolate);
    try {
        Ray_2 &ray = ExtractWrapped(info.This());
        ARGS_ASSERT(isolate, info.Length() == 1);
        ARGS_ASSERT(isolate, info[0]->IsNumber())
        info.GetReturnValue().Set(Point2::New(isolate, ray.point(info[0]->NumberValue())));
    }
    catch (const exception &e) {
        isolate->ThrowException(String::NewFromUtf8(isolate, e.what()));
    }
}


void Ray2::Direction(const FunctionCallbackInfo<Value> &info)
{
    Isolate *isolate = info.GetIsolate();
    HandleScope scope(isolate);
    try {
        Ray_2 &ray = ExtractWrapped(info.This());
        info.GetReturnValue().Set(Direction2::New(isolate, ray.direction()));
    }
    catch (const exception &e) {
        isolate->ThrowException(String::NewFromUtf8(isolate, e.what()));
    }
}


void Ray2::ToVector(const FunctionCallbackInfo<Value> &info)
{
    Isolate *isolate = info.GetIsolate();
    HandleScope scope(isolate);
    try {
        Ray_2 &ray = ExtractWrapped(info.This());
        info.GetReturnValue().Set(Vector2::New(isolate, ray.to_vector()));
    }
    catch (const exception &e) {
        isolate->ThrowException(String::NewFromUtf8(isolate, e.what()));
    }
}


void Ray2::SupportingLine(const FunctionCallbackInfo<Value> &info)
{
    Isolate *isolate = info.GetIsolate();
    HandleScope scope(isolate);
    try {
        Ray_2 &ray = ExtractWrapped(info.This());
        info.GetReturnValue().Set(Line2::New(isolate, ray.supporting_line()));
    }
    catch (const exception &e) {
        isolate->ThrowException(String::NewFromUtf8(isolate, e.what()));
    }
}


void Ray2::Opposite(const FunctionCallbackInfo<Value> &info)
{
    Isolate *isolate = info.GetIsolate();
    HandleScope scope(isolate);
    try {
        Ray_2 &ray = ExtractWrapped(info.This());
        info.GetReturnValue().Set(Ray2::New(isolate, ray.opposite()));
    }
    catch (const exception &e) {
        isolate->ThrowException(String::NewFromUtf8(isolate, e.what()));
    }
}


void Ray2::IsDegenerate(const FunctionCallbackInfo<Value> &info)
{
    Isolate *isolate = info.GetIsolate();
    HandleScope scope(isolate);
    try {
        Ray_2 &ray = ExtractWrapped(info.This());
        info.GetReturnValue().Set(Boolean::New(isolate, ray.is_degenerate()));
    }
    catch (const exception &e) {
        isolate->ThrowException(String::NewFromUtf8(isolate, e.what()));
    }
}


void Ray2::IsHorizontal(const FunctionCallbackInfo<Value> &info)
{
    Isolate *isolate = info.GetIsolate();
    HandleScope scope(isolate);
    try {
        Ray_2 &ray = ExtractWrapped(info.This());
        info.GetReturnValue().Set(Boolean::New(isolate, ray.is_horizontal()));
    }
    catch (const exception &e) {
        isolate->ThrowException(String::NewFromUtf8(isolate, e.what()));
    }
}


void Ray2::IsVertical(const FunctionCallbackInfo<Value> &info)
{
    Isolate *isolate = info.GetIsolate();
    HandleScope scope(isolate);
    try {
        Ray_2 &ray = ExtractWrapped(info.This());
        info.GetReturnValue().Set(Boolean::New(isolate, ray.is_vertical()));
    }
    catch (const exception &e) {
        isolate->ThrowException(String::NewFromUtf8(isolate, e.what()));
    }
}


void Ray2::HasOn(const FunctionCallbackInfo<Value> &info)
{
    Isolate *isolate = info.GetIsolate();
    HandleScope scope(isolate);
    try {
        Ray_2 &ray = ExtractWrapped(info.This());
        ARGS_ASSERT(isolate, info.Length() == 1);
        ARGS_PARSE_LOCAL(isolate, Point2::ParseArg, Point_2, point, info[0]);
        info.GetReturnValue().Set(Boolean::New(isolate, ray.has_on(point)));
    }
    catch (const exception &e) {
        isolate->ThrowException(String::NewFromUtf8(isolate, e.what()));
    }
}


void Ray2::CollinearHasOn(const FunctionCallbackInfo<Value> &info)
{
    Isolate *isolate = info.GetIsolate();
    HandleScope scope(isolate);
    try {
        Ray_2 &ray = ExtractWrapped(info.This());
        ARGS_ASSERT(isolate, info.Length() == 1);
        ARGS_PARSE_LOCAL(isolate, Point2::ParseArg, Point_2, point, info[0]);
        info.GetReturnValue().Set(Boolean::New(isolate, ray.collinear_has_on(point)));
    }
    catch (const exception &e) {
        isolate->ThrowException(String::NewFromUtf8(isolate, e.what()));
    }
}
