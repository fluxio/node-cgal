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
    static void RegisterMethods(v8::Isolate *isolate);

    // Attempt to parse a v8 argument into the CGAL object referred to by receiver.  Returns true
    // if parse was successful, false otherwise.
    static bool ParseArg(v8::Isolate *isolate, v8::Local<v8::Value> arg, Polygon_set_2 &receiver);

    // Convert a CGAL object of the wrapped class to a POD v8 object.  If precise is set to false,
    // will attempt to render in terms of doubles for coordinates, and may lose precision.
    static v8::Local<v8::Value> ToPOD(v8::Isolate *isolate, const Polygon_set_2 &polySet, bool precise=true);

private:

    //
    //----- The following methods will be callable from JS.  These will mostly match
    //      the semantics and names of the wrapped CGAL class.
    //

    static void PolygonsWithHoles(const v8::FunctionCallbackInfo<v8::Value> &info);
    static void NumPolygonsWithHoles(const v8::FunctionCallbackInfo<v8::Value> &info);
    static void IsEmpty(const v8::FunctionCallbackInfo<v8::Value> &info);
    static void IsPlane(const v8::FunctionCallbackInfo<v8::Value> &info);
    // static void Arrangement(const v8::FunctionCallbackInfo<v8::Value> &info);
    static void Clear(const v8::FunctionCallbackInfo<v8::Value> &info);
    static void Insert(const v8::FunctionCallbackInfo<v8::Value> &info);
    static void Complement(const v8::FunctionCallbackInfo<v8::Value> &info);
    static void Intersection(const v8::FunctionCallbackInfo<v8::Value> &info);
    static void Join(const v8::FunctionCallbackInfo<v8::Value> &info);
    static void Difference(const v8::FunctionCallbackInfo<v8::Value> &info);
    static void SymmetricDifference(const v8::FunctionCallbackInfo<v8::Value> &info);
    static void Intersects(const v8::FunctionCallbackInfo<v8::Value> &info);
    // static void Locate(const v8::FunctionCallbackInfo<v8::Value> &info);
    static void OrientedSide(const v8::FunctionCallbackInfo<v8::Value> &info);
    static void IsValid(const v8::FunctionCallbackInfo<v8::Value> &info);

};

namespace std {
    ostream &operator<<(ostream &str, const Polygon_set_2 &pset);
}

#endif // !defined(POLYGONSET2_H)
