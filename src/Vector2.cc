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


void Vector2::RegisterMethods(Isolate *isolate)
{
}


bool Vector2::ParseArg(Isolate *isolate, Local<Value> arg, Vector_2 &receiver)
{
    HandleScope scope(isolate);

    if (sConstructorTemplate.Get(isolate)->HasInstance(arg)) {
        receiver = ExtractWrapped(Local<Object>::Cast(arg));
        return true;
    }

    Line_2 line;
    if (Line2::ParseArg(isolate, arg, line)) {
        receiver = Vector_2(line);
        return true;
    }

    Segment_2 segment;
    if (Segment2::ParseArg(isolate, arg, segment)) {
        receiver = Vector_2(segment);
        return true;
    }

    Ray_2 ray;
    if (Ray2::ParseArg(isolate, arg, ray)) {
        receiver = Vector_2(ray);
        return true;
    }

    if (arg->IsObject()) {
        Local<Object> inits = Local<Object>::Cast(arg);

        K::FT x, y;
        if (::ParseArg(isolate, inits->Get(SYMBOL(isolate, "x")), x) &&
            ::ParseArg(isolate, inits->Get(SYMBOL(isolate, "y")), y))
        {
            receiver = Vector_2(x, y);
            return true;
        }

    }

    return false;
}


Local<Value> Vector2::ToPOD(Isolate *isolate, const Vector_2 &vector, bool precise)
{
    EscapableHandleScope scope(isolate);
    Local<Object> obj = Object::New(isolate);

    if (precise) {

        ostringstream xstr;
#if CGAL_USE_EPECK
        xstr << vector.x().exact();
#else
        xstr << setprecision(20) << vector.x();
#endif
        obj->Set(SYMBOL(isolate, "x"), String::NewFromUtf8(isolate, xstr.str().c_str()));

        ostringstream ystr;
#if CGAL_USE_EPECK
        ystr << vector.y().exact();
#else
        ystr << setprecision(20) << vector.y();
#endif
        obj->Set(SYMBOL(isolate, "y"), String::NewFromUtf8(isolate, ystr.str().c_str()));

    } else {
        obj->Set(SYMBOL(isolate, "x"), Number::New(isolate, CGAL::to_double(vector.x())));
        obj->Set(SYMBOL(isolate, "y"), Number::New(isolate, CGAL::to_double(vector.y())));
    }

    return scope.Escape(obj);
}
