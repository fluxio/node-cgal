#ifndef CGALWRAPPER_INL_H
#define CGALWRAPPER_INL_H

#include "CGAL/Object.h"
#include "cgal_args.h"
#include <sstream>


template<typename WrapperClass, typename CGALClass>
v8::Global<v8::FunctionTemplate> CGALWrapper<WrapperClass, CGALClass>::sConstructorTemplate;


template<typename WrapperClass, typename CGALClass>
CGALWrapper<WrapperClass, CGALClass>::CGALWrapper()
{
}


template<typename WrapperClass, typename CGALClass>
CGALWrapper<WrapperClass, CGALClass>::~CGALWrapper()
{
}


template<typename WrapperClass, typename CGALClass>
template<typename ParentScope>
void CGALWrapper<WrapperClass, CGALClass>::Init(v8::Local<ParentScope> exports)
{
    v8::Isolate *isolate = v8::Isolate::GetCurrent();
    v8::HandleScope scope(isolate);

    // In some circumstances, our module init gets called more than once within the same process by
    // node.  We need to be careful to avoid re-initializing our static constructor template,
    // otherwise we can get type detection failures against objects constructed with the previous
    // value.

    if (sConstructorTemplate.IsEmpty()) {

        v8::Local<v8::FunctionTemplate> constructorTemplate
            = v8::FunctionTemplate::New(isolate, CGALWrapper<WrapperClass, CGALClass>::New);

        sConstructorTemplate.Reset(isolate, constructorTemplate);

        NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "toPOD", CGALWrapper<WrapperClass, CGALClass>::ToPOD);
        NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "inspect", CGALWrapper<WrapperClass, CGALClass>::Inspect);
        NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "toString", CGALWrapper<WrapperClass, CGALClass>::ToString);

        WrapperClass::RegisterMethods(isolate);

        constructorTemplate->InstanceTemplate()->SetInternalFieldCount(1);
        constructorTemplate->SetClassName(v8::String::NewFromUtf8(isolate, WrapperClass::Name));

    }

    exports->Set(
        v8::String::NewFromUtf8(isolate, WrapperClass::Name),
        sConstructorTemplate.Get(isolate)->GetFunction()
    );
}


template<typename WrapperClass, typename CGALClass>
v8::Local<v8::Value> CGALWrapper<WrapperClass, CGALClass>::New(v8::Isolate *isolate, const CGALClass &CGALInstance)
{
    v8::EscapableHandleScope scope(isolate);
    v8::Local<v8::Object> wrapper = sConstructorTemplate.Get(isolate)->GetFunction()->NewInstance();
    CGALClass &wrapped = ExtractWrapped(wrapper);
    wrapped = CGALInstance;
    return scope.Escape(wrapper);
}


template<typename NumberPrimitive>
bool ParseArg(v8::Isolate *isolate, v8::Local<v8::Value> obj, NumberPrimitive &parsed)
{
    if (obj->IsNumber()) {
        parsed = obj->NumberValue();
        return true;
    } else if (obj->IsString()) {
        std::istringstream str(*v8::String::Utf8Value(obj));
        str >> parsed;
        return !str.fail();
    } else {
        return false;
    }
}


template<typename WrapperClass, typename CGALClass>
template<typename ForwardIterator>
v8::Local<v8::Value> CGALWrapper<WrapperClass, CGALClass>::SeqToPOD(
    v8::Isolate *isolate,
    ForwardIterator first, ForwardIterator last,
    bool precise)
{
    v8::EscapableHandleScope scope(isolate);
    v8::Local<v8::Array> array = v8::Array::New(isolate);
    ForwardIterator it;
    uint32_t i;
    for(it=first,i=0; it!=last; ++it,++i) {
        array->Set(i, WrapperClass::ToPOD(isolate, *it, precise));
    }
    return scope.Escape(array);
}


template<typename WrapperClass, typename CGALClass>
template<typename OutputIterator>
bool CGALWrapper<WrapperClass, CGALClass>::ParseSeqArg(
    v8::Isolate *isolate,
    v8::Local<v8::Value> arg,
    OutputIterator iterator)
{
    v8::HandleScope scope(isolate);
    if (!arg->IsArray()) return false;
    v8::Local<v8::Array> wrappers = v8::Local<v8::Array>::Cast(arg);
    for(uint32_t i=0; i<wrappers->Length(); ++i) {
        CGALClass newCGALInstance;
        if (WrapperClass::ParseArg(isolate, wrappers->Get(i), newCGALInstance)) {
            *(iterator++) = newCGALInstance;
        } else {
            return false;
        }
    }
    return true;
}


template<typename WrapperClass, typename CGALClass>
CGALClass &CGALWrapper<WrapperClass, CGALClass>::ExtractWrapped(v8::Local<v8::Object> obj)
{
    return node::ObjectWrap::Unwrap<WrapperClass>(obj)->mWrapped;
}


template<typename WrapperClass, typename CGALClass>
void CGALWrapper<WrapperClass, CGALClass>::New(const v8::FunctionCallbackInfo<v8::Value> &info)
{
    v8::Isolate *isolate = info.GetIsolate();

    ARGS_ASSERT(isolate, info.Length() <= 1);

    WrapperClass *wrapper = new WrapperClass();

    if (info.Length() == 1) {
        ARGS_ASSERT(isolate, WrapperClass::ParseArg(isolate, info[0], wrapper->mWrapped));
    }

    wrapper->Wrap(info.This());

    info.GetReturnValue().Set(info.This());
}


template<typename WrapperClass, typename CGALClass>
void CGALWrapper<WrapperClass, CGALClass>::ToPOD(const v8::FunctionCallbackInfo<v8::Value> &info)
{
    v8::Isolate *isolate = info.GetIsolate();
    v8::HandleScope scope(isolate);
    WrapperClass *wrapper = ObjectWrap::Unwrap<WrapperClass>(info.This());
    ARGS_ASSERT(isolate, info.Length() <= 1)

    bool precise = true;
    if (info.Length() == 1) {
        ARGS_ASSERT(isolate, info[0]->IsBoolean())
        precise = info[0]->BooleanValue();
    }

    info.GetReturnValue().Set(WrapperClass::ToPOD(isolate, wrapper->mWrapped, precise));
}


template<typename WrapperClass, typename CGALClass>
void CGALWrapper<WrapperClass, CGALClass>::Inspect(const v8::FunctionCallbackInfo<v8::Value> &info)
{
    v8::Isolate *isolate = info.GetIsolate();
    v8::HandleScope scope(isolate);
    info.GetReturnValue().Set(info.This()->ToString());
}


template<typename WrapperClass, typename CGALClass>
void CGALWrapper<WrapperClass, CGALClass>::ToString(const v8::FunctionCallbackInfo<v8::Value> &info)
{
    v8::Isolate *isolate = info.GetIsolate();
    v8::HandleScope scope(isolate);
    CGALClass &wrapped = ExtractWrapped(info.This());
    std::ostringstream str;
    str << "[object "  << WrapperClass::Name << " " << wrapped << "]";
    info.GetReturnValue().Set(v8::String::NewFromUtf8(isolate, str.str().c_str()));
}


#endif // !defined(CGALWRAPPER_INL_H)
