#include "Point2.h"
#include "cgal_args.h"

using namespace v8;
using namespace node;
using namespace std;


const char *Point2::Name = "Point2";


void Point2::RegisterMethods()
{
    SetPrototypeMethod(sConstructorTemplate, "x", X);
    SetPrototypeMethod(sConstructorTemplate, "y", Y);
}


bool Point2::ParseArg(Local<Value> arg, Point_2 &receiver)
{
    if (sConstructorTemplate->HasInstance(arg)) {

        // This supports e.g.: newPoint = new CGAL.Point2(oldPoint);

        receiver = ExtractWrapped(Local<Object>::Cast(arg));
        return true;

    } else if (arg->IsArray()) {

        // This supports e.g.: newPoint = new CGAL.Point2([0,0]);

        Local<Array> coords = Local<Array>::Cast(arg);

        if ((coords->Length() < 2)
            || !coords->Get(0)->IsNumber()
            || !coords->Get(1)->IsNumber())
        {
            return false;
        }

        receiver = Point_2(coords->Get(0)->NumberValue(), coords->Get(1)->NumberValue());
        return true;

    } else {

        return false;

    }
}


Handle<Value> Point2::ToPOD(const Point_2 &point)
{
    HandleScope scope;
    Local<Array> array = Array::New(2);
    array->Set(0, Number::New(CGAL::to_double(point.cartesian(0))));
    array->Set(1, Number::New(CGAL::to_double(point.cartesian(1))));
    return scope.Close(array);
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


//----- Explicit instantiations here since we are a shared library:

template class CGALWrapper<Point2, Point_2>;

template bool CGALWrapper<Point2, Point_2>::ParseSeqArg(
    v8::Local<v8::Value> arg, std::back_insert_iterator<std::list<Point_2> >
);

template bool CGALWrapper<Point2, Point_2>::ParseSeqArg(
    v8::Local<v8::Value> arg, std::back_insert_iterator<std::vector<Point_2> >
);

template bool CGALWrapper<Point2, Point_2>::ParseSeqArg(
    v8::Local<v8::Value> arg, std::back_insert_iterator<Polygon_2>
);

template v8::Handle<v8::Value> CGALWrapper<Point2, Point_2>::SeqToPOD(
    std::vector<Point_2>::iterator first, std::vector<Point_2>::iterator last
);
