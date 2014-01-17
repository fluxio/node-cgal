#ifndef CGALWRAPPER_H
#define CGALWRAPPER_H

#include "node.h"
#include "v8.h"


template<typename WrapperClass, typename CGALClass>
class CGALWrapper : public node::ObjectWrap
{
public:

    CGALWrapper();
    virtual ~CGALWrapper();

    template<typename ParentScope>
    static void Init(v8::Handle<ParentScope> exports);

    static v8::Handle<v8::Value> New(const CGALClass &CGALInstance);

    template<typename OutputIterator>
    static bool ParseSeqArg(v8::Local<v8::Value> arg, OutputIterator iterator);

    template<typename ForwardIterator>
    static v8::Handle<v8::Value> SeqToPOD(ForwardIterator first, ForwardIterator last);

protected:

    CGALClass mWrapped;

    static v8::Persistent<v8::FunctionTemplate> sConstructorTemplate;

    static CGALClass &ExtractWrapped(v8::Handle<v8::Object> obj);

    static v8::Handle<v8::Value> New(const v8::Arguments &args);
    static v8::Handle<v8::Value> ToPOD(const v8::Arguments &args);
    static v8::Handle<v8::Value> Inspect(const v8::Arguments &args);

};


#include "CGALWrapper-inl.h"

#endif // !defined(CGALWRAPPER_H)
