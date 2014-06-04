#include "Arrangement2.h"
#include "Arrangement2Face.h"
#include "Arrangement2Halfedge.h"
#include "Arrangement2Vertex.h"
#include "Line2.h"
#include "Point2.h"
#include "Polygon2.h"
#include "Curve2.h"
#include "cgal_args.h"

using namespace v8;
using namespace node;
using namespace std;


const char *Arrangement2::Name = "Arrangement2";


void Arrangement2::RegisterMethods()
{
    SetPrototypeMethod(sConstructorTemplate, "toString", ToString);
    SetPrototypeMethod(sConstructorTemplate, "clear", Clear);
    SetPrototypeMethod(sConstructorTemplate, "isEmpty", IsEmpty);
    SetPrototypeMethod(sConstructorTemplate, "isValid", IsValid);
    SetPrototypeMethod(sConstructorTemplate, "insert", Insert);
    SetPrototypeMethod(sConstructorTemplate, "insertLines", InsertLines); // deprecated
    SetPrototypeMethod(sConstructorTemplate, "numberOfVertices", NumberOfVertices);
    SetPrototypeMethod(sConstructorTemplate, "numberOfIsolatedVertices", NumberOfIsolatedVertices);
    SetPrototypeMethod(sConstructorTemplate, "vertices", Vertices);
    SetPrototypeMethod(sConstructorTemplate, "numberOfVerticesAtInfinity", NumberOfVerticesAtInfinity);
    SetPrototypeMethod(sConstructorTemplate, "unboundedFace", UnboundedFace);
    SetPrototypeMethod(sConstructorTemplate, "numberOfFaces", NumberOfFaces);
    SetPrototypeMethod(sConstructorTemplate, "faces", Faces);
    SetPrototypeMethod(sConstructorTemplate, "numberOfUnboundedFaces", NumberOfUnboundedFaces);
    SetPrototypeMethod(sConstructorTemplate, "unboundedFaces", UnboundedFaces);
    SetPrototypeMethod(sConstructorTemplate, "fictitiousFace", FictitiousFace);
    SetPrototypeMethod(sConstructorTemplate, "numberOfHalfedges", NumberOfHalfedges);
    SetPrototypeMethod(sConstructorTemplate, "halfedges", Halfedges);
    SetPrototypeMethod(sConstructorTemplate, "numberOfEdges", NumberOfEdges);
    SetPrototypeMethod(sConstructorTemplate, "edges", Edges);
    SetPrototypeMethod(sConstructorTemplate, "insertInFaceInterior", InsertInFaceInterior);
    SetPrototypeMethod(sConstructorTemplate, "insertFromLeftVertex", InsertFromLeftVertex);
    SetPrototypeMethod(sConstructorTemplate, "insertFromRightVertex", InsertFromRightVertex);
    SetPrototypeMethod(sConstructorTemplate, "insertAtVertices", InsertAtVertices);
    SetPrototypeMethod(sConstructorTemplate, "modifyVertex", ModifyVertex);
    SetPrototypeMethod(sConstructorTemplate, "removeIsolatedVertex", RemoveIsolatedVertex);
    SetPrototypeMethod(sConstructorTemplate, "modifyEdge", ModifyEdge);
    SetPrototypeMethod(sConstructorTemplate, "splitEdge", SplitEdge);
    SetPrototypeMethod(sConstructorTemplate, "mergeEdge", MergeEdge);
    SetPrototypeMethod(sConstructorTemplate, "removeEdge", RemoveEdge);
    SetPrototypeMethod(sConstructorTemplate, "removeEdgeAndMerge", RemoveEdgeAndMerge);

    Arrangement2Face::Init(sConstructorTemplate);
    Arrangement2Halfedge::Init(sConstructorTemplate);
    Arrangement2Vertex::Init(sConstructorTemplate);
}


bool Arrangement2::ParseArg(Local<Value> arg, Arrangement_2 &receiver)
{
    if (sConstructorTemplate->HasInstance(arg)) {

        // This supports e.g.: newArrangement = new CGAL.Arrangement2(oldArrangement);
        receiver = ExtractWrapped(Local<Object>::Cast(arg));
        return true;

    } else {

        return false;

    }
}


