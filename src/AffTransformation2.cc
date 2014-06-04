#include "AffTransformation2.h"
#include "Direction2.h"
#include "cgal_args.h"

using namespace v8;
using namespace node;
using namespace std;


const char *AffTransformation2::Name = "AffTransformation2";


void AffTransformation2::RegisterMethods()
{
}


bool AffTransformation2::ParseArg(Local<Value> arg, Aff_transformation_2 &receiver)
{
    if (sConstructorTemplate->HasInstance(arg)) {

        receiver = ExtractWrapped(Local<Object>::Cast(arg));
        return true;

    } else if (arg->IsArray()) {

        Local<Array> coords = Local<Array>::Cast(arg);
        if (coords->Length() >= 6 && coords->Length() <= 7) {

            if (coords->Get(0)->IsNumber() && coords->Get(1)->IsNumber() &&
                coords->Get(2)->IsNumber() && coords->Get(3)->IsNumber() &&
                coords->Get(4)->IsNumber() && coords->Get(5)->IsNumber() &&
                (coords->Length() == 6 || coords->Get(6)->IsNumber())) {

                K::RT hw(1);
                if (coords->Length() == 7)
                    hw = K::RT(coords->Get(6)->NumberValue());

                K::RT m00(coords->Get(0)->NumberValue());
                K::RT m01(coords->Get(1)->NumberValue());
                K::RT m02(coords->Get(2)->NumberValue());
                K::RT m10(coords->Get(3)->NumberValue());
                K::RT m11(coords->Get(4)->NumberValue());
                K::RT m12(coords->Get(5)->NumberValue());

                receiver = Aff_transformation_2(m00, m01, m02, m10, m11, m12, hw);
                return true;

            } else if (coords->Get(0)->IsString() && coords->Get(1)->IsString() &&
                coords->Get(2)->IsString() && coords->Get(3)->IsString() &&
                coords->Get(4)->IsString() && coords->Get(5)->IsString() &&
                (coords->Length() == 6 || coords->Get(6)->IsString())) {

                K::RT hw(1);

#ifdef CGAL_USE_EPECK

                if (coords->Length() == 7)
                    hw = K::RT(CGAL::Epeck_ft(*String::AsciiValue(coords->Get(6))));

                K::RT m00(CGAL::Epeck_ft(*String::AsciiValue(coords->Get(0))));
                K::RT m01(CGAL::Epeck_ft(*String::AsciiValue(coords->Get(1))));
                K::RT m02(CGAL::Epeck_ft(*String::AsciiValue(coords->Get(2))));
                K::RT m10(CGAL::Epeck_ft(*String::AsciiValue(coords->Get(3))));
                K::RT m11(CGAL::Epeck_ft(*String::AsciiValue(coords->Get(4))));
                K::RT m12(CGAL::Epeck_ft(*String::AsciiValue(coords->Get(5))));

#else // !defined(CGAL_USE_EPECK)

                if (coords->Length() == 7)
                    hw = K::RT(atof(*String::AsciiValue(coords->Get(6))));

                K::RT m00(atof(*String::AsciiValue(coords->Get(0))));
                K::RT m01(atof(*String::AsciiValue(coords->Get(1))));
                K::RT m02(atof(*String::AsciiValue(coords->Get(2))));
                K::RT m10(atof(*String::AsciiValue(coords->Get(3))));
                K::RT m11(atof(*String::AsciiValue(coords->Get(4))));
                K::RT m12(atof(*String::AsciiValue(coords->Get(5))));

#endif // !defined(CGAL_USE_EPECK)

                receiver = Aff_transformation_2(m00, m01, m02, m10, m11, m12, hw);
                return true;

            } else {
                return false;
            }

        } else if (coords->Length() == 2 || coords->Length() == 3) {

            Direction_2 dir;
            if (Direction2::ParseArg(coords->Get(0), dir) && coords->Get(1)->IsNumber()
                && (coords->Length() == 2 || coords->Get(2)->IsNumber())) {

                K::RT den(1);
                if (coords->Length() == 3)
                    den = K::RT(coords->Get(2)->NumberValue());

                K::RT num(coords->Get(1)->NumberValue());

                receiver = Aff_transformation_2(Rotation(), dir, num, den);
                return true;

            } else {
                return false;
            }

        } else {
            return false;
        }

    } else {
        return false;
    }

}


Handle<Value> AffTransformation2::ToPOD(const Aff_transformation_2 &aff, bool precise)
{
    HandleScope scope;
    Local<Array> array = Array::New(7);

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
                array->Set(i, String::New(str.str().c_str()));
            } else {
                array->Set(i, Number::New(CGAL::to_double(a)));
            }
        }
    }

    catch (const exception &e) {
        return ThrowException(String::New(e.what()));
    }

    return scope.Close(array);
}

