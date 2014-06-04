#include "Point2.h"
#include "AffTransformation2.h"
#include "cgal_args.h"
#include "iomanip"

using namespace v8;
using namespace node;
using namespace std;


const char *Point2::Name = "Point2";


void Point2::RegisterMethods()
{
    SetPrototypeMethod(sConstructorTemplate, "toString", ToString);
    SetPrototypeMethod(sConstructorTemplate, "isEqual", IsEqual);
    SetPrototypeMethod(sConstructorTemplate, "x", X);
    SetPrototypeMethod(sConstructorTemplate, "y", Y);
    SetPrototypeMethod(sConstructorTemplate, "transform", Transform);
}


bool Point2::ParseArg(Local<Value> arg, Point_2 &receiver)
{
    if (sConstructorTemplate->HasInstance(arg)) {

        // This supports e.g.: newPoint = new CGAL.Point2(oldPoint);

        receiver = ExtractWrapped(Local<Object>::Cast(arg));
        return true;

    } else if (arg->IsArray()) {

        Local<Array> coords = Local<Array>::Cast(arg);

        if (coords->Length() < 2)
            return false;

        if (coords->Get(0)->IsNumber() && coords->Get(1)->IsNumber()) {

            receiver = Point_2(coords->Get(0)->NumberValue(), coords->Get(1)->NumberValue());
            return true;

        } else if (coords->Get(0)->IsString() && coords->Get(1)->IsString()) {

#ifdef CGAL_USE_EPECK

            K::FT x(CGAL::Epeck_ft(*String::AsciiValue(coords->Get(0))));
            K::FT y(CGAL::Epeck_ft(*String::AsciiValue(coords->Get(1))));

#else // !defined(CGAL_USE_EPECK)

            istringstream xstr(*String::AsciiValue(coords->Get(0)));
            K::FT x;
            xstr >> x;

            istringstream ystr(*String::AsciiValue(coords->Get(1)));
            K::FT y;
            ystr >> y;

#endif // !defined(CGAL_USE_EPECK)

            receiver = Point_2(x, y);
            return true;

        } else {
            return false;
        }

    } else {
        return false;
    }

}


Handle<Value> Point2::ToPOD(const Point_2 &point, bool precise)
{
    HandleScope scope;
    Local<Array> array = Array::New(2);

    if (precise) {

        ostringstream x_str;
#if CGAL_USE_EPECK
        x_str << point.x().exact();
#else
        x_str << setprecision(20) << point.x();
#endif
        array->Set(0, String::New(x_str.str().c_str()));

        ostringstream y_str;
#if CGAL_USE_EPECK
        y_str << point.y().exact();
#else
        y_str << setprecision(20) << point.y();
#endif
        array->Set(1, String::New(y_str.str().c_str()));

    } else {
        array->Set(0, Number::New(CGAL::to_double(point.cartesian(0))));
        array->Set(1, Number::New(CGAL::to_double(point.cartesian(1))));
    }

    return scope.Close(array);
}


Handle<Value> Point2::ToString(const v8::Arguments &args)
{
    HandleScope scope;
    Point_2 &point = ExtractWrapped(args.This());
    ostringstream str;
    str << "[object "  << Name << " " << point << "]";
    return scope.Close(String::New(str.str().c_str()));
}


Handle<Value> Point2::IsEqual(const Arguments &args)
{
    HandleScope scope;
    try {
        Point_2 &thisPoint = ExtractWrapped(args.This());
        ARGS_ASSERT(args.Length() == 1);
        ARGS_PARSE_LOCAL(Point2::ParseArg, Point_2, otherPoint, args[0]);
        return scope.Close(Boolean::New(thisPoint == otherPoint));
    }
    catch (const exception &e) {
        return ThrowException(String::New(e.what()));
    }
}


Handle<Value> Point2::X(const Arguments &args)
{
    HandleScope scope;
    try {
        Point_2 &point = ExtractWrapped(args.This());
        return scope.Close(Number::New(CGAL::to_double(point.x())));
    }
    catch (const exception &e) {
        return ThrowException(String::New(e.what()));
    }
}


Handle<Value> Point2::Y(const Arguments &args)
{
    HandleScope scope;
    try {
        Point_2 &point = ExtractWrapped(args.This());
        return scope.Close(Number::New(CGAL::to_double(point.y())));
    }
    catch (const exception &e) {
        return ThrowException(String::New(e.what()));
    }
}


Handle<Value> Point2::Transform(const Arguments &args)
{
  HandleScope scope;
  try {
    Point_2 &point = ExtractWrapped(args.This());
    ARGS_ASSERT(args.Length() == 1);


    Aff_transformation_2 afft;
    if (AffTransformation2::ParseArg(args[0], afft)) {
      Point_2 new_point = point.transform(afft);
      return scope.Close(New(new_point));
    }

    ARGS_ASSERT(false);
  }
  catch (const exception &e) {
    return ThrowException(String::New(e.what()));
  }
}