Handle<Value> Arrangement2::ToPOD(const Arrangement_2 &arrangement, bool precise)
{
    HandleScope scope;
    Local<Object> obj = Object::New();
    obj->Set(String::NewSymbol("numFaces"), Number::New(arrangement.number_of_faces()));
    obj->Set(String::NewSymbol("numUnboundedFaces"),
        Number::New(arrangement.number_of_unbounded_faces()));
    obj->Set(String::NewSymbol("numBoundedFaces"),
        Number::New(arrangement.number_of_faces()-arrangement.number_of_unbounded_faces()));
    obj->Set(String::NewSymbol("numVertices"), Number::New(arrangement.number_of_vertices()));

    Local<Array> faceArray = Array::New();
    obj->Set(String::NewSymbol("boundedFaces"), faceArray);

    // POD-ify arrangement faces and assign to array within object.
    Arrangement_2::Face_const_iterator fit;
    uint32_t faceNum = 0;
    for(fit = arrangement.faces_begin(); fit != arrangement.faces_end(); ++fit){
        if (!fit->is_unbounded()){

            Polygon_2 poly;
            back_insert_iterator<Polygon_2> bit = back_inserter(poly);

            Arrangement_2::Ccb_halfedge_const_circulator circ = fit->outer_ccb();
            Arrangement_2::Ccb_halfedge_const_circulator curr = circ;
            // Step through face edges and add edge source point to poly.
            do { *bit++  = curr->source()->point(); } while (++curr != circ);

            // Add poly created from edge source points to face array.
            faceArray->Set(faceNum, Polygon2::ToPOD(poly, precise));
            faceNum++;
        }
    }

    return scope.Close(obj);
}


Handle<Value> Arrangement2::ToString(const v8::Arguments &args)
{
    HandleScope scope;
    Arrangement_2 &arrangement = ExtractWrapped(args.This());
    ostringstream str;
    str << "[object "  << Name << " " << &arrangement << " ";
    str << "F:" << arrangement.number_of_faces() << " ";
    str << "V:" << arrangement.number_of_vertices() << " ";
    str << "E:" << arrangement.number_of_edges() << "]";
    return scope.Close(String::New(str.str().c_str()));
}


Handle<Value> Arrangement2::Clear(const Arguments &args)
{
    HandleScope scope;
    try {
        Arrangement_2 &arrangement = ExtractWrapped(args.This());
        arrangement.clear();
        return Undefined();
    }
    catch (const exception &e) {
        return ThrowException(String::New(e.what()));
    }
}


Handle<Value> Arrangement2::IsEmpty(const Arguments &args)
{
    HandleScope scope;
    try {
        Arrangement_2 &arrangement = ExtractWrapped(args.This());
        return scope.Close(Boolean::New(arrangement.is_empty()));
    }
    catch (const exception &e) {
        return ThrowException(String::New(e.what()));
    }
}


Handle<Value> Arrangement2::IsValid(const Arguments &args)
{
    HandleScope scope;
    try {
        Arrangement_2 &arrangement = ExtractWrapped(args.This());
        return scope.Close(Boolean::New(arrangement.is_valid()));
    }
    catch (const exception &e) {
        return ThrowException(String::New(e.what()));
    }
}


Handle<Value> Arrangement2::Insert(const v8::Arguments &args)
{
    HandleScope scope;
    try {

        Arrangement_2 &arrangement = ExtractWrapped(args.This());

        ARGS_ASSERT(args.Length() == 1);

        if (args[0]->IsArray()) {
            std::vector<Curve_2> curves;
            Curve2::ParseSeqArg(args[0], back_inserter(curves));
            insert(arrangement, curves.begin(), curves.end());
            return Undefined();
        }

        Curve_2 curve;
        if (Curve2::ParseArg(args[0], curve)) {
            insert(arrangement, curve);
            return Undefined();
        }

        ARGS_ASSERT(false);

    }

    catch (const exception &e) {
        return ThrowException(String::New(e.what()));
    }

}


Handle<Value> Arrangement2::InsertLines(const Arguments &args)
{
    HandleScope scope;

    // InsertLines expects to be called with an array of Line2 objects.
    ARGS_ASSERT(args[0]->IsArray());

    try {

        Arrangement_2 &arrangement = ExtractWrapped(args.This());

        Local<Array> lines = Local<Array>::Cast(args[0]);
        for(uint32_t i=0; i<lines->Length(); ++i) {
            ARGS_PARSE_LOCAL(Line2::ParseArg, Line_2, line, lines->Get(i));
            CGAL::insert(arrangement, line);
        }
        return Undefined();

    }

    catch (const exception &e) {
        return ThrowException(String::New(e.what()));
    }

}


