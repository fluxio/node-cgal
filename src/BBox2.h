#ifndef BBOX2_H
#define BBOX2_H

#include "CGALWrapper.h"
#include "cgal_types.h"
#include "v8.h"


// Wraps the CGAL::Bbox_2 class

class BBox2 : public CGALWrapper<BBox2, Bbox_2>
{
public:

    // The name to be used for our JS class.
    static const char *Name;

    // Add our function templates to the package exports, and return string to be used to name
    // the class and constructor in JS.  Called indirectly at module load time via the module
    // init function.
    static void RegisterMethods();

    // Attempt to parse a v8 object into the CGAL Bbox_2 object referred to by receiver.  Accepts
    // either a BBox2 object or a POD rep {xmin:,ymin:,xmax:,ymax:}.  Returns true if parse was
    // successful, false otherwise.
    static bool ParseArg(v8::Local<v8::Value> arg, Bbox_2 &receiver);

    // Convert a CGAL::BBox_2 object to a POD v8 object of the form  {xmin:,ymin:,xmax:,ymax:}.
    // This may lose precision.
    static v8::Handle<v8::Value> ToPOD(const Bbox_2 &box);

private:

    //
    //----- The following methods will be callable from JS.  These will mostly match
    //      the semantics and names of CGAL::BBox_2 methods.
    //

    // Returns true if this bbox overlaps with the bbox argument.
    static v8::Handle<v8::Value> Overlaps(const v8::Arguments &args);

    // Returns the smallest bbox that contains both this bbox and the bbox arguemnt.
    static v8::Handle<v8::Value> Add(const v8::Arguments &args);

};

#endif // !defined(BBOX2_H)
