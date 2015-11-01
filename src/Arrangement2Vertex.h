#ifndef ARRANGEMENT2VERTEX_H
#define ARRANGEMENT2VERTEX_H

#include "CGALWrapper.h"
#include "cgal_types.h"
#include "v8.h"


class Arrangement2Vertex : public CGALWrapper<Arrangement2Vertex, Arrangement_2::Vertex_handle>
{
public:

    // The name to be used for our JS class.
    static const char *Name;

    // Add our function templates to the package exports, and return string to be used to name
    // the class and constructor in JS.  Called indirectly at module load time via the module
    // init function.
    static void RegisterMethods(v8::Isolate *isolate);

    // Attempt to parse a v8 argument into the CGAL object referred to by receiver.  Returns true
    // if parse was successful, false otherwise.
    static bool ParseArg(v8::Isolate *isolate, v8::Local<v8::Value> arg, Arrangement_2::Vertex_handle &receiver);

    // Convert a CGAL object of the wrapped class to a POD v8 object.  If precise is set to false,
    // will attempt to render in terms of doubles for coordinates, and may lose precision.
    static v8::Local<v8::Value> ToPOD(
        v8::Isolate *isolate, const Arrangement_2::Vertex_handle &Vertex, bool precise=true
    );

private:

    //
    //----- The following methods will be callable from JS.  These will mostly match
    //      the semantics and names of the wrapped CGAL class.
    //

    static void ToString(const v8::FunctionCallbackInfo<v8::Value> &info);
    static void IsAtOpenBoundary(const v8::FunctionCallbackInfo<v8::Value> &info);
    static void IsIsolated(const v8::FunctionCallbackInfo<v8::Value> &info);
    static void Degree(const v8::FunctionCallbackInfo<v8::Value> &info);
    static void IncidentHalfedges(const v8::FunctionCallbackInfo<v8::Value> &info);
    static void Face(const v8::FunctionCallbackInfo<v8::Value> &info);
    static void Point(const v8::FunctionCallbackInfo<v8::Value> &info);
    static void ParameterSpaceInX(const v8::FunctionCallbackInfo<v8::Value> &info);
    static void ParameterSpaceInY(const v8::FunctionCallbackInfo<v8::Value> &info);

};

// Declare missing output stream operator so compiler can expand default ToString template method.
// We won't actually link against this since the method is shadowed above, but it needs to be
// declared to satisfy the compiler.

namespace std {
    ostream &operator<<(ostream &str, const Arrangement_2::Vertex_handle &vertex);
}

#endif // !defined(ARRANGEMENT2VERTEX_H)
