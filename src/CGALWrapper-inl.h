#ifndef CGALWRAPPER_INL_H
#define CGALWRAPPER_INL_H

#include "CGAL/Object.h"
#include "cgal_args.h"


template<typename WrapperClass, typename CGALClass>
v8::Persistent<v8::FunctionTemplate> CGALWrapper<WrapperClass, CGALClass>::sConstructorTemplate;


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
void CGALWrapper<WrapperClass, CGALClass>::Init(v8::Handle<ParentScope> exports)
{
    // In some circumstances, our module init gets called more than once within the same process by
    // node.  We need to be careful to avoid re-initializing our static constructor template,
    // otherwise we can get type detection failures against objects constructed with the previous
    // value.

    if (sConstructorTemplate.IsEmpty()) {

        sConstructorTemplate = v8::Persistent<v8::FunctionTemplate>::New(
            v8::FunctionTemplate::New(CGALWrapper<WrapperClass, CGALClass>::New)
        );

        node::SetPrototypeMethod(sConstructorTemplate, "toPOD", CGALWrapper<WrapperClass, CGALClass>::ToPOD);
        node::SetPrototypeMethod(sConstructorTemplate, "inspect", CGALWrapper<WrapperClass, CGALClass>::Inspect);

        WrapperClass::RegisterMethods();

        sConstructorTemplate->InstanceTemplate()->SetInternalFieldCount(1);
        sConstructorTemplate->SetClassName(v8::String::NewSymbol(WrapperClass::Name));

    }

    exports->Set(v8::String::NewSymbol(WrapperClass::Name), sConstructorTemplate->GetFunction());
}


template<typename WrapperClass, typename CGALClass>
v8::Handle<v8::Value> CGALWrapper<WrapperClass, CGALClass>::New(const CGALClass &CGALInstance)
{
    v8::HandleScope scope;
    v8::Local<v8::Object> wrapper = sConstructorTemplate->GetFunction()->NewInstance();
    CGALClass &wrapped = ExtractWrapped(wrapper);
    wrapped = CGALInstance;
    return scope.Close(wrapper);
}


template<typename WrapperClass, typename CGALClass>
template<typename ForwardIterator>
v8::Handle<v8::Value> CGALWrapper<WrapperClass, CGALClass>::SeqToPOD(ForwardIterator first, ForwardIterator last)
{
    v8::HandleScope scope;
    v8::Local<v8::Array> array = v8::Array::New();
    ForwardIterator it;
    uint32_t i;
    for(it=first,i=0; it!=last; ++it,++i) {
        array->Set(i, WrapperClass::ToPOD(*it));
    }
    return scope.Close(array);
}


template<typename WrapperClass, typename CGALClass>
template<typename OutputIterator>
bool CGALWrapper<WrapperClass, CGALClass>::ParseSeqArg(v8::Local<v8::Value> arg, OutputIterator iterator)
{
    v8::HandleScope scope;
    if (!arg->IsArray()) return false;
    v8::Local<v8::Array> wrappers = v8::Local<v8::Array>::Cast(arg);
    for(uint32_t i=0; i<wrappers->Length(); ++i) {
        CGALClass newCGALInstance;
        if (WrapperClass::ParseArg(wrappers->Get(i), newCGALInstance)) {
            *(iterator++) = newCGALInstance;
        } else {
            return false;
        }
    }
    return true;
}


template<typename WrapperClass, typename CGALClass>
CGALClass &CGALWrapper<WrapperClass, CGALClass>::ExtractWrapped(v8::Handle<v8::Object> obj)
{
    return node::ObjectWrap::Unwrap<WrapperClass>(obj)->mWrapped;
}


template<typename WrapperClass, typename CGALClass>
v8::Handle<v8::Value> CGALWrapper<WrapperClass, CGALClass>::New(const v8::Arguments &args)
{
    v8::HandleScope scope;

    ARGS_ASSERT(args.Length() <= 1);

    WrapperClass *wrapper = new WrapperClass();

    if (args.Length() == 1) {
        ARGS_ASSERT(WrapperClass::ParseArg(args[0], wrapper->mWrapped));
    }

    wrapper->Wrap(args.This());

    return scope.Close(args.This());
}


template<typename WrapperClass, typename CGALClass>
v8::Handle<v8::Value> CGALWrapper<WrapperClass, CGALClass>::ToPOD(const v8::Arguments &args)
{
    v8::HandleScope scope;
    WrapperClass *wrapper = ObjectWrap::Unwrap<WrapperClass>(args.This());
    return scope.Close(WrapperClass::ToPOD(wrapper->mWrapped));
}


template<typename WrapperClass, typename CGALClass>
v8::Handle<v8::Value> CGALWrapper<WrapperClass, CGALClass>::Inspect(const v8::Arguments &args)
{
    v8::HandleScope scope;
    return scope.Close(args.This()->ToString());
}


#endif // !defined(CGALWRAPPER_INL_H)
