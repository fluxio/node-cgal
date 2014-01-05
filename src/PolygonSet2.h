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

    // Attempt to parse a v8 value into the CGAL Polygon_with_holes_2 object referred to by
    // receiver.  Accepts either a PolygonWithHoles2 object, a Polygon2 constructable taken as the
    // boundary (no holes), or an object of form {boundary:,holes:}, where the value of boundary
    // is a Polygon2 constructable and the value of holes is an array of Polygon2 constructables.
    // Returns true if parse was successful, false otherwise.
    static bool ParseArg(v8::Local<v8::Value> arg, Polygon_set_2 &receiver);

    // Convert a CGAL::Polygon_with_holes_2 object to a POD v8 object.  This renders a poly with
    // holes as an object of form {boundary:,holes:}, where the value of boundary is the POD rep
    // of the boundary poly, and the value of holes is an array of POD reps of hole polys.  This
    // may lose precision.
    static v8::Handle<v8::Value> ToPOD(const Polygon_set_2 &polySet);

private:

    //
    //----- The following methods will be callable from JS.  These will mostly match
    //      the semantics and names of CGAL::Polygon_with_holes_2 methods.
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
