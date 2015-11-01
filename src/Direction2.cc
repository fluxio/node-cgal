#include "Direction2.h"
#include "Point2.h"
#include "Line2.h"
#include "Vector2.h"
#include "Segment2.h"
#include "Ray2.h"
#include "cgal_args.h"

using namespace v8;
using namespace node;
using namespace std;


const char *Direction2::Name = "Direction2";


void Direction2::RegisterMethods(Isolate *isolate)
{
    HandleScope scope(isolate);
    Local<FunctionTemplate> constructorTemplate = sConstructorTemplate.Get(isolate);
    NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "isEqual", IsEqual);
    NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "isLessThan", IsLessThan);
    NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "isGreaterThan", IsGreaterThan);
    NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "isCCWBetween", IsCCWBetween);
    NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "opposite", Opposite);
    NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "toVector", ToVector);
    NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "dx", DX);
    NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "dy", DY);
}


bool Direction2::ParseArg(Isolate *isolate, Local<Value> arg, Direction_2 &receiver)
{
    HandleScope scope(isolate);

    if (sConstructorTemplate.Get(isolate)->HasInstance(arg)) {
        receiver = ExtractWrapped(Local<Object>::Cast(arg));
        return true;
    }

    Vector_2 vector;
    if (Vector2::ParseArg(isolate, arg, vector)) {
        receiver = Direction_2(vector);
        return true;
    }

    Line_2 line;
    if (Line2::ParseArg(isolate, arg, line)) {
        receiver = Direction_2(line);
        return true;
    }

    Ray_2 ray;
    if (Ray2::ParseArg(isolate, arg, ray)) {
        receiver = Direction_2(ray);
        return true;
    }

    Segment_2 segment;
    if (Segment2::ParseArg(isolate, arg, segment)) {
        receiver = Direction_2(segment);
        return true;
    }

    if (arg->IsObject()) {
        Local<Object> inits = Local<Object>::Cast(arg);

        K::FT dx, dy;
        if (::ParseArg(isolate, inits->Get(SYMBOL(isolate, "dx")), dx) &&
            ::ParseArg(isolate, inits->Get(SYMBOL(isolate, "dy")), dy))
        {
            receiver = Direction_2(dx, dy);
            return true;
        }

    }

    return false;
}


Local<Value> Direction2::ToPOD(Isolate *isolate, const Direction_2 &direction, bool precise)
{
    EscapableHandleScope scope(isolate);
    Local<Object> obj = Object::New(isolate);

    if (precise) {

        ostringstream dxstr;
#if CGAL_USE_EPECK
        dxstr << direction.dx().exact();
#else
        dxstr << setprecision(20) << direction.dx();
#endif
        obj->Set(SYMBOL(isolate, "dx"), String::NewFromUtf8(isolate, dxstr.str().c_str()));

        ostringstream dystr;
#if CGAL_USE_EPECK
        dystr << direction.dy().exact();
#else
        dystr << setprecision(20) << direction.dy();
#endif
        obj->Set(SYMBOL(isolate, "dy"), String::NewFromUtf8(isolate, dystr.str().c_str()));

    } else {

        obj->Set(SYMBOL(isolate, "dx"), Number::New(isolate, CGAL::to_double(direction.dx())));
        obj->Set(SYMBOL(isolate, "dy"), Number::New(isolate, CGAL::to_double(direction.dy())));

    }

    return scope.Escape(obj);
}


void Direction2::IsEqual(const FunctionCallbackInfo<Value> &info)
{
    Isolate *isolate = info.GetIsolate();
    HandleScope scope(isolate);
    try {
        Direction_2 &thisDir = ExtractWrapped(info.This());
        ARGS_ASSERT(isolate, info.Length() == 1);
        ARGS_PARSE_LOCAL(isolate, Direction2::ParseArg, Direction_2, otherDir, info[0]);
        info.GetReturnValue().Set(Boolean::New(isolate, thisDir == otherDir));
    }
    catch (const exception &e) {
        isolate->ThrowException(String::NewFromUtf8(isolate, e.what()));
    }
}


