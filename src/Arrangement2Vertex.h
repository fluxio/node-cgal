#ifndef ARRANGEMENT2VERTEX_H
#define ARRANGEMENT2VERTEX_H

#include "CGALWrapper.h"
#include "cgal_types.h"
#include "v8.h"


// Wraps the CGAL::Arrangement_2::Vertex_handle class

class Arrangement2Vertex : public CGALWrapper<Arrangement2Vertex, Arrangement_2::Vertex_handle>
{
public:

    // The name to be used for our JS class.
    static const char *Name;

    // Add our function templates to the package exports, and return string to be used to name
    // the class and constructor in JS.  Called indirectly at module load time via the module
    // init function.
    static void RegisterMethods();

    // Attempt to parse a v8 argument into the CGAL Arrangement_2 object referred to
    // by receiver.  Accepts either an Arrangement2.Vertex_handle JS object or ...
    // Returns true if parse was successful, false otherwise.
    static bool ParseArg(v8::Local<v8::Value> arg, Arrangement_2::Vertex_handle &receiver);

    // Convert a CGAL::Arrangement_2::Vertex_handle object to a POD v8 object.  This renders a 
    // vertex handle as ... and may lose precision.
    static v8::Handle<v8::Value> ToPOD(const Arrangement_2::Vertex_handle &Vertex);

private:

    //
    //----- The following methods will be callable from JS.  These will mostly match
    //      the semantics and names of CGAL::Arrangement_2::Vertex methods.
    //

    static v8::Handle<v8::Value> IsAtOpenBoundary(const v8::Arguments &args);
    static v8::Handle<v8::Value> IsIsolated(const v8::Arguments &args);
    static v8::Handle<v8::Value> Degree(const v8::Arguments &args);
    static v8::Handle<v8::Value> IncidentHalfedges(const v8::Arguments &args);
    static v8::Handle<v8::Value> Face(const v8::Arguments &args);
    static v8::Handle<v8::Value> Point(const v8::Arguments &args);
    static v8::Handle<v8::Value> ParameterSpaceInX(const v8::Arguments &args);
    static v8::Handle<v8::Value> ParameterSpaceInY(const v8::Arguments &args);

};

#endif // !defined(ARRANGEMENT2VERTEX_H)
