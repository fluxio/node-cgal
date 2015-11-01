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


void Arrangement2::RegisterMethods(Isolate *isolate)
{
    HandleScope scope(isolate);
    Local<FunctionTemplate> constructorTemplate = sConstructorTemplate.Get(isolate);
    NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "toString", ToString);
    NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "clear", Clear);
    NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "isEmpty", IsEmpty);
    NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "isValid", IsValid);
    NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "insert", Insert);
    NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "insertLines", InsertLines); // deprecated
    NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "numberOfVertices", NumberOfVertices);
    NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "numberOfIsolatedVertices", NumberOfIsolatedVertices);
    NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "vertices", Vertices);
    NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "numberOfVerticesAtInfinity", NumberOfVerticesAtInfinity);
    NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "unboundedFace", UnboundedFace);
    NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "numberOfFaces", NumberOfFaces);
    NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "faces", Faces);
    NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "numberOfUnboundedFaces", NumberOfUnboundedFaces);
    NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "unboundedFaces", UnboundedFaces);
    NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "fictitiousFace", FictitiousFace);
    NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "numberOfHalfedges", NumberOfHalfedges);
    NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "halfedges", Halfedges);
    NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "numberOfEdges", NumberOfEdges);
    NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "edges", Edges);
    NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "insertInFaceInterior", InsertInFaceInterior);
    NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "insertFromLeftVertex", InsertFromLeftVertex);
    NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "insertFromRightVertex", InsertFromRightVertex);
    NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "insertAtVertices", InsertAtVertices);
    NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "modifyVertex", ModifyVertex);
    NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "removeIsolatedVertex", RemoveIsolatedVertex);
    NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "modifyEdge", ModifyEdge);
    NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "splitEdge", SplitEdge);
    NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "mergeEdge", MergeEdge);
    NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "removeEdge", RemoveEdge);
    NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "removeEdgeAndMerge", RemoveEdgeAndMerge);

    Arrangement2Face::Init(constructorTemplate);
    Arrangement2Halfedge::Init(constructorTemplate);
    Arrangement2Vertex::Init(constructorTemplate);
}


bool Arrangement2::ParseArg(Isolate *isolate, Local<Value> arg, Arrangement_2 &receiver)
{
    if (sConstructorTemplate.Get(isolate)->HasInstance(arg)) {
        receiver = ExtractWrapped(Local<Object>::Cast(arg));
        return true;
    }

    return false;
}


Local<Value> Arrangement2::ToPOD(Isolate *isolate, const Arrangement_2 &arrangement, bool precise)
{
    EscapableHandleScope scope(isolate);

    Local<Object> obj = Object::New(isolate);
    obj->Set(SYMBOL(isolate, "numFaces"),
        Number::New(isolate, arrangement.number_of_faces()));
    obj->Set(SYMBOL(isolate, "numUnboundedFaces"),
        Number::New(isolate, arrangement.number_of_unbounded_faces()));
    obj->Set(SYMBOL(isolate, "numBoundedFaces"),
        Number::New(isolate, arrangement.number_of_faces()-arrangement.number_of_unbounded_faces()));
    obj->Set(SYMBOL(isolate, "numVertices"),
        Number::New(isolate, arrangement.number_of_vertices()));

    Local<Array> faceArray = Array::New(isolate);
    obj->Set(SYMBOL(isolate, "boundedFaces"), faceArray);

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
            faceArray->Set(faceNum, Polygon2::ToPOD(isolate, poly, precise));
            faceNum++;
        }
    }

    return scope.Escape(obj);
}


void Arrangement2::ToString(const FunctionCallbackInfo<Value> &info)
{
    Isolate *isolate = info.GetIsolate();
    HandleScope scope(isolate);
    Arrangement_2 &arrangement = ExtractWrapped(info.This());
    ostringstream str;
    str << "[object "  << Name << " " << &arrangement << " ";
    str << "F:" << arrangement.number_of_faces() << " ";
    str << "V:" << arrangement.number_of_vertices() << " ";
    str << "E:" << arrangement.number_of_edges() << "]";
    info.GetReturnValue().Set(String::NewFromUtf8(isolate, str.str().c_str()));
}


