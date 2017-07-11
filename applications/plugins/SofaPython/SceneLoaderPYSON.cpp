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
#include "PythonMacros.h"
#include "PythonEnvironment.h"
#include "SceneLoaderPYSON.h"


#include <sofa/simulation/Simulation.h>
#include <SofaSimulationCommon/xml/NodeElement.h>
#include <SofaSimulationCommon/FindByTypeVisitor.h>

#include <sstream>

#include "PythonMainScriptController.h"
#include "PythonEnvironment.h"
#include "PythonFactory.h"

using namespace sofa::core::objectmodel;

namespace sofa
{

namespace simulation
{

namespace _sceneloaderpyson_
{

bool SceneLoaderPYSON::canLoadFileExtension(const char *extension)
{
    std::string ext = extension;
    std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
    return (ext=="pyson");
}

bool SceneLoaderPYSON::canWriteFileExtension(const char *extension)
{
    return canLoadFileExtension(extension);
}

/// get the file type description
std::string SceneLoaderPYSON::getFileTypeDesc()
{
    return "SOFA Json Scenes + Python";
}

/// get the list of file extensions
void SceneLoaderPYSON::getExtensionList(ExtensionList* list)
{
    list->clear();
    list->push_back("pyson");
}

void SceneLoaderPYSON::write(sofa::simulation::Node* n, const char *filename)
{
    std::stringstream s;
    s << "from pysonloader import save as pysonsave" ;

    msg_info("SceneLoaderPYSON") << "Trying saving file: " << filename ;

    PyObject* pDict = PyModule_GetDict(PyImport_AddModule("__main__"));

    PyObject* result = PyRun_String(s.str().c_str(), Py_file_input, pDict, pDict);
    if (result==nullptr){
         PyErr_Print();
         return;
    }

    PyObject *pFunc = PyDict_GetItemString(pDict, "pysonsave");
    if (PyCallable_Check(pFunc))
    {
        Node::SPtr rootNode = Node::create("root");
        SP_CALL_MODULEFUNC(pFunc, "(Os)", sofa::PythonFactory::toPython(n), filename)
        return;
    }

    assert(PyCallable_Check(pFunc));
    return;
}


sofa::simulation::Node::SPtr SceneLoaderPYSON::load(const char *filename)
{
    std::stringstream s;
    s << "from pysonloader import load as pysonload" ;

    PyObject* pDict = PyModule_GetDict(PyImport_AddModule("__main__"));

    PyObject* result = PyRun_String(s.str().c_str(), Py_file_input, pDict, pDict);
    if (result==nullptr){
         PyErr_Print();
         return nullptr;
    }

    msg_info("SceneLoaderPYSON") << "Loading file: " << filename ;
    PyRun_String("print(dir())", Py_file_input, pDict, pDict);

    PyObject *pFunc = PyDict_GetItemString(pDict, "pysonload");
    if (PyCallable_Check(pFunc))
    {
        Node::SPtr rootNode = Node::create("root");
        SP_CALL_MODULEFUNC(pFunc, "(Os)", sofa::PythonFactory::toPython(rootNode.get()), filename)
        return rootNode;
    }

    assert(PyCallable_Check(pFunc));
    return nullptr ;
}


} // namespace _sceneloaderpyson_

} // namespace simulation

} // namespace sofa

