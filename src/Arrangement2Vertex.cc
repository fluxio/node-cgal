#include "Arrangement2Vertex.h"
#include "Arrangement2Halfedge.h"
#include "Arrangement2Face.h"
#include "Point2.h"
#include "cgal_args.h"
#include <sstream>

using namespace v8;
using namespace node;
using namespace std;


const char *Arrangement2Vertex::Name = "Vertex";


void Arrangement2Vertex::RegisterMethods(Isolate *isolate)
{
    HandleScope scope(isolate);
    Local<FunctionTemplate> constructorTemplate = sConstructorTemplate.Get(isolate);
    NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "toString", ToString);
    NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "isAtOpenBoundary", IsAtOpenBoundary);
    NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "isIsolated", IsIsolated);
    NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "degree", Degree);
    NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "incidentHalfedges", IncidentHalfedges);
    NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "face", Face);
    NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "point", Point);
    NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "parameterSpaceInX", ParameterSpaceInX);
    NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "parameterSpaceInY", ParameterSpaceInY);
}


bool Arrangement2Vertex::ParseArg(Isolate *isolate, Local<Value> arg, Arrangement_2::Vertex_handle &receiver)
{
    if (sConstructorTemplate.Get(isolate)->HasInstance(arg)) {
        receiver = ExtractWrapped(Local<Object>::Cast(arg));
        return true;
    }

    return false;
}


Local<Value> Arrangement2Vertex::ToPOD(Isolate *isolate, const Arrangement_2::Vertex_handle &vertex, bool precise)
{
    EscapableHandleScope scope(isolate);
    Local<Object> obj = Object::New(isolate);
    return scope.Escape(obj);
}


void Arrangement2Vertex::ToString(const FunctionCallbackInfo<Value> &info)
{
    Isolate *isolate = info.GetIsolate();
    HandleScope scope(isolate);
    Arrangement_2::Vertex_handle &vertex = ExtractWrapped(info.This());
    ostringstream str;
    str << "[object "  << Name << " " << vertex.ptr() <<" ";
    if (vertex->is_at_open_boundary()) {
        switch(vertex->parameter_space_in_x()) {
        case CGAL::ARR_LEFT_BOUNDARY:
            str << "LEFT";
            break;
        case CGAL::ARR_RIGHT_BOUNDARY:
            str << "RIGHT";
            break;
        default:
            str << "INTERIOR";
            break;
        }
        str << " ";
        switch(vertex->parameter_space_in_y()) {
        case CGAL::ARR_TOP_BOUNDARY:
            str << "TOP";
            break;
        case CGAL::ARR_BOTTOM_BOUNDARY:
            str << "BOTTOM";
            break;
        default:
            str << "INTERIOR";
            break;
        }
    } else {
        str << vertex->point();
    }
    str << "]";
    info.GetReturnValue().Set(String::NewFromUtf8(isolate, str.str().c_str()));
}


void Arrangement2Vertex::IsAtOpenBoundary(const FunctionCallbackInfo<Value> &info)
{
    Isolate *isolate = info.GetIsolate();
    HandleScope scope(isolate);
    try {
        Arrangement_2::Vertex_handle &vertex = ExtractWrapped(info.This());
        info.GetReturnValue().Set(Boolean::New(isolate, vertex->is_at_open_boundary()));
    }
    catch (const exception &e) {
        isolate->ThrowException(String::NewFromUtf8(isolate, e.what()));
    }
}


void Arrangement2Vertex::IsIsolated(const FunctionCallbackInfo<Value> &info)
{
    Isolate *isolate = info.GetIsolate();
    HandleScope scope(isolate);
    try {
        Arrangement_2::Vertex_handle &vertex = ExtractWrapped(info.This());
        info.GetReturnValue().Set(Boolean::New(isolate, vertex->is_isolated()));
    }
    catch (const exception &e) {
        isolate->ThrowException(String::NewFromUtf8(isolate, e.what()));
    }
}


void Arrangement2Vertex::Degree(const FunctionCallbackInfo<Value> &info)
{
    Isolate *isolate = info.GetIsolate();
    HandleScope scope(isolate);
    try {
        Arrangement_2::Vertex_handle &vertex = ExtractWrapped(info.This());
        info.GetReturnValue().Set(Integer::New(isolate, vertex->degree()));
    }
    catch (const exception &e) {
        isolate->ThrowException(String::NewFromUtf8(isolate, e.what()));
    }
}


void Arrangement2Vertex::IncidentHalfedges(const FunctionCallbackInfo<Value> &info)
{
    Isolate *isolate = info.GetIsolate();
    HandleScope scope(isolate);
    try {
        Arrangement_2::Vertex_handle &vertex = ExtractWrapped(info.This());
        Local<Array> array = Array::New(isolate);
        Arrangement_2::Halfedge_around_vertex_circulator first, curr;
        first = curr = vertex->incident_halfedges();
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


void Arrangement2Vertex::Face(const FunctionCallbackInfo<Value> &info)
{
    Isolate *isolate = info.GetIsolate();
    HandleScope scope(isolate);
    try {
        Arrangement_2::Vertex_handle &vertex = ExtractWrapped(info.This());
        info.GetReturnValue().Set(Arrangement2Face::New(isolate, vertex->face()));
    }
    catch (const exception &e) {
        isolate->ThrowException(String::NewFromUtf8(isolate, e.what()));
    }
}


void Arrangement2Vertex::Point(const FunctionCallbackInfo<Value> &info)
{
    Isolate *isolate = info.GetIsolate();
    HandleScope scope(isolate);
    try {
        Arrangement_2::Vertex_handle &vertex = ExtractWrapped(info.This());
        info.GetReturnValue().Set(Point2::New(isolate, vertex->point()));
    }
    catch (const exception &e) {
        isolate->ThrowException(String::NewFromUtf8(isolate, e.what()));
    }
}


void Arrangement2Vertex::ParameterSpaceInX(const FunctionCallbackInfo<Value> &info)
{
    Isolate *isolate = info.GetIsolate();
    HandleScope scope(isolate);
    try {
        Arrangement_2::Vertex_handle &vertex = ExtractWrapped(info.This());
        info.GetReturnValue().Set(Integer::New(isolate, vertex->parameter_space_in_x()));
    }
    catch (const exception &e) {
        isolate->ThrowException(String::NewFromUtf8(isolate, e.what()));
    }
}


void Arrangement2Vertex::ParameterSpaceInY(const FunctionCallbackInfo<Value> &info)
{
    Isolate *isolate = info.GetIsolate();
    HandleScope scope(isolate);
    try {
        Arrangement_2::Vertex_handle &vertex = ExtractWrapped(info.This());
        info.GetReturnValue().Set(Integer::New(isolate, vertex->parameter_space_in_y()));
    }
    catch (const exception &e) {
        isolate->ThrowException(String::NewFromUtf8(isolate, e.what()));
    }
}
