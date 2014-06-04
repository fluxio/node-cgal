#include "Ray2.h"
#include "Point2.h"
#include "Line2.h"
#include "Direction2.h"
#include "Vector2.h"
#include "cgal_args.h"

using namespace v8;
using namespace node;
using namespace std;


const char *Ray2::Name = "Ray2";


void Ray2::RegisterMethods()
{
    SetPrototypeMethod(sConstructorTemplate, "isEqual", IsEqual);
    SetPrototypeMethod(sConstructorTemplate, "source", Source);
    SetPrototypeMethod(sConstructorTemplate, "point", Point);
    SetPrototypeMethod(sConstructorTemplate, "direction", Direction);
    SetPrototypeMethod(sConstructorTemplate, "toVector", ToVector);
    SetPrototypeMethod(sConstructorTemplate, "supportingLine", SupportingLine);
    SetPrototypeMethod(sConstructorTemplate, "opposite", Opposite);
    SetPrototypeMethod(sConstructorTemplate, "isDegenerate", IsDegenerate);
    SetPrototypeMethod(sConstructorTemplate, "isHorizontal", IsHorizontal);
    SetPrototypeMethod(sConstructorTemplate, "isVertical", IsVertical);
    SetPrototypeMethod(sConstructorTemplate, "hasOn", HasOn);
    SetPrototypeMethod(sConstructorTemplate, "collinearHasOn", CollinearHasOn);
}


bool Ray2::ParseArg(Local<Value> arg, Ray_2 &receiver)
{
    if (sConstructorTemplate->HasInstance(arg)) {

        // This supports e.g.: newray = new CGAL.Segment2(oldray);

        receiver = ExtractWrapped(Local<Object>::Cast(arg));
        return true;

    } else if (arg->IsObject()) {

        Local<Object> inits = Local<Object>::Cast(arg);

        // This supports e.g.: newline = new CGAL.Ray2({p:,d:});
        if (inits->Has(String::NewSymbol("p")) &&
            inits->Has(String::NewSymbol("d")))
        {
            Point_2 p;
            if (!Point2::ParseArg(inits->Get(String::NewSymbol("p")), p))
                return false;

            Direction_2 d;
            if (!Direction2::ParseArg(inits->Get(String::NewSymbol("d")), d))
                return false;

            receiver = Ray_2(p, d);
            return true;
        }

        // This supports e.g.: newseg = new CGAL.Ray2({p:,q:});
        if (inits->Has(String::NewSymbol("p")) &&
            inits->Has(String::NewSymbol("q")))
        {
            Point_2 p;
            if (!Point2::ParseArg(inits->Get(String::NewSymbol("p")), p))
                return false;

            Point_2 q;
            if (!Point2::ParseArg(inits->Get(String::NewSymbol("q")), q))
                return false;

            receiver = Ray_2(p, q);
            return true;
        }

        // This supports e.g.: newline = new CGAL.Ray2({p:,l:});
        if (inits->Has(String::NewSymbol("p")) &&
            inits->Has(String::NewSymbol("l")))
        {
            Point_2 p;
            if (!Point2::ParseArg(inits->Get(String::NewSymbol("p")), p))
                return false;

            Line_2 l;
            if (!Line2::ParseArg(inits->Get(String::NewSymbol("l")), l))
                return false;

            receiver = Ray_2(p, l);
            return true;
        }

        // This supports e.g.: newline = new CGAL.Ray2({p:,v:});
        if (inits->Has(String::NewSymbol("p")) &&
            inits->Has(String::NewSymbol("v")))
        {
            Point_2 p;
            if (!Point2::ParseArg(inits->Get(String::NewSymbol("p")), p))
                return false;

            Vector_2 v;
            if (!Vector2::ParseArg(inits->Get(String::NewSymbol("v")), v))
                return false;

            receiver = Ray_2(p, v);
            return true;
        }

        return false;

    } else {

        return false;

    }
}


Handle<Value> Ray2::ToPOD(const Ray_2 &ray, bool precise)
{
    HandleScope scope;
    Local<Object> obj = Object::New();
    obj->Set(String::NewSymbol("p"), Point2::ToPOD(ray.source(), precise));
    obj->Set(String::NewSymbol("d"), Direction2::ToPOD(ray.direction(), precise));
    return scope.Close(obj);
}


