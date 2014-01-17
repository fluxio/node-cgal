#ifndef VECTOR2_H
#define VECTOR2_H

#include "CGALWrapper.h"
#include "cgal_types.h"
#include "v8.h"


// Wraps the CGAL::Vector_2 class

class Vector2 : public CGALWrapper<Vector2, Vector_2>
{
public:

    // The name to be used for our JS class.
    static const char *Name;

    // Add our function templates to the package exports, and return string to be used to name
    // the class and constructor in JS.  Called indirectly at module load time via the module
    // init function.
    static void RegisterMethods();

    // Attempt to parse a v8 object into the CGAL Vector_2 object referred to by receiver. Accepts
    // either a Vector2 object or ... Returns true if parse was successful, false otherwise.
    static bool ParseArg(v8::Local<v8::Value> arg, Vector_2 &receiver);

    // Convert a CGAL::Vector_2 object to a POD v8 object.  This renders a vector to an object
    // ... and may lose precision.
    static v8::Handle<v8::Value> ToPOD(const Vector_2 &vector);

private:

    //
    //----- The following methods will be callable from JS.  These will mostly match
    //      the semantics and names of CGAL::Vector_2 methods.
    //

};

#endif // !defined(VECTOR2_H)
