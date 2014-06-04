#ifndef POLYGONSET2_H
#define POLYGONSET2_H

#include "CGALWrapper.h"
#include "cgal_types.h"
#include "v8.h"


class PolygonSet2 : public CGALWrapper<PolygonSet2, Polygon_set_2>
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
    static bool ParseArg(v8::Local<v8::Value> arg, Polygon_set_2 &receiver);

    // Convert a CGAL object of the wrapped class to a POD v8 object.  If precise is set to false,
    // will attempt to render in terms of doubles for coordinates, and may lose precision.
    static v8::Handle<v8::Value> ToPOD(const Polygon_set_2 &polySet, bool precise=true);

private:

    //
    //----- The following methods will be callable from JS.  These will mostly match
    //      the semantics and names of the wrapped CGAL class.
    //

    static v8::Handle<v8::Value> PolygonsWithHoles(const v8::Arguments &args);
    static v8::Handle<v8::Value> NumPolygonsWithHoles(const v8::Arguments &args);
    static v8::Handle<v8::Value> IsEmpty(const v8::Arguments &args);
    static v8::Handle<v8::Value> IsPlane(const v8::Arguments &args);
    // static v8::Handle<v8::Value> Arrangement(const v8::Arguments &args);
    static v8::Handle<v8::Value> Clear(const v8::Arguments &args);
    static v8::Handle<v8::Value> Insert(const v8::Arguments &args);
    static v8::Handle<v8::Value> Complement(const v8::Arguments &args);
    static v8::Handle<v8::Value> Intersection(const v8::Arguments &args);
    static v8::Handle<v8::Value> Join(const v8::Arguments &args);
    static v8::Handle<v8::Value> Difference(const v8::Arguments &args);
    static v8::Handle<v8::Value> SymmetricDifference(const v8::Arguments &args);
    static v8::Handle<v8::Value> Intersects(const v8::Arguments &args);
    // static v8::Handle<v8::Value> Locate(const v8::Arguments &args);
    static v8::Handle<v8::Value> OrientedSide(const v8::Arguments &args);
    static v8::Handle<v8::Value> IsValid(const v8::Arguments &args);

};

#endif // !defined(POLYGONSET2_H)