void Arrangement2::Clear(const FunctionCallbackInfo<Value> &info)
{
    Isolate *isolate = info.GetIsolate();
    HandleScope scope(isolate);
    try {
        Arrangement_2 &arrangement = ExtractWrapped(info.This());
        arrangement.clear();
        info.GetReturnValue().SetUndefined();
    }
    catch (const exception &e) {
        isolate->ThrowException(String::NewFromUtf8(isolate, e.what()));
    }
}


void Arrangement2::IsEmpty(const FunctionCallbackInfo<Value> &info)
{
    Isolate *isolate = info.GetIsolate();
    HandleScope scope(isolate);
    try {
        Arrangement_2 &arrangement = ExtractWrapped(info.This());
        info.GetReturnValue().Set(Boolean::New(isolate, arrangement.is_empty()));
    }
    catch (const exception &e) {
        isolate->ThrowException(String::NewFromUtf8(isolate, e.what()));
    }
}


void Arrangement2::IsValid(const FunctionCallbackInfo<Value> &info)
{
    Isolate *isolate = info.GetIsolate();
    HandleScope scope(isolate);
    try {
        Arrangement_2 &arrangement = ExtractWrapped(info.This());
        info.GetReturnValue().Set(Boolean::New(isolate, arrangement.is_valid()));
    }
    catch (const exception &e) {
        isolate->ThrowException(String::NewFromUtf8(isolate, e.what()));
    }
}


void Arrangement2::Insert(const FunctionCallbackInfo<Value> &info)
{
    Isolate *isolate = info.GetIsolate();
    HandleScope scope(isolate);
    try {

        Arrangement_2 &arrangement = ExtractWrapped(info.This());

        ARGS_ASSERT(isolate, info.Length() == 1);

        if (info[0]->IsArray()) {
            std::vector<Curve_2> curves;
            Curve2::ParseSeqArg(isolate, info[0], back_inserter(curves));
            insert(arrangement, curves.begin(), curves.end());
            info.GetReturnValue().SetUndefined();
            return;
        }

        Curve_2 curve;
        if (Curve2::ParseArg(isolate, info[0], curve)) {
            insert(arrangement, curve);
            info.GetReturnValue().SetUndefined();
        }

        ARGS_ASSERT(isolate, false);

    }

    catch (const exception &e) {
        isolate->ThrowException(String::NewFromUtf8(isolate, e.what()));
    }

}


void Arrangement2::InsertLines(const FunctionCallbackInfo<Value> &info)
{
    Isolate *isolate = info.GetIsolate();
    HandleScope scope(isolate);

    // InsertLines expects to be called with an array of Line2 objects.
    ARGS_ASSERT(isolate, info[0]->IsArray());

    try {

        Arrangement_2 &arrangement = ExtractWrapped(info.This());

        Local<Array> lines = Local<Array>::Cast(info[0]);
        for(uint32_t i=0; i<lines->Length(); ++i) {
            ARGS_PARSE_LOCAL(isolate, Line2::ParseArg, Line_2, line, lines->Get(i));
            CGAL::insert(arrangement, line);
        }

        info.GetReturnValue().SetUndefined();

    }

    catch (const exception &e) {
        isolate->ThrowException(String::NewFromUtf8(isolate, e.what()));
    }

}


void Arrangement2::NumberOfVertices(const FunctionCallbackInfo<Value> &info)
{
    Isolate *isolate = info.GetIsolate();
    HandleScope scope(isolate);
    try {
        Arrangement_2 &arrangement = ExtractWrapped(info.This());
        info.GetReturnValue().Set(Number::New(isolate, arrangement.number_of_vertices()));
    }
    catch (const exception &e) {
        isolate->ThrowException(String::NewFromUtf8(isolate, e.what()));
    }
}


void Arrangement2::NumberOfIsolatedVertices(const FunctionCallbackInfo<Value> &info)
{
    Isolate *isolate = info.GetIsolate();
    HandleScope scope(isolate);
    try {
        Arrangement_2 &arrangement = ExtractWrapped(info.This());
        info.GetReturnValue().Set(Number::New(isolate, arrangement.number_of_isolated_vertices()));
    }
    catch (const exception &e) {
        isolate->ThrowException(String::NewFromUtf8(isolate, e.what()));
    }
}


