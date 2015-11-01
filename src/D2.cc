#include "D2.h"
#include "cgal_args.h"
#include "cgal_types.h"
#include "node.h"
#include "v8.h"
#include "AffTransformation2.h"
#include "Point2.h"
#include "Polygon2.h"
#include "PolygonWithHoles2.h"
#include "CGAL/Boolean_set_operations_2.h"

using namespace v8;
using namespace std;


void D2::Init(v8::Local<v8::Object> exports)
{
    NODE_SET_METHOD(exports, "doIntersect", DoIntersect);
    NODE_SET_METHOD(exports, "convexPartition2", ConvexPartition2);
    NODE_SET_METHOD(exports, "convexHull2", ConvexHull2);
    NODE_SET_METHOD(exports, "collinear", Collinear);
}


void DoIntersect(const FunctionCallbackInfo<Value> &info)
{
    Isolate *isolate = info.GetIsolate();
    HandleScope scope(isolate);

    try {

        ARGS_ASSERT(isolate, info.Length() == 2);

        Polygon_2 poly0;
        if (Polygon2::ParseArg(isolate, info[0], poly0)) {

            Polygon_2 poly1;
            if (Polygon2::ParseArg(isolate, info[1], poly1)) {
                info.GetReturnValue().Set(Boolean::New(isolate, CGAL::do_intersect(poly0, poly1)));
                return;
            }

            Polygon_with_holes_2 pwh1;
            if (PolygonWithHoles2::ParseArg(isolate, info[1], pwh1)) {
                info.GetReturnValue().Set(Boolean::New(isolate, CGAL::do_intersect(poly0, pwh1)));
                return;
            }

            ARGS_ASSERT(isolate, false);
        }

        Polygon_with_holes_2 pwh0;
        if (PolygonWithHoles2::ParseArg(isolate, info[0], pwh0)) {

            Polygon_2 poly1;
            if (Polygon2::ParseArg(isolate, info[1], poly1)) {
                info.GetReturnValue().Set(Boolean::New(isolate, CGAL::do_intersect(pwh0, poly1)));
                return;
            }

            Polygon_with_holes_2 pwh1;
            if (PolygonWithHoles2::ParseArg(isolate, info[1], pwh1)) {
                info.GetReturnValue().Set(Boolean::New(isolate, CGAL::do_intersect(pwh0, pwh1)));
                return;
            }

            ARGS_ASSERT(isolate, false);
        }

        ARGS_ASSERT(isolate, false);
    }

    catch (const exception &e) {
        isolate->ThrowException(String::NewFromUtf8(isolate, e.what()));
    }

}


void ConvexPartition2(const FunctionCallbackInfo<Value> &info)
{
    Isolate *isolate = info.GetIsolate();
    HandleScope scope(isolate);

    try {

        ARGS_ASSERT(isolate, info.Length() == 1);
        ARGS_PARSE_LOCAL(isolate, Polygon2::ParseArg, Polygon_2, inputPoly, info[0]);
        Partition_Traits partition_traits;
        list<Partition_Traits::Polygon_2> partition;
        CGAL::approx_convex_partition_2(
            inputPoly.vertices_begin(), inputPoly.vertices_end(),
            back_inserter(partition),
            partition_traits
        );

        Local<Array> array = Array::New(isolate);
        uint32_t i;
        list<Partition_Traits::Polygon_2>::iterator it;
        for(it=partition.begin(),i=0; it!=partition.end(); ++it,++i) {
            array->Set(i, Polygon2::New(isolate, Polygon_2(it->vertices_begin(), it->vertices_end())));
        }

        info.GetReturnValue().Set(array);
    }

    catch(const exception &e) {
        isolate->ThrowException(String::NewFromUtf8(isolate, e.what()));
    }

}


void ConvexHull2(const FunctionCallbackInfo<Value> &info)
{
    Isolate *isolate = info.GetIsolate();
    HandleScope scope(isolate);

    try {

        ARGS_ASSERT(isolate, info.Length() == 1);
        ARGS_PARSE_LOCAL_SEQ(isolate, Point2::ParseSeqArg, list<Point_2>, points, info[0]);
        list<Point_2> hull;
        CGAL::convex_hull_2(points.begin(), points.end(), back_inserter(hull));

        Local<Array> array = Array::New(isolate);
        uint32_t i;
        list<Point_2>::iterator it;
        for(it=hull.begin(),i=0; it!=hull.end(); ++it,++i) {
            array->Set(i, Point2::New(isolate, *it));
        }

        info.GetReturnValue().Set(array);
    }

    catch(const exception &e) {
        isolate->ThrowException(String::NewFromUtf8(isolate, e.what()));
    }

}


void Collinear(const FunctionCallbackInfo<Value> &info)
{
    Isolate *isolate = info.GetIsolate();
    HandleScope scope(isolate);

    try {

        ARGS_ASSERT(isolate, info.Length() == 3);
        ARGS_PARSE_LOCAL(isolate, Point2::ParseArg, Point_2, p0, info[0])
        ARGS_PARSE_LOCAL(isolate, Point2::ParseArg, Point_2, p1, info[1])
        ARGS_PARSE_LOCAL(isolate, Point2::ParseArg, Point_2, p2, info[2])

        info.GetReturnValue().Set(Boolean::New(isolate, CGAL::collinear(p0, p1, p2)));

    }

    catch(const exception &e) {
        isolate->ThrowException(String::NewFromUtf8(isolate, e.what()));
    }

}
