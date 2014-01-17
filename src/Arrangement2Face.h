#ifndef ARRANGEMENT2FACE_H
#define ARRANGEMENT2FACE_H

#include "CGALWrapper.h"
#include "cgal_types.h"
#include "v8.h"


// Wraps the CGAL::Arrangement_2::Face_handle class

class Arrangement2Face : public CGALWrapper<Arrangement2Face, Arrangement_2::Face_handle>
{
public:

    // The name to be used for our JS class.
    static const char *Name;

    // Add our function templates to the package exports, and return string to be used to name
    // the class and constructor in JS.  Called indirectly at module load time via the module
    // init function.
    static void RegisterMethods();

    // Attempt to parse a v8 argument into the CGAL Arrangement_2::Face_handle object referred to
    // by receiver.  Accepts either an Arrangement2.Face JS object or ...
    // Returns true if parse was successful, false otherwise.
    static bool ParseArg(v8::Local<v8::Value> arg, Arrangement_2::Face_handle &receiver);

    // Convert a CGAL::Arrangement_2::Face_handle object to a POD v8 object.  This renders an
    // face handle as ... and may lose precision.
    static v8::Handle<v8::Value> ToPOD(const Arrangement_2::Face_handle &face);

private:

    //
    //----- The following methods will be callable from JS.  These will mostly match
    //      the semantics and names of CGAL::Arrangement_2::Face methods.
    //

    static v8::Handle<v8::Value> IsFictitious(const v8::Arguments &args);
    static v8::Handle<v8::Value> IsUnbounded(const v8::Arguments &args);
    static v8::Handle<v8::Value> OuterCCB(const v8::Arguments &args);
    static v8::Handle<v8::Value> Holes(const v8::Arguments &args);
    static v8::Handle<v8::Value> IsolatedVertices(const v8::Arguments &args);

};

#endif // !defined(ARRANGEMENT2FACE_H)