void Arrangement2::Vertices(const FunctionCallbackInfo<Value> &info)
{
    Isolate *isolate = info.GetIsolate();
    HandleScope scope(isolate);
    try {
        Arrangement_2 &arrangement = ExtractWrapped(info.This());
        Local<Array> array = Array::New(isolate);
        Arrangement_2::Vertex_iterator it;
        uint32_t i;
        for(it=arrangement.vertices_begin(),i=0; it!=arrangement.vertices_end(); ++it,++i) {
            array->Set(i, Arrangement2Vertex::New(isolate, it));
        }
        info.GetReturnValue().Set(array);
    }
    catch (const exception &e) {
        isolate->ThrowException(String::NewFromUtf8(isolate, e.what()));
    }
}


void Arrangement2::NumberOfVerticesAtInfinity(const FunctionCallbackInfo<Value> &info)
{
    Isolate *isolate = info.GetIsolate();
    HandleScope scope(isolate);
    try {
        Arrangement_2 &arrangement = ExtractWrapped(info.This());
        info.GetReturnValue().Set(Number::New(isolate, arrangement.number_of_vertices_at_infinity()));
    }
    catch (const exception &e) {
        isolate->ThrowException(String::NewFromUtf8(isolate, e.what()));
    }
}


void Arrangement2::UnboundedFace(const FunctionCallbackInfo<Value> &info)
{
    Isolate *isolate = info.GetIsolate();
    HandleScope scope(isolate);
    try {
        Arrangement_2 &arrangement = ExtractWrapped(info.This());
        info.GetReturnValue().Set(Arrangement2Face::New(isolate, arrangement.unbounded_face()));
    }
    catch (const exception &e) {
        isolate->ThrowException(String::NewFromUtf8(isolate, e.what()));
    }
}


void Arrangement2::NumberOfFaces(const FunctionCallbackInfo<Value> &info)
{
    Isolate *isolate = info.GetIsolate();
    HandleScope scope(isolate);
    try {
        Arrangement_2 &arrangement = ExtractWrapped(info.This());
        info.GetReturnValue().Set(Number::New(isolate, arrangement.number_of_faces()));
    }
    catch (const exception &e) {
        isolate->ThrowException(String::NewFromUtf8(isolate, e.what()));
    }
}


void Arrangement2::Faces(const FunctionCallbackInfo<Value> &info)
{
    Isolate *isolate = info.GetIsolate();
    HandleScope scope(isolate);
    try {
        Arrangement_2 &arrangement = ExtractWrapped(info.This());
        Local<Array> array = Array::New(isolate);
        Arrangement_2::Face_iterator it;
        uint32_t i;
        for(it=arrangement.faces_begin(),i=0; it!=arrangement.faces_end(); ++it,++i) {
            array->Set(i, Arrangement2Face::New(isolate, it));
        }
        info.GetReturnValue().Set(array);
    }
    catch (const exception &e) {
        isolate->ThrowException(String::NewFromUtf8(isolate, e.what()));
    }
}


void Arrangement2::NumberOfUnboundedFaces(const FunctionCallbackInfo<Value> &info)
{
    Isolate *isolate = info.GetIsolate();
    HandleScope scope(isolate);
    try {
        Arrangement_2 &arrangement = ExtractWrapped(info.This());
        info.GetReturnValue().Set(Number::New(isolate, arrangement.number_of_unbounded_faces()));
    }
    catch (const exception &e) {
        isolate->ThrowException(String::NewFromUtf8(isolate, e.what()));
    }
}


void Arrangement2::UnboundedFaces(const FunctionCallbackInfo<Value> &info)
{
    Isolate *isolate = info.GetIsolate();
    HandleScope scope(isolate);
    try {
        Arrangement_2 &arrangement = ExtractWrapped(info.This());
        Local<Array> array = Array::New(isolate);
        Arrangement_2::Face_iterator it;
        uint32_t i;
        for(it=arrangement.unbounded_faces_begin(),i=0; it!=arrangement.unbounded_faces_end(); ++it,++i) {
            array->Set(i, Arrangement2Face::New(isolate, it));
        }
        info.GetReturnValue().Set(array);
    }
    catch (const exception &e) {
        isolate->ThrowException(String::NewFromUtf8(isolate, e.what()));
    }
}


