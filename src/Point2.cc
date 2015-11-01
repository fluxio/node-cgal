#include "Point2.h"
#include "AffTransformation2.h"
#include "cgal_args.h"
#include "iomanip"

using namespace v8;
using namespace node;
using namespace std;


const char *Point2::Name = "Point2";


void Point2::RegisterMethods(Isolate *isolate)
{
    HandleScope scope(isolate);
    Local<FunctionTemplate> constructorTemplate = sConstructorTemplate.Get(isolate);
    NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "isEqual", IsEqual);
    NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "x", X);
    NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "y", Y);
    NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "transform", Transform);
}


bool Point2::ParseArg(Isolate *isolate, Local<Value> arg, Point_2 &receiver)
{
    if (sConstructorTemplate.Get(isolate)->HasInstance(arg)) {
        receiver = ExtractWrapped(Local<Object>::Cast(arg));
        return true;
    }

    if (arg->IsArray()) {
        Local<Array> coords = Local<Array>::Cast(arg);

        K::FT x, y;
        if (::ParseArg(isolate, coords->Get(0), x) &&
            ::ParseArg(isolate, coords->Get(1), y))
        {
            receiver = Point_2(x, y);
            return true;
        }

    }

    return false;
}


Local<Value> Point2::ToPOD(Isolate *isolate, const Point_2 &point, bool precise)
{
    EscapableHandleScope scope(isolate);
    Local<Array> array = Array::New(isolate, 2);

    if (precise) {

        ostringstream x_str;
#if CGAL_USE_EPECK
        x_str << point.x().exact();
#else
        x_str << setprecision(20) << point.x();
#endif
        array->Set(0, String::NewFromUtf8(isolate, x_str.str().c_str()));

        ostringstream y_str;
#if CGAL_USE_EPECK
        y_str << point.y().exact();
#else
        y_str << setprecision(20) << point.y();
#endif
        array->Set(1, String::NewFromUtf8(isolate, y_str.str().c_str()));

    } else {
        array->Set(0, Number::New(isolate, CGAL::to_double(point.cartesian(0))));
        array->Set(1, Number::New(isolate, CGAL::to_double(point.cartesian(1))));
    }

    return scope.Escape(array);
}


void Point2::IsEqual(const FunctionCallbackInfo<Value> &info)
{
    Isolate *isolate = info.GetIsolate();
    HandleScope scope(isolate);
    try {
        Point_2 &thisPoint = ExtractWrapped(info.This());
        ARGS_ASSERT(isolate, info.Length() == 1);
        ARGS_PARSE_LOCAL(isolate, Point2::ParseArg, Point_2, otherPoint, info[0]);
        info.GetReturnValue().Set(Boolean::New(isolate, thisPoint == otherPoint));
    }
    catch (const exception &e) {
        isolate->ThrowException(String::NewFromUtf8(isolate, e.what()));
    }
}


void Point2::X(const FunctionCallbackInfo<Value> &info)
{
    Isolate *isolate = info.GetIsolate();
    HandleScope scope(isolate);
    try {
        Point_2 &point = ExtractWrapped(info.This());
        info.GetReturnValue().Set(Number::New(isolate, CGAL::to_double(point.x())));
    }
    catch (const exception &e) {
        isolate->ThrowException(String::NewFromUtf8(isolate, e.what()));
    }
}


void Point2::Y(const FunctionCallbackInfo<Value> &info)
{
    Isolate *isolate = info.GetIsolate();
    HandleScope scope(isolate);
    try {
        Point_2 &point = ExtractWrapped(info.This());
        info.GetReturnValue().Set(Number::New(isolate, CGAL::to_double(point.y())));
    }
    catch (const exception &e) {
        isolate->ThrowException(String::NewFromUtf8(isolate, e.what()));
    }
}


void Point2::Transform(const FunctionCallbackInfo<Value> &info)
{
    Isolate *isolate = info.GetIsolate();
    HandleScope scope(isolate);
    try {
        Point_2 &point = ExtractWrapped(info.This());
        ARGS_ASSERT(isolate, info.Length() == 1);
        Aff_transformation_2 afft;
        if (AffTransformation2::ParseArg(isolate, info[0], afft)) {
            Point_2 new_point = point.transform(afft);
            info.GetReturnValue().Set(New(isolate, new_point));
            return;
        }
        ARGS_ASSERT(isolate, false);
    }
    catch (const exception &e) {
        isolate->ThrowException(String::NewFromUtf8(isolate, e.what()));
    }
}
