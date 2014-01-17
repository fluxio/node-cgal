#ifndef CURVE2_H
#define CURVE2_H

#include "CGALWrapper.h"
#include "cgal_types.h"
#include "v8.h"


// Wraps the CGAL::Arr_linear_traits_2::Curve_2 class

class Curve2 : public CGALWrapper<Curve2, Curve_2>
{
public:

    // The name to be used for our JS class.
    static const char *Name;

    // Add our function templates to the package exports, and return string to be used to name
    // the class and constructor in JS.  Called indirectly at module load time via the module
    // init function.
    static void RegisterMethods();

    // Attempt to parse a v8 argument into the CGAL Curve_2 object referred to by receiver.  Accepts 
    // either a Curve2 JS object or ... 
    // Returns true if parse was successful, false otherwise.
    static bool ParseArg(v8::Local<v8::Value> arg, Curve_2 &receiver);

    // Convert a CGAL Curve_2 object to a POD v8 object.  This renders a Curve_2 to ...
    // and may lose precision.
    static v8::Handle<v8::Value> ToPOD(const Curve_2 &curve);

private:

    //
    //----- The following methods will be callable from JS.  These will mostly match
    //      the semantics and names of CGAL Curve_2 methods.
    //

    static v8::Handle<v8::Value> IsSegment(const v8::Arguments &args);
    static v8::Handle<v8::Value> Segment(const v8::Arguments &args);
    static v8::Handle<v8::Value> IsRay(const v8::Arguments &args);
    static v8::Handle<v8::Value> Ray(const v8::Arguments &args);
    static v8::Handle<v8::Value> IsLine(const v8::Arguments &args);
    static v8::Handle<v8::Value> Line(const v8::Arguments &args);
    static v8::Handle<v8::Value> SupportingLine(const v8::Arguments &args);
    static v8::Handle<v8::Value> Source(const v8::Arguments &args);
    static v8::Handle<v8::Value> Target(const v8::Arguments &args);

};

#endif // !defined(CURVE2_H)
