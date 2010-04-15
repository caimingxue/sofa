/******************************************************************************
*       SOFA, Simulation Open-Framework Architecture, version 1.0 beta 4      *
*                (c) 2006-2009 MGH, INRIA, USTL, UJF, CNRS                    *
*                                                                             *
* This library is free software; you can redistribute it and/or modify it     *
* under the terms of the GNU Lesser General Public License as published by    *
* the Free Software Foundation; either version 2.1 of the License, or (at     *
* your option) any later version.                                             *
*                                                                             *
* This library is distributed in the hope that it will be useful, but WITHOUT *
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or       *
* FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License *
* for more details.                                                           *
*                                                                             *
* You should have received a copy of the GNU Lesser General Public License    *
* along with this library; if not, write to the Free Software Foundation,     *
* Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301 USA.          *
*******************************************************************************
*                               SOFA :: Modules                               *
*                                                                             *
* Authors: The SOFA Team and external contributors (see Authors.txt)          *
*                                                                             *
* Contact information: contact@sofa-framework.org                             *
******************************************************************************/
#ifndef SOFA_GPU_OPENCL_OPENCLSPRINGFORCEFIELD_INL
#define SOFA_GPU_OPENCL_OPENCLSPRINGFORCEFIELD_INL

#include "OpenCLSpringForceField.h"
#include <sofa/component/forcefield/SpringForceField.inl>
#include <sofa/component/forcefield/StiffSpringForceField.inl>
#include <sofa/component/forcefield/MeshSpringForceField.inl>
#include <sofa/component/forcefield/TriangleBendingSprings.inl>
#include <sofa/component/forcefield/QuadBendingSprings.inl>