void Direction2::IsLessThan(const FunctionCallbackInfo<Value> &info)
{
    Isolate *isolate = info.GetIsolate();
    HandleScope scope(isolate);
    try {
        Direction_2 &thisDir = ExtractWrapped(info.This());
        ARGS_ASSERT(isolate, info.Length() == 1);
        ARGS_PARSE_LOCAL(isolate, Direction2::ParseArg, Direction_2, otherDir, info[0]);
        info.GetReturnValue().Set(Boolean::New(isolate, thisDir < otherDir));
    }
    catch (const exception &e) {
        isolate->ThrowException(String::NewFromUtf8(isolate, e.what()));
    }
}


void Direction2::IsGreaterThan(const FunctionCallbackInfo<Value> &info)
{
    Isolate *isolate = info.GetIsolate();
    HandleScope scope(isolate);
    try {
        Direction_2 &thisDir = ExtractWrapped(info.This());
        ARGS_ASSERT(isolate, info.Length() == 1);
        ARGS_PARSE_LOCAL(isolate, Direction2::ParseArg, Direction_2, otherDir, info[0]);
        info.GetReturnValue().Set(Boolean::New(isolate, thisDir > otherDir));
    }
    catch (const exception &e) {
        isolate->ThrowException(String::NewFromUtf8(isolate, e.what()));
    }
}


void Direction2::IsCCWBetween(const FunctionCallbackInfo<Value> &info)
{
    Isolate *isolate = info.GetIsolate();
    HandleScope scope(isolate);
    try {
        Direction_2 &dir = ExtractWrapped(info.This());
        ARGS_ASSERT(isolate, info.Length() == 2);
        ARGS_PARSE_LOCAL(isolate, Direction2::ParseArg, Direction_2, d1, info[0]);
        ARGS_PARSE_LOCAL(isolate, Direction2::ParseArg, Direction_2, d2, info[1]);
        info.GetReturnValue().Set(Boolean::New(isolate, dir.counterclockwise_in_between(d1, d2)));
    }
    catch (const exception &e) {
        isolate->ThrowException(String::NewFromUtf8(isolate, e.what()));
    }
}


void Direction2::Opposite(const FunctionCallbackInfo<Value> &info)
{
    Isolate *isolate = info.GetIsolate();
    HandleScope scope(isolate);
    try {
        Direction_2 &dir = ExtractWrapped(info.This());
        info.GetReturnValue().Set(Direction2::New(isolate, -dir));
    }
    catch (const exception &e) {
        isolate->ThrowException(String::NewFromUtf8(isolate, e.what()));
    }
}


void Direction2::ToVector(const FunctionCallbackInfo<Value> &info)
{
    Isolate *isolate = info.GetIsolate();
    HandleScope scope(isolate);
    try {
        Direction_2 &dir = ExtractWrapped(info.This());
        info.GetReturnValue().Set(Vector2::New(isolate, dir.vector()));
    }
    catch (const exception &e) {
        isolate->ThrowException(String::NewFromUtf8(isolate, e.what()));
    }
}


void Direction2::DX(const FunctionCallbackInfo<Value> &info)
{
    Isolate *isolate = info.GetIsolate();
    HandleScope scope(isolate);
    try {
        Direction_2 &dir = ExtractWrapped(info.This());
        info.GetReturnValue().Set(Number::New(isolate, CGAL::to_double(dir.dx())));
    }
    catch (const exception &e) {
        isolate->ThrowException(String::NewFromUtf8(isolate, e.what()));
    }
}


void Direction2::DY(const FunctionCallbackInfo<Value> &info)
{
    Isolate *isolate = info.GetIsolate();
    HandleScope scope(isolate);
    try {
        Direction_2 &dir = ExtractWrapped(info.This());
        info.GetReturnValue().Set(Number::New(isolate, CGAL::to_double(dir.dy())));
    }
    catch (const exception &e) {
        isolate->ThrowException(String::NewFromUtf8(isolate, e.what()));
    }
}
