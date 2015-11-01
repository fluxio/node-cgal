#include "Segment2.h"
#include "Point2.h"
#include "cgal_args.h"

using namespace v8;
using namespace node;
using namespace std;


const char *Segment2::Name = "Segment2";


void Segment2::RegisterMethods(Isolate *isolate)
{
    HandleScope scope(isolate);
    Local<FunctionTemplate> constructorTemplate = sConstructorTemplate.Get(isolate);
    NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "isVertical", IsVertical);
    NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "isHorizontal", IsHorizontal);
}


bool Segment2::ParseArg(Isolate *isolate, Local<Value> arg, Segment_2 &receiver)
{
    HandleScope scope(isolate);

    if (sConstructorTemplate.Get(isolate)->HasInstance(arg)) {
        receiver = ExtractWrapped(Local<Object>::Cast(arg));
        return true;
    }

    if (arg->IsObject()) {
        Local<Object> ends = Local<Object>::Cast(arg);

        Point_2 source, target;

        if (Point2::ParseArg(isolate, ends->Get(SYMBOL(isolate, "source")), source) &&
            Point2::ParseArg(isolate, ends->Get(SYMBOL(isolate, "target")), target))
        {
            receiver = Segment_2(source, target);
            return true;
        }

    }

    return false;
}


Local<Value> Segment2::ToPOD(Isolate *isolate, const Segment_2 &segment, bool precise)
{
    EscapableHandleScope scope(isolate);
    Local<Object> obj = Object::New(isolate);
    obj->Set(SYMBOL(isolate, "source"), Point2::ToPOD(isolate, segment.source(), precise));
    obj->Set(SYMBOL(isolate, "target"), Point2::ToPOD(isolate, segment.target(), precise));
    return scope.Escape(obj);
}


void Segment2::IsHorizontal(const FunctionCallbackInfo<Value> &info)
{
    Isolate *isolate = info.GetIsolate();
    HandleScope scope(isolate);
    try {
        Segment_2 &segment = ExtractWrapped(info.This());
        info.GetReturnValue().Set(Boolean::New(isolate, segment.is_horizontal()));
    }
    catch (const exception &e) {
        isolate->ThrowException(String::NewFromUtf8(isolate, e.what()));
    }
}


void Segment2::IsVertical(const FunctionCallbackInfo<Value> &info)
{
    Isolate *isolate = info.GetIsolate();
    HandleScope scope(isolate);
    try {
        Segment_2 &segment = ExtractWrapped(info.This());
        info.GetReturnValue().Set(Boolean::New(isolate, segment.is_vertical()));
    }
    catch (const exception &e) {
        isolate->ThrowException(String::NewFromUtf8(isolate, e.what()));
    }
}
