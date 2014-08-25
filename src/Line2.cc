#include "Line2.h"
#include "Point2.h"
#include "cgal_args.h"

using namespace v8;
using namespace node;
using namespace std;


const char *Line2::Name = "Line2";


void Line2::RegisterMethods()
{
    SetPrototypeMethod(sConstructorTemplate, "isEqual", IsEqual);
    SetPrototypeMethod(sConstructorTemplate, "isDegenerate", IsDegenerate);
    SetPrototypeMethod(sConstructorTemplate, "isHorizontal", IsHorizontal);
    SetPrototypeMethod(sConstructorTemplate, "isVertical", IsVertical);
    SetPrototypeMethod(sConstructorTemplate, "opposite", Opposite);
}


bool Line2::ParseArg(Local<Value> arg, Line_2 &receiver)
{
    if (sConstructorTemplate->HasInstance(arg)) {
        receiver = ExtractWrapped(Local<Object>::Cast(arg));
        return true;
    }

    if (arg->IsObject()) {
        Local<Object> inits = Local<Object>::Cast(arg);

        K::FT a, b, c;
        if (::ParseArg(inits->Get(String::NewSymbol("a")), a) &&
            ::ParseArg(inits->Get(String::NewSymbol("b")), b) &&
            ::ParseArg(inits->Get(String::NewSymbol("c")), c))
        {
            receiver = Line_2(a, b, c);
            return true;
        }

        Point_2 p, q;
        if (Point2::ParseArg(inits->Get(String::NewSymbol("p")), p) &&
            Point2::ParseArg(inits->Get(String::NewSymbol("q")), q))
        {
            receiver = Line_2(p, q);
            return true;
        }

    }

    return false;
}


Handle<Value> Line2::ToPOD(const Line_2 &line, bool precise)
{
    HandleScope scope;
    Local<Object> obj = Object::New();

    if (precise) {

        ostringstream astr;
#if CGAL_USE_EPECK
        astr << line.a().exact();
#else
        astr << setprecision(20) << line.a();
#endif
        obj->Set(String::NewSymbol("a"), String::New(astr.str().c_str()));

        ostringstream bstr;
#if CGAL_USE_EPECK
        bstr << line.b().exact();
#else
        bstr << setprecision(20) << line.b();
#endif
        obj->Set(String::NewSymbol("b"), String::New(bstr.str().c_str()));

        ostringstream cstr;
#if CGAL_USE_EPECK
        cstr << line.c().exact();
#else
        cstr << setprecision(20) << line.c();
#endif
        obj->Set(String::NewSymbol("c"), String::New(cstr.str().c_str()));

    } else {
        obj->Set(String::NewSymbol("a"), Number::New(CGAL::to_double(line.a())));
        obj->Set(String::NewSymbol("b"), Number::New(CGAL::to_double(line.b())));
        obj->Set(String::NewSymbol("c"), Number::New(CGAL::to_double(line.c())));
    }

    return scope.Close(obj);
}


Handle<Value> Line2::IsEqual(const Arguments &args)
{
    HandleScope scope;
    try {
        Line_2 &thisLine = ExtractWrapped(args.This());
        ARGS_ASSERT(args.Length() == 1);
        ARGS_PARSE_LOCAL(Line2::ParseArg, Line_2, otherLine, args[0]);
        return scope.Close(Boolean::New(thisLine == otherLine));
    }
    catch (const exception &e) {
        return ThrowException(String::New(e.what()));
    }
}


Handle<Value> Line2::IsDegenerate(const Arguments &args)
{
    HandleScope scope;
    try {
        Line_2 &line = ExtractWrapped(args.This());
        return scope.Close(Boolean::New(line.is_degenerate()));
    }
    catch (const exception &e) {
        return ThrowException(String::New(e.what()));
    }
}


Handle<Value> Line2::IsHorizontal(const Arguments &args)
{
    HandleScope scope;
    try {
        Line_2 &line = ExtractWrapped(args.This());
        return scope.Close(Boolean::New(line.is_horizontal()));
    }
    catch (const exception &e) {
        return ThrowException(String::New(e.what()));
    }
}


Handle<Value> Line2::IsVertical(const Arguments &args)
{
    HandleScope scope;
    try {
        Line_2 &line = ExtractWrapped(args.This());
        return scope.Close(Boolean::New(line.is_vertical()));
    }
    catch (const exception &e) {
        return ThrowException(String::New(e.what()));
    }
}


Handle<Value> Line2::Opposite(const Arguments &args)
{
    HandleScope scope;
    try {
        Line_2 &line = ExtractWrapped(args.This());
        return scope.Close(Line2::New(line.opposite()));
    }
    catch (const exception &e) {
        return ThrowException(String::New(e.what()));
    }
}
