#include "Arrangement2Vertex.h"
#include "Arrangement2Halfedge.h"
#include "Arrangement2Face.h"
#include "Point2.h"
#include "cgal_args.h"

using namespace v8;
using namespace node;
using namespace std;


const char *Arrangement2Vertex::Name = "Vertex";


void Arrangement2Vertex::RegisterMethods()
{
    SetPrototypeMethod(sConstructorTemplate, "isAtOpenBoundary", IsAtOpenBoundary);
    SetPrototypeMethod(sConstructorTemplate, "isIsolated", IsIsolated);
    SetPrototypeMethod(sConstructorTemplate, "degree", Degree);
    SetPrototypeMethod(sConstructorTemplate, "incidentHalfedges", IncidentHalfedges);
    SetPrototypeMethod(sConstructorTemplate, "face", Face);
    SetPrototypeMethod(sConstructorTemplate, "point", Point);
    SetPrototypeMethod(sConstructorTemplate, "parameterSpaceInX", ParameterSpaceInX);
    SetPrototypeMethod(sConstructorTemplate, "parameterSpaceInY", ParameterSpaceInY);
}


bool Arrangement2Vertex::ParseArg(Local<Value> arg, Arrangement_2::Vertex_handle &receiver)
{
    if (sConstructorTemplate->HasInstance(arg)) {

        // This supports e.g.: newvertex = new CGAL.Arrangement2.Vertex(oldvertex);

        receiver = ExtractWrapped(Local<Object>::Cast(arg));
        return true;

    } else {

        return false;

    }
}


Handle<Value> Arrangement2Vertex::ToPOD(const Arrangement_2::Vertex_handle &vertex)
{
    HandleScope scope;
    Local<Object> obj = Object::New();
    return scope.Close(obj);
}


Handle<Value> Arrangement2Vertex::IsAtOpenBoundary(const v8::Arguments &args)
{
    HandleScope scope;
    try {
        Arrangement_2::Vertex_handle &vertex = ExtractWrapped(args.This());
        return scope.Close(Boolean::New(vertex->is_at_open_boundary()));
    }
    catch (const exception &e) {
        return ThrowException(String::New(e.what()));
    }
}


Handle<Value> Arrangement2Vertex::IsIsolated(const v8::Arguments &args)
{
    HandleScope scope;
    try {
        Arrangement_2::Vertex_handle &vertex = ExtractWrapped(args.This());
        return scope.Close(Boolean::New(vertex->is_isolated()));
    }
    catch (const exception &e) {
        return ThrowException(String::New(e.what()));
    }
}


Handle<Value> Arrangement2Vertex::Degree(const v8::Arguments &args)
{
    HandleScope scope;
    try {
        Arrangement_2::Vertex_handle &vertex = ExtractWrapped(args.This());
        return scope.Close(Integer::New(vertex->degree()));
    }
    catch (const exception &e) {
        return ThrowException(String::New(e.what()));
    }
}


Handle<Value> Arrangement2Vertex::IncidentHalfedges(const v8::Arguments &args)
{
    HandleScope scope;
    try {
        Arrangement_2::Vertex_handle &vertex = ExtractWrapped(args.This());
        Local<Array> array = Array::New();
        Arrangement_2::Halfedge_around_vertex_circulator first, curr;
        first = curr = vertex->incident_halfedges();
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


Handle<Value> Arrangement2Vertex::Face(const v8::Arguments &args)
{
    HandleScope scope;
    try {
        Arrangement_2::Vertex_handle &vertex = ExtractWrapped(args.This());
        return scope.Close(Arrangement2Face::New(vertex->face()));
    }
    catch (const exception &e) {
        return ThrowException(String::New(e.what()));
    }
}


Handle<Value> Arrangement2Vertex::Point(const v8::Arguments &args)
{
    HandleScope scope;
    try {
        Arrangement_2::Vertex_handle &vertex = ExtractWrapped(args.This());
        return scope.Close(Point2::New(vertex->point()));
    }
    catch (const exception &e) {
        return ThrowException(String::New(e.what()));
    }
}


Handle<Value> Arrangement2Vertex::ParameterSpaceInX(const v8::Arguments &args)
{
    HandleScope scope;
    try {
        Arrangement_2::Vertex_handle &vertex = ExtractWrapped(args.This());
        return scope.Close(Integer::New(vertex->parameter_space_in_x()));
    }
    catch (const exception &e) {
        return ThrowException(String::New(e.what()));
    }
}


Handle<Value> Arrangement2Vertex::ParameterSpaceInY(const v8::Arguments &args)
{
    HandleScope scope;
    try {
        Arrangement_2::Vertex_handle &vertex = ExtractWrapped(args.This());
        return scope.Close(Integer::New(vertex->parameter_space_in_y()));
    }
    catch (const exception &e) {
        return ThrowException(String::New(e.what()));
    }
}

//----- Explicit instantiations here since we are a shared library:

template class CGALWrapper<Arrangement2Vertex, Arrangement_2::Vertex_handle>;
