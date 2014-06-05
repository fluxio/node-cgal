#ifndef ARRANGEMENT2HALFEDGE_H
#define ARRANGEMENT2HALFEDGE_H

#include "CGALWrapper.h"
#include "cgal_types.h"
#include "v8.h"


class Arrangement2Halfedge : public CGALWrapper<Arrangement2Halfedge, Arrangement_2::Halfedge_handle>
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
    static bool ParseArg(v8::Local<v8::Value> arg, Arrangement_2::Halfedge_handle &receiver);

    // Convert a CGAL object of the wrapped class to a POD v8 object.  If precise is set to false,
    // will attempt to render in terms of doubles for coordinates, and may lose precision.
    static v8::Handle<v8::Value> ToPOD(const Arrangement_2::Halfedge_handle &halfedge, bool precise=true);

private:

    //
    //----- The following methods will be callable from JS.  These will mostly match
    //      the semantics and names of the wrapped CGAL class.
    //

    static v8::Handle<v8::Value> ToString(const v8::Arguments &args);
    static v8::Handle<v8::Value> IsFictitious(const v8::Arguments &args);
    static v8::Handle<v8::Value> Source(const v8::Arguments &args);
    static v8::Handle<v8::Value> Target(const v8::Arguments &args);
    static v8::Handle<v8::Value> Face(const v8::Arguments &args);
    static v8::Handle<v8::Value> Twin(const v8::Arguments &args);
    static v8::Handle<v8::Value> Prev(const v8::Arguments &args);
    static v8::Handle<v8::Value> Next(const v8::Arguments &args);
    static v8::Handle<v8::Value> CCB(const v8::Arguments &args);
    static v8::Handle<v8::Value> Curve(const v8::Arguments &args);

};

#endif // !defined(ARRANGEMENT2HALFEDGE_H)
