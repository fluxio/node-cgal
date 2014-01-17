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
    SetPrototypeMethod(sConstructorTemplate, "isFictitious", IsFictitious);
    SetPrototypeMethod(sConstructorTemplate, "isUnbounded", IsUnbounded);
    SetPrototypeMethod(sConstructorTemplate, "outerCCB", OuterCCB);
    SetPrototypeMethod(sConstructorTemplate, "holes", Holes);
    SetPrototypeMethod(sConstructorTemplate, "isolatedVertices", IsolatedVertices);
}


bool Arrangement2Face::ParseArg(Local<Value> arg, Arrangement_2::Face_handle &receiver)
{
    if (sConstructorTemplate->HasInstance(arg)) {

        // This supports e.g.: newface = new CGAL.Arrangment2.Face(oldface);

        receiver = ExtractWrapped(Local<Object>::Cast(arg));
        return true;

    } else {

        return false;

    }
}


Handle<Value> Arrangement2Face::ToPOD(const Arrangement_2::Face_handle &face)
{
    HandleScope scope;
    Local<Object> obj = Object::New();
    return scope.Close(obj);
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

//----- Explicit instantiations here since we are a shared library:

template class CGALWrapper<Arrangement2Face, Arrangement_2::Face_handle>;
