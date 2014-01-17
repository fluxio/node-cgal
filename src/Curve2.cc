#include "Curve2.h"
#include "Line2.h"
#include "Point2.h"
#include "Segment2.h"
#include "Ray2.h"
#include "cgal_args.h"

using namespace v8;
using namespace node;
using namespace std;


const char *Curve2::Name = "Curve2";


void Curve2::RegisterMethods()
{
    SetPrototypeMethod(sConstructorTemplate, "isSegment", IsSegment);
    SetPrototypeMethod(sConstructorTemplate, "segment", Segment);
    SetPrototypeMethod(sConstructorTemplate, "isRay", IsRay);
    SetPrototypeMethod(sConstructorTemplate, "ray", Ray);
    SetPrototypeMethod(sConstructorTemplate, "isLine", IsLine);
    SetPrototypeMethod(sConstructorTemplate, "line", Line);
    SetPrototypeMethod(sConstructorTemplate, "supportingLine", SupportingLine);
    SetPrototypeMethod(sConstructorTemplate, "source", Source);
    SetPrototypeMethod(sConstructorTemplate, "target", Target);
}


bool Curve2::ParseArg(Local<Value> arg, Curve_2 &receiver)
{
    // This supports e.g.: newcurve = new CGAL.Curve2(oldcurve);
    if (sConstructorTemplate->HasInstance(arg)) {
        receiver = ExtractWrapped(Local<Object>::Cast(arg));
        return true;
    }

    // This supports e.g.: newcurve = new CGAL.Curve2(aSegment2);
    Segment_2 segment;
    if (Segment2::ParseArg(arg, segment)) {
        receiver = Curve_2(segment);
        return true;
    }

    // This supports e.g.: newcurve = new CGAL.Curve2(aLine2);
    Line_2 line;
    if (Line2::ParseArg(arg, line)) {
        receiver = Curve_2(line);
        return true;
    }

    // This supports e.g.: newcurve = new CGAL.Curve2(aLine2);
    Ray_2 ray;
    if (Ray2::ParseArg(arg, ray)) {
        receiver = Curve_2(ray);
        return true;
    }

    // no good...
    return false;
}


Handle<Value> Curve2::ToPOD(const Curve_2 &curve)
{
    HandleScope scope;
    Local<Object> obj = Object::New();
    return scope.Close(obj);
}


Handle<Value> Curve2::IsSegment(const v8::Arguments &args)
{
    HandleScope scope;
    try {
        Curve_2 &curve = ExtractWrapped(args.This());
        return scope.Close(Boolean::New(curve.is_segment()));
    }
    catch (const exception &e) {
        return ThrowException(String::New(e.what()));
    }
}


Handle<Value> Curve2::Segment(const v8::Arguments &args)
{
    HandleScope scope;
    try {
        Curve_2 &curve = ExtractWrapped(args.This());
        return scope.Close(Segment2::New(curve.segment()));
    }
    catch (const exception &e) {
        return ThrowException(String::New(e.what()));
    }
}


Handle<Value> Curve2::IsRay(const v8::Arguments &args)
{
    HandleScope scope;
    try {
        Curve_2 &curve = ExtractWrapped(args.This());
        return scope.Close(Boolean::New(curve.is_ray()));
    }
    catch (const exception &e) {
        return ThrowException(String::New(e.what()));
    }
}


Handle<Value> Curve2::Ray(const v8::Arguments &args)
{
    HandleScope scope;
    try {
        Curve_2 &curve = ExtractWrapped(args.This());
        return scope.Close(Ray2::New(curve.ray()));
    }
    catch (const exception &e) {
        return ThrowException(String::New(e.what()));
    }
}


Handle<Value> Curve2::IsLine(const v8::Arguments &args)
{
    HandleScope scope;
    try {
        Curve_2 &curve = ExtractWrapped(args.This());
        return scope.Close(Boolean::New(curve.is_line()));
    }
    catch (const exception &e) {
        return ThrowException(String::New(e.what()));
    }
}


Handle<Value> Curve2::Line(const v8::Arguments &args)
{
    HandleScope scope;
    try {
        Curve_2 &curve = ExtractWrapped(args.This());
        return scope.Close(Line2::New(curve.line()));
    }
    catch (const exception &e) {
        return ThrowException(String::New(e.what()));
    }
}


Handle<Value> Curve2::SupportingLine(const v8::Arguments &args)
{
    HandleScope scope;
    try {
        Curve_2 &curve = ExtractWrapped(args.This());
        return scope.Close(Line2::New(curve.supporting_line()));
    }
    catch (const exception &e) {
        return ThrowException(String::New(e.what()));
    }
}


Handle<Value> Curve2::Source(const v8::Arguments &args)
{
    HandleScope scope;
    try {
        Curve_2 &curve = ExtractWrapped(args.This());
        return scope.Close(Point2::New(curve.source()));
    }
    catch (const exception &e) {
        return ThrowException(String::New(e.what()));
    }
}


Handle<Value> Curve2::Target(const v8::Arguments &args)
{
    HandleScope scope;
    try {
        Curve_2 &curve = ExtractWrapped(args.This());
        return scope.Close(Point2::New(curve.target()));
    }
    catch (const exception &e) {
        return ThrowException(String::New(e.what()));
    }
}

//----- Explicit instantiations here since we are a shared library:

template class CGALWrapper<Curve2, Curve_2>;