void Arrangement2::FictitiousFace(const FunctionCallbackInfo<Value> &info)
{
    Isolate *isolate = info.GetIsolate();
    HandleScope scope(isolate);
    try {
        Arrangement_2 &arrangement = ExtractWrapped(info.This());
        info.GetReturnValue().Set(Arrangement2Face::New(isolate, arrangement.fictitious_face()));
    }
    catch (const exception &e) {
        isolate->ThrowException(String::NewFromUtf8(isolate, e.what()));
    }
}


void Arrangement2::NumberOfHalfedges(const FunctionCallbackInfo<Value> &info)
{
    Isolate *isolate = info.GetIsolate();
    HandleScope scope(isolate);
    try {
        Arrangement_2 &arrangement = ExtractWrapped(info.This());
        info.GetReturnValue().Set(Number::New(isolate, arrangement.number_of_halfedges()));
    }
    catch (const exception &e) {
        isolate->ThrowException(String::NewFromUtf8(isolate, e.what()));
    }
}


void Arrangement2::Halfedges(const FunctionCallbackInfo<Value> &info)
{
    Isolate *isolate = info.GetIsolate();
    HandleScope scope(isolate);
    try {
        Arrangement_2 &arrangement = ExtractWrapped(info.This());
        Local<Array> array = Array::New(isolate);
        Arrangement_2::Halfedge_iterator it;
        uint32_t i;
        for(it=arrangement.halfedges_begin(),i=0; it!=arrangement.halfedges_end(); ++it,++i) {
            array->Set(i, Arrangement2Halfedge::New(isolate, it));
        }
        info.GetReturnValue().Set(array);
    }
    catch (const exception &e) {
        isolate->ThrowException(String::NewFromUtf8(isolate, e.what()));
    }
}


void Arrangement2::NumberOfEdges(const FunctionCallbackInfo<Value> &info)
{
    Isolate *isolate = info.GetIsolate();
    HandleScope scope(isolate);
    try {
        Arrangement_2 &arrangement = ExtractWrapped(info.This());
        info.GetReturnValue().Set(Number::New(isolate, arrangement.number_of_edges()));
    }
    catch (const exception &e) {
        isolate->ThrowException(String::NewFromUtf8(isolate, e.what()));
    }
}


void Arrangement2::Edges(const FunctionCallbackInfo<Value> &info)
{
    Isolate *isolate = info.GetIsolate();
    HandleScope scope(isolate);
    try {
        Arrangement_2 &arrangement = ExtractWrapped(info.This());
        Local<Array> array = Array::New(isolate);
        Arrangement_2::Halfedge_iterator it;
        uint32_t i;
        for(it=arrangement.edges_begin(),i=0; it!=arrangement.edges_end(); ++it,++i) {
            array->Set(i, Arrangement2Halfedge::New(isolate, it));
        }
        info.GetReturnValue().Set(array);
    }
    catch (const exception &e) {
        isolate->ThrowException(String::NewFromUtf8(isolate, e.what()));
    }
}


void Arrangement2::InsertInFaceInterior(const FunctionCallbackInfo<Value> &info)
{
    Isolate *isolate = info.GetIsolate();
    HandleScope scope(isolate);
    try {

        Arrangement_2 &arrangement = ExtractWrapped(info.This());

        Point_2 point;
        Arrangement_2::Face_handle face;
        Curve_2 curve;

        if ((info.Length() == 2)
            && Point2::ParseArg(isolate, info[0], point)
            && Arrangement2Face::ParseArg(isolate, info[1], face))
        {
            info.GetReturnValue().Set(
                Arrangement2Vertex::New(isolate, arrangement.insert_in_face_interior(point, face))
            );
            return;
        }

        if ((info.Length() == 2)
            && Curve2::ParseArg(isolate, info[0], curve)
            && Arrangement2Face::ParseArg(isolate, info[1], face))
        {
            info.GetReturnValue().Set(
                Arrangement2Halfedge::New(isolate, arrangement.insert_in_face_interior(curve, face))
            );
            return;
        }

        ARGS_ASSERT(isolate, false);

    }
    catch (const exception &e) {
        isolate->ThrowException(String::NewFromUtf8(isolate, e.what()));
    }
}


