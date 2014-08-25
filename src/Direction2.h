#ifndef DIRECTION2_H
#define DIRECTION2_H

#include "CGALWrapper.h"
#include "cgal_types.h"
#include "v8.h"


class Direction2 : public CGALWrapper<Direction2, Direction_2>
{
public:

    // The name to be used for our JS class.
    static const char *Name;

    // Add our function templates to the package exports, and return string to be used to name
    // the class and constructor in JS.  Called indirectly at module load time via the module
    // init function.
    static void RegisterMethods();

    // Attempt to parse a v8 argument into the CGAL object referred to by receiver.  Returns true
    // if parse was successful, false otherwise.
    static bool ParseArg(v8::Local<v8::Value> arg, Direction_2 &receiver);

    // Convert a CGAL object of the wrapped class to a POD v8 object.  If precise is set to false,
    // will attempt to render in terms of doubles for coordinates, and may lose precision.
    static v8::Handle<v8::Value> ToPOD(const Direction_2 &direction, bool precise=true);

private:

    //
    //----- The following methods will be callable from JS.  These will mostly match
    //      the semantics and names of the wrapped CGAL class.
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
