#include "Arrangement2.h"
#include "Line2.h"
#include "Point2.h"
#include "Polygon2.h"
#include "cgal_args.h"

using namespace v8;
using namespace node;
using namespace std;


const char *Arrangement2::Name = "Arrangement2";


void Arrangement2::RegisterMethods()
{
    SetPrototypeMethod(sConstructorTemplate, "insertLines", InsertLines);
    SetPrototypeMethod(sConstructorTemplate, "isEmpty", IsEmpty);
    SetPrototypeMethod(sConstructorTemplate, "numberOfVertices", NumberOfVertices);
    SetPrototypeMethod(sConstructorTemplate, "numberOfFaces", NumberOfFaces);
    SetPrototypeMethod(sConstructorTemplate, "numberOfEdges", NumberOfEdges);
}


bool Arrangement2::ParseArg(Local<Value> arg, Arrangement_2 &receiver)
{
    if (sConstructorTemplate->HasInstance(arg)) {

        // This supports e.g.: newArrangement = new CGAL.Arrangement2(oldArrangement);
        receiver = ExtractWrapped(Local<Object>::Cast(arg));
        return true;

    } else {

        return false;

    }
}


Handle<Value> Arrangement2::ToPOD(const Arrangement_2 &arrangement)
{
    HandleScope scope;
    Local<Object> obj = Object::New();
    obj->Set(String::NewSymbol("numFaces"), Number::New(arrangement.number_of_faces()));
    obj->Set(String::NewSymbol("numUnboundedFaces"),
        Number::New(arrangement.number_of_unbounded_faces()));
    obj->Set(String::NewSymbol("numBoundedFaces"),
        Number::New(arrangement.number_of_faces()-arrangement.number_of_unbounded_faces()));
    obj->Set(String::NewSymbol("numVertices"), Number::New(arrangement.number_of_vertices()));

    Local<Array> faceArray = Array::New();
    obj->Set(String::NewSymbol("boundedFaces"), faceArray);

    // POD-ify arrangement faces and assign to array within object.
    Arrangement_2::Face_const_iterator fit;
    uint32_t faceNum = 0;
    for(fit = arrangement.faces_begin(); fit != arrangement.faces_end(); ++fit){
        if (!fit->is_unbounded()){

            Polygon_2 poly;
            back_insert_iterator<Polygon_2> bit = back_inserter(poly);

            Arrangement_2::Ccb_halfedge_const_circulator circ = fit->outer_ccb();
            Arrangement_2::Ccb_halfedge_const_circulator curr = circ;
            // Step through face edges and add edge source point to poly.
            do { *bit++  = curr->source()->point(); } while (++curr != circ);

            // Add poly created from edge source points to face array.
            faceArray->Set(faceNum, Polygon2::ToPOD(poly));
            faceNum++;
        }
    }

    return scope.Close(obj);
}


Handle<Value> Arrangement2::InsertLines(const Arguments &args)
{
    HandleScope scope;

    // InsertLines expects to be called with an array of Line2 objects.
    ARGS_ASSERT(args[0]->IsArray());

    try {

        Arrangement_2 &arrangement = ExtractWrapped(args.This());

        Local<Array> lines = Local<Array>::Cast(args[0]);
        for(uint32_t i=0; i<lines->Length(); ++i) {
            ARGS_PARSE_LOCAL(Line2::ParseArg, Line_2, line, lines->Get(i));
            CGAL::insert(arrangement, line);
        }
        return Undefined();

    }

    catch (const exception &e) {
        return ThrowException(String::New(e.what()));
    }

}


Handle<Value> Arrangement2::IsEmpty(const Arguments &args)
{
    HandleScope scope;
    try {
        Arrangement_2 &arrangement = ExtractWrapped(args.This());
        return scope.Close(Boolean::New(arrangement.is_empty()));
    }
    catch (const exception &e) {
        return ThrowException(String::New(e.what()));
    }
}


Handle<Value> Arrangement2::NumberOfVertices(const Arguments &args)
{
    HandleScope scope;
    try {
        Arrangement_2 &arrangement = ExtractWrapped(args.This());
        return scope.Close(Number::New(arrangement.number_of_vertices()));
    }
    catch (const exception &e) {
        return ThrowException(String::New(e.what()));
    }
}


Handle<Value> Arrangement2::NumberOfFaces(const Arguments &args)
{
    HandleScope scope;
    try {
        Arrangement_2 &arrangement = ExtractWrapped(args.This());
        return scope.Close(Number::New(arrangement.number_of_faces()));
    }
    catch (const exception &e) {
        return ThrowException(String::New(e.what()));
    }
}


Handle<Value> Arrangement2::NumberOfEdges(const Arguments &args)
{
    HandleScope scope;
    try {
        Arrangement_2 &arrangement = ExtractWrapped(args.This());
        return scope.Close(Number::New(arrangement.number_of_edges()));
    }
    catch (const exception &e) {
        return ThrowException(String::New(e.what()));
    }
}


//----- Explicit instantiations here since we are a shared library:

template class CGALWrapper<Arrangement2, Arrangement_2>;
