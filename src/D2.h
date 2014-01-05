#ifndef D2_H
#define D2_H

#include "node.h"
#include "v8.h"
#include "cgal_types.h"
#include "CGAL/convex_hull_2.h"

namespace D2
{
    // Add function templates for CGAL global 2d functions to the package exports.  Called at module
    // load time via the module init function.
    void Init(v8::Handle<v8::Object> exports);
}

// Takes a Polygon2 constructable and returns an array of Polygon2 objects that are an approximately
// optimal (within 4x) partition of the origin polygon into convex sub-polygons.
v8::Handle<v8::Value> ConvexPartition2(const v8::Arguments &args);

// Takes an array of Point2 constructables and returns the convex hull of those points as an array
// of Point2 objects.
v8::Handle<v8::Value> ConvexHull2(const v8::Arguments &args);

// Takes two Polygon2 or PolygonWithHoles2 constructables (or a mix) and returns true if they
// intersect.
v8::Handle<v8::Value> DoIntersect(const v8::Arguments &args);

#endif // !defined(D2_H)
