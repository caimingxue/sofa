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
#ifndef SOFAIMPLICITFIELD_COMPONENT_POINTCLOUDIMPLICITFIELD_H
#define SOFAIMPLICITFIELD_COMPONENT_POINTCLOUDIMPLICITFIELD_H
#include <SofaImplicitField/config.h>

#include <sofa/core/objectmodel/BaseObject.h>
#include <sofa/core/DataEngine.h>
#include <sofa/core/objectmodel/Link.h>
#include <SofaImplicitField/components/geometry/ScalarField.h>

#include <thread>
#include <mutex>
#include <queue>
#include <condition_variable>

#include <sofa/helper/types/RGBAColor.h>


namespace sofa
{

namespace component
{

namespace visual
{

namespace _pointcloudimplicitfieldvisualization_
{
using sofa::component::geometry::ScalarFieldR3;
using  sofa::component::geometry::ScalarField;
using sofa::core::objectmodel::BaseObject ;
using sofa::core::DataEngine ;
using sofa::core::DataTracker ;

using sofa::defaulttype::Vec3d ;

template <typename T>
class Queue
{
 public:

  T pop()
  {
    std::unique_lock<std::mutex> mlock(mutex_);
    while (queue_.empty())
    {
      cond_.wait(mlock);
    }
    auto item = queue_.front();
    queue_.pop();
    return item;
  }

  void pop(T& item)
  {
    std::unique_lock<std::mutex> mlock(mutex_);
    while (queue_.empty())
    {
      cond_.wait(mlock);
    }
    item = queue_.front();
    queue_.pop();
  }

  void push(const T& item)
  {
    std::unique_lock<std::mutex> mlock(mutex_);
    queue_.push(item);
    mlock.unlock();
    cond_.notify_one();
  }

  void push(T&& item)
  {
    std::unique_lock<std::mutex> mlock(mutex_);
    queue_.push(std::move(item));
    mlock.unlock();
    cond_.notify_one();
  }

  bool empty(){
      std::scoped_lock<std::mutex> mlock(mutex_);
      return queue_.empty();
  }

 private:
  std::queue<T> queue_;
  std::mutex mutex_;
  std::condition_variable cond_;
};

////////////////// ///////////////
class SOFA_SOFAIMPLICITFIELD_API PointCloudImplicitFieldVisualization : public BaseObject
{
public:
    SOFA_CLASS(PointCloudImplicitFieldVisualization, BaseObject);

    SingleLink<PointCloudImplicitFieldVisualization, ScalarField,
               BaseLink::FLAG_STOREPATH|BaseLink::FLAG_STRONGLINK> l_field ;

    Data<unsigned int> d_gridresolution ;
    Data< sofa::defaulttype::BoundingBox > d_bbox;
    Data< sofa::helper::types::RGBAColor > d_color ;
    Data< ScalarFieldR3 > d_evalFunction;

    virtual void computeBBox(const core::ExecParams *, bool) override ;

protected:
    PointCloudImplicitFieldVisualization( ) ;
    ~PointCloudImplicitFieldVisualization() override ;

    virtual void init() override ;
    virtual void reinit() override ;
    virtual void draw(const core::visual::VisualParams*) override ;
private:
    PointCloudImplicitFieldVisualization(const PointCloudImplicitFieldVisualization& n) ;
    PointCloudImplicitFieldVisualization& operator=(const PointCloudImplicitFieldVisualization& n) ;

    /// Rendering data
    std::vector<Vec3d> m_points ;
    std::vector<double> m_field ;
    std::vector<Vec3d> m_colors ;
    std::vector<Vec3d> m_normals ;

    /// Field last computation data
    std::vector<Vec3d> m_cpoints ;
    std::vector<double> m_cfield ;
    std::vector<Vec3d> m_cnormals ;

    std::thread m_asyncthread;
    std::mutex m_datamutex ;
    std::mutex m_cmdmutex ;
    std::condition_variable m_cmdcond ;

    double m_minv = +1000;
    double m_maxv = 0.0;

    enum Cmd {
        CMD_IDLE,
        CMD_RESET,
        CMD_START,
        CMD_PROCESS,
        CMD_STOP,
    }  ;
    Queue<Cmd> m_cmdqueue;

    DataTracker m_datatracker ;

    void asyncCompute() ;
    void updateBufferFromComputeKernel() ;
};



/////////////////////////////////////////////////////////

} // namespace _scalarfield_

using _pointcloudimplicitfieldvisualization_::PointCloudImplicitFieldVisualization ;

} // namespace visual

} // namespace component

} // namespace sofa

#endif
