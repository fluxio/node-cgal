#ifndef LINE2_H
#define LINE2_H

#include "CGALWrapper.h"
#include "cgal_types.h"
#include "v8.h"


// Wraps the CGAL::Line_2 class

class Line2 : public CGALWrapper<Line2, Line_2>
{
public:

    // The name to be used for our JS class.
    static const char *Name;

    // Add our function templates to the package exports, and return string to be used to name
    // the class and constructor in JS.  Called indirectly at module load time via the module
    // init function.
    static void RegisterMethods();

    // Attempt to parse a v8 value into the CGAL Line_2 object referred to by receiver.  Accepts
    // either a Line2 object, an object of form {a:,b:,c:} where the values of a, b, and c are
    // doubles representing coefficients of the line equation ax + by + c = 0, or an object of the
    // form {p:,q:} where the values of p and q are Point2 constructables representing two points
    // on the line.  Returns true if parse was successful, false otherwise.
    static bool ParseArg(v8::Local<v8::Value> arg, Line_2 &receiver);

    // Convert a CGAL::Line_2 object to a POD v8 object of the form {a:,b:,c:} where the values of
    // a, b, and c are doubles representing coefficients of the line equation ax + by + c = 0.  This
    // may lose precision.
    static v8::Handle<v8::Value> ToPOD(const Line_2 &Line);

private:

    //
    //----- The following methods will be callable from JS.  These will mostly match
    //      the semantics and names of CGAL::Line_2 methods.
    //

    // Returns true if this line and line provided by argument are overlapping and
    // oriented in the same direction.
    static v8::Handle<v8::Value> IsEqual(const v8::Arguments &args);

    // Returns true if the a and b coefficients of the line are both zero.
    static v8::Handle<v8::Value> IsDegenerate(const v8::Arguments &args);

    // Returns true if the endpoints of this edge have the same y coordinate.
    static v8::Handle<v8::Value> IsHorizontal(const v8::Arguments &args);

    // Returns true if the endpoints of this edge have the same x coordinate.
    static v8::Handle<v8::Value> IsVertical(const v8::Arguments &args);

    // Returns an abitrary point on the line, given an integer index.  It holds that point(i) is
    // Returns the incident line oriented in the opposite direction.
    static v8::Handle<v8::Value> Opposite(const v8::Arguments &args);

};

#endif // !defined(LINE2_H)