Handle<Value> Arrangement2::NumberOfVertices(const Arguments &args)
{
    HandleScope scope;
    try {
        Arrangement_2 &arrangement = ExtractWrapped(args.This());
        return scope.Close(Number::New(arrangement.number_of_vertices()));
    }
    catch (const exception &e) {
        return ThrowException(String::New(e.what()));
    }
}


Handle<Value> Arrangement2::NumberOfIsolatedVertices(const Arguments &args)
{
    HandleScope scope;
    try {
        Arrangement_2 &arrangement = ExtractWrapped(args.This());
        return scope.Close(Number::New(arrangement.number_of_isolated_vertices()));
    }
    catch (const exception &e) {
        return ThrowException(String::New(e.what()));
    }
}


Handle<Value> Arrangement2::Vertices(const Arguments &args)
{
    HandleScope scope;
    try {
        Arrangement_2 &arrangement = ExtractWrapped(args.This());
        Local<Array> array = Array::New();
        Arrangement_2::Vertex_iterator it;
        uint32_t i;
        for(it=arrangement.vertices_begin(),i=0; it!=arrangement.vertices_end(); ++it,++i) {
            array->Set(i, Arrangement2Vertex::New(it));
        }
        return scope.Close(array);
    }
    catch (const exception &e) {
        return ThrowException(String::New(e.what()));
    }
}


Handle<Value> Arrangement2::NumberOfVerticesAtInfinity(const Arguments &args)
{
    HandleScope scope;
    try {
        Arrangement_2 &arrangement = ExtractWrapped(args.This());
        return scope.Close(Number::New(arrangement.number_of_vertices_at_infinity()));
    }
    catch (const exception &e) {
        return ThrowException(String::New(e.what()));
    }
}


Handle<Value> Arrangement2::UnboundedFace(const Arguments &args)
{
    HandleScope scope;
    try {
        Arrangement_2 &arrangement = ExtractWrapped(args.This());
        return scope.Close(Arrangement2Face::New(arrangement.unbounded_face()));
    }
    catch (const exception &e) {
        return ThrowException(String::New(e.what()));
    }
}


Handle<Value> Arrangement2::NumberOfFaces(const Arguments &args)
{
    HandleScope scope;
    try {
        Arrangement_2 &arrangement = ExtractWrapped(args.This());
        return scope.Close(Number::New(arrangement.number_of_faces()));
    }
    catch (const exception &e) {
        return ThrowException(String::New(e.what()));
    }
}


Handle<Value> Arrangement2::Faces(const Arguments &args)
{
    HandleScope scope;
    try {
        Arrangement_2 &arrangement = ExtractWrapped(args.This());
        Local<Array> array = Array::New();
        Arrangement_2::Face_iterator it;
        uint32_t i;
        for(it=arrangement.faces_begin(),i=0; it!=arrangement.faces_end(); ++it,++i) {
            array->Set(i, Arrangement2Face::New(it));
        }
        return scope.Close(array);
    }
    catch (const exception &e) {
        return ThrowException(String::New(e.what()));
    }
}


Handle<Value> Arrangement2::NumberOfUnboundedFaces(const Arguments &args)
{
    HandleScope scope;
    try {
        Arrangement_2 &arrangement = ExtractWrapped(args.This());
        return scope.Close(Number::New(arrangement.number_of_unbounded_faces()));
    }
    catch (const exception &e) {
        return ThrowException(String::New(e.what()));
    }
}


Handle<Value> Arrangement2::UnboundedFaces(const Arguments &args)
{
    HandleScope scope;
    try {
        Arrangement_2 &arrangement = ExtractWrapped(args.This());
        Local<Array> array = Array::New();
        Arrangement_2::Face_iterator it;
        uint32_t i;
        for(it=arrangement.unbounded_faces_begin(),i=0; it!=arrangement.unbounded_faces_end(); ++it,++i) {
            array->Set(i, Arrangement2Face::New(it));
        }
        return scope.Close(array);
    }
    catch (const exception &e) {
        return ThrowException(String::New(e.what()));
    }
}


Handle<Value> Arrangement2::FictitiousFace(const Arguments &args)
{
    HandleScope scope;
    try {
        Arrangement_2 &arrangement = ExtractWrapped(args.This());
        return scope.Close(Arrangement2Face::New(arrangement.fictitious_face()));
    }
    catch (const exception &e) {
        return ThrowException(String::New(e.what()));
    }
}