void Arrangement2::InsertFromLeftVertex(const FunctionCallbackInfo<Value> &info)
{
    Isolate *isolate = info.GetIsolate();
    HandleScope scope(isolate);
    try {

        Arrangement_2 &arrangement = ExtractWrapped(info.This());

        Curve_2 curve;
        Arrangement_2::Vertex_handle vertex;
        Arrangement_2::Face_handle face;
        Arrangement_2::Halfedge_handle edge;

        if ((info.Length() == 2)
            && Curve2::ParseArg(isolate, info[0], curve)
            && Arrangement2Vertex::ParseArg(isolate, info[1], vertex))
        {
            info.GetReturnValue().Set(
                Arrangement2Halfedge::New(isolate, arrangement.insert_from_left_vertex(curve, vertex))
            );
            return;
        }

        if ((info.Length() == 3)
            && Curve2::ParseArg(isolate, info[0], curve)
            && Arrangement2Vertex::ParseArg(isolate, info[1], vertex)
            && Arrangement2Face::ParseArg(isolate, info[2], face))
        {
            info.GetReturnValue().Set(
                Arrangement2Halfedge::New(isolate, arrangement.insert_from_left_vertex(curve, vertex, face))
            );
            return;
        }

        if ((info.Length() == 2)
            && Curve2::ParseArg(isolate, info[0], curve)
            && Arrangement2Halfedge::ParseArg(isolate, info[1], edge))
        {
            info.GetReturnValue().Set(
                Arrangement2Halfedge::New(isolate, arrangement.insert_from_left_vertex(curve, edge))
            );
            return;
        }

        ARGS_ASSERT(isolate, false);

    }
    catch (const exception &e) {
        isolate->ThrowException(String::NewFromUtf8(isolate, e.what()));
    }
}


void Arrangement2::InsertFromRightVertex(const FunctionCallbackInfo<Value> &info)
{
    Isolate *isolate = info.GetIsolate();
    HandleScope scope(isolate);
    try {

        Arrangement_2 &arrangement = ExtractWrapped(info.This());

        Curve_2 curve;
        Arrangement_2::Vertex_handle vertex;
        Arrangement_2::Face_handle face;
        Arrangement_2::Halfedge_handle edge;

        if ((info.Length() == 2)
            && Curve2::ParseArg(isolate, info[0], curve)
            && Arrangement2Vertex::ParseArg(isolate, info[1], vertex))
        {
            info.GetReturnValue().Set(
                Arrangement2Halfedge::New(isolate, arrangement.insert_from_right_vertex(curve, vertex))
            );
            return;
        }

        if ((info.Length() == 3)
            && Curve2::ParseArg(isolate, info[0], curve)
            && Arrangement2Vertex::ParseArg(isolate, info[1], vertex)
            && Arrangement2Face::ParseArg(isolate, info[2], face))
        {
            info.GetReturnValue().Set(
                Arrangement2Halfedge::New(isolate, arrangement.insert_from_right_vertex(curve, vertex, face))
            );
            return;
        }

        if ((info.Length() == 2)
            && Curve2::ParseArg(isolate, info[0], curve)
            && Arrangement2Halfedge::ParseArg(isolate, info[1], edge))
        {
            info.GetReturnValue().Set(
                Arrangement2Halfedge::New(isolate, arrangement.insert_from_right_vertex(curve, edge))
            );
            return;
        }

        ARGS_ASSERT(isolate, false);

    }
    catch (const exception &e) {
        isolate->ThrowException(String::NewFromUtf8(isolate, e.what()));
    }
}


