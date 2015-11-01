#include "Arrangement2Halfedge.h"
#include "Arrangement2Vertex.h"
#include "Arrangement2Face.h"
#include "Curve2.h"
#include "cgal_args.h"

using namespace v8;
using namespace node;
using namespace std;


const char *Arrangement2Halfedge::Name = "Halfedge";


void Arrangement2Halfedge::RegisterMethods(Isolate *isolate)
{
    HandleScope scope(isolate);
    Local<FunctionTemplate> constructorTemplate = sConstructorTemplate.Get(isolate);
    NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "toString", ToString);
    NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "isFictitious", IsFictitious);
    NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "source", Source);
    NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "target", Target);
    NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "face", Face);
    NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "twin", Twin);
    NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "prev", Prev);
    NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "next", Next);
    NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "ccb", CCB);
    NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "curve", Curve);
}


bool Arrangement2Halfedge::ParseArg(Isolate *isolate, Local<Value> arg, Arrangement_2::Halfedge_handle &receiver)
{
    if (sConstructorTemplate.Get(isolate)->HasInstance(arg)) {
        receiver = ExtractWrapped(Local<Object>::Cast(arg));
        return true;
    }

    return false;
}


Local<Value> Arrangement2Halfedge::ToPOD(
    Isolate *isolate, const Arrangement_2::Halfedge_handle &halfedge, bool precise)
{
    EscapableHandleScope scope(isolate);
    Local<Object> obj = Object::New(isolate);
    return scope.Escape(obj);
}


void Arrangement2Halfedge::ToString(const FunctionCallbackInfo<Value> &info)
{
    Isolate *isolate = info.GetIsolate();
    HandleScope scope(isolate);
    Arrangement_2::Halfedge_handle &edge = ExtractWrapped(info.This());
    ostringstream str;
    str << "[object "  << Name << " " << edge.ptr() << " ";
    if (edge->is_fictitious()) {
        str << "FIC ";
    }
    str << "]";
    info.GetReturnValue().Set(String::NewFromUtf8(isolate, str.str().c_str()));
}


void Arrangement2Halfedge::IsFictitious(const FunctionCallbackInfo<Value> &info)
{
    Isolate *isolate = info.GetIsolate();
    HandleScope scope(isolate);
    try {
        Arrangement_2::Halfedge_handle &edge = ExtractWrapped(info.This());
        info.GetReturnValue().Set(Boolean::New(isolate, edge->is_fictitious()));
    }
    catch (const exception &e) {
        isolate->ThrowException(String::NewFromUtf8(isolate, e.what()));
    }
}


void Arrangement2Halfedge::Source(const FunctionCallbackInfo<Value> &info)
{
    Isolate *isolate = info.GetIsolate();
    HandleScope scope(isolate);
    try {
        Arrangement_2::Halfedge_handle &edge = ExtractWrapped(info.This());
        info.GetReturnValue().Set(Arrangement2Vertex::New(isolate, edge->source()));
    }
    catch (const exception &e) {
        isolate->ThrowException(String::NewFromUtf8(isolate, e.what()));
    }
}


void Arrangement2Halfedge::Target(const FunctionCallbackInfo<Value> &info)
{
    Isolate *isolate = info.GetIsolate();
    HandleScope scope(isolate);
    try {
        Arrangement_2::Halfedge_handle &edge = ExtractWrapped(info.This());
        info.GetReturnValue().Set(Arrangement2Vertex::New(isolate, edge->target()));
    }
    catch (const exception &e) {
        isolate->ThrowException(String::NewFromUtf8(isolate, e.what()));
    }
}


void Arrangement2Halfedge::Face(const FunctionCallbackInfo<Value> &info)
{
    Isolate *isolate = info.GetIsolate();
    HandleScope scope(isolate);
    try {
        Arrangement_2::Halfedge_handle &edge = ExtractWrapped(info.This());
        info.GetReturnValue().Set(Arrangement2Face::New(isolate, edge->face()));
    }
    catch (const exception &e) {
        isolate->ThrowException(String::NewFromUtf8(isolate, e.what()));
    }
}


void Arrangement2Halfedge::Twin(const FunctionCallbackInfo<Value> &info)
{
    Isolate *isolate = info.GetIsolate();
    HandleScope scope(isolate);
    try {
        Arrangement_2::Halfedge_handle &edge = ExtractWrapped(info.This());
        info.GetReturnValue().Set(Arrangement2Halfedge::New(isolate, edge->twin()));
    }
    catch (const exception &e) {
        isolate->ThrowException(String::NewFromUtf8(isolate, e.what()));
    }
}


void Arrangement2Halfedge::Prev(const FunctionCallbackInfo<Value> &info)
{
    Isolate *isolate = info.GetIsolate();
    HandleScope scope(isolate);
    try {
        Arrangement_2::Halfedge_handle &edge = ExtractWrapped(info.This());
        info.GetReturnValue().Set(Arrangement2Halfedge::New(isolate, edge->prev()));
    }
    catch (const exception &e) {
        isolate->ThrowException(String::NewFromUtf8(isolate, e.what()));
    }
}


void Arrangement2Halfedge::Next(const FunctionCallbackInfo<Value> &info)
{
    Isolate *isolate = info.GetIsolate();
    HandleScope scope(isolate);
    try {
        Arrangement_2::Halfedge_handle &edge = ExtractWrapped(info.This());
        info.GetReturnValue().Set(Arrangement2Halfedge::New(isolate, edge->next()));
    }
    catch (const exception &e) {
        isolate->ThrowException(String::NewFromUtf8(isolate, e.what()));
    }
}


void Arrangement2Halfedge::CCB(const FunctionCallbackInfo<Value> &info)
{
    Isolate *isolate = info.GetIsolate();
    HandleScope scope(isolate);
    try {
        Arrangement_2::Halfedge_handle &edge = ExtractWrapped(info.This());
        Local<Array> array = Array::New(isolate);
        Arrangement_2::Ccb_halfedge_circulator first, curr;
        first = curr = edge->ccb();
        uint32_t i = 0;
        do {
            array->Set(i, Arrangement2Halfedge::New(isolate, curr));
        } while(++i,++curr != first);
        info.GetReturnValue().Set(array);
    }
    catch (const exception &e) {
        isolate->ThrowException(String::NewFromUtf8(isolate, e.what()));
    }
}


void Arrangement2Halfedge::Curve(const FunctionCallbackInfo<Value> &info)
{
    Isolate *isolate = info.GetIsolate();
    HandleScope scope(isolate);
    try {
        Arrangement_2::Halfedge_handle &edge = ExtractWrapped(info.This());
        info.GetReturnValue().Set(Curve2::New(isolate, edge->curve()));
    }
    catch (const exception &e) {
        isolate->ThrowException(String::NewFromUtf8(isolate, e.what()));
    }
}
