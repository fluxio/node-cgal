#ifndef CGALWRAPPER_H
#define CGALWRAPPER_H

#include "cgal_types.h"
#include "node.h"
#include "node_object_wrap.h"
#include "v8.h"


template<typename WrapperClass, typename CGALClass>
class CGALWrapper : public node::ObjectWrap
{
public:

    CGALWrapper();
    virtual ~CGALWrapper();

    template<typename ParentScope>
    static void Init(v8::Local<ParentScope> exports);

    static v8::Local<v8::Value> New(v8::Isolate *isolate, const CGALClass &CGALInstance);

    template<typename NumberPrimitive>
    static bool ParseArg(v8::Isolate *isolate, v8::Local<v8::Value> arg, NumberPrimitive &parsed);

    template<typename OutputIterator>
    static bool ParseSeqArg(v8::Isolate *isolate, v8::Local<v8::Value> arg, OutputIterator iterator);

    template<typename ForwardIterator>
    static v8::Local<v8::Value> SeqToPOD(
        v8::Isolate *isolate, ForwardIterator first, ForwardIterator last, bool precise
    );

protected:

    CGALClass mWrapped;

    static v8::Global<v8::FunctionTemplate> sConstructorTemplate;

    static CGALClass &ExtractWrapped(v8::Local<v8::Object> obj);

    static void New(const v8::FunctionCallbackInfo<v8::Value> &args);
    static void ToPOD(const v8::FunctionCallbackInfo<v8::Value> &args);
    static void Inspect(const v8::FunctionCallbackInfo<v8::Value> &args);
    static void ToString(const v8::FunctionCallbackInfo<v8::Value> &args);

};


#include "CGALWrapper-inl.h"

#endif // !defined(CGALWRAPPER_H)
