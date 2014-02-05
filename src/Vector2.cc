#include "Vector2.h"
#include "Point2.h"
#include "Line2.h"
#include "Segment2.h"
#include "Ray2.h"
#include "cgal_args.h"

using namespace v8;
using namespace node;
using namespace std;


const char *Vector2::Name = "Vector2";


void Vector2::RegisterMethods()
{
}


bool Vector2::ParseArg(Local<Value> arg, Vector_2 &receiver)
{
    // This supports e.g.: newvec = new CGAL.Direction2(oldvec);
    if (sConstructorTemplate->HasInstance(arg)) {
        receiver = ExtractWrapped(Local<Object>::Cast(arg));
        return true;
    }

    // This supports e.g.: newvec = new CGAL.Direction2(aLine);
    Line_2 line;
    if (Line2::ParseArg(arg, line)) {
        receiver = Vector_2(line);
        return true;
    }

    // This supports e.g.: newvec = new CGAL.Direction2(aSegment);
    Segment_2 segment;
    if (Segment2::ParseArg(arg, segment)) {
        receiver = Vector_2(segment);
        return true;
    }

    // This supports e.g.: newvec = new CGAL.Direction2(aRay);
    Ray_2 ray;
    if (Ray2::ParseArg(arg, ray)) {
        receiver = Vector_2(ray);
        return true;
    }

    if (arg->IsObject()) {

        Local<Object> inits = Local<Object>::Cast(arg);

        // This supports e.g.: newvec = new CGAL.Vector2({x:,y:});
        if (inits->Has(String::NewSymbol("x")) &&
            inits->Has(String::NewSymbol("y")))
        {
            double dx = inits->Get(String::NewSymbol("x"))->NumberValue();
            double dy = inits->Get(String::NewSymbol("y"))->NumberValue();
            receiver = Vector_2(dx, dy);
            return true;
        }

    } 

    return false;
}


Handle<Value> Vector2::ToPOD(const Vector_2 &vector)
{
    HandleScope scope;
    Local<Object> obj = Object::New();
    obj->Set(String::NewSymbol("x"), Number::New(CGAL::to_double(vector.x())));
    obj->Set(String::NewSymbol("y"), Number::New(CGAL::to_double(vector.y())));
    return scope.Close(obj);
}
