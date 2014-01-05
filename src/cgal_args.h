#ifndef CGAL_ARGS_H
#define CGAL_ARGS_H

#define ARGS_ASSERT(ASSERTION)                                                                   \
    if (!(ASSERTION)) {                                                                          \
        return v8::ThrowException(v8::Exception::TypeError(v8::String::New("Wrong arguments"))); \
    }                                                                                            \


#define ARGS_PARSE_LOCAL(PARSER, ARG_TYPE, RECEIVER, ARG) \
    ARG_TYPE RECEIVER;                                    \
    ARGS_ASSERT(PARSER(ARG, RECEIVER));                   \


#define ARGS_PARSE_LOCAL_SEQ(PARSER, ARG_TYPE, RECEIVER, ARG) \
    ARG_TYPE RECEIVER;                                        \
    ARGS_ASSERT(PARSER(ARG, std::back_inserter(RECEIVER)));   \


#define ARGS_PARSE_NEW(PARSER, ARG_TYPE, RECEIVER, ARG)   \
    ARG_TYPE *RECEIVER = new ARG_TYPE();                  \
    ARGS_ASSERT(PARSER(ARG, *RECEIVER));                  \


#define NOARGS_PARSE_NEW(PARSER, ARG_TYPE, RECEIVER)    \
    ARG_TYPE *RECEIVER = new ARG_TYPE();                \
    ARGS_ASSERT(PARSER(*RECEIVER));                     \


#endif // !defined(CGAL_ARGS_H)
