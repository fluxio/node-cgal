#include "BBox2.h"
#include "cgal_args.h"

using namespace v8;
using namespace node;
using namespace std;


const char *BBox2::Name = "BBox2";


void BBox2::RegisterMethods()
{
    SetPrototypeMethod(sConstructorTemplate, "overlaps", Overlaps);
    SetPrototypeMethod(sConstructorTemplate, "add", Add);
}


bool BBox2::ParseArg(Local<Value> arg, Bbox_2 &receiver)
{
    if (sConstructorTemplate->HasInstance(arg)) {

        // This supports e.g.: newbox = new CGAL.BBox2(oldbox);

        receiver = ExtractWrapped(Local<Object>::Cast(arg));
        return true;

    } else if (arg->IsObject()) {

        // This supports e.g.: newbox = new CGAL.BBox2({xmin:,ymin:,xmax:,ymax:});

        Local<Object> bounds = Local<Object>::Cast(arg);

        if (!bounds->Get(String::NewSymbol("xmin"))->IsNumber()
            || !bounds->Get(String::NewSymbol("ymin"))->IsNumber()
            || !bounds->Get(String::NewSymbol("xmax"))->IsNumber()
            || !bounds->Get(String::NewSymbol("ymax"))->IsNumber())
        {
            return false;
        }

        receiver = Bbox_2(
            bounds->Get(String::NewSymbol("xmin"))->NumberValue(),
            bounds->Get(String::NewSymbol("ymin"))->NumberValue(),
            bounds->Get(String::NewSymbol("xmax"))->NumberValue(),
            bounds->Get(String::NewSymbol("ymax"))->NumberValue()
        );

        return true;

    } else {

        return false;

    }
}


Handle<Value> BBox2::ToPOD(const Bbox_2 &box)
{
    HandleScope scope;
    Local<Object> obj = Object::New();
    obj->Set(String::NewSymbol("xmin"), Number::New(box.xmin()));
    obj->Set(String::NewSymbol("ymin"), Number::New(box.ymin()));
    obj->Set(String::NewSymbol("xmax"), Number::New(box.xmax()));
    obj->Set(String::NewSymbol("ymax"), Number::New(box.ymax()));
    return scope.Close(obj);
}


v8::Handle<v8::Value> BBox2::Overlaps(const v8::Arguments &args)
{
    HandleScope scope;
    try {
        Bbox_2 &thisBox = ExtractWrapped(args.This());
        ARGS_ASSERT(args.Length() == 1);
        ARGS_PARSE_LOCAL(BBox2::ParseArg, Bbox_2, otherBox, args[0]);
        return scope.Close(Boolean::New(do_overlap(thisBox, otherBox)));
    }
    catch (const exception &e) {
        return ThrowException(String::New(e.what()));
    }
}


v8::Handle<v8::Value> BBox2::Add(const v8::Arguments &args)
{
    HandleScope scope;
    try {
        Bbox_2 &thisBox = ExtractWrapped(args.This());
        ARGS_ASSERT(args.Length() == 1);
        ARGS_PARSE_LOCAL(BBox2::ParseArg, Bbox_2, otherBox, args[0]);
        return scope.Close(BBox2::New(thisBox + otherBox));
    }
    catch (const exception &e) {
        return ThrowException(String::New(e.what()));
    }
}