namespace sofa
{

namespace gpu
{

namespace opencl
{

//
//extern "C"
//{
//extern void SpringForceFieldOpenCL3f_addForce(unsigned int nbVertex, unsigned int nbSpringPerVertex, const _device_pointer springs, _device_pointer f, const _device_pointer x, const _device_pointer v);
//extern void SpringForceFieldOpenCL3f_addExternalForce(unsigned int nbVertex, unsigned int nbSpringPerVertex, const _device_pointer springs, _device_pointer f1, const _device_pointer x1, const _device_pointer v1, const _device_pointer x2, const _device_pointer v2);
//extern void StiffSpringForceFieldOpenCL3f_addForce(unsigned int nbVertex, unsigned int nbSpringPerVertex, const _device_pointer springs, _device_pointer f, const _device_pointer x, const _device_pointer v, _device_pointer dfdx);
//extern void StiffSpringForceFieldOpenCL3f_addExternalForce(unsigned int nbVertex, unsigned int nbSpringPerVertex, const _device_pointer springs, _device_pointer f1, const _device_pointer x1, const _device_pointer v1, const _device_pointer x2, const _device_pointer v2, _device_pointer dfdx);
//extern void StiffSpringForceFieldOpenCL3f_addDForce(unsigned int nbVertex, unsigned int nbSpringPerVertex, const _device_pointer springs, _device_pointer f, const _device_pointer dx, const _device_pointer x, const _device_pointer dfdx, double factor);
//extern void StiffSpringForceFieldOpenCL3f_addExternalDForce(unsigned int nbVertex, unsigned int nbSpringPerVertex, const _device_pointer springs, _device_pointer f1, const _device_pointer dx1, const _device_pointer x1, const _device_pointer dx2, const _device_pointer x2, const _device_pointer dfdx, double factor);
//
//struct SpringDForceOp
//{
//	int size;
//	unsigned int nbSpringPerVertex;
//	_device_pointer springs;
//	_device_pointer f;
//	_device_pointer dx;
//	_device_pointer x;
//	_device_pointer dfdx;
//};
//
//extern void MultiStiffSpringForceFieldOpenCL3f_addDForce(int n, SpringDForceOp* ops, double factor);
//
//extern void SpringForceFieldOpenCL3f1_addForce(unsigned int nbVertex, unsigned int nbSpringPerVertex, const _device_pointer springs, _device_pointer f, const _device_pointer x, const _device_pointer v);
//extern void SpringForceFieldOpenCL3f1_addExternalForce(unsigned int nbVertex, unsigned int nbSpringPerVertex, const _device_pointer springs, _device_pointer f1, const _device_pointer x1, const _device_pointer v1, const _device_pointer x2, const _device_pointer v2);
//extern void StiffSpringForceFieldOpenCL3f1_addForce(unsigned int nbVertex, unsigned int nbSpringPerVertex, const _device_pointer springs, _device_pointer f, const _device_pointer x, const _device_pointer v, _device_pointer dfdx);
//extern void StiffSpringForceFieldOpenCL3f1_addExternalForce(unsigned int nbVertex, unsigned int nbSpringPerVertex, const _device_pointer springs, _device_pointer f1, const _device_pointer x1, const _device_pointer v1, const _device_pointer x2, const _device_pointer v2, _device_pointer dfdx);
//extern void StiffSpringForceFieldOpenCL3f1_addDForce(unsigned int nbVertex, unsigned int nbSpringPerVertex, const _device_pointer springs, _device_pointer f, const _device_pointer dx, const _device_pointer x, const _device_pointer dfdx, double factor);
//extern void StiffSpringForceFieldOpenCL3f1_addExternalDForce(unsigned int nbVertex, unsigned int nbSpringPerVertex, const _device_pointer springs, _device_pointer f1, const _device_pointer dx1, const _device_pointer x1, const _device_pointer dx2, const _device_pointer x2, const _device_pointer dfdx, double factor);
//
//
//
//extern void SpringForceFieldOpenCL3d_addForce(unsigned int nbVertex, unsigned int nbSpringPerVertex, const _device_pointer springs, _device_pointer f, const _device_pointer x, const _device_pointer v);
//extern void SpringForceFieldOpenCL3d_addExternalForce(unsigned int nbVertex, unsigned int nbSpringPerVertex, const _device_pointer springs, _device_pointer f1, const _device_pointer x1, const _device_pointer v1, const _device_pointer x2, const _device_pointer v2);
//extern void StiffSpringForceFieldOpenCL3d_addForce(unsigned int nbVertex, unsigned int nbSpringPerVertex, const _device_pointer springs, _device_pointer f, const _device_pointer x, const _device_pointer v, _device_pointer dfdx);
//extern void StiffSpringForceFieldOpenCL3d_addExternalForce(unsigned int nbVertex, unsigned int nbSpringPerVertex, const _device_pointer springs, _device_pointer f1, const _device_pointer x1, const _device_pointer v1, const _device_pointer x2, const _device_pointer v2, _device_pointer dfdx);
//extern void StiffSpringForceFieldOpenCL3d_addDForce(unsigned int nbVertex, unsigned int nbSpringPerVertex, const _device_pointer springs, _device_pointer f, const _device_pointer dx, const _device_pointer x, const _device_pointer dfdx, double factor);
//extern void StiffSpringForceFieldOpenCL3d_addExternalDForce(unsigned int nbVertex, unsigned int nbSpringPerVertex, const _device_pointer springs, _device_pointer f1, const _device_pointer dx1, const _device_pointer x1, const _device_pointer dx2, const _device_pointer x2, const _device_pointer dfdx, double factor);
//
//extern void SpringForceFieldOpenCL3d1_addForce(unsigned int nbVertex, unsigned int nbSpringPerVertex, const _device_pointer springs, _device_pointer f, const _device_pointer x, const _device_pointer v);
//extern void SpringForceFieldOpenCL3d1_addExternalForce(unsigned int nbVertex, unsigned int nbSpringPerVertex, const _device_pointer springs, _device_pointer f1, const _device_pointer x1, const _device_pointer v1, const _device_pointer x2, const _device_pointer v2);
//extern void StiffSpringForceFieldOpenCL3d1_addForce(unsigned int nbVertex, unsigned int nbSpringPerVertex, const _device_pointer springs, _device_pointer f, const _device_pointer x, const _device_pointer v, _device_pointer dfdx);
//extern void StiffSpringForceFieldOpenCL3d1_addExternalForce(unsigned int nbVertex, unsigned int nbSpringPerVertex, const _device_pointer springs, _device_pointer f1, const _device_pointer x1, const _device_pointer v1, const _device_pointer x2, const _device_pointer v2, _device_pointer dfdx);
//extern void StiffSpringForceFieldOpenCL3d1_addDForce(unsigned int nbVertex, unsigned int nbSpringPerVertex, const _device_pointer springs, _device_pointer f, const _device_pointer dx, const _device_pointer x, const _device_pointer dfdx, double factor);
//extern void StiffSpringForceFieldOpenCL3d1_addExternalDForce(unsigned int nbVertex, unsigned int nbSpringPerVertex, const _device_pointer springs, _device_pointer f1, const _device_pointer dx1, const _device_pointer x1, const _device_pointer dx2, const _device_pointer x2, const _device_pointer dfdx, double factor);
//
//
//
//} // extern "C"
//
//
//template<>
//class OpenCLKernelsSpringForceField<OpenCLVec3fTypes>
//{
//public:
//	static void addForce(unsigned int nbVertex, unsigned int nbSpringPerVertex, const _device_pointer springs, _device_pointer f, const _device_pointer x, const _device_pointer v)
//	{   SpringForceFieldOpenCL3f_addForce(nbVertex, nbSpringPerVertex, springs, f, x, v); }
//	static void addExternalForce(unsigned int nbVertex, unsigned int nbSpringPerVertex, const _device_pointer springs, _device_pointer f1, const _device_pointer x1, const _device_pointer v1, const _device_pointer x2, const _device_pointer v2)
//	{   SpringForceFieldOpenCL3f_addExternalForce(nbVertex, nbSpringPerVertex, springs, f1, x1, v1, x2, v2); }
//	static void addForce(unsigned int nbVertex, unsigned int nbSpringPerVertex, const _device_pointer springs, _device_pointer f, const _device_pointer x, const _device_pointer v, _device_pointer dfdx)
//	{   StiffSpringForceFieldOpenCL3f_addForce(nbVertex, nbSpringPerVertex, springs, f, x, v, dfdx); }
//	static void addExternalForce(unsigned int nbVertex, unsigned int nbSpringPerVertex, const _device_pointer springs, _device_pointer f1, const _device_pointer x1, const _device_pointer v1, const _device_pointer x2, const _device_pointer v2, _device_pointer dfdx)
//	{   StiffSpringForceFieldOpenCL3f_addExternalForce(nbVertex, nbSpringPerVertex, springs, f1, x1, v1, x2, v2, dfdx); }
//	static void addDForce(unsigned int nbVertex, unsigned int nbSpringPerVertex, const _device_pointer springs, _device_pointer f, const _device_pointer dx, const _device_pointer x, const _device_pointer dfdx, double factor)
//	{   StiffSpringForceFieldOpenCL3f_addDForce(nbVertex, nbSpringPerVertex, springs, f, dx, x, dfdx, factor); }
//	static void addExternalDForce(unsigned int nbVertex, unsigned int nbSpringPerVertex, const _device_pointer springs, _device_pointer f1, const _device_pointer dx1, const _device_pointer x1, const _device_pointer dx2, const _device_pointer x2, const _device_pointer dfdx, double factor)
//	{   StiffSpringForceFieldOpenCL3f_addExternalDForce(nbVertex, nbSpringPerVertex, springs, f1, dx1, x1, dx2, x2, dfdx, factor); }
//
//	static bool supportMultiAddDForce() { return myopenclMultiOpMax>0; }
//	static void multiAddDForce(int n, SpringDForceOp* ops, double factor)
//	{   MultiStiffSpringForceFieldOpenCL3f_addDForce(n, ops, factor); }
//};
//
//template<>
//class OpenCLKernelsSpringForceField<OpenCLVec3f1Types>
//{
//public:
//	static void addForce(unsigned int nbVertex, unsigned int nbSpringPerVertex, const _device_pointer springs, _device_pointer f, const _device_pointer x, const _device_pointer v)
//	{   SpringForceFieldOpenCL3f1_addForce(nbVertex, nbSpringPerVertex, springs, f, x, v); }
//	static void addExternalForce(unsigned int nbVertex, unsigned int nbSpringPerVertex, const _device_pointer springs, _device_pointer f1, const _device_pointer x1, const _device_pointer v1, const _device_pointer x2, const _device_pointer v2)
//	{   SpringForceFieldOpenCL3f1_addExternalForce(nbVertex, nbSpringPerVertex, springs, f1, x1, v1, x2, v2); }
//	static void addForce(unsigned int nbVertex, unsigned int nbSpringPerVertex, const _device_pointer springs, _device_pointer f, const _device_pointer x, const _device_pointer v, _device_pointer dfdx)
//	{   StiffSpringForceFieldOpenCL3f1_addForce(nbVertex, nbSpringPerVertex, springs, f, x, v, dfdx); }
//	static void addExternalForce(unsigned int nbVertex, unsigned int nbSpringPerVertex, const _device_pointer springs, _device_pointer f1, const _device_pointer x1, const _device_pointer v1, const _device_pointer x2, const _device_pointer v2, _device_pointer dfdx)
//	{   StiffSpringForceFieldOpenCL3f1_addExternalForce(nbVertex, nbSpringPerVertex, springs, f1, x1, v1, x2, v2, dfdx); }
//	static void addDForce(unsigned int nbVertex, unsigned int nbSpringPerVertex, const _device_pointer springs, _device_pointer f, const _device_pointer dx, const _device_pointer x, const _device_pointer dfdx, double factor)
//	{   StiffSpringForceFieldOpenCL3f1_addDForce(nbVertex, nbSpringPerVertex, springs, f, dx, x, dfdx, factor); }
//	static void addExternalDForce(unsigned int nbVertex, unsigned int nbSpringPerVertex, const _device_pointer springs, _device_pointer f1, const _device_pointer dx1, const _device_pointer x1, const _device_pointer dx2, const _device_pointer x2, const _device_pointer dfdx, double factor)
//	{   StiffSpringForceFieldOpenCL3f1_addExternalDForce(nbVertex, nbSpringPerVertex, springs, f1, dx1, x1, dx2, x2, dfdx, factor); }
//
//	static bool supportMultiAddDForce() { return false; }
//	static void multiAddDForce(int, SpringDForceOp*, double)
//	{}
//};
//
//
//
//template<>
//class OpenCLKernelsSpringForceField<OpenCLVec3dTypes>
//{
//public:
//	static void addForce(unsigned int nbVertex, unsigned int nbSpringPerVertex, const _device_pointer springs, _device_pointer f, const _device_pointer x, const _device_pointer v)
//	{   SpringForceFieldOpenCL3d_addForce(nbVertex, nbSpringPerVertex, springs, f, x, v); }
//	static void addExternalForce(unsigned int nbVertex, unsigned int nbSpringPerVertex, const _device_pointer springs, _device_pointer f1, const _device_pointer x1, const _device_pointer v1, const _device_pointer x2, const _device_pointer v2)
//	{   SpringForceFieldOpenCL3d_addExternalForce(nbVertex, nbSpringPerVertex, springs, f1, x1, v1, x2, v2); }
//	static void addForce(unsigned int nbVertex, unsigned int nbSpringPerVertex, const _device_pointer springs, _device_pointer f, const _device_pointer x, const _device_pointer v, _device_pointer dfdx)
//	{   StiffSpringForceFieldOpenCL3d_addForce(nbVertex, nbSpringPerVertex, springs, f, x, v, dfdx); }
//	static void addExternalForce(unsigned int nbVertex, unsigned int nbSpringPerVertex, const _device_pointer springs, _device_pointer f1, const _device_pointer x1, const _device_pointer v1, const _device_pointer x2, const _device_pointer v2, _device_pointer dfdx)
//	{   StiffSpringForceFieldOpenCL3d_addExternalForce(nbVertex, nbSpringPerVertex, springs, f1, x1, v1, x2, v2, dfdx); }
//	static void addDForce(unsigned int nbVertex, unsigned int nbSpringPerVertex, const _device_pointer springs, _device_pointer f, const _device_pointer dx, const _device_pointer x, const _device_pointer dfdx, double factor)
//	{   StiffSpringForceFieldOpenCL3d_addDForce(nbVertex, nbSpringPerVertex, springs, f, dx, x, dfdx, factor); }
//	static void addExternalDForce(unsigned int nbVertex, unsigned int nbSpringPerVertex, const _device_pointer springs, _device_pointer f1, const _device_pointer dx1, const _device_pointer x1, const _device_pointer dx2, const _device_pointer x2, const _device_pointer dfdx, double factor)
//	{   StiffSpringForceFieldOpenCL3d_addExternalDForce(nbVertex, nbSpringPerVertex, springs, f1, dx1, x1, dx2, x2, dfdx, factor); }
//
//	static bool supportMultiAddDForce() { return false; }
//	static void multiAddDForce(int, SpringDForceOp*, double)
//	{}
//};
//
//template<>
//class OpenCLKernelsSpringForceField<OpenCLVec3d1Types>
//{
//public:
//	static void addForce(unsigned int nbVertex, unsigned int nbSpringPerVertex, const _device_pointer springs, _device_pointer f, const _device_pointer x, const _device_pointer v)
//	{   SpringForceFieldOpenCL3d1_addForce(nbVertex, nbSpringPerVertex, springs, f, x, v); }
//	static void addExternalForce(unsigned int nbVertex, unsigned int nbSpringPerVertex, const _device_pointer springs, _device_pointer f1, const _device_pointer x1, const _device_pointer v1, const _device_pointer x2, const _device_pointer v2)
//	{   SpringForceFieldOpenCL3d1_addExternalForce(nbVertex, nbSpringPerVertex, springs, f1, x1, v1, x2, v2); }
//	static void addForce(unsigned int nbVertex, unsigned int nbSpringPerVertex, const _device_pointer springs, _device_pointer f, const _device_pointer x, const _device_pointer v, _device_pointer dfdx)
//	{   StiffSpringForceFieldOpenCL3d1_addForce(nbVertex, nbSpringPerVertex, springs, f, x, v, dfdx); }
//	static void addExternalForce(unsigned int nbVertex, unsigned int nbSpringPerVertex, const _device_pointer springs, _device_pointer f1, const _device_pointer x1, const _device_pointer v1, const _device_pointer x2, const _device_pointer v2, _device_pointer dfdx)
//	{   StiffSpringForceFieldOpenCL3d1_addExternalForce(nbVertex, nbSpringPerVertex, springs, f1, x1, v1, x2, v2, dfdx); }
//	static void addDForce(unsigned int nbVertex, unsigned int nbSpringPerVertex, const _device_pointer springs, _device_pointer f, const _device_pointer dx, const _device_pointer x, const _device_pointer dfdx, double factor)
//	{   StiffSpringForceFieldOpenCL3d1_addDForce(nbVertex, nbSpringPerVertex, springs, f, dx, x, dfdx, factor); }
//	static void addExternalDForce(unsigned int nbVertex, unsigned int nbSpringPerVertex, const _device_pointer springs, _device_pointer f1, const _device_pointer dx1, const _device_pointer x1, const _device_pointer dx2, const _device_pointer x2, const _device_pointer dfdx, double factor)
//	{   StiffSpringForceFieldOpenCL3d1_addExternalDForce(nbVertex, nbSpringPerVertex, springs, f1, dx1, x1, dx2, x2, dfdx, factor); }
//
//	static bool supportMultiAddDForce() { return false; }
//	static void multiAddDForce(int, SpringDForceOp*, double)
//	{}
//};
//


} // namespace OpenCL

} // namespace gpu

namespace component
{

namespace forcefield
{
//
//
//using namespace gpu::opencl;
//
//template<class TCoord, class TDeriv, class TReal>
//void SpringForceFieldInternalData< gpu::opencl::OpenCLVectorTypes<TCoord,TDeriv,TReal> >::init(Main* m, bool stiff)
//{
//	Data& data = m->data;
//	m->Inherit::init();
//	const sofa::helper::vector<Spring>& springs = m->springs.getValue();
//	if (!springs.empty())
//	{
//		bool external = (m->mstate1!=m->mstate2);
//		if (external)
//		{
//			std::map<int,int> nsprings1;
//			std::map<int,int> nsprings2;
//			for (unsigned int i=0;i<springs.size();i++)
//			{
//				nsprings1[springs[i].m1]++;
//				nsprings2[springs[i].m2]++;
//			}
//
//			int nmax1 = 0;
//			for (std::map<int,int>::const_iterator it = nsprings1.begin(); it != nsprings1.end(); ++it)
//				if (it->second > nmax1)
//					nmax1 = it->second;
//			data.springs1.init(nsprings1.begin()->first, nsprings1.rbegin()->first - nsprings1.begin()->first + 1, nmax1);
//
//			int nmax2 = 0;
//			for (std::map<int,int>::const_iterator it = nsprings2.begin(); it != nsprings2.end(); ++it)
//				if (it->second > nmax2)
//					nmax2 = it->second;
//			data.springs2.init(nsprings2.begin()->first, nsprings2.rbegin()->first - nsprings2.begin()->first + 1, nmax2);
//
//			nsprings1.clear();
//			nsprings2.clear();
//			for (unsigned int i=0;i<springs.size();i++)
//			{
//				int m1 = springs[i].m1 - data.springs1.vertex0;
//				int m2 = springs[i].m2 - data.springs2.vertex0;
//				data.springs1.set(m1, nsprings1[m1]++, m2,
//					(float)springs[i].initpos,
//					(float)springs[i].ks,
//					(float)springs[i].kd);
//				data.springs2.set(m2, nsprings2[m2]++, m1,
//					(float)springs[i].initpos,
//					(float)springs[i].ks,
//					(float)springs[i].kd);
//			}
//		}
//		else
//		{
//			std::map<int,int> nsprings;
//			for (unsigned int i=0;i<springs.size();i++)
//			{
//				nsprings[springs[i].m1]++;
//				nsprings[springs[i].m2]++;
//			}
//
//			int nmax = 0;
//			for (std::map<int,int>::const_iterator it = nsprings.begin(); it != nsprings.end(); ++it)
//				if (it->second > nmax)
//					nmax = it->second;
//			data.springs1.init(nsprings.begin()->first, nsprings.rbegin()->first - nsprings.begin()->first + 1, nmax);
//			std::cout << "OpenCL SpringForceField: "<<springs.size()<<" springs, "<<data.springs1.nbVertex<<" attached points, max "<<data.springs1.nbSpringPerVertex<<" springs per point."<<std::endl;
//			nsprings.clear();
//			for (unsigned int i=0;i<springs.size();i++)
//			{
//				int m1 = springs[i].m1 - data.springs1.vertex0;
//				int m2 = springs[i].m2 - data.springs1.vertex0;
//				data.springs1.set(m1, nsprings[m1]++, m2,
//					(float)springs[i].initpos,
//					(float)springs[i].ks,
//					(float)springs[i].kd);
//				data.springs1.set(m2, nsprings[m2]++, m1,
//					(float)springs[i].initpos,
//					(float)springs[i].ks,
//					(float)springs[i].kd);
//			}
//		}
//	}
//	if (stiff)
//	{
//		data.springs1.dfdx.resize(data.springs1.springs.size());
//		data.springs2.dfdx.resize(data.springs2.springs.size());
//	}
//}
//
//// -- InteractionForceField interface
//template<class TCoord, class TDeriv, class TReal>
//void SpringForceFieldInternalData< gpu::opencl::OpenCLVectorTypes<TCoord,TDeriv,TReal> >::addForce(Main* m, bool stiff, VecDeriv& f1, VecDeriv& f2, const VecCoord& x1, const VecCoord& x2, const VecDeriv& v1, const VecDeriv& v2, bool prefetch)
//{
//	Data& data = m->data;
//	if (prefetch) return;
//
//	if (m->mstate1 == m->mstate2)
//	{
//		VecDeriv& f = f1;
//		const VecCoord& x = x1;
//		const VecDeriv& v = v1;
//		f.resize(x.size());
//		int d = data.springs1.vertex0;
//		if (data.springs1.nbSpringPerVertex > 0)
//		{
//			if (!stiff)
//			Kernels::addForce(data.springs1.nbVertex,
//				data.springs1.nbSpringPerVertex,
//				data.springs1.springs.deviceRead(),
//				OpenCLMemoryManager<Deriv>::deviceOffset(f.deviceWrite(),d),
//				OpenCLMemoryManager<Coord>::deviceOffset(x.deviceRead(),d),
//				OpenCLMemoryManager<Deriv>::deviceOffset(v.deviceRead(),d));
//			else
//			Kernels::addForce(data.springs1.nbVertex,
//				data.springs1.nbSpringPerVertex,
//				data.springs1.springs.deviceRead(),
//				OpenCLMemoryManager<Deriv>::deviceOffset(f.deviceWrite(),d),
//				OpenCLMemoryManager<Coord>::deviceOffset(x.deviceRead(),d),
//				OpenCLMemoryManager<Deriv>::deviceOffset(v.deviceRead(),d),
//				data.springs1.dfdx.deviceWrite());
//		}
//	}
//	else
//	{
//		f1.resize(x1.size());
//		f2.resize(x2.size());
//		int d1 = data.springs1.vertex0;
//		int d2 = data.springs2.vertex0;
//		if (data.springs1.nbSpringPerVertex > 0)
//		{
//			if (!stiff)
//			Kernels::addExternalForce(data.springs1.nbVertex,
//				data.springs1.nbSpringPerVertex,
//				data.springs1.springs.deviceRead(),
//				OpenCLMemoryManager<Deriv>::deviceOffset(f1.deviceWrite(), d1),
//				OpenCLMemoryManager<Coord>::deviceOffset(x1.deviceRead(), d1),
//				OpenCLMemoryManager<Deriv>::deviceOffset(v1.deviceRead(), d1),
//				OpenCLMemoryManager<Coord>::deviceOffset(x2.deviceRead(), d2),
//				OpenCLMemoryManager<Deriv>::deviceOffset(v2.deviceRead(), d2));
//			else
//			Kernels::addExternalForce(data.springs1.nbVertex,
//				data.springs1.nbSpringPerVertex,
//				data.springs1.springs.deviceRead(),
//				OpenCLMemoryManager<Deriv>::deviceOffset(f1.deviceWrite(), d1),
//				OpenCLMemoryManager<Coord>::deviceOffset(x1.deviceRead(), d1),
//				OpenCLMemoryManager<Deriv>::deviceOffset(v1.deviceRead(), d1),
//				OpenCLMemoryManager<Coord>::deviceOffset(x2.deviceRead(), d2),
//				OpenCLMemoryManager<Deriv>::deviceOffset(v2.deviceRead(), d2),
//				data.springs1.dfdx.deviceWrite());
//		}
//		if (data.springs2.nbSpringPerVertex > 0)
//		{
//			if (!stiff)
//			Kernels::addExternalForce(data.springs2.nbVertex,
//				data.springs2.nbSpringPerVertex,
//				data.springs2.springs.deviceRead(),
//				OpenCLMemoryManager<Deriv>::deviceOffset(f2.deviceWrite() , d2),
//				OpenCLMemoryManager<Coord>::deviceOffset(x2.deviceRead()  , d2),
//				OpenCLMemoryManager<Deriv>::deviceOffset(v2.deviceRead()  , d2),
//				OpenCLMemoryManager<Coord>::deviceOffset(x1.deviceRead()  , d1),
//				OpenCLMemoryManager<Deriv>::deviceOffset(v1.deviceRead()  , d1));
//			else
//			Kernels::addExternalForce(data.springs2.nbVertex,
//				data.springs2.nbSpringPerVertex,
//				data.springs2.springs.deviceRead(),
//				OpenCLMemoryManager<Deriv>::deviceOffset(f2.deviceWrite() ,d2),
//				OpenCLMemoryManager<Coord>::deviceOffset(x2.deviceRead()  , d2),
//				OpenCLMemoryManager<Deriv>::deviceOffset(v2.deviceRead()  , d2),
//				OpenCLMemoryManager<Coord>::deviceOffset(x1.deviceRead()  , d1),
//				OpenCLMemoryManager<Deriv>::deviceOffset(v1.deviceRead()  , d1),
//				data.springs2.dfdx.deviceWrite());
//		}
//	}
//}
//
//template<class TCoord, class TDeriv, class TReal>
//void SpringForceFieldInternalData< gpu::opencl::OpenCLVectorTypes<TCoord,TDeriv,TReal> >::addDForce(Main* m, bool stiff, VecDeriv& df1, VecDeriv& df2, const VecDeriv& dx1, const VecDeriv& dx2, double kFactor, double /*bFactor*/, bool prefetch)
//{
//	if (!stiff) return;
//	Data& data = m->data;
//	if (prefetch)
//	{
//	if (m->mstate1 == m->mstate2)
//	{
//		if (!Kernels::supportMultiAddDForce()) return;
//		VecDeriv& df = df1;
//		const VecDeriv& dx = dx1;
//		const VecCoord& x = *m->mstate1->getX();
//		df.resize(x.size());
//		int d = data.springs1.vertex0;
//		if (data.springs1.nbSpringPerVertex > 0)
//		{
//		SpringDForceOp op;
//		op.size = data.springs1.nbVertex;
//		op.nbSpringPerVertex = data.springs1.nbSpringPerVertex;
//		op.springs = data.springs1.springs.deviceRead();
//		op.f  = OpenCLMemoryManager<Deriv>::deviceOffset(df.deviceWrite() , d);
//		op.dx = OpenCLMemoryManager<Deriv>::deviceOffset(dx.deviceRead() , d);
//		op.x  = OpenCLMemoryManager<Coord>::deviceOffset(x.deviceRead()  , d);
//		op.dfdx = data.springs1.dfdx.deviceRead();
//
//		data.preDForceOpID = data.opsDForce().size();
//		data.opsDForce().push_back(op);
//		}
//	}
//	return;
//	}
//	else if (data.preDForceOpID != -1)
//	{
//	helper::vector<SpringDForceOp>& ops = data.opsDForce();
//	if (!ops.empty())
//	{
//		if (ops.size() == 1)
//		{ // only one object -> use regular kernel
//		m->data.preDForceOpID = -1;
//		}
//		else
//		{
//		Kernels::multiAddDForce(ops.size(), &(ops[0]), kFactor);
//		}
//		ops.clear();
//	}
//	if (data.preDForceOpID != -1)
//	{
//		m->data.preDForceOpID = -1;
//		return;
//	}
//	}
//	if (m->mstate1 == m->mstate2)
//	{
//		VecDeriv& df = df1;
//		const VecDeriv& dx = dx1;
//		const VecCoord& x = *m->mstate1->getX();
//		df.resize(x.size());
//		int d = data.springs1.vertex0;
//		if (data.springs1.nbSpringPerVertex > 0)
//		{
//			Kernels::addDForce(data.springs1.nbVertex,
//				data.springs1.nbSpringPerVertex,
//				data.springs1.springs.deviceRead(),
//				OpenCLMemoryManager<Deriv>::deviceOffset(df.deviceWrite() , d),
//				OpenCLMemoryManager<Deriv>::deviceOffset(dx.deviceRead() , d),
//				OpenCLMemoryManager<Coord>::deviceOffset(x.deviceRead()  , d),
//				data.springs1.dfdx.deviceRead(),
//				kFactor);
//		}
//	}
//	else
//	{
//		const VecCoord& x1 = *m->mstate1->getX();
//		const VecCoord& x2 = *m->mstate2->getX();
//		df1.resize(x1.size());
//		df2.resize(x2.size());
//		int d1 = data.springs1.vertex0;
//		int d2 = data.springs2.vertex0;
//		if (data.springs1.nbSpringPerVertex > 0)
//		{
//			Kernels::addExternalDForce(data.springs1.nbVertex,
//				data.springs1.nbSpringPerVertex,
//				data.springs1.springs.deviceRead(),
//				OpenCLMemoryManager<Deriv>::deviceOffset(df1.deviceWrite() , d1),
//				OpenCLMemoryManager<Coord>::deviceOffset(x1.deviceRead()  , d1),
//				OpenCLMemoryManager<Deriv>::deviceOffset(dx1.deviceRead()  , d1),
//				OpenCLMemoryManager<Coord>::deviceOffset(x2.deviceRead()  , d2),
//				OpenCLMemoryManager<Deriv>::deviceOffset(dx2.deviceRead()  , d2),
//				data.springs1.dfdx.deviceRead(),
//				kFactor);
//		}
//		if (data.springs2.nbSpringPerVertex > 0)
//		{
//			Kernels::addExternalDForce(data.springs2.nbVertex,
//				data.springs2.nbSpringPerVertex,
//				data.springs2.springs.deviceRead(),
//				OpenCLMemoryManager<Deriv>::deviceOffset(df2.deviceWrite() , d2),
//				OpenCLMemoryManager<Deriv>::deviceOffset(dx2.deviceRead() , d2),
//				OpenCLMemoryManager<Coord>::deviceOffset(x2.deviceRead()  , d2),
//				OpenCLMemoryManager<Deriv>::deviceOffset(dx1.deviceRead() , d1),
//				OpenCLMemoryManager<Coord>::deviceOffset(x1.deviceRead()  , d1),
//				data.springs2.dfdx.deviceRead(),
//				kFactor);
//		}
//	}
//}
//
//
//// I know using macros is bad design but this is the only way not to repeat the code for all OpenCL types
//#define OpenCLSpringForceField_ImplMethods(T) \
//	template<> bool SpringForceField< T >::canPrefetch() const \
//	{ return true; } \
//	template<> void SpringForceField< T >::init() \
//	{ data.init(this, false); } \
//	template<> void SpringForceField< T >::addForce(VecDeriv& f1, VecDeriv& f2, const VecCoord& x1, const VecCoord& x2, const VecDeriv& v1, const VecDeriv& v2) \
//	{ data.addForce(this, false, f1, f2, x1, x2, v1, v2, this->isPrefetching()); } \
//	template<> void StiffSpringForceField< T >::init() \
//	{ data.init(this, true); } \
//	template<> void StiffSpringForceField< T >::addForce(VecDeriv& f1, VecDeriv& f2, const VecCoord& x1, const VecCoord& x2, const VecDeriv& v1, const VecDeriv& v2) \
//	{ data.addForce(this, true, f1, f2, x1, x2, v1, v2, this->isPrefetching()); } \
//	template<> void StiffSpringForceField< T >::addDForce(VecDeriv& df1, VecDeriv& df2, const VecDeriv& dx1, const VecDeriv& dx2, double kFactor, double bFactor) \
//	{ data.addDForce(this, true, df1, df2, dx1, dx2, kFactor, bFactor, this->isPrefetching()); }
//
//OpenCLSpringForceField_ImplMethods(gpu::opencl::OpenCLVec3fTypes);
//OpenCLSpringForceField_ImplMethods(gpu::opencl::OpenCLVec3f1Types);
//
//
//
//OpenCLSpringForceField_ImplMethods(gpu::opencl::OpenCLVec3dTypes);
//OpenCLSpringForceField_ImplMethods(gpu::opencl::OpenCLVec3d1Types);
//
//
//
//#undef OpenCLSpringForceField_ImplMethods

} // namespace forcefield

} // namespace component

} // namespace sofa

#endif
