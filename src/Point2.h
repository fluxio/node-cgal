#ifndef POINT2_H
#define POINT2_H

#include "CGALWrapper.h"
#include "cgal_types.h"
#include "v8.h"


class Point2 : public CGALWrapper<Point2, Point_2>
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
    static bool ParseArg(v8::Isolate *Isolate, v8::Local<v8::Value> arg, Point_2 &receiver);

    // Convert a CGAL object of the wrapped class to a POD v8 object.  If precise is set to false,
    // will attempt to render in terms of doubles for coordinates, and may lose precision.
    static v8::Local<v8::Value> ToPOD(v8::Isolate *isolate, const Point_2 &point, bool precise=true);

private:

    //
    //----- The following methods will be callable from JS.  These will mostly match
    //      the semantics and names of CGAL::Point_2 methods.
    //

    static void IsEqual(const v8::FunctionCallbackInfo<v8::Value> &info);
    static void X(const v8::FunctionCallbackInfo<v8::Value> &info);
    static void Y(const v8::FunctionCallbackInfo<v8::Value> &info);
    static void Transform(const v8::FunctionCallbackInfo<v8::Value> &info);

};

#endif // !defined(POINT2_H)
