#include "Curve2.h"
#include "Line2.h"
#include "Point2.h"
#include "Segment2.h"
#include "Ray2.h"
#include "cgal_args.h"

using namespace v8;
using namespace node;
using namespace std;


const char *Curve2::Name = "Curve2";


void Curve2::RegisterMethods(Isolate *isolate)
{
    HandleScope scope(isolate);
    Local<FunctionTemplate> constructorTemplate = sConstructorTemplate.Get(isolate);
    NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "isSegment", IsSegment);
    NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "segment", Segment);
    NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "isRay", IsRay);
    NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "ray", Ray);
    NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "isLine", IsLine);
    NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "line", Line);
    NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "supportingLine", SupportingLine);
    NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "source", Source);
    NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "target", Target);
}


bool Curve2::ParseArg(Isolate *isolate, Local<Value> arg, Curve_2 &receiver)
{
    HandleScope scope(isolate);

    if (sConstructorTemplate.Get(isolate)->HasInstance(arg)) {
        receiver = ExtractWrapped(Local<Object>::Cast(arg));
        return true;
    }

    Segment_2 segment;
    if (Segment2::ParseArg(isolate, arg, segment)) {
        receiver = Curve_2(segment);
        return true;
    }

    Line_2 line;
    if (Line2::ParseArg(isolate, arg, line)) {
        receiver = Curve_2(line);
        return true;
    }

    Ray_2 ray;
    if (Ray2::ParseArg(isolate, arg, ray)) {
        receiver = Curve_2(ray);
        return true;
    }

    return false;
}


Local<Value> Curve2::ToPOD(Isolate *isolate, const Curve_2 &curve, bool precise)
{
    EscapableHandleScope scope(isolate);
    Local<Object> obj = Object::New(isolate);
    return scope.Escape(obj);
}


void Curve2::IsSegment(const FunctionCallbackInfo<Value> &info)
{
    Isolate *isolate = info.GetIsolate();
    HandleScope scope(isolate);
    try {
        Curve_2 &curve = ExtractWrapped(info.This());
        info.GetReturnValue().Set(Boolean::New(isolate, curve.is_segment()));
    }
    catch (const exception &e) {
        isolate->ThrowException(String::NewFromUtf8(isolate, e.what()));
    }
}


void Curve2::Segment(const FunctionCallbackInfo<Value> &info)
{
    Isolate *isolate = info.GetIsolate();
    HandleScope scope(isolate);
    try {
        Curve_2 &curve = ExtractWrapped(info.This());
        info.GetReturnValue().Set(Segment2::New(isolate, curve.segment()));
    }
    catch (const exception &e) {
        isolate->ThrowException(String::NewFromUtf8(isolate, e.what()));
    }
}


void Curve2::IsRay(const FunctionCallbackInfo<Value> &info)
{
    Isolate *isolate = info.GetIsolate();
    HandleScope scope(isolate);
    try {
        Curve_2 &curve = ExtractWrapped(info.This());
        info.GetReturnValue().Set(Boolean::New(isolate, curve.is_ray()));
    }
    catch (const exception &e) {
        isolate->ThrowException(String::NewFromUtf8(isolate, e.what()));
    }
}


void Curve2::Ray(const FunctionCallbackInfo<Value> &info)
{
    Isolate *isolate = info.GetIsolate();
    HandleScope scope(isolate);
    try {
        Curve_2 &curve = ExtractWrapped(info.This());
        info.GetReturnValue().Set(Ray2::New(isolate, curve.ray()));
    }
    catch (const exception &e) {
        isolate->ThrowException(String::NewFromUtf8(isolate, e.what()));
    }
}


void Curve2::IsLine(const FunctionCallbackInfo<Value> &info)
{
    Isolate *isolate = info.GetIsolate();
    HandleScope scope(isolate);
    try {
        Curve_2 &curve = ExtractWrapped(info.This());
        info.GetReturnValue().Set(Boolean::New(isolate, curve.is_line()));
    }
    catch (const exception &e) {
        isolate->ThrowException(String::NewFromUtf8(isolate, e.what()));
    }
}


void Curve2::Line(const FunctionCallbackInfo<Value> &info)
{
    Isolate *isolate = info.GetIsolate();
    HandleScope scope(isolate);
    try {
        Curve_2 &curve = ExtractWrapped(info.This());
        info.GetReturnValue().Set(Line2::New(isolate, curve.line()));
    }
    catch (const exception &e) {
        isolate->ThrowException(String::NewFromUtf8(isolate, e.what()));
    }
}


void Curve2::SupportingLine(const FunctionCallbackInfo<Value> &info)
{
    Isolate *isolate = info.GetIsolate();
    HandleScope scope(isolate);
    try {
        Curve_2 &curve = ExtractWrapped(info.This());
        info.GetReturnValue().Set(Line2::New(isolate, curve.supporting_line()));
    }
    catch (const exception &e) {
        isolate->ThrowException(String::NewFromUtf8(isolate, e.what()));
    }
}


void Curve2::Source(const FunctionCallbackInfo<Value> &info)
{
    Isolate *isolate = info.GetIsolate();
    HandleScope scope(isolate);
    try {
        Curve_2 &curve = ExtractWrapped(info.This());
        info.GetReturnValue().Set(Point2::New(isolate, curve.source()));
    }
    catch (const exception &e) {
        isolate->ThrowException(String::NewFromUtf8(isolate, e.what()));
    }
}


void Curve2::Target(const FunctionCallbackInfo<Value> &info)
{
    Isolate *isolate = info.GetIsolate();
    HandleScope scope(isolate);
    try {
        Curve_2 &curve = ExtractWrapped(info.This());
        info.GetReturnValue().Set(Point2::New(isolate, curve.target()));
    }
    catch (const exception &e) {
        isolate->ThrowException(String::NewFromUtf8(isolate, e.what()));
    }
}
