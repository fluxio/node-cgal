cgal
====

[![Build Status](https://travis-ci.org/Vannevartech/cgal.png?branch=master)](https://travis-ci.org/Vannevartech/cgal)

A node.js module providing access to parts of the CGAL computational geometry library (non-SWIG).

- Prerequisite: you will need to have the CGAL libraries and headers installed on your build and
test machines for this.  CGAL sources can be downloaded from cgal.org, and built and installed by following the directions there.  This release has been developed and tested against CGAL release 
4.3.

- To install and test locally, do "npm install", and "npm test" in this directory.

- To install into and test within a different node application, change to the target application's
top level directory and do "npm install <path-to-this-dir>" and "npm test cgal".

- Shell variables CGAL_GYP_INCLUDES, CGAL_GYP_CXXFLAGS, and CGAL_GYP_LDFLAGS can be used to pass
additional options to the bindings build (e.g. to point to CGAL includes and libs installed in
non-standard locations or off the system include/library paths.)

More soon (work in progress...)