Handle<Value> Arrangement2::NumberOfHalfedges(const Arguments &args)
{
    HandleScope scope;
    try {
        Arrangement_2 &arrangement = ExtractWrapped(args.This());
        return scope.Close(Number::New(arrangement.number_of_halfedges()));
    }
    catch (const exception &e) {
        return ThrowException(String::New(e.what()));
    }
}


Handle<Value> Arrangement2::Halfedges(const Arguments &args)
{
    HandleScope scope;
    try {
        Arrangement_2 &arrangement = ExtractWrapped(args.This());
        Local<Array> array = Array::New();
        Arrangement_2::Halfedge_iterator it;
        uint32_t i;
        for(it=arrangement.halfedges_begin(),i=0; it!=arrangement.halfedges_end(); ++it,++i) {
            array->Set(i, Arrangement2Halfedge::New(it));
        }
        return scope.Close(array);
    }
    catch (const exception &e) {
        return ThrowException(String::New(e.what()));
    }
}


Handle<Value> Arrangement2::NumberOfEdges(const Arguments &args)
{
    HandleScope scope;
    try {
        Arrangement_2 &arrangement = ExtractWrapped(args.This());
        return scope.Close(Number::New(arrangement.number_of_edges()));
    }
    catch (const exception &e) {
        return ThrowException(String::New(e.what()));
    }
}


Handle<Value> Arrangement2::Edges(const Arguments &args)
{
    HandleScope scope;
    try {
        Arrangement_2 &arrangement = ExtractWrapped(args.This());
        Local<Array> array = Array::New();
        Arrangement_2::Halfedge_iterator it;
        uint32_t i;
        for(it=arrangement.edges_begin(),i=0; it!=arrangement.edges_end(); ++it,++i) {
            array->Set(i, Arrangement2Halfedge::New(it));
        }
        return scope.Close(array);
    }
    catch (const exception &e) {
        return ThrowException(String::New(e.what()));
    }
}


Handle<Value> Arrangement2::InsertInFaceInterior(const v8::Arguments &args)
{
    HandleScope scope;
    try {

        Arrangement_2 &arrangement = ExtractWrapped(args.This());

        Point_2 point;
        Arrangement_2::Face_handle face;
        Curve_2 curve;

        if ((args.Length() == 2)
            && Point2::ParseArg(args[0], point)
            && Arrangement2Face::ParseArg(args[1], face))
        {
            return scope.Close(Arrangement2Vertex::New(arrangement.insert_in_face_interior(point, face)));
        }

        if ((args.Length() == 2)
            && Curve2::ParseArg(args[0], curve)
            && Arrangement2Face::ParseArg(args[1], face))
        {
            return scope.Close(Arrangement2Halfedge::New(arrangement.insert_in_face_interior(curve, face)));
        }

        ARGS_ASSERT(false);

    }
    catch (const exception &e) {
        return ThrowException(String::New(e.what()));
    }
}


Handle<Value> Arrangement2::InsertFromLeftVertex(const v8::Arguments &args)
{
    HandleScope scope;
    try {

        Arrangement_2 &arrangement = ExtractWrapped(args.This());

        Curve_2 curve;
        Arrangement_2::Vertex_handle vertex;
        Arrangement_2::Face_handle face;
        Arrangement_2::Halfedge_handle edge;

        if ((args.Length() == 2)
            && Curve2::ParseArg(args[0], curve)
            && Arrangement2Vertex::ParseArg(args[1], vertex))
        {
            return scope.Close(Arrangement2Halfedge::New(arrangement.insert_from_left_vertex(curve, vertex)));
        }

        if ((args.Length() == 3)
            && Curve2::ParseArg(args[0], curve)
            && Arrangement2Vertex::ParseArg(args[1], vertex)
            && Arrangement2Face::ParseArg(args[2], face))
        {
            return scope.Close(Arrangement2Halfedge::New(arrangement.insert_from_left_vertex(curve, vertex, face)));
        }

        if ((args.Length() == 2)
            && Curve2::ParseArg(args[0], curve)
            && Arrangement2Halfedge::ParseArg(args[1], edge))
        {
            return scope.Close(Arrangement2Halfedge::New(arrangement.insert_from_left_vertex(curve, edge)));
        }

        ARGS_ASSERT(false);

    }
    catch (const exception &e) {
        return ThrowException(String::New(e.what()));
    }
}


