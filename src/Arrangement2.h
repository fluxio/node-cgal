#ifndef ARRANGEMENT2_H
#define ARRANGEMENT2_H

#include "CGALWrapper.h"
#include "cgal_types.h"
#include "v8.h"


// Wraps the CGAL::Arrangement_2 class

class Arrangement2 : public CGALWrapper<Arrangement2, Arrangement_2>
{
public:

    // The name to be used for our JS class.
    static const char *Name;

    // Add our function templates to the package exports, and return string to be used to name
    // the class and constructor in JS.  Called indirectly at module load time via the module
    // init function.
    static void RegisterMethods();

    // Attempt to parse a v8 argument into the CGAL Arrangement_2 object referred to
    // by receiver.  Accepts either an Arrangement2 JS object or an array of any two things that are
    // or can be constructed into Point2 objects (taken as start and end points of Arrangement).
    // Returns true if parse was successful, false otherwise.
    static bool ParseArg(v8::Local<v8::Value> arg, Arrangement_2 &receiver);

    // Convert a CGAL::Arrangement_2 object to a POD v8 object.  This renders a Arrangement to
    // an array of arrays of two doubles (start and end point coords), and may lose precision.
    static v8::Handle<v8::Value> ToPOD(const Arrangement_2 &Arrangement);

private:

    //
    //----- The following methods will be callable from JS.  These will mostly match
    //      the semantics and names of CGAL::Arrangement_2 methods.
    //

    static v8::Handle<v8::Value> ToString(const v8::Arguments &args);
    static v8::Handle<v8::Value> Clear(const v8::Arguments &args);
    static v8::Handle<v8::Value> IsEmpty(const v8::Arguments &args);
    static v8::Handle<v8::Value> IsValid(const v8::Arguments &args);
    static v8::Handle<v8::Value> InsertLines(const v8::Arguments &args); // deprecated
    static v8::Handle<v8::Value> Insert(const v8::Arguments &args);
    static v8::Handle<v8::Value> NumberOfVertices(const v8::Arguments &args);
    static v8::Handle<v8::Value> NumberOfIsolatedVertices(const v8::Arguments &args);
    static v8::Handle<v8::Value> Vertices(const v8::Arguments &args);
    static v8::Handle<v8::Value> NumberOfVerticesAtInfinity(const v8::Arguments &args);
    static v8::Handle<v8::Value> UnboundedFace(const v8::Arguments &args);
    static v8::Handle<v8::Value> NumberOfFaces(const v8::Arguments &args);
    static v8::Handle<v8::Value> Faces(const v8::Arguments &args);
    static v8::Handle<v8::Value> NumberOfUnboundedFaces(const v8::Arguments &args);
    static v8::Handle<v8::Value> UnboundedFaces(const v8::Arguments &args);
    static v8::Handle<v8::Value> FictitiousFace(const v8::Arguments &args);
    static v8::Handle<v8::Value> NumberOfHalfedges(const v8::Arguments &args);
    static v8::Handle<v8::Value> Halfedges(const v8::Arguments &args);
    static v8::Handle<v8::Value> NumberOfEdges(const v8::Arguments &args);
    static v8::Handle<v8::Value> Edges(const v8::Arguments &args);
    static v8::Handle<v8::Value> InsertInFaceInterior(const v8::Arguments &args);
    static v8::Handle<v8::Value> InsertFromLeftVertex(const v8::Arguments &args);
    static v8::Handle<v8::Value> InsertFromRightVertex(const v8::Arguments &args);
    static v8::Handle<v8::Value> InsertAtVertices(const v8::Arguments &args);
    static v8::Handle<v8::Value> ModifyVertex(const v8::Arguments &args);
    static v8::Handle<v8::Value> RemoveIsolatedVertex(const v8::Arguments &args);
    static v8::Handle<v8::Value> ModifyEdge(const v8::Arguments &args);
    static v8::Handle<v8::Value> SplitEdge(const v8::Arguments &args);
    static v8::Handle<v8::Value> MergeEdge(const v8::Arguments &args);
    static v8::Handle<v8::Value> RemoveEdge(const v8::Arguments &args);
    static v8::Handle<v8::Value> RemoveEdgeAndMerge(const v8::Arguments &args);

};

#endif // !defined(ARRANGEMENT2_H)