Handle<Value> Ray2::IsEqual(const v8::Arguments &args)
{
    HandleScope scope;
    try {
        Ray_2 &thisRay = ExtractWrapped(args.This());
        ARGS_ASSERT(args.Length() == 1);
        ARGS_PARSE_LOCAL(Ray2::ParseArg, Ray_2, otherRay, args[0]);
        return scope.Close(Boolean::New(thisRay == otherRay));
    }
    catch (const exception &e) {
        return ThrowException(String::New(e.what()));
    }
}


Handle<Value> Ray2::Source(const v8::Arguments &args)
{
    HandleScope scope;
    try {
        Ray_2 &ray = ExtractWrapped(args.This());
        return scope.Close(Point2::New(ray.source()));
    }
    catch (const exception &e) {
        return ThrowException(String::New(e.what()));
    }
}


Handle<Value> Ray2::Point(const v8::Arguments &args)
{
    HandleScope scope;
    try {
        Ray_2 &ray = ExtractWrapped(args.This());
        ARGS_ASSERT(args.Length() == 1);
        ARGS_ASSERT(args[0]->IsNumber())
        return scope.Close(Point2::New(ray.point(args[0]->NumberValue())));
    }
    catch (const exception &e) {
        return ThrowException(String::New(e.what()));
    }
}


Handle<Value> Ray2::Direction(const v8::Arguments &args)
{
    HandleScope scope;
    try {
        Ray_2 &ray = ExtractWrapped(args.This());
        return scope.Close(Direction2::New(ray.direction()));
    }
    catch (const exception &e) {
        return ThrowException(String::New(e.what()));
    }
}


Handle<Value> Ray2::ToVector(const v8::Arguments &args)
{
    HandleScope scope;
    try {
        Ray_2 &ray = ExtractWrapped(args.This());
        return scope.Close(Vector2::New(ray.to_vector()));
    }
    catch (const exception &e) {
        return ThrowException(String::New(e.what()));
    }
}


Handle<Value> Ray2::SupportingLine(const v8::Arguments &args)
{
    HandleScope scope;
    try {
        Ray_2 &ray = ExtractWrapped(args.This());
        return scope.Close(Line2::New(ray.supporting_line()));
    }
    catch (const exception &e) {
        return ThrowException(String::New(e.what()));
    }
}


Handle<Value> Ray2::Opposite(const v8::Arguments &args)
{
    HandleScope scope;
    try {
        Ray_2 &ray = ExtractWrapped(args.This());
        return scope.Close(Ray2::New(ray.opposite()));
    }
    catch (const exception &e) {
        return ThrowException(String::New(e.what()));
    }
}


Handle<Value> Ray2::IsDegenerate(const v8::Arguments &args)
{
    HandleScope scope;
    try {
        Ray_2 &ray = ExtractWrapped(args.This());
        return scope.Close(Boolean::New(ray.is_degenerate()));
    }
    catch (const exception &e) {
        return ThrowException(String::New(e.what()));
    }
}


Handle<Value> Ray2::IsHorizontal(const v8::Arguments &args)
{
    HandleScope scope;
    try {
        Ray_2 &ray = ExtractWrapped(args.This());
        return scope.Close(Boolean::New(ray.is_horizontal()));
    }
    catch (const exception &e) {
        return ThrowException(String::New(e.what()));
    }
}


Handle<Value> Ray2::IsVertical(const v8::Arguments &args)
{
    HandleScope scope;
    try {
        Ray_2 &ray = ExtractWrapped(args.This());
        return scope.Close(Boolean::New(ray.is_vertical()));
    }
    catch (const exception &e) {
        return ThrowException(String::New(e.what()));
    }
}


Handle<Value> Ray2::HasOn(const v8::Arguments &args)
{
    HandleScope scope;
    try {
        Ray_2 &ray = ExtractWrapped(args.This());
        ARGS_ASSERT(args.Length() == 1);
        ARGS_PARSE_LOCAL(Point2::ParseArg, Point_2, point, args[0]);
        return scope.Close(Boolean::New(ray.has_on(point)));
    }
    catch (const exception &e) {
        return ThrowException(String::New(e.what()));
    }
}


Handle<Value> Ray2::CollinearHasOn(const v8::Arguments &args)
{
    HandleScope scope;
    try {
        Ray_2 &ray = ExtractWrapped(args.This());
        ARGS_ASSERT(args.Length() == 1);
        ARGS_PARSE_LOCAL(Point2::ParseArg, Point_2, point, args[0]);
        return scope.Close(Boolean::New(ray.collinear_has_on(point)));
    }
    catch (const exception &e) {
        return ThrowException(String::New(e.what()));
    }
}
