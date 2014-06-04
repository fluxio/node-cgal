#include "Arrangement2Halfedge.h"
#include "Arrangement2Vertex.h"
#include "Arrangement2Face.h"
#include "Curve2.h"
#include "cgal_args.h"

using namespace v8;
using namespace node;
using namespace std;


const char *Arrangement2Halfedge::Name = "Halfedge";


void Arrangement2Halfedge::RegisterMethods()
{
    SetPrototypeMethod(sConstructorTemplate, "toString", ToString);
    SetPrototypeMethod(sConstructorTemplate, "isFictitious", IsFictitious);
    SetPrototypeMethod(sConstructorTemplate, "source", Source);
    SetPrototypeMethod(sConstructorTemplate, "target", Target);
    SetPrototypeMethod(sConstructorTemplate, "face", Face);
    SetPrototypeMethod(sConstructorTemplate, "twin", Twin);
    SetPrototypeMethod(sConstructorTemplate, "prev", Prev);
    SetPrototypeMethod(sConstructorTemplate, "next", Next);
    SetPrototypeMethod(sConstructorTemplate, "ccb", CCB);
    SetPrototypeMethod(sConstructorTemplate, "curve", Curve);
}


bool Arrangement2Halfedge::ParseArg(Local<Value> arg, Arrangement_2::Halfedge_handle &receiver)
{
    if (sConstructorTemplate->HasInstance(arg)) {

        // This supports e.g.: newhalfedge = new CGAL.Arrangement2.Halfedge(oldhalfedge);

        receiver = ExtractWrapped(Local<Object>::Cast(arg));
        return true;

    } else {

        return false;

    }
}


Handle<Value> Arrangement2Halfedge::ToPOD(const Arrangement_2::Halfedge_handle &halfedge, bool precise)
{
    HandleScope scope;
    Local<Object> obj = Object::New();
    return scope.Close(obj);
}


Handle<Value> Arrangement2Halfedge::ToString(const v8::Arguments &args)
{
    HandleScope scope;
    Arrangement_2::Halfedge_handle &edge = ExtractWrapped(args.This());
    ostringstream str;
    str << "[object "  << Name << " " << edge.ptr() << " ";
    if (edge->is_fictitious()) {
        str << "FIC ";
    }
    str << "]";
    return scope.Close(String::New(str.str().c_str()));
}


Handle<Value> Arrangement2Halfedge::IsFictitious(const v8::Arguments &args)
{
    HandleScope scope;
    try {
        Arrangement_2::Halfedge_handle &edge = ExtractWrapped(args.This());
        return scope.Close(Boolean::New(edge->is_fictitious()));
    }
    catch (const exception &e) {
        return ThrowException(String::New(e.what()));
    }
}


Handle<Value> Arrangement2Halfedge::Source(const v8::Arguments &args)
{
    HandleScope scope;
    try {
        Arrangement_2::Halfedge_handle &edge = ExtractWrapped(args.This());
        return scope.Close(Arrangement2Vertex::New(edge->source()));
    }
    catch (const exception &e) {
        return ThrowException(String::New(e.what()));
    }
}


Handle<Value> Arrangement2Halfedge::Target(const v8::Arguments &args)
{
    HandleScope scope;
    try {
        Arrangement_2::Halfedge_handle &edge = ExtractWrapped(args.This());
        return scope.Close(Arrangement2Vertex::New(edge->target()));
    }
    catch (const exception &e) {
        return ThrowException(String::New(e.what()));
    }
}


Handle<Value> Arrangement2Halfedge::Face(const v8::Arguments &args)
{
    HandleScope scope;
    try {
        Arrangement_2::Halfedge_handle &edge = ExtractWrapped(args.This());
        return scope.Close(Arrangement2Face::New(edge->face()));
    }
    catch (const exception &e) {
        return ThrowException(String::New(e.what()));
    }
}


Handle<Value> Arrangement2Halfedge::Twin(const v8::Arguments &args)
{
    HandleScope scope;
    try {
        Arrangement_2::Halfedge_handle &edge = ExtractWrapped(args.This());
        return scope.Close(Arrangement2Halfedge::New(edge->twin()));
    }
    catch (const exception &e) {
        return ThrowException(String::New(e.what()));
    }
}


Handle<Value> Arrangement2Halfedge::Prev(const v8::Arguments &args)
{
    HandleScope scope;
    try {
        Arrangement_2::Halfedge_handle &edge = ExtractWrapped(args.This());
        return scope.Close(Arrangement2Halfedge::New(edge->prev()));
    }
    catch (const exception &e) {
        return ThrowException(String::New(e.what()));
    }
}


Handle<Value> Arrangement2Halfedge::Next(const v8::Arguments &args)
{
    HandleScope scope;
    try {
        Arrangement_2::Halfedge_handle &edge = ExtractWrapped(args.This());
        return scope.Close(Arrangement2Halfedge::New(edge->next()));
    }
    catch (const exception &e) {
        return ThrowException(String::New(e.what()));
    }
}


Handle<Value> Arrangement2Halfedge::CCB(const v8::Arguments &args)
{
    HandleScope scope;
    try {
        Arrangement_2::Halfedge_handle &edge = ExtractWrapped(args.This());
        Local<Array> array = Array::New();
        Arrangement_2::Ccb_halfedge_circulator first, curr;
        first = curr = edge->ccb();
        uint32_t i = 0;
        do {
            array->Set(i, Arrangement2Halfedge::New(curr));
        } while(++i,++curr != first);
        return scope.Close(array);
    }
    catch (const exception &e) {
        return ThrowException(String::New(e.what()));
    }
}


Handle<Value> Arrangement2Halfedge::Curve(const v8::Arguments &args)
{
    HandleScope scope;
    try {
        Arrangement_2::Halfedge_handle &edge = ExtractWrapped(args.This());
        return scope.Close(Curve2::New(edge->curve()));
    }
    catch (const exception &e) {
        return ThrowException(String::New(e.what()));
    }
}
