#ifndef SEGMENT2_H
#define SEGMENT2_H

#include "CGALWrapper.h"
#include "cgal_types.h"
#include "v8.h"


// Wraps the CGAL::Segment_2 class

class Segment2 : public CGALWrapper<Segment2, Segment_2>
{
public:

    // The name to be used for our JS class.
    static const char *Name;

    // Add our function templates to the package exports, and return string to be used to name
    // the class and constructor in JS.  Called indirectly at module load time via the module
    // init function.
    static void RegisterMethods();

    // Attempt to parse a v8 object into the CGAL Segment_2 object referred to by receiver. Accepts
    // either a Segment2 object or an object of form {source:,target:}, where the values of source
    // and target are Point2 constructables.  Returns true if parse was successful, false otherwise.
    static bool ParseArg(v8::Local<v8::Value> arg, Segment_2 &receiver);

    // Convert a CGAL::Segment_2 object to a POD v8 object.  This renders a segment to and object
    // {source: [double,double], target: [double, double]}, and may lose precision.
    static v8::Handle<v8::Value> ToPOD(const Segment_2 &segment);

private:

    //
    //----- The following methods will be callable from JS.  These will mostly match
    //      the semantics and names of CGAL::Segment_2 methods.
    //

    // Returns true if the endpoints of this edge have the same y coordinate.
    static v8::Handle<v8::Value> IsHorizontal(const v8::Arguments &args);

    // Returns true if the endpoints of this edge have the same x coordinate.
    static v8::Handle<v8::Value> IsVertical(const v8::Arguments &args);

};

#endif // !defined(SEGMENT2_H)
