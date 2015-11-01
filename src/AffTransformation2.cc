#include "AffTransformation2.h"
#include "Direction2.h"
#include "cgal_args.h"

using namespace v8;
using namespace node;
using namespace std;


const char *AffTransformation2::Name = "AffTransformation2";


void AffTransformation2::RegisterMethods(v8::Isolate *isolate)
{
}


bool AffTransformation2::ParseArg(Isolate *isolate, Local<Value> arg, Aff_transformation_2 &receiver)
{
    HandleScope scope(isolate);

    if (sConstructorTemplate.Get(isolate)->HasInstance(arg)) {
        receiver = ExtractWrapped(Local<Object>::Cast(arg));
        return true;
    }

    if (arg->IsArray()) {
        Local<Array> inits = Local<Array>::Cast(arg);

        if (inits->Length() >= 6 && inits->Length() <= 7) {

            K::RT m00, m01, m02, m10, m11, m12, hw(1);
            if (::ParseArg(isolate, inits->Get(0), m00) &&
                ::ParseArg(isolate, inits->Get(1), m01) &&
                ::ParseArg(isolate, inits->Get(2), m02) &&
                ::ParseArg(isolate, inits->Get(3), m10) &&
                ::ParseArg(isolate, inits->Get(4), m11) &&
                ::ParseArg(isolate, inits->Get(5), m12))
            {
                if ((inits->Length() == 7) && !::ParseArg(isolate, inits->Get(6), hw))
                    return false;

                receiver = Aff_transformation_2(m00, m01, m02, m10, m11, m12, hw);
                return true;
            }

        }

        if (inits->Length() >= 2 && inits->Length() <= 3) {

            Direction_2 dir;
            K::RT num, den(1);
            if (Direction2::ParseArg(isolate, inits->Get(0), dir) &&
                ::ParseArg(isolate, inits->Get(1), num))
            {
                if ((inits->Length() == 3) && !::ParseArg(isolate, inits->Get(2), den))
                    return false;

                receiver = Aff_transformation_2(Rotation(), dir, num, den);
                return true;
            }

        }

    }

    return false;
}


Local<Value> AffTransformation2::ToPOD(Isolate *isolate, const Aff_transformation_2 &aff, bool precise)
{
    EscapableHandleScope scope(isolate);
    Local<Array> array = Array::New(isolate, 7);

    try {
        for(int i=0; i<7; ++i) {
            int r = (i == 6) ? 2 : i/3;
            int c = (i == 6) ? 2 : i%3;
            K::RT a = aff.hm(r, c);
            if (precise) {
                ostringstream str;
#ifdef CGAL_USE_EPECK
                str << a.exact();
#else
                str << a;
#endif
                array->Set(i, String::NewFromUtf8(isolate, str.str().c_str()));
            } else {
                array->Set(i, Number::New(isolate, CGAL::to_double(a)));
            }
        }
    }

    catch (const exception &e) {
        isolate->ThrowException(String::NewFromUtf8(isolate, e.what()));
    }

    return scope.Escape(array);
}

