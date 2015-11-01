#ifndef POLYGONWITHHOLES2_H
#define POLYGONWITHHOLES2_H

#include "CGALWrapper.h"
#include "cgal_types.h"
#include "v8.h"


class PolygonWithHoles2 : public CGALWrapper<PolygonWithHoles2, Polygon_with_holes_2>
{
public:

    // The name to be used for our JS class.
    static const char *Name;

    // Add our function templates to the package exports, and return string to be used to name
    // the class and constructor in JS.  Called indirectly at module load time via the module
    // init function.
    static void RegisterMethods(v8::Isolate *isolate);

    // Attempt to parse a v8 argument into the CGAL object referred to by receiver.  Returns true
    // if parse was successful, false otherwise.
    static bool ParseArg(v8::Isolate *isolate, v8::Local<v8::Value> arg, Polygon_with_holes_2 &receiver);

    // Convert a CGAL object of the wrapped class to a POD v8 object.  If precise is set to false,
    // will attempt to render in terms of doubles for coordinates, and may lose precision.
    static v8::Local<v8::Value> ToPOD(v8::Isolate *isolate, const Polygon_with_holes_2 &poly, bool precise=true);

private:

    //
    //----- The following methods will be callable from JS.  These will mostly match
    //      the semantics and names of the wrapped CGAL class.
    //

    static void IsEqual(const v8::FunctionCallbackInfo<v8::Value> &info);
    static void Outer(const v8::FunctionCallbackInfo<v8::Value> &info);
    static void Holes(const v8::FunctionCallbackInfo<v8::Value> &info);
    static void IsUnbounded(const v8::FunctionCallbackInfo<v8::Value> &info);

};

#endif // !defined(POLYGONWITHHOLES2_H)
