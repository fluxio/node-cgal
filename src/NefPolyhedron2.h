#ifndef NEFPOLYHEDRON2_H
#define NEFPOLYHEDRON2_H

#include "CGALWrapper.h"
#include "cgal_types.h"
#include "v8.h"


// Wraps the CGAL::Nef_polyhedron_2 class

class NefPolyhedron2 : public CGALWrapper<NefPolyhedron2, Nef_polyhedron_2>
{
public:

    // The name to be used for our JS class.
    static const char *Name;

    // Add our function templates to the package exports, and return string to be used to name
    // the class and constructor in JS.  Called indirectly at module load time via the module
    // init function.
    static void RegisterMethods();

    // Attempt to parse a v8 argument into the CGAL Nef_polyhedron_2 object referred to by receiver.
    // Accepts either a NefPolyhedron2 JS object or ...  Returns true if parse was successful,
    // false otherwise.
    static bool ParseArg(v8::Local<v8::Value> arg, Nef_polyhedron_2 &receiver);

    // Convert a CGAL::Nef_polyhedron_2 object to a POD v8 object of the form... This may lose
    // precision.
    static v8::Handle<v8::Value> ToPOD(const Nef_polyhedron_2 &nef);

private:

    //
    //----- The following methods will be callable from JS.  These will mostly match
    //      the semantics and names of CGAL::Nef_polyhedron_2 methods.
    //

};

#endif // !defined(NEFPOLYHEDRON2_H)
