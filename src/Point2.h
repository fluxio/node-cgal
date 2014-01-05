#ifndef POINT2_H
#define POINT2_H

#include "CGALWrapper.h"
#include "cgal_types.h"
#include "v8.h"


// Wraps the CGAL::Point_2 class

class Point2 : public CGALWrapper<Point2, Point_2>
{
public:

    // The name to be used for our JS class.
    static const char *Name;

    // Add our function templates to the package exports, and return string to be used to name
    // the class and constructor in JS.  Called indirectly at module load time via the module
    // init function.
    static void RegisterMethods();

    // Attempt to parse a v8 argument into the CGAL Point_2 object referred to
    // by receiver.  Accepts either a Point2 JS object or a POD rep (e.g. [0,0]).
    // Returns true if parse was successful, false otherwise.
    static bool ParseArg(v8::Local<v8::Value> arg, Point_2 &receiver);

    // Convert a CGAL::Point_2 object to a POD v8 object.  This renders a point to
    // and array of two doubles, and may lose precision.
    static v8::Handle<v8::Value> ToPOD(const Point_2 &point);

private:

    //
    //----- The following methods will be callable from JS.  These will mostly match
    //      the semantics and names of CGAL::Point_2 methods.
    //

    // Get the named cartesian components of this Point2, as doubles.  May lose precision.
    static v8::Handle<v8::Value> X(const v8::Arguments &args);
    static v8::Handle<v8::Value> Y(const v8::Arguments &args);

};

#endif // !defined(POINT2_H)
