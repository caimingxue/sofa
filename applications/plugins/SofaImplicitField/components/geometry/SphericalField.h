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
#ifndef SOFA_IMPLICIT_SPHERICALFIELD_H
#define SOFA_IMPLICIT_SPHERICALFIELD_H

#include "ScalarField.h"

namespace sofa
{

namespace component
{

namespace geometry
{

namespace _sphericalfield_
{

using sofa::defaulttype::Vec3d ;

class SphericalField  : public ScalarField
{
public:
    SOFA_CLASS(SphericalField, ScalarField);

public:
    SphericalField() ;
    ~SphericalField() { }

    /// Inherited from BaseObject
    virtual void init() override ;
    virtual void reinit() override ;

    /// Inherited from ScalarField.
    virtual double getValue(Vec3d& Pos, int &domain) override ;
    virtual Vec3d getGradient(Vec3d &Pos, int& domain) override ;
    virtual void getValueAndGradient(Vec3d& pos, double& val, Vec3d& grad, int& domain) override ;

    using ScalarField::getValue ;
    using ScalarField::getGradient ;
    using ScalarField::getValueAndGradient ;

    Data<bool> d_inside;
    Data<double> d_radiusSphere;
    Data<Vec3d> d_centerSphere;

protected:
    Vec3d m_center;
    double m_radius;
    bool m_inside;
};

} /// _sphericalfield_

using _sphericalfield_::SphericalField ;

} /// geometry

} /// component

} /// sofa

#endif