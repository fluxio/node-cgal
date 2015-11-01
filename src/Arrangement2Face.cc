#include "Arrangement2Face.h"
#include "Arrangement2Halfedge.h"
#include "Arrangement2Vertex.h"
#include "cgal_args.h"

using namespace v8;
using namespace node;
using namespace std;


const char *Arrangement2Face::Name = "Face";


void Arrangement2Face::RegisterMethods(Isolate *isolate)
{
    HandleScope scope(isolate);
    Local<FunctionTemplate> constructorTemplate = sConstructorTemplate.Get(isolate);
    NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "toString", ToString);
    NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "isFictitious", IsFictitious);
    NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "isUnbounded", IsUnbounded);
    NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "outerCCB", OuterCCB);
    NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "holes", Holes);
    NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "isolatedVertices", IsolatedVertices);
}


bool Arrangement2Face::ParseArg(Isolate *isolate, Local<Value> arg, Arrangement_2::Face_handle &receiver)
{
    if (sConstructorTemplate.Get(isolate)->HasInstance(arg)) {
        receiver = ExtractWrapped(Local<Object>::Cast(arg));
        return true;
    }

    return false;
}


Local<Value> Arrangement2Face::ToPOD(Isolate *isolate, const Arrangement_2::Face_handle &face, bool precise)
{
    EscapableHandleScope scope(isolate);
    Local<Object> obj = Object::New(isolate);
    return scope.Escape(obj);
}


void Arrangement2Face::ToString(const v8::FunctionCallbackInfo<v8::Value> &info)
{
    Isolate *isolate = info.GetIsolate();
    HandleScope scope(isolate);
    Arrangement_2::Face_handle &face = ExtractWrapped(info.This());
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
    info.GetReturnValue().Set(String::NewFromUtf8(isolate, str.str().c_str()));
}


void Arrangement2Face::IsFictitious(const v8::FunctionCallbackInfo<v8::Value> &info)
{
    Isolate *isolate = info.GetIsolate();
    HandleScope scope(isolate);
    try {
        Arrangement_2::Face_handle &face = ExtractWrapped(info.This());
        info.GetReturnValue().Set(Boolean::New(isolate, face->is_fictitious()));
    }
    catch (const exception &e) {
        isolate->ThrowException(String::NewFromUtf8(isolate, e.what()));
    }
}


void Arrangement2Face::IsUnbounded(const v8::FunctionCallbackInfo<v8::Value> &info)
{
    Isolate *isolate = info.GetIsolate();
    HandleScope scope(isolate);
    try {
        Arrangement_2::Face_handle &face = ExtractWrapped(info.This());
        info.GetReturnValue().Set(Boolean::New(isolate, face->is_unbounded()));
    }
    catch (const exception &e) {
        isolate->ThrowException(String::NewFromUtf8(isolate, e.what()));
    }
}


void Arrangement2Face::OuterCCB(const v8::FunctionCallbackInfo<v8::Value> &info)
{
    Isolate *isolate = info.GetIsolate();
    EscapableHandleScope scope(isolate);
    try {
        Arrangement_2::Face_handle &face = ExtractWrapped(info.This());
        Local<Array> array = Array::New(isolate);
        if (face->has_outer_ccb()) {
            Arrangement_2::Ccb_halfedge_circulator first, curr;
            first = curr = face->outer_ccb();
            uint32_t i = 0;
            do {
                array->Set(i, Arrangement2Halfedge::New(isolate, curr));
            } while(++i,++curr != first);
        }
        info.GetReturnValue().Set(scope.Escape(array));
    }
    catch (const exception &e) {
        isolate->ThrowException(String::NewFromUtf8(isolate, e.what()));
    }
}


void Arrangement2Face::Holes(const v8::FunctionCallbackInfo<v8::Value> &info)
{
    Isolate *isolate = info.GetIsolate();
    EscapableHandleScope scope(isolate);
    try {
        Arrangement_2::Face_handle &face = ExtractWrapped(info.This());
        Local<Array> array = Array::New(isolate);
        Arrangement_2::Hole_iterator it;
        uint32_t i;
        for(it=face->holes_begin(),i=0; it!=face->holes_end(); ++it,++i) {
            Local<Array> hole = Array::New(isolate);
            array->Set(i, hole);
            Arrangement_2::Ccb_halfedge_circulator first, curr;
            first = curr = *it;
            uint32_t j = 0;
            do {
                hole->Set(j, Arrangement2Halfedge::New(isolate, curr));
            } while(++j,++curr != first);
        }
        info.GetReturnValue().Set(scope.Escape(array));
    }
    catch (const exception &e) {
        isolate->ThrowException(String::NewFromUtf8(isolate, e.what()));
    }
}


void Arrangement2Face::IsolatedVertices(const v8::FunctionCallbackInfo<v8::Value> &info)
{
    Isolate* isolate = info.GetIsolate();
    EscapableHandleScope scope(isolate);
    try {
        Arrangement_2::Face_handle &face = ExtractWrapped(info.This());
        Local<Array> array = Array::New(isolate);
        Arrangement_2::Isolated_vertex_iterator it;
        uint32_t i;
        for(it=face->isolated_vertices_begin(),i=0; it!=face->isolated_vertices_end(); ++it,++i) {
            array->Set(i, Arrangement2Vertex::New(isolate, it));
        }
        info.GetReturnValue().Set(scope.Escape(array));
    }
    catch (const exception &e) {
        isolate->ThrowException(String::NewFromUtf8(isolate, e.what()));
    }
}
