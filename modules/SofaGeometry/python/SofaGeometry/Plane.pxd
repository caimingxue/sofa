from libcpp.memory cimport shared_ptr
from cpp_Plane cimport Plane as _Plane
from vector cimport Vec3d

cdef class Plane:
    cdef shared_ptr[_Plane] planeptr
    cdef __init__v(self, Vec3d normal, Vec3d position)
     
