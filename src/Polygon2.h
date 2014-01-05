#ifndef POLYGON2_H
#define POLYGON2_H

#include "CGALWrapper.h"
#include "cgal_types.h"
#include "v8.h"


// Wraps the CGAL::Polygon_2 class.

class Polygon2 : public CGALWrapper<Polygon2, Polygon_2>
{
public:

    // The name to be used for our JS class.
    static const char *Name;

    // Add our function templates to the package exports, and return string to be used to name
    // the class and constructor in JS.  Called indirectly at module load time via the module
    // init function.
    static void RegisterMethods();

    // Attempt to parse a v8 argument into the CGAL Polygon_2 object referred to
    // by receiver.  Accepts either a Polygon2 JS object or an array of objects
    // that are constructable to Point2 objects. Returns true if parse was successful,
    // false otherwise.
    static bool ParseArg(v8::Local<v8::Value> arg, Polygon_2 &receiver);

    // Convert a CGAL::Polygon_2 object to a POD v8 object.  This renders a polygon to
    // an array of arrays of two doubles, and may lose precision.
    static v8::Handle<v8::Value> ToPOD(const Polygon_2 &poly);

private:

    //
    //----- The following methods will be callable from JS.  These will mostly match
    //      the semantics and names of CGAL::Point_2 methods.
    //

    // Test for equality: two polygons are equal iff there exists a cyclic permutation of the
    // vertices of p2 such that they are equal to the vertices of p1.
    static v8::Handle<v8::Value> IsEqual(const v8::Arguments &args);

    // Returns true of this polygon is simple (edges don't intersect except at vertices).
    static v8::Handle<v8::Value> IsSimple(const v8::Arguments &args);

    // Returns true of this polygon is convex.
    static v8::Handle<v8::Value> IsConvex(const v8::Arguments &args);

    // Returns constant CGAL.COUNTERCLOCKWISE, CGAL.CLOCKWISE, or CGAL::COLLINEAR).
    static v8::Handle<v8::Value> Orientation(const v8::Arguments &args);

    // Takes a point as an argument (Point2 or POD rep) and returns constant CGAL.POSITIVE_SIDE,
    // CGAL.NEGATIVE_SIDE, or CGAL.ON_ORIENTED_BOUNDARY, depending on where the point is in relation
    // to this polygon.
    static v8::Handle<v8::Value> OrientedSide(const v8::Arguments &args);

    // Takes a point as an argument (Point2 or POD rep) and returns constant CGAL.ON_BOUNDED_SIDE,
    // CGAL.ON_BOUNDARY or CGAL.ON_UNBOUNDED_SIDE, depending on where the point is in relation to
    // this polygon.
    static v8::Handle<v8::Value> BoundedSide(const v8::Arguments &args);

    // Returns the signed area of this polygon (negative if orientation is clockwise).
    static v8::Handle<v8::Value> Area(const v8::Arguments &args);

};

#endif // !defined(POLYGON2_H)
