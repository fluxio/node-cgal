#ifndef GENIE_CGAL_H
#define GENIE_CGAL_H

#include "node.h"

NODE_MODULE_DECL(cgal);

// Top level init function called at module load time.
void init(v8::Handle<v8::Object> exports);

#endif
