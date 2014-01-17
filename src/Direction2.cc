#include "Direction2.h"
#include "Point2.h"
#include "Line2.h"
#include "Vector2.h"
#include "Segment2.h"
#include "Ray2.h"
#include "cgal_args.h"

using namespace v8;
using namespace node;
using namespace std;


const char *Direction2::Name = "Direction2";


void Direction2::RegisterMethods()
{
    SetPrototypeMethod(sConstructorTemplate, "isEqual", IsEqual);
    SetPrototypeMethod(sConstructorTemplate, "isLessThan", IsLessThan);
    SetPrototypeMethod(sConstructorTemplate, "isGreaterThan", IsGreaterThan);
    SetPrototypeMethod(sConstructorTemplate, "isCCWBetween", IsCCWBetween);
    SetPrototypeMethod(sConstructorTemplate, "opposite", Opposite);
    SetPrototypeMethod(sConstructorTemplate, "toVector", ToVector);
    SetPrototypeMethod(sConstructorTemplate, "dx", DX);
    SetPrototypeMethod(sConstructorTemplate, "dy", DY);
}


bool Direction2::ParseArg(Local<Value> arg, Direction_2 &receiver)
{
    // This supports e.g.: newdir = new CGAL.Direction2(olddir);
    if (sConstructorTemplate->HasInstance(arg)) {
        receiver = ExtractWrapped(Local<Object>::Cast(arg));
        return true;
    }

    // This supports e.g.: newdir = new CGAL.Direction2(aVector);
    Vector_2 vector;
    if (Vector2::ParseArg(arg, vector)) {
        receiver = Direction_2(vector);
        return true;
    }

    // This supports e.g.: newdir = new CGAL.Direction2(aLine);
    Line_2 line;
    if (Line2::ParseArg(arg, line)) {
        receiver = Direction_2(line);
        return true;
    }

    // This supports e.g.: newdir = new CGAL.Direction2(aRay);
    Ray_2 ray;
    if (Ray2::ParseArg(arg, ray)) {
        receiver = Direction_2(ray);
        return true;
    }

    // This supports e.g.: newdir = new CGAL.Direction2(aSegment);
    Segment_2 segment;
    if (Segment2::ParseArg(arg, segment)) {
        receiver = Direction_2(segment);
        return true;
    }

    if (arg->IsObject()) {

        Local<Object> inits = Local<Object>::Cast(arg);

        // This supports e.g.: newdir = new CGAL.Direction2({dx:,dy:});
        if (inits->Has(String::NewSymbol("dx")) &&
            inits->Has(String::NewSymbol("dy")))
        {
            double dx = inits->Get(String::NewSymbol("dx"))->NumberValue();
            double dy = inits->Get(String::NewSymbol("dy"))->NumberValue();
            receiver = Direction_2(dx, dy);
            return true;
        }

    } 

    return false;
}


Handle<Value> Direction2::ToPOD(const Direction_2 &direction)
{
    HandleScope scope;
    Local<Object> obj = Object::New();
    obj->Set(String::NewSymbol("dx"), Number::New(CGAL::to_double(direction.dx())));
    obj->Set(String::NewSymbol("dy"), Number::New(CGAL::to_double(direction.dy())));
    return scope.Close(obj);
}


Handle<Value> Direction2::IsEqual(const v8::Arguments &args)
{
    HandleScope scope;
    try {
        Direction_2 &thisDir = ExtractWrapped(args.This());
        ARGS_ASSERT(args.Length() == 1);
        ARGS_PARSE_LOCAL(Direction2::ParseArg, Direction_2, otherDir, args[0]);
        return scope.Close(Boolean::New(thisDir == otherDir));
    }
    catch (const exception &e) {
        return ThrowException(String::New(e.what()));
    }
}


Handle<Value> Direction2::IsLessThan(const v8::Arguments &args)
{
    HandleScope scope;
    try {
        Direction_2 &thisDir = ExtractWrapped(args.This());
        ARGS_ASSERT(args.Length() == 1);
        ARGS_PARSE_LOCAL(Direction2::ParseArg, Direction_2, otherDir, args[0]);
        return scope.Close(Boolean::New(thisDir < otherDir));
    }
    catch (const exception &e) {
        return ThrowException(String::New(e.what()));
    }
}


Handle<Value> Direction2::IsGreaterThan(const v8::Arguments &args)
{
    HandleScope scope;
    try {
        Direction_2 &thisDir = ExtractWrapped(args.This());
        ARGS_ASSERT(args.Length() == 1);
        ARGS_PARSE_LOCAL(Direction2::ParseArg, Direction_2, otherDir, args[0]);
        return scope.Close(Boolean::New(thisDir > otherDir));
    }
    catch (const exception &e) {
        return ThrowException(String::New(e.what()));
    }
}


Handle<Value> Direction2::IsCCWBetween(const v8::Arguments &args)
{
    HandleScope scope;
    try {
        Direction_2 &dir = ExtractWrapped(args.This());
        ARGS_ASSERT(args.Length() == 2);
        ARGS_PARSE_LOCAL(Direction2::ParseArg, Direction_2, d1, args[0]);
        ARGS_PARSE_LOCAL(Direction2::ParseArg, Direction_2, d2, args[1]);
        return scope.Close(Boolean::New(dir.counterclockwise_in_between(d1, d2)));
    }
    catch (const exception &e) {
        return ThrowException(String::New(e.what()));
    }
}


Handle<Value> Direction2::Opposite(const v8::Arguments &args)
{
    HandleScope scope;
    try {
        Direction_2 &dir = ExtractWrapped(args.This());
        return scope.Close(Direction2::New(-dir));
    }
    catch (const exception &e) {
        return ThrowException(String::New(e.what()));
    }
}


Handle<Value> Direction2::ToVector(const v8::Arguments &args)
{
    HandleScope scope;
    try {
        Direction_2 &dir = ExtractWrapped(args.This());
        return scope.Close(Vector2::New(dir.vector()));
    }
    catch (const exception &e) {
        return ThrowException(String::New(e.what()));
    }
}


Handle<Value> Direction2::DX(const v8::Arguments &args)
{
    HandleScope scope;
    try {
        Direction_2 &dir = ExtractWrapped(args.This());
        return scope.Close(Number::New(CGAL::to_double(dir.dx())));
    }
    catch (const exception &e) {
        return ThrowException(String::New(e.what()));
    }
}


Handle<Value> Direction2::DY(const v8::Arguments &args)
{
    HandleScope scope;
    try {
        Direction_2 &dir = ExtractWrapped(args.This());
        return scope.Close(Number::New(CGAL::to_double(dir.dy())));
    }
    catch (const exception &e) {
        return ThrowException(String::New(e.what()));
    }
}

//----- Explicit instantiations here since we are a shared library:

template class CGALWrapper<Direction2, Direction_2>;
