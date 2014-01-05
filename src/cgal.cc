#include "cgal.h"
#include "cgal_args.h"
#include "cgal_types.h"
#include "node.h"
#include "v8.h"
#include "Arrangement2.h"
#include "BBox2.h"
#include "D2.h"
#include "Line2.h"
#include "NefPolyhedron2.h"
#include "Point2.h"
#include "Polygon2.h"
#include "PolygonSet2.h"
#include "PolygonWithHoles2.h"
#include "Segment2.h"

using namespace std;
using namespace v8;


namespace {

    enum {
        NEGATIVE = CGAL::NEGATIVE,
        ZERO = CGAL::ZERO,
        POSITIVE = CGAL::POSITIVE,
        RIGHT_TURN = CGAL::RIGHT_TURN,
        LEFT_TURN = CGAL::LEFT_TURN,
        CLOCKWISE = CGAL::CLOCKWISE,
        COUNTERCLOCKWISE = CGAL::COUNTERCLOCKWISE,
        COLLINEAR = CGAL::COLLINEAR,
        COPLANAR = CGAL::COPLANAR,
        DEGENERATE = CGAL::DEGENERATE,
        ON_NEGATIVE_SIDE = CGAL::ON_NEGATIVE_SIDE,
        ON_ORIENTED_BOUNDARY = CGAL::ON_ORIENTED_BOUNDARY,
        ON_POSITIVE_SIDE = CGAL::ON_POSITIVE_SIDE,
        SMALLER = CGAL::SMALLER,
        EQUAL = CGAL::EQUAL,
        LARGER = CGAL::LARGER,
        ON_UNBOUNDED_SIDE = CGAL::ON_UNBOUNDED_SIDE,
        ON_BOUNDARY = CGAL::ON_BOUNDARY,
        ON_BOUNDED_SIDE = CGAL::ON_BOUNDED_SIDE,
        OBTUSE = CGAL::OBTUSE,
        RIGHT = CGAL::RIGHT,
        ACUTE = CGAL::ACUTE
    };

}


NODE_MODULE(cgal, init);

void init(Handle<Object> exports)
{
    NODE_DEFINE_CONSTANT(exports, NEGATIVE);
    NODE_DEFINE_CONSTANT(exports, ZERO);
    NODE_DEFINE_CONSTANT(exports, POSITIVE);
    NODE_DEFINE_CONSTANT(exports, RIGHT_TURN);
    NODE_DEFINE_CONSTANT(exports, LEFT_TURN);
    NODE_DEFINE_CONSTANT(exports, CLOCKWISE);
    NODE_DEFINE_CONSTANT(exports, COUNTERCLOCKWISE);
    NODE_DEFINE_CONSTANT(exports, COLLINEAR);
    NODE_DEFINE_CONSTANT(exports, COPLANAR);
    NODE_DEFINE_CONSTANT(exports, DEGENERATE);
    NODE_DEFINE_CONSTANT(exports, ON_NEGATIVE_SIDE);
    NODE_DEFINE_CONSTANT(exports, ON_ORIENTED_BOUNDARY);
    NODE_DEFINE_CONSTANT(exports, ON_POSITIVE_SIDE);
    NODE_DEFINE_CONSTANT(exports, SMALLER);
    NODE_DEFINE_CONSTANT(exports, EQUAL);
    NODE_DEFINE_CONSTANT(exports, LARGER);
    NODE_DEFINE_CONSTANT(exports, ON_UNBOUNDED_SIDE);
    NODE_DEFINE_CONSTANT(exports, ON_BOUNDARY);
    NODE_DEFINE_CONSTANT(exports, ON_BOUNDED_SIDE);
    NODE_DEFINE_CONSTANT(exports, OBTUSE);
    NODE_DEFINE_CONSTANT(exports, RIGHT);
    NODE_DEFINE_CONSTANT(exports, ACUTE);

    Arrangement2::Init(exports);
    BBox2::Init(exports);
    D2::Init(exports);
    Line2::Init(exports);
    NefPolyhedron2::Init(exports);
    Point2::Init(exports);
    Polygon2::Init(exports);
    PolygonSet2::Init(exports);
    PolygonWithHoles2::Init(exports);
    Segment2::Init(exports);
}