Handle<Value> Arrangement2::InsertFromRightVertex(const v8::Arguments &args)
{
    HandleScope scope;
    try {

        Arrangement_2 &arrangement = ExtractWrapped(args.This());

        Curve_2 curve;
        Arrangement_2::Vertex_handle vertex;
        Arrangement_2::Face_handle face;
        Arrangement_2::Halfedge_handle edge;

        if ((args.Length() == 2)
            && Curve2::ParseArg(args[0], curve)
            && Arrangement2Vertex::ParseArg(args[1], vertex))
        {
            return scope.Close(Arrangement2Halfedge::New(arrangement.insert_from_right_vertex(curve, vertex)));
        }

        if ((args.Length() == 3)
            && Curve2::ParseArg(args[0], curve)
            && Arrangement2Vertex::ParseArg(args[1], vertex)
            && Arrangement2Face::ParseArg(args[2], face))
        {
            return scope.Close(Arrangement2Halfedge::New(arrangement.insert_from_right_vertex(curve, vertex, face)));
        }

        if ((args.Length() == 2)
            && Curve2::ParseArg(args[0], curve)
            && Arrangement2Halfedge::ParseArg(args[1], edge))
        {
            return scope.Close(Arrangement2Halfedge::New(arrangement.insert_from_right_vertex(curve, edge)));
        }

        ARGS_ASSERT(false);

    }
    catch (const exception &e) {
        return ThrowException(String::New(e.what()));
    }
}


Handle<Value> Arrangement2::InsertAtVertices(const v8::Arguments &args)
{
    HandleScope scope;
    try {

        Arrangement_2 &arrangement = ExtractWrapped(args.This());

        Curve_2 curve;
        Arrangement_2::Vertex_handle vertex1, vertex2;
        Arrangement_2::Face_handle face;
        Arrangement_2::Halfedge_handle edge1, edge2;

        if ((args.Length() == 3)
            && Curve2::ParseArg(args[0], curve)
            && Arrangement2Vertex::ParseArg(args[1], vertex1)
            && Arrangement2Vertex::ParseArg(args[2], vertex2))
        {
            return scope.Close(Arrangement2Halfedge::New(arrangement.insert_at_vertices(curve, vertex1, vertex2)));
        }

        if ((args.Length() == 4)
            && Curve2::ParseArg(args[0], curve)
            && Arrangement2Vertex::ParseArg(args[1], vertex1)
            && Arrangement2Vertex::ParseArg(args[2], vertex2)
            && Arrangement2Face::ParseArg(args[3], face))
        {
            return scope.Close(Arrangement2Halfedge::New(arrangement.insert_at_vertices(curve, vertex1, vertex2, face)));
        }

        if ((args.Length() == 3)
            && Curve2::ParseArg(args[0], curve)
            && Arrangement2Halfedge::ParseArg(args[1], edge1)
            && Arrangement2Vertex::ParseArg(args[2], vertex1))
        {
            return scope.Close(Arrangement2Halfedge::New(arrangement.insert_at_vertices(curve, edge1, vertex1)));
        }

        if ((args.Length() == 3)
            && Curve2::ParseArg(args[0], curve)
            && Arrangement2Halfedge::ParseArg(args[1], edge1)
            && Arrangement2Halfedge::ParseArg(args[2], edge1))
        {
            return scope.Close(Arrangement2Halfedge::New(arrangement.insert_at_vertices(curve, edge1, edge2)));
        }

        ARGS_ASSERT(false);

    }
    catch (const exception &e) {
        return ThrowException(String::New(e.what()));
    }
}


Handle<Value> Arrangement2::ModifyVertex(const v8::Arguments &args)
{
    HandleScope scope;
    try {
        Arrangement_2 &arrangement = ExtractWrapped(args.This());
        ARGS_ASSERT(args.Length() == 2);
        ARGS_PARSE_LOCAL(Arrangement2Vertex::ParseArg, Arrangement_2::Vertex_handle, vertex, args[0]);
        ARGS_PARSE_LOCAL(Point2::ParseArg, Point_2, point, args[1]);
        return scope.Close(Arrangement2Vertex::New(arrangement.modify_vertex(vertex, point)));
    }
    catch (const exception &e) {
        return ThrowException(String::New(e.what()));
    }
}


Handle<Value> Arrangement2::RemoveIsolatedVertex(const v8::Arguments &args)
{
    HandleScope scope;
    try {
        Arrangement_2 &arrangement = ExtractWrapped(args.This());
        ARGS_ASSERT(args.Length() == 1);
        ARGS_PARSE_LOCAL(Arrangement2Vertex::ParseArg, Arrangement_2::Vertex_handle, vertex, args[0]);
        return scope.Close(Arrangement2Face::New(arrangement.remove_isolated_vertex(vertex)));
    }
    catch (const exception &e) {
        return ThrowException(String::New(e.what()));
    }
}


