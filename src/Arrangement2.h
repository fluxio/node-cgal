#ifndef ARRANGEMENT2_H
#define ARRANGEMENT2_H

#include "CGALWrapper.h"
#include "cgal_types.h"
#include "v8.h"


class Arrangement2 : public CGALWrapper<Arrangement2, Arrangement_2>
{
public:

    // The name to be used for our JS class.
    static const char *Name;

    // Add our function templates to the package exports, and return string to be used to name
    // the class and constructor in JS.  Called indirectly at module load time via the module
    // init function.
    static void RegisterMethods(v8::Isolate *isolate);

    // Attempt to parse a v8 argument into the CGAL object referred to by receiver.  Returns true
    // if parse was successful, false otherwise.
    static bool ParseArg(v8::Isolate *isolate, v8::Local<v8::Value> arg, Arrangement_2 &receiver);

    // Convert a CGAL object of the wrapped class to a POD v8 object.  If precise is set to false,
    // will attempt to render in terms of doubles for coordinates, and may lose precision.
    static v8::Local<v8::Value> ToPOD(
        v8::Isolate *isolate, const Arrangement_2 &Arrangement, bool precise=true
    );

private:

    //
    //----- The following methods will be callable from JS.  These will mostly match
    //      the semantics and names of the wrapped CGAL class.
    //

    static void ToString(const v8::FunctionCallbackInfo<v8::Value> &args);
    static void Clear(const v8::FunctionCallbackInfo<v8::Value> &args);
    static void IsEmpty(const v8::FunctionCallbackInfo<v8::Value> &args);
    static void IsValid(const v8::FunctionCallbackInfo<v8::Value> &args);
    static void InsertLines(const v8::FunctionCallbackInfo<v8::Value> &args); // deprecated
    static void Insert(const v8::FunctionCallbackInfo<v8::Value> &args);
    static void NumberOfVertices(const v8::FunctionCallbackInfo<v8::Value> &args);
    static void NumberOfIsolatedVertices(const v8::FunctionCallbackInfo<v8::Value> &args);
    static void Vertices(const v8::FunctionCallbackInfo<v8::Value> &args);
    static void NumberOfVerticesAtInfinity(const v8::FunctionCallbackInfo<v8::Value> &args);
    static void UnboundedFace(const v8::FunctionCallbackInfo<v8::Value> &args);
    static void NumberOfFaces(const v8::FunctionCallbackInfo<v8::Value> &args);
    static void Faces(const v8::FunctionCallbackInfo<v8::Value> &args);
    static void NumberOfUnboundedFaces(const v8::FunctionCallbackInfo<v8::Value> &args);
    static void UnboundedFaces(const v8::FunctionCallbackInfo<v8::Value> &args);
    static void FictitiousFace(const v8::FunctionCallbackInfo<v8::Value> &args);
    static void NumberOfHalfedges(const v8::FunctionCallbackInfo<v8::Value> &args);
    static void Halfedges(const v8::FunctionCallbackInfo<v8::Value> &args);
    static void NumberOfEdges(const v8::FunctionCallbackInfo<v8::Value> &args);
    static void Edges(const v8::FunctionCallbackInfo<v8::Value> &args);
    static void InsertInFaceInterior(const v8::FunctionCallbackInfo<v8::Value> &args);
    static void InsertFromLeftVertex(const v8::FunctionCallbackInfo<v8::Value> &args);
    static void InsertFromRightVertex(const v8::FunctionCallbackInfo<v8::Value> &args);
    static void InsertAtVertices(const v8::FunctionCallbackInfo<v8::Value> &args);
    static void ModifyVertex(const v8::FunctionCallbackInfo<v8::Value> &args);
    static void RemoveIsolatedVertex(const v8::FunctionCallbackInfo<v8::Value> &args);
    static void ModifyEdge(const v8::FunctionCallbackInfo<v8::Value> &args);
    static void SplitEdge(const v8::FunctionCallbackInfo<v8::Value> &args);
    static void MergeEdge(const v8::FunctionCallbackInfo<v8::Value> &args);
    static void RemoveEdge(const v8::FunctionCallbackInfo<v8::Value> &args);
    static void RemoveEdgeAndMerge(const v8::FunctionCallbackInfo<v8::Value> &args);

};

#endif // !defined(ARRANGEMENT2_H)
