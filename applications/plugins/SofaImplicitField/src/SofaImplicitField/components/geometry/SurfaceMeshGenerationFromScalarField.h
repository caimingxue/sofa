/******************************************************************************
*       SOFA, Simulation Open-Framework Architecture, development version     *
*                (c) 2006-2017 INRIA, USTL, UJF, CNRS, MGH                    *
*                                                                             *
* This program is free software; you can redistribute it and/or modify it     *
* under the terms of the GNU Lesser General Public License as published by    *
* the Free Software Foundation; either version 2.1 of the License, or (at     *
* your option) any later version.                                             *
*                                                                             *
* This program is distributed in the hope that it will be useful, but WITHOUT *
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or       *
* FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License *
* for more details.                                                           *
*                                                                             *
* You should have received a copy of the GNU Lesser General Public License    *
* along with this program. If not, see <http://www.gnu.org/licenses/>.        *
*******************************************************************************
* Authors: The SOFA Team and external contributors (see Authors.txt)          *
*                                                                             *
* Contact information: contact@sofa-framework.org                             *
******************************************************************************/
#ifndef SOFAIMPLICITFIELD_COMPONENT_SURFACEMESHGENERATIONFRMOSCALARFIELD_H
#define SOFAIMPLICITFIELD_COMPONENT_SURFACEMESHGENERATIONFRMOSCALARFIELD_H
#include <SofaImplicitField/config.h>

/// Topology
#include <SofaBaseTopology/MeshTopology.h>

#include <SofaImplicitField/components/geometry/ScalarField.h>

////////////////////////////////////////////////////////////////////////////////////////////////////
namespace sofa
{

namespace component
{

namespace geometry
{

namespace _surfacemeshgenerationfromscalarfield_
{
typedef sofa::core::topology::BaseMeshTopology::SeqTriangles SeqTriangles;
typedef sofa::core::topology::BaseMeshTopology::Triangle Triangle;
typedef sofa::helper::vector<sofa::defaulttype::Vec3d> VecCoord;

using sofa::core::visual::VisualParams ;
using sofa::core::objectmodel::BaseObject ;
using sofa::defaulttype::Vec3d ;

class SurfaceMeshGenerationFromScalarField : public BaseObject
{
public:
    SOFA_CLASS(SurfaceMeshGenerationFromScalarField, BaseObject);

    virtual void init() override ;
    virtual void draw(const VisualParams*params) override ;

    double getStep() const { return mStep.getValue(); }
    void setStep(double val) { mStep.setValue(val); }

    double getIsoValue() const { return mIsoValue.getValue(); }
    void setIsoValue(double val) { mIsoValue.setValue(val); }

    const Vec3d& getGridMin() const { return mGridMin.getValue(); }
    void setGridMin(const Vec3d& val) { mGridMin.setValue(val); }
    void setGridMin(double x, double y, double z) { mGridMin.setValue( Vec3d(x,y,z)); }

    const Vec3d& getGridMax() const { return mGridMax.getValue(); }
    void setGridMax(const Vec3d& val) { mGridMax.setValue(val); }
    void setGridMax(double x, double y, double z) { mGridMax.setValue( Vec3d(x,y,z)); }

protected:
    Data< ScalarFieldR3 > d_evalFunction;

    Data <double > mStep;
    Data <double > mIsoValue;

    Data< Vec3d > mGridMin;
    Data< Vec3d > mGridMax;

    /// For each cube, store the vertex indices on each 3 first edges, and the data value
    struct CubeData
    {
        int p[3];
        double data;
        inline friend std::istream& operator >> ( std::istream& in, CubeData& c)
        {
            in >> c.p[0] >> c.p[1] >> c.p[2] >> c.data;

            return in;
        }

        inline friend std::ostream& operator << ( std::ostream& out, const CubeData& c)
        {
            out << c.p[0] << " " << c.p[1] << " " << c.p[2] << " " << c.data ;
            return out;
        }
    };

    int addPoint(VecCoord& v, int i, Vec3d pos, const Vec3d& gridmin, double v0, double v1, double step, double iso)
    {
        pos[i] -= (iso-v0)/(v1-v0);
        v.push_back( (pos * step)+gridmin ) ;
        return v.size()-1;
    }

    int addFace(SeqTriangles& triangles, int p1, int p2, int p3, int nbp)
    {
        if ((unsigned)p1<(unsigned)nbp &&
            (unsigned)p2<(unsigned)nbp &&
            (unsigned)p3<(unsigned)nbp)
        {
            triangles.push_back(Triangle(p1, p3, p2));
            return triangles.size()-1;
        }
        else
        {
            return -1;
        }
    }

    /// Output
    Data<VecCoord>      d_out_points;
    Data<SeqTriangles>  d_out_triangles;
    Data<bool> d_visuCavity;

    Data < sofa::helper::vector<CubeData> > planes;
    typename sofa::helper::vector<CubeData>::iterator P0; /// Pointer to first plane
    typename sofa::helper::vector<CubeData>::iterator P1; /// Pointer to second plane

    void newPlane();
    void generateSurfaceMesh();

protected:
    SurfaceMeshGenerationFromScalarField() ;
    virtual ~SurfaceMeshGenerationFromScalarField() ;
};

} /// namespace _surfacemeshgenerationfromscalarfield_
} /// namespace mapping
} /// namespace component
} /// namespace sofa

#endif /// SOFAIMPLICITFIELD_COMPONENT_SURFACEMESHGENERATIONFRMOSCALARFIELD_H
