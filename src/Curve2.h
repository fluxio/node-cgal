#ifndef CURVE2_H
#define CURVE2_H

#include "CGALWrapper.h"
#include "cgal_types.h"
#include "v8.h"


class Curve2 : public CGALWrapper<Curve2, Curve_2>
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
    static bool ParseArg(v8::Isolate *isolate, v8::Local<v8::Value> arg, Curve_2 &receiver);

    // Convert a CGAL object of the wrapped class to a POD v8 object.  If precise is set to false,
    // will attempt to render in terms of doubles for coordinates, and may lose precision.
    static v8::Local<v8::Value> ToPOD(v8::Isolate *isolate, const Curve_2 &curve, bool precise=true);

private:

    //
    //----- The following methods will be callable from JS.  These will mostly match
    //      the semantics and names of the wrapped CGAL class.
    //

    static void IsSegment(const v8::FunctionCallbackInfo<v8::Value> &info);
    static void Segment(const v8::FunctionCallbackInfo<v8::Value> &info);
    static void IsRay(const v8::FunctionCallbackInfo<v8::Value> &info);
    static void Ray(const v8::FunctionCallbackInfo<v8::Value> &info);
    static void IsLine(const v8::FunctionCallbackInfo<v8::Value> &info);
    static void Line(const v8::FunctionCallbackInfo<v8::Value> &info);
    static void SupportingLine(const v8::FunctionCallbackInfo<v8::Value> &info);
    static void Source(const v8::FunctionCallbackInfo<v8::Value> &info);
    static void Target(const v8::FunctionCallbackInfo<v8::Value> &info);

};

#endif // !defined(CURVE2_H)
