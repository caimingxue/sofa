#cython: language=c++
from libcpp.memory cimport shared_ptr
from cpp_Ray cimport Ray as _Ray

cdef class Ray:
    cdef shared_ptr[_Ray] inst
