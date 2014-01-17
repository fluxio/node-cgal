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

        // This supports e.g.: newline = new CGAL.Line2(oldline);

        receiver = ExtractWrapped(Local<Object>::Cast(arg));
        return true;

    } else if (arg->IsObject()) {

        Local<Object> inits = Local<Object>::Cast(arg);

        // This supports e.g.: newline = new CGAL.Line2({a:,b:,c:});
        if (inits->Get(String::NewSymbol("a"))->IsNumber() &&
            inits->Get(String::NewSymbol("b"))->IsNumber() &&
            inits->Get(String::NewSymbol("c"))->IsNumber())
        {
            receiver = Line_2(
                inits->Get(String::NewSymbol("a"))->NumberValue(),
                inits->Get(String::NewSymbol("b"))->NumberValue(),
                inits->Get(String::NewSymbol("c"))->NumberValue()
            );
            return true;
        }

        // This supports e.g.: newline = new CGAL.Line2({p:,q:});
        else if (inits->Has(String::NewSymbol("p")) &&
            inits->Has(String::NewSymbol("q")) )
        {
            Point_2 p;
            if (!Point2::ParseArg(inits->Get(String::NewSymbol("p")), p))
            {
                return false;
            }

            Point_2 q;
            if (!Point2::ParseArg(inits->Get(String::NewSymbol("q")), q))
            {
                return false;
            }

            receiver = Line_2(p, q);
            return true;

        }

        else {
            return false;
        }

    } else {

        return false;

    }
}


Handle<Value> Line2::ToPOD(const Line_2 &line)
{
    HandleScope scope;
    Local<Object> obj = Object::New();
    obj->Set(String::NewSymbol("a"), Number::New(CGAL::to_double(line.a())));
    obj->Set(String::NewSymbol("b"), Number::New(CGAL::to_double(line.b())));
    obj->Set(String::NewSymbol("c"), Number::New(CGAL::to_double(line.c())));
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

//----- Explicit instantiations here since we are a shared library:

template class CGALWrapper<Line2, Line_2>;