void Arrangement2::InsertAtVertices(const FunctionCallbackInfo<Value> &info)
{
    Isolate *isolate = info.GetIsolate();
    HandleScope scope(isolate);
    try {

        Arrangement_2 &arrangement = ExtractWrapped(info.This());

        Curve_2 curve;
        Arrangement_2::Vertex_handle vertex1, vertex2;
        Arrangement_2::Face_handle face;
        Arrangement_2::Halfedge_handle edge1, edge2;

        if ((info.Length() == 3)
            && Curve2::ParseArg(isolate, info[0], curve)
            && Arrangement2Vertex::ParseArg(isolate, info[1], vertex1)
            && Arrangement2Vertex::ParseArg(isolate, info[2], vertex2))
        {
            info.GetReturnValue().Set(
                Arrangement2Halfedge::New(isolate, arrangement.insert_at_vertices(curve, vertex1, vertex2))
            );
            return;
        }

        if ((info.Length() == 4)
            && Curve2::ParseArg(isolate, info[0], curve)
            && Arrangement2Vertex::ParseArg(isolate, info[1], vertex1)
            && Arrangement2Vertex::ParseArg(isolate, info[2], vertex2)
            && Arrangement2Face::ParseArg(isolate, info[3], face))
        {
            info.GetReturnValue().Set(
                Arrangement2Halfedge::New(isolate, arrangement.insert_at_vertices(curve, vertex1, vertex2, face))
            );
            return;
        }

        if ((info.Length() == 3)
            && Curve2::ParseArg(isolate, info[0], curve)
            && Arrangement2Halfedge::ParseArg(isolate, info[1], edge1)
            && Arrangement2Vertex::ParseArg(isolate, info[2], vertex1))
        {
            info.GetReturnValue().Set(
                Arrangement2Halfedge::New(isolate, arrangement.insert_at_vertices(curve, edge1, vertex1))
            );
            return;
        }

        if ((info.Length() == 3)
            && Curve2::ParseArg(isolate, info[0], curve)
            && Arrangement2Halfedge::ParseArg(isolate, info[1], edge1)
            && Arrangement2Halfedge::ParseArg(isolate, info[2], edge1))
        {
            info.GetReturnValue().Set(
                Arrangement2Halfedge::New(isolate, arrangement.insert_at_vertices(curve, edge1, edge2))
            );
            return;
        }

        ARGS_ASSERT(isolate, false);

    }
    catch (const exception &e) {
        isolate->ThrowException(String::NewFromUtf8(isolate, e.what()));
    }
}


void Arrangement2::ModifyVertex(const FunctionCallbackInfo<Value> &info)
{
    Isolate *isolate = info.GetIsolate();
    HandleScope scope(isolate);
    try {
        Arrangement_2 &arrangement = ExtractWrapped(info.This());
        ARGS_ASSERT(isolate, info.Length() == 2);
        ARGS_PARSE_LOCAL(isolate, Arrangement2Vertex::ParseArg, Arrangement_2::Vertex_handle, vertex, info[0]);
        ARGS_PARSE_LOCAL(isolate, Point2::ParseArg, Point_2, point, info[1]);
        info.GetReturnValue().Set(Arrangement2Vertex::New(isolate, arrangement.modify_vertex(vertex, point)));
    }
    catch (const exception &e) {
        isolate->ThrowException(String::NewFromUtf8(isolate, e.what()));
    }
}


void Arrangement2::RemoveIsolatedVertex(const FunctionCallbackInfo<Value> &info)
{
    Isolate *isolate = info.GetIsolate();
    HandleScope scope(isolate);
    try {
        Arrangement_2 &arrangement = ExtractWrapped(info.This());
        ARGS_ASSERT(isolate, info.Length() == 1);
        ARGS_PARSE_LOCAL(isolate, Arrangement2Vertex::ParseArg, Arrangement_2::Vertex_handle, vertex, info[0]);
        info.GetReturnValue().Set(Arrangement2Face::New(isolate, arrangement.remove_isolated_vertex(vertex)));
    }
    catch (const exception &e) {
        isolate->ThrowException(String::NewFromUtf8(isolate, e.what()));
    }
}


void Arrangement2::ModifyEdge(const FunctionCallbackInfo<Value> &info)
{
    Isolate *isolate = info.GetIsolate();
    HandleScope scope(isolate);
    try {
        Arrangement_2 &arrangement = ExtractWrapped(info.This());
        ARGS_ASSERT(isolate, info.Length() == 2);
        ARGS_PARSE_LOCAL(isolate, Arrangement2Halfedge::ParseArg, Arrangement_2::Halfedge_handle, halfedge, info[0]);
        ARGS_PARSE_LOCAL(isolate, Curve2::ParseArg, Curve_2, curve, info[1]);
        info.GetReturnValue().Set(Arrangement2Halfedge::New(isolate, arrangement.modify_edge(halfedge, curve)));
    }
    catch (const exception &e) {
        isolate->ThrowException(String::NewFromUtf8(isolate, e.what()));
    }
}


