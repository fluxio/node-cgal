#include "Arrangement2Face.h"
#include "Arrangement2Halfedge.h"
#include "Arrangement2Vertex.h"
#include "cgal_args.h"

using namespace v8;
using namespace node;
using namespace std;


const char *Arrangement2Face::Name = "Face";


void Arrangement2Face::RegisterMethods()
{
    SetPrototypeMethod(sConstructorTemplate, "toString", ToString);
    SetPrototypeMethod(sConstructorTemplate, "isFictitious", IsFictitious);
    SetPrototypeMethod(sConstructorTemplate, "isUnbounded", IsUnbounded);
    SetPrototypeMethod(sConstructorTemplate, "outerCCB", OuterCCB);
    SetPrototypeMethod(sConstructorTemplate, "holes", Holes);
    SetPrototypeMethod(sConstructorTemplate, "isolatedVertices", IsolatedVertices);
}


bool Arrangement2Face::ParseArg(Local<Value> arg, Arrangement_2::Face_handle &receiver)
{
    if (sConstructorTemplate->HasInstance(arg)) {
        receiver = ExtractWrapped(Local<Object>::Cast(arg));
        return true;
    }

    return false;
}


Handle<Value> Arrangement2Face::ToPOD(const Arrangement_2::Face_handle &face, bool precise)
{
    HandleScope scope;
    Local<Object> obj = Object::New();
    return scope.Close(obj);
}


Handle<Value> Arrangement2Face::ToString(const v8::Arguments &args)
{
    HandleScope scope;
    Arrangement_2::Face_handle &face = ExtractWrapped(args.This());
    ostringstream str;
    str << "[object "  << Name << " " << face.ptr() << " ";
    if (face->is_fictitious()) {
        str << "FIC ";
    } else if (face->is_unbounded()) {
        str << "UNB ";
    }
    int numedges = 0;
    if (face->has_outer_ccb()) {
        Arrangement_2::Ccb_halfedge_circulator e, e0;
        e = e0 = face->outer_ccb();
        do { ++numedges; } while(++e != e0);
    }
    str << "E:" << numedges << " ";
    int numholes = 0;
    Arrangement_2::Hole_iterator h;
    for(h=face->holes_begin(); h!=face->holes_end(); ++h,++numholes) {}
    str << "H:" << numholes << " ";
    int numisolated = 0;
    Arrangement_2::Isolated_vertex_iterator i;
    for(i=face->isolated_vertices_begin(); i!=face->isolated_vertices_end(); ++i,++numisolated) {}
    str << "I:" << numisolated << "]";
    return scope.Close(String::New(str.str().c_str()));
}


Handle<Value> Arrangement2Face::IsFictitious(const v8::Arguments &args)
{
    HandleScope scope;
    try {
        Arrangement_2::Face_handle &face = ExtractWrapped(args.This());
        return scope.Close(Boolean::New(face->is_fictitious()));
    }
    catch (const exception &e) {
        return ThrowException(String::New(e.what()));
    }
}


Handle<Value> Arrangement2Face::IsUnbounded(const v8::Arguments &args)
{
    HandleScope scope;
    try {
        Arrangement_2::Face_handle &face = ExtractWrapped(args.This());
        return scope.Close(Boolean::New(face->is_unbounded()));
    }
    catch (const exception &e) {
        return ThrowException(String::New(e.what()));
    }
}


Handle<Value> Arrangement2Face::OuterCCB(const v8::Arguments &args)
{
    HandleScope scope;
    try {
        Arrangement_2::Face_handle &face = ExtractWrapped(args.This());
        Local<Array> array = Array::New();
        if (face->has_outer_ccb()) {
            Arrangement_2::Ccb_halfedge_circulator first, curr;
            first = curr = face->outer_ccb();
            uint32_t i = 0;
            do {
                array->Set(i, Arrangement2Halfedge::New(curr));
            } while(++i,++curr != first);
        }
        return scope.Close(array);
    }
    catch (const exception &e) {
        return ThrowException(String::New(e.what()));
    }
}


Handle<Value> Arrangement2Face::Holes(const v8::Arguments &args)
{
    HandleScope scope;
    try {
        Arrangement_2::Face_handle &face = ExtractWrapped(args.This());
        Local<Array> array = Array::New();
        Arrangement_2::Hole_iterator it;
        uint32_t i;
        for(it=face->holes_begin(),i=0; it!=face->holes_end(); ++it,++i) {
            Local<Array> hole = Array::New();
            array->Set(i, hole);
            Arrangement_2::Ccb_halfedge_circulator first, curr;
            first = curr = *it;
            uint32_t j = 0;
            do {
                hole->Set(j, Arrangement2Halfedge::New(curr));
            } while(++j,++curr != first);
        }
        return scope.Close(array);
    }
    catch (const exception &e) {
        return ThrowException(String::New(e.what()));
    }
}


Handle<Value> Arrangement2Face::IsolatedVertices(const v8::Arguments &args)
{
    HandleScope scope;
    try {
        Arrangement_2::Face_handle &face = ExtractWrapped(args.This());
        Local<Array> array = Array::New();
        Arrangement_2::Isolated_vertex_iterator it;
        uint32_t i;
        for(it=face->isolated_vertices_begin(),i=0; it!=face->isolated_vertices_end(); ++it,++i) {
            array->Set(i, Arrangement2Vertex::New(it));
        }
        return scope.Close(array);
    }
    catch (const exception &e) {
        return ThrowException(String::New(e.what()));
    }
}
