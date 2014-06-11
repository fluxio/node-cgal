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
    if (sConstructorTemplate->HasInstance(arg)) {
        receiver = ExtractWrapped(Local<Object>::Cast(arg));
        return true;
    }

    Line_2 line;
    if (Line2::ParseArg(arg, line)) {
        receiver = Vector_2(line);
        return true;
    }

    Segment_2 segment;
    if (Segment2::ParseArg(arg, segment)) {
        receiver = Vector_2(segment);
        return true;
    }

    Ray_2 ray;
    if (Ray2::ParseArg(arg, ray)) {
        receiver = Vector_2(ray);
        return true;
    }

    if (arg->IsObject()) {
        Local<Object> inits = Local<Object>::Cast(arg);

        K::FT x, y;
        if (::ParseArg(inits->Get(String::NewSymbol("x")), x) &&
            ::ParseArg(inits->Get(String::NewSymbol("y")), y))
        {
            receiver = Vector_2(x, y);
            return true;
        }

    }

    return false;
}


Handle<Value> Vector2::ToPOD(const Vector_2 &vector, bool precise)
{
    HandleScope scope;
    Local<Object> obj = Object::New();

    if (precise) {

        ostringstream xstr;
#if CGAL_USE_EPECK
        xstr << vector.x().exact();
#else
        xstr << setprecision(20) << vector.x();
#endif
        obj->Set(String::NewSymbol("x"), String::New(xstr.str().c_str()));

        ostringstream ystr;
#if CGAL_USE_EPECK
        ystr << vector.y().exact();
#else
        ystr << setprecision(20) << vector.y();
#endif
        obj->Set(String::NewSymbol("y"), String::New(ystr.str().c_str()));

    } else {
        obj->Set(String::NewSymbol("x"), Number::New(CGAL::to_double(vector.x())));
        obj->Set(String::NewSymbol("y"), Number::New(CGAL::to_double(vector.y())));
    }

    return scope.Close(obj);
}
