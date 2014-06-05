#ifndef CGAL_TYPES_H
#define CGAL_TYPES_H

//
// If CGAL_USE_APPROX is defined, we parameterize the kernel stack in the wrappers to be based
// on the Vannevar approximate interval number type; otherwise we configure with the stock GCAL
// epick (exact predicates, inexact constructions) kernel.
//
// The Vannevar approximate interval stack is still early in development and not included in this
// release, but we hope to include it soon in an updated release.
//

#if defined(CGAL_USE_APPROX)
#include "CGAL/Interval_nt_approx.h"
#include "CGAL/Arr_linear_traits_2_approx.h"
#elif defined(CGAL_USE_EPECK)
#include "CGAL/Exact_predicates_exact_constructions_kernel.h"
#include "CGAL/Arr_linear_traits_2.h"
#else
#include "CGAL/Exact_predicates_inexact_constructions_kernel.h"
#include "CGAL/Arr_linear_traits_2.h"
#endif
#include "CGAL/number_utils.h"
#include "CGAL/Extended_cartesian.h"
#include "CGAL/Bbox_2.h"
#include "CGAL/Partition_traits_2.h"
#include "CGAL/partition_2.h"
#include "CGAL/Nef_polyhedron_2.h"
#include "CGAL/Segment_2.h"
#include "CGAL/Line_2.h"
#include "CGAL/Ray_2.h"
#include "CGAL/Arrangement_2.h"
#include "CGAL/Polygon_with_holes_2.h"
#include "CGAL/Polygon_set_2.h"

#if defined(CGAL_USE_APPROX)
typedef CGAL::Interval_nt_approx<true> Num;
typedef CGAL::Simple_cartesian<Num> K;
typedef CGAL::Arr_linear_traits_2_approx<K> Arr_linear_traits_2;
#elif defined(CGAL_USE_EPECK)
typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef CGAL::Arr_linear_traits_2<K> Arr_linear_traits_2;
#else
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Arr_linear_traits_2<K> Arr_linear_traits_2;
#endif
typedef CGAL::Bbox_2 Bbox_2;
typedef CGAL::Polygon_2<K> Polygon_2;
typedef CGAL::Polygon_with_holes_2<K> Polygon_with_holes_2;
typedef Polygon_with_holes_2::Hole_const_iterator Hole_const_iterator;
typedef CGAL::Polygon_set_2<K> Polygon_set_2;
typedef CGAL::Direction_2<K> Direction_2;
typedef CGAL::Segment_2<K> Segment_2;
typedef CGAL::Line_2<K> Line_2;
typedef CGAL::Ray_2<K> Ray_2;
typedef CGAL::Vector_2<K> Vector_2;
typedef CGAL::Aff_transformation_2<K> Aff_transformation_2;
typedef CGAL::Rotation Rotation;
typedef K::Point_2 Point_2;
typedef Polygon_2::Vertex_iterator Vertex_iterator;
typedef CGAL::Extended_cartesian<K::FT> EK;
typedef CGAL::Nef_polyhedron_2<EK> Nef_polyhedron_2;
typedef CGAL::Arrangement_2<Arr_linear_traits_2> Arrangement_2;
typedef Arr_linear_traits_2::X_monotone_curve_2 X_monotone_curve_2;
typedef Arr_linear_traits_2::Curve_2 Curve_2;
typedef CGAL::Partition_traits_2<K> Partition_Traits;

#endif // !defined(CGAL_TYPES_H)
