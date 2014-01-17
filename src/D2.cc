#include "D2.h"
#include "cgal_args.h"
#include "cgal_types.h"
#include "node.h"
#include "v8.h"
#include "Point2.h"
#include "Polygon2.h"
#include "PolygonWithHoles2.h"
#include "CGAL/Boolean_set_operations_2.h"

using namespace v8;
using namespace std;


void D2::Init(v8::Handle<v8::Object> exports)
{
    exports->Set(String::NewSymbol("doIntersect"), FunctionTemplate::New(DoIntersect)->GetFunction());
    exports->Set(String::NewSymbol("convexPartition2"), FunctionTemplate::New(ConvexPartition2)->GetFunction());
    exports->Set(String::NewSymbol("convexHull2"), FunctionTemplate::New(ConvexHull2)->GetFunction());
}

Handle<Value> DoIntersect(const Arguments &args)
{
    HandleScope scope;

    try {

        ARGS_ASSERT(args.Length() == 2);

        Polygon_2 poly0;
        if (Polygon2::ParseArg(args[0], poly0)) {

            Polygon_2 poly1;
            if (Polygon2::ParseArg(args[1], poly1)) {
                return scope.Close(Boolean::New(CGAL::do_intersect(poly0, poly1)));
            }

            Polygon_with_holes_2 pwh1;
            if (PolygonWithHoles2::ParseArg(args[1], pwh1)) {
                return scope.Close(Boolean::New(CGAL::do_intersect(poly0, pwh1)));
            }

            ARGS_ASSERT(false);
        }

        Polygon_with_holes_2 pwh0;
        if (PolygonWithHoles2::ParseArg(args[0], pwh0)) {

            Polygon_2 poly1;
            if (Polygon2::ParseArg(args[1], poly1)) {
                return scope.Close(Boolean::New(CGAL::do_intersect(pwh0, poly1)));
            }

            Polygon_with_holes_2 pwh1;
            if (PolygonWithHoles2::ParseArg(args[1], pwh1)) {
                return scope.Close(Boolean::New(CGAL::do_intersect(pwh0, pwh1)));
            }

            ARGS_ASSERT(false);
        }

        ARGS_ASSERT(false);
    }

    catch (const exception &e) {
        return ThrowException(String::New(e.what()));
    }

}

Handle<Value> ConvexPartition2(const Arguments& args)
{
    HandleScope scope;

    try {

        ARGS_ASSERT(args.Length() == 1);
        ARGS_PARSE_LOCAL(Polygon2::ParseArg, Polygon_2, inputPoly, args[0]);
        Partition_Traits partition_traits;
        list<Partition_Traits::Polygon_2> partition;
        CGAL::approx_convex_partition_2(
            inputPoly.vertices_begin(), inputPoly.vertices_end(),
            back_inserter(partition),
            partition_traits
        );

        Local<Array> array = Array::New();
        uint32_t i;
        list<Partition_Traits::Polygon_2>::iterator it;
        for(it=partition.begin(),i=0; it!=partition.end(); ++it,++i) {
            array->Set(i, Polygon2::New(Polygon_2(it->vertices_begin(), it->vertices_end())));
        }

        return scope.Close(array);
    }

    catch(const exception &e) {
        return ThrowException(String::New(e.what()));
    }

}


Handle<Value> ConvexHull2(const Arguments& args)
{
    HandleScope scope;

    try {

        ARGS_ASSERT(args.Length() == 1);
        ARGS_PARSE_LOCAL_SEQ(Point2::ParseSeqArg, list<Point_2>, points, args[0]);
        list<Point_2> hull;
        CGAL::convex_hull_2(points.begin(), points.end(), back_inserter(hull));

        Local<Array> array = Array::New();
        uint32_t i;
        list<Point_2>::iterator it;
        for(it=hull.begin(),i=0; it!=hull.end(); ++it,++i) {
            array->Set(i, Point2::New(*it));
        }

        return scope.Close(array);
    }

    catch(const exception &e) {
        return ThrowException(String::New(e.what()));
    }

}
