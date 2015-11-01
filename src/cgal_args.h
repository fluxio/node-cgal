#ifndef CGAL_ARGS_H
#define CGAL_ARGS_H

#define ARGS_ASSERT(ISOLATE, ASSERTION)                             \
    if (!(ASSERTION)) {                                             \
        (ISOLATE)->ThrowException(                                  \
            v8::Exception::TypeError(                               \
                v8::String::NewFromUtf8(ISOLATE, "Wrong arguments") \
            )                                                       \
        );                                                          \
    }                                                               \


#define ARGS_PARSE_LOCAL(ISOLATE, PARSER, ARG_TYPE, RECEIVER, ARG) \
    ARG_TYPE RECEIVER;                                             \
    ARGS_ASSERT(ISOLATE, PARSER(ISOLATE, ARG, RECEIVER));          \


#define ARGS_PARSE_LOCAL_SEQ(ISOLATE, PARSER, ARG_TYPE, RECEIVER, ARG)        \
    ARG_TYPE RECEIVER;                                                        \
    ARGS_ASSERT(ISOLATE, PARSER(ISOLATE, ARG, std::back_inserter(RECEIVER))); \


#define ARGS_PARSE_NEW(ISOLATE, PARSER, ARG_TYPE, RECEIVER, ARG) \
    ARG_TYPE *RECEIVER = new ARG_TYPE();                         \
    ARGS_ASSERT(ISOLATE, PARSER(ISOLATE, ARG, *RECEIVER));       \


#define NOARGS_PARSE_NEW(ISOLATE, PARSER, ARG_TYPE, RECEIVER) \
    ARG_TYPE *RECEIVER = new ARG_TYPE();                      \
    ARGS_ASSERT(ISOLATE, PARSER(ISOLATE, *RECEIVER));         \


// Convenience macro for the deprecated v8::String::NewSymbol, beacuse
// the recommended replacement incantation is super verbose...

#define SYMBOL(ISOLATE, STRING) v8::String::NewFromUtf8(ISOLATE, STRING, v8::String::kInternalizedString)

#endif // !defined(CGAL_ARGS_H)