Handle<Value> Arrangement2::ModifyEdge(const v8::Arguments &args)
{
    HandleScope scope;
    try {
        Arrangement_2 &arrangement = ExtractWrapped(args.This());
        ARGS_ASSERT(args.Length() == 2);
        ARGS_PARSE_LOCAL(Arrangement2Halfedge::ParseArg, Arrangement_2::Halfedge_handle, halfedge, args[0]);
        ARGS_PARSE_LOCAL(Curve2::ParseArg, Curve_2, curve, args[1]);
        return scope.Close(Arrangement2Halfedge::New(arrangement.modify_edge(halfedge, curve)));
    }
    catch (const exception &e) {
        return ThrowException(String::New(e.what()));
    }
}


Handle<Value> Arrangement2::SplitEdge(const v8::Arguments &args)
{
    HandleScope scope;
    try {
        Arrangement_2 &arrangement = ExtractWrapped(args.This());
        ARGS_ASSERT(args.Length() == 3);
        ARGS_PARSE_LOCAL(Arrangement2Halfedge::ParseArg, Arrangement_2::Halfedge_handle, halfedge, args[0]);
        ARGS_PARSE_LOCAL(Curve2::ParseArg, Curve_2, curve1, args[1]);
        ARGS_PARSE_LOCAL(Curve2::ParseArg, Curve_2, curve2, args[2]);
        return scope.Close(Arrangement2Halfedge::New(arrangement.split_edge(halfedge, curve1, curve2)));
    }
    catch (const exception &e) {
        return ThrowException(String::New(e.what()));
    }
}


Handle<Value> Arrangement2::MergeEdge(const v8::Arguments &args)
{
    HandleScope scope;
    try {
        Arrangement_2 &arrangement = ExtractWrapped(args.This());
        ARGS_ASSERT(args.Length() == 3);
        ARGS_PARSE_LOCAL(Arrangement2Halfedge::ParseArg, Arrangement_2::Halfedge_handle, halfedge1, args[0]);
        ARGS_PARSE_LOCAL(Arrangement2Halfedge::ParseArg, Arrangement_2::Halfedge_handle, halfedge2, args[1]);
        ARGS_PARSE_LOCAL(Curve2::ParseArg, Curve_2, curve, args[2]);
        return scope.Close(Arrangement2Halfedge::New(arrangement.merge_edge(halfedge1, halfedge2, curve)));
    }
    catch (const exception &e) {
        return ThrowException(String::New(e.what()));
    }
}


Handle<Value> Arrangement2::RemoveEdge(const v8::Arguments &args)
{
    HandleScope scope;
    try {

        Arrangement_2 &arrangement = ExtractWrapped(args.This());

        Arrangement_2::Halfedge_handle edge;

        if ((args.Length() == 1)
            && Arrangement2Halfedge::ParseArg(args[0], edge))
        {
            return scope.Close(Arrangement2Face::New(arrangement.remove_edge(edge)));
        }

        if ((args.Length() == 2)
            && Arrangement2Halfedge::ParseArg(args[0], edge)
            && args[1]->IsBoolean())
        {
            return scope.Close(Arrangement2Face::New(arrangement.remove_edge(edge, args[1]->BooleanValue())));
        }

        if ((args.Length() == 3)
            && Arrangement2Halfedge::ParseArg(args[0], edge)
            && args[1]->IsBoolean()
            && args[2]->IsBoolean())
        {
            return scope.Close(Arrangement2Face::New(arrangement.remove_edge(edge, args[1]->BooleanValue(), args[2]->BooleanValue())));
        }

        ARGS_ASSERT(false);

    }
    catch (const exception &e) {
        return ThrowException(String::New(e.what()));
    }
}


Handle<Value> Arrangement2::RemoveEdgeAndMerge(const v8::Arguments &args)
{
    HandleScope scope;
    try {

        Arrangement_2 &arrangement = ExtractWrapped(args.This());

        Arrangement_2::Halfedge_handle edge;

        if ((args.Length() == 1)
            && Arrangement2Halfedge::ParseArg(args[0], edge))
        {
            return scope.Close(Arrangement2Face::New(remove_edge(arrangement, edge)));
        }

        ARGS_ASSERT(false);

    }
    catch (const exception &e) {
        return ThrowException(String::New(e.what()));
    }
}
