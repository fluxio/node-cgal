#ifndef DIRECTION2_H
#define DIRECTION2_H

#include "CGALWrapper.h"
#include "cgal_types.h"
#include "v8.h"


// Wraps the CGAL::Direction_2 class

class Direction2 : public CGALWrapper<Direction2, Direction_2>
{
public:

    // The name to be used for our JS class.
    static const char *Name;

    // Add our function templates to the package exports, and return string to be used to name
    // the class and constructor in JS.  Called indirectly at module load time via the module
    // init function.
    static void RegisterMethods();

    // Attempt to parse a v8 object into the CGAL Direction_2 object referred to by receiver.
    // Accepts either a Direction2 object or ... Returns true if parse was successful, false 
    // otherwise.
    static bool ParseArg(v8::Local<v8::Value> arg, Direction_2 &receiver);

    // Convert a CGAL::Direction_2 object to a POD v8 object.  This renders a direction to an 
    // object ... and may lose precision.
    static v8::Handle<v8::Value> ToPOD(const Direction_2 &direction);

private:

    //
    //----- The following methods will be callable from JS.  These will mostly match
    //      the semantics and names of CGAL::Direction_2 methods.
    //

    static v8::Handle<v8::Value> IsEqual(const v8::Arguments &args);
    static v8::Handle<v8::Value> IsLessThan(const v8::Arguments &args);
    static v8::Handle<v8::Value> IsGreaterThan(const v8::Arguments &args);
    static v8::Handle<v8::Value> IsCCWBetween(const v8::Arguments &args);
    static v8::Handle<v8::Value> Opposite(const v8::Arguments &args);
    static v8::Handle<v8::Value> ToVector(const v8::Arguments &args);
    static v8::Handle<v8::Value> DX(const v8::Arguments &args);
    static v8::Handle<v8::Value> DY(const v8::Arguments &args);

};

#endif // !defined(DIRECTION2_H)
