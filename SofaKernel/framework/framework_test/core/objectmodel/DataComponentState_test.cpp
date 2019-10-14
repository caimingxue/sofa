/******************************************************************************
*       SOFA, Simulation Open-Framework Architecture, development version     *
*                (c) 2006-2019 INRIA, USTL, UJF, CNRS, MGH                    *
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
#include <sofa/core/DataTracker.h>
using sofa::core::DataTrackerEngine;
#include <sofa/core/objectmodel/Link.h>
using sofa::core::objectmodel::SingleLink;

#include <sofa/core/objectmodel/BaseObject.h>

#include <sofa/helper/testing/BaseTest.h>
using sofa::helper::testing::BaseTest ;

#include <algorithm>

namespace std{
std::istream& operator>>(std::istream& i, std::vector<int>& c)
{
    return i;
}

std::ostream& operator<<(std::ostream& i, const std::vector<int>& c)
{
    return i;
}
}

namespace sofa {

enum class ComponentState
{
    Valid,
    Invalid
};

std::istream& operator>>(std::istream& i, ComponentState& c)
{
    c = ComponentState::Valid;
    return i;
}

std::ostream& operator<<(std::ostream& o, const ComponentState& c)
{
    o << "ComponentState";
    return o;
}

template<class B>
class NewLink : public Data<ComponentState>
{
public:
    NewLink(){}

    void set(B* l)
    {
        if(l==nullptr)
        {
            setParent(nullptr);
            return;
        }
        m_target = l;
        setParent( &(m_target->d_componentState) );
    }

    B* get()
    {
        updateIfDirty();
        return m_target;
    }
    B* m_target {nullptr};
};

///  Test suite for data callbacks
struct DataComponentState_test: public BaseTest
{
    class NewBaseObject : public sofa::core::objectmodel::BaseObject
    {
    public:
        /// data attached to an object
        Data<ComponentState> d_componentState {ComponentState::Valid};
        DataTrackerEngine m_internalCB;

        void reinit()
        {
            msg_warning() << "BaseObject is updated";
            d_componentState = ComponentState::Valid;
        }

        NewBaseObject()
            : sofa::core::objectmodel::BaseObject()
            , d_componentState(initData(&d_componentState, ComponentState::Valid, "componentState", "componentState"))
        {
            m_internalCB.addOutput(&d_componentState);
            m_internalCB.setUpdateCallback((std::bind(&NewBaseObject::reinit, this)));
        }
    };

    class MeshLoader : public NewBaseObject
    {
    public:
        /// data attached to an object
        Data<std::string> d_filename;
        Data<int> d_numVertices {10};
        Data<std::vector<int>> d_vertices {};

        void reinit()
        {
            d_numVertices = d_numVertices.getValue()*2;
            std::vector<int> f;
            f.resize(d_numVertices.getValue());
            d_vertices = f;

            msg_warning() << "Loading a new mesh from: " << d_filename.getValue() << msgendl
                          << "     number of vertices: " << d_numVertices.getValue();

            d_componentState = ComponentState::Valid;
        }

        MeshLoader() : NewBaseObject()
          , d_filename(initData(&d_filename, "undefined", "filename", "filename"))
          , d_numVertices(initData(&d_numVertices, 1, "numVertices", "numVertices"))
          , d_vertices(initData(&d_vertices, std::vector<int>(), "vertices", "vertices"))
        {
            m_internalCB.addInputs({&d_filename});
            m_internalCB.addOutputs({&d_numVertices, &d_vertices, &d_componentState});
            m_internalCB.setUpdateCallback((std::bind(&MeshLoader::reinit, this)));
        }
    };

    class MechanicalObject : public NewBaseObject
    {
    public:
        //Data<std::vector<int>> d_INpositions {};
        Data<std::vector<int>> d_positions {};

        void reinit()
        {
            //d_positions = d_INpositions.getValue();
            msg_warning() << "Update mechanical object. " << msgendl
                          << "     number of positions: " << d_positions.getValue().size();

        }

        MechanicalObject() : NewBaseObject()
        {
            //m_internalCB.addInput(&d_INpositions);
            m_internalCB.addOutput(&d_positions);
            m_internalCB.addOutput(&d_componentState);
            m_internalCB.setUpdateCallback((std::bind(&MechanicalObject::reinit, this)));
        }

        void fakeAddForce()
        {
            if(d_componentState.getValue() != ComponentState::Valid)
                return ;

            std::vector<int> newPos;
            newPos.resize(d_positions.getValue().size());
            d_positions = newPos;
            std::cout << "fakeAddForce with number of positions: " << d_positions.getValue().size() << std::endl;
            d_componentState.setValue(ComponentState::Valid);
        }
    };

    class UniformMass : public NewBaseObject
    {
    public:
        NewLink<MechanicalObject> l_mstate;
        Data<std::vector<int>> d_masses;

        void reinit()
        {
            /// If this didn't worked then we quit
            if(l_mstate.get()==nullptr){
                d_componentState = ComponentState::Invalid;
                msg_error() << "The component UniformMass is not yet ready because there is a missing link to the 'mstate'";
                return;
            }
            if( d_masses.getValue().size() != l_mstate.get()->d_positions.getValue().size())
            {
                d_masses = l_mstate.get()->d_positions.getValue();

                msg_warning() << "UniformMass is updated from: " << l_mstate.get()->getName() << msgendl
                              << "                  mass size: " << d_masses.getValue().size() ;
            }
            d_componentState = ComponentState::Valid;
        }

        UniformMass() : NewBaseObject()
        {
            m_internalCB.addInput(&l_mstate);
            m_internalCB.addOutput(&d_componentState);
            m_internalCB.addOutput(&d_masses);
            m_internalCB.setUpdateCallback((std::bind(&UniformMass::reinit, this)));
        }

        void fakeAddMass()
        {
            if(d_componentState.getValue() != ComponentState::Valid)
                return ;
            std::cout << "number of masse: " << d_masses.getValue().size() << std::endl;
        }
    };
};

TEST_F(DataComponentState_test, testNewLink)
{
    /// two object are connected with a Link. When the first object change
    /// the second is dirtyfied and updated on demand.
    MechanicalObject state;
    state.setName("mymeca");

    UniformMass mass;
    mass.setName("mass");

    {
        EXPECT_MSG_EMIT(Error);
        /// Normally the mass component state is not valid until a link is set.
        ASSERT_EQ( mass.d_componentState.getValue(), ComponentState::Invalid );
    }

    /// Set the link from the mass to the mechanical object
    mass.l_mstate.set(&state);

    /// As the link between the mass and a mstate is set the mass should be valid
    ASSERT_EQ( mass.d_componentState.getValue(), ComponentState::Valid );

    /// But as the mstate is of zero size then the mass should be the same.
    ASSERT_EQ( mass.d_masses.getValue().size(), 0 );

    std::vector<int> tmp;
    tmp.resize(10);
    state.d_positions = tmp;

    ASSERT_EQ(state.d_positions.isDirty(), false);
    ASSERT_EQ(state.d_componentState.isDirty(), false);
    ASSERT_EQ(mass.d_masses.isDirty(), false);
    ASSERT_EQ(mass.d_componentState.isDirty(), false);

    /// We want to check now that when we update the mechanical counter we update the mass.
    /// For that we call a function that change the state of the component and check that its
    /// successor are dirty and get updated.
    auto cp = mass.d_componentState.getCounter();
    state.fakeAddForce();

    ASSERT_EQ(state.d_positions.isDirty(), false);
    ASSERT_EQ(state.d_componentState.isDirty(), false);
    ASSERT_EQ(mass.d_masses.isDirty(), true);
    ASSERT_EQ(mass.d_componentState.isDirty(), true);

    /// Force the update by getting the state.
    mass.d_componentState.getValue();
    ASSERT_NE(mass.d_componentState.getCounter(), cp);
}

TEST_F(DataComponentState_test, testScenario1)
{
    /// Mimick the following scene:
    /// <MeshLoader name="loader">
    /// <MechanicalObject name="state", position="@loader.position"/>
    /// <UniformMass mstate="@state"/>
    EXPECT_MSG_EMIT(Error);

    /// mimicking the following scene
    /// <MeshLoader name="loader">>
    std::cout << "CREATE LOADER" << std::endl;
    MeshLoader loader;
    loader.setName("loader1");
    ASSERT_EQ(loader.d_componentState.getValue(), ComponentState::Valid);

    /// <MechanicalObject position="@loader.position"/>
    std::cout << "CREATE MECHANICAL OBJECT" << std::endl;
    MechanicalObject state;
    state.setName("state");
    ASSERT_EQ(state.d_componentState.getValue(), ComponentState::Valid);

    std::cout << "CONNECT DATA PARENTING" << std::endl;
    state.d_positions.setParent( &loader.d_vertices );
    state.m_internalCB.addInput( &loader.d_vertices );
    ASSERT_TRUE(state.d_positions.isDirty());
    ASSERT_TRUE(state.d_componentState.isDirty());
    ASSERT_EQ(state.d_componentState.getValue(), ComponentState::Valid);

    /// <UniformMass/>
    std::cout << "CREATE UNIFORM MASS" << std::endl;
    UniformMass mass;
    mass.setName("mass");
    ASSERT_EQ(mass.d_componentState.getValue(), ComponentState::Invalid);

    std::cout << "CONNECT OBJECT LINK" << std::endl;
    mass.l_mstate.set( &state );
    ASSERT_EQ(mass.d_componentState.getValue(), ComponentState::Valid);

    std::cout << "RETRY FULL CHAIN" << std::endl;
    loader.d_filename.setValue("file2.obj");
    ASSERT_EQ(mass.d_componentState.getValue(), ComponentState::Valid);

    std::cout << "RETRY FULL CHAIN" << std::endl;
    loader.d_filename.setValue("file3.obj");
    ASSERT_EQ(mass.d_componentState.getValue(), ComponentState::Valid);


    std::cout << "FAKE ANIMATION LOOP:::" << std::endl;
    for(unsigned int i=0;i<10;i++)
    {
        state.fakeAddForce();
        mass.fakeAddMass();
    }

    std::cout << "CHANGE FILENAME:::" << std::endl;
    loader.d_filename.setValue("file3.obj");

    std::cout << "FAKE ANIMATION LOOP:::" << std::endl;
    for(unsigned int i=0;i<10;i++)
    {
        state.fakeAddForce();
        mass.fakeAddMass();
    }
}

TEST_F(DataComponentState_test, testUpdatePolicy)
{
    /// <MechanicalObject position="@loader.position"/>
    MeshLoader loader;
    loader.setName("loader1");

    MechanicalObject state;
    state.setName("state");

    state.d_positions.setParent( &loader.d_vertices ); /// Parenting is tricky as we need to connect set the parent.
    state.m_internalCB.addInput( &loader.d_vertices ); /// then connect it to the state cb.

    UniformMass mass;
    mass.setName("mass");
    mass.l_mstate.set( &state );  /// Connect the mass to the mechanical object

    mass.d_masses.getValue();
}



}// namespace sofa
