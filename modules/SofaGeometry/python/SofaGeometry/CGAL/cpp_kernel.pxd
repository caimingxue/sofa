# -*- coding: ASCII -*-


cdef extern from "<SofaGeometry/CGAL/Kernel.h>" namespace "SofaGeometryCGAL":

    cdef cppclass Kernel "SofaGeometryCGAL::Kernel":
        Kernel() except +

    cdef cppclass FT "SofaGeometryCGAL::FT":
        FT() except +