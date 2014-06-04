#ifndef RAY2_H
#define RAY2_H

#include "CGALWrapper.h"
#include "cgal_types.h"
#include "v8.h"


class Ray2 : public CGALWrapper<Ray2, Ray_2>
{
public:

    // The name to be used for our JS class.
    static const char *Name;

    // Add our function templates to the package exports, and return string to be used to name
    // the class and constructor in JS.  Called indirectly at module load time via the module
    // init function.
    static void RegisterMethods();

    // Attempt to parse a v8 argument into the CGAL object referred to by receiver.  Returns true
    // if parse was successful, false otherwise.
    static bool ParseArg(v8::Local<v8::Value> arg, Ray_2 &receiver);

    // Convert a CGAL object of the wrapped class to a POD v8 object.  If precise is set to false,
    // will attempt to render in terms of doubles for coordinates, and may lose precision.
    static v8::Handle<v8::Value> ToPOD(const Ray_2 &ray, bool precise=true);

private:

    //
    //----- The following methods will be callable from JS.  These will mostly match
    //      the semantics and names of the wrapped CGAL class.
    //

    static v8::Handle<v8::Value> IsEqual(const v8::Arguments &args);
    static v8::Handle<v8::Value> Source(const v8::Arguments &args);
    static v8::Handle<v8::Value> Point(const v8::Arguments &args);
    static v8::Handle<v8::Value> Direction(const v8::Arguments &args);
    static v8::Handle<v8::Value> ToVector(const v8::Arguments &args);
    static v8::Handle<v8::Value> SupportingLine(const v8::Arguments &args);
    static v8::Handle<v8::Value> Opposite(const v8::Arguments &args);
    static v8::Handle<v8::Value> IsDegenerate(const v8::Arguments &args);
    static v8::Handle<v8::Value> IsHorizontal(const v8::Arguments &args);
    static v8::Handle<v8::Value> IsVertical(const v8::Arguments &args);
    static v8::Handle<v8::Value> HasOn(const v8::Arguments &args);
    static v8::Handle<v8::Value> CollinearHasOn(const v8::Arguments &args);

};

#endif // !defined(SEGMENT2_H)