void Arrangement2::SplitEdge(const FunctionCallbackInfo<Value> &info)
{
    Isolate *isolate = info.GetIsolate();
    HandleScope scope(isolate);
    try {
        Arrangement_2 &arrangement = ExtractWrapped(info.This());
        ARGS_ASSERT(isolate, info.Length() == 3);
        ARGS_PARSE_LOCAL(isolate, Arrangement2Halfedge::ParseArg, Arrangement_2::Halfedge_handle, halfedge, info[0]);
        ARGS_PARSE_LOCAL(isolate, Curve2::ParseArg, Curve_2, curve1, info[1]);
        ARGS_PARSE_LOCAL(isolate, Curve2::ParseArg, Curve_2, curve2, info[2]);
        info.GetReturnValue().Set(Arrangement2Halfedge::New(isolate, arrangement.split_edge(halfedge, curve1, curve2)));
    }
    catch (const exception &e) {
        isolate->ThrowException(String::NewFromUtf8(isolate, e.what()));
    }
}


void Arrangement2::MergeEdge(const FunctionCallbackInfo<Value> &info)
{
    Isolate *isolate = info.GetIsolate();
    HandleScope scope(isolate);
    try {
        Arrangement_2 &arrangement = ExtractWrapped(info.This());
        ARGS_ASSERT(isolate, info.Length() == 3);
        ARGS_PARSE_LOCAL(isolate, Arrangement2Halfedge::ParseArg, Arrangement_2::Halfedge_handle, halfedge1, info[0]);
        ARGS_PARSE_LOCAL(isolate, Arrangement2Halfedge::ParseArg, Arrangement_2::Halfedge_handle, halfedge2, info[1]);
        ARGS_PARSE_LOCAL(isolate, Curve2::ParseArg, Curve_2, curve, info[2]);
        info.GetReturnValue().Set(Arrangement2Halfedge::New(isolate, arrangement.merge_edge(halfedge1, halfedge2, curve)));
    }
    catch (const exception &e) {
        isolate->ThrowException(String::NewFromUtf8(isolate, e.what()));
    }
}


void Arrangement2::RemoveEdge(const FunctionCallbackInfo<Value> &info)
{
    Isolate *isolate = info.GetIsolate();
    HandleScope scope(isolate);
    try {

        Arrangement_2 &arrangement = ExtractWrapped(info.This());

        Arrangement_2::Halfedge_handle edge;

        if ((info.Length() == 1)
            && Arrangement2Halfedge::ParseArg(isolate, info[0], edge))
        {
            info.GetReturnValue().Set(Arrangement2Face::New(isolate, arrangement.remove_edge(edge)));
            return;
        }

        if ((info.Length() == 2)
            && Arrangement2Halfedge::ParseArg(isolate, info[0], edge)
            && info[1]->IsBoolean())
        {
            info.GetReturnValue().Set(
                Arrangement2Face::New(isolate, arrangement.remove_edge(edge, info[1]->BooleanValue()))
            );
            return;
        }

        if ((info.Length() == 3)
            && Arrangement2Halfedge::ParseArg(isolate, info[0], edge)
            && info[1]->IsBoolean()
            && info[2]->IsBoolean())
        {
            info.GetReturnValue().Set(
                Arrangement2Face::New(
                    isolate,
                    arrangement.remove_edge(edge, info[1]->BooleanValue(), info[2]->BooleanValue())
                )
            );
            return;
        }

        ARGS_ASSERT(isolate, false);

    }
    catch (const exception &e) {
        isolate->ThrowException(String::NewFromUtf8(isolate, e.what()));
    }
}


void Arrangement2::RemoveEdgeAndMerge(const FunctionCallbackInfo<Value> &info)
{
    Isolate *isolate = info.GetIsolate();
    HandleScope scope(isolate);
    try {

        Arrangement_2 &arrangement = ExtractWrapped(info.This());

        Arrangement_2::Halfedge_handle edge;

        if ((info.Length() == 1)
            && Arrangement2Halfedge::ParseArg(isolate, info[0], edge))
        {
            info.GetReturnValue().Set(Arrangement2Face::New(isolate, remove_edge(arrangement, edge)));
            return;
        }

        ARGS_ASSERT(isolate, false);

    }
    catch (const exception &e) {
        isolate->ThrowException(String::NewFromUtf8(isolate, e.what()));
    }
}
