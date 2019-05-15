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
#ifndef PYTHONENVIRONMENT_H
#define PYTHONENVIRONMENT_H

#include "PythonCommon.h"
#include "PythonMacros.h"

#include "Binding.h"
#include <SofaPython/config.h>
#include <sofa/simulation/SceneLoaderFactory.h>
#include <vector>
#include <string>

namespace sofa
{

namespace simulation
{

/// Forward definition
class PythonEnvironmentData ;

class SOFA_SOFAPYTHON_API PythonEnvironment
{
public:
    static void Init();
    static void Release();

    /// Add a path to sys.path, the list of search path for Python modules.
    static void addPythonModulePath(const std::string& path);

    /// Add each line of a file to sys.path
    static void addPythonModulePathsFromConfigFile(const std::string& path);

    /// Add all the directories matching <pluginsDirectory>/*/python to sys.path
    /// NB: can also be used for projects <projectDirectory>/*/python
    static void addPythonModulePathsForPlugins(const std::string& pluginsDirectory);
    static void addPythonModulePathsForPluginsByName(const std::string& pluginName);


    /** \brief getPythonModuleContent
     Returns a map of all callable objects in the python module. Each
     callable object's name (key) is assigned a type (value) in the map
     Possible types are: function, class, SofaPrefab,
     PythonScriptController and PythonScriptDataEngine
     \param moduleDir
     \param moduleName
     \return map of the callable objects in the module
    **/
    static std::map<std::string, std::string> getPythonModuleContent(const std::string& moduleDir, const std::string& moduleName);
    static std::string getPythonModuleDocstring(const std::string& modulepath);


    /// add module to python context, Init() must have been called before
    static void addModule(const std::string& name, PyMethodDef* methodDef);

    /// set the content of sys.argv.
    static void         setArguments(const std::string& filename, const std::vector<std::string>& arguments=std::vector<std::string>(0));

    /// basic script functions
    static std::string  getError();
    static bool         runString(const std::string& script);
    static bool         runFile(const std::string& filename, const std::vector<std::string>& arguments=std::vector<std::string>(0) );

    /** Calls a python callable
     * \param callableName The name of the callable object.
     * \param module The module containing the callable object.
     * \param args The arguments to pass to the function.
     * \param kwargs Optional keyword arguments to pass to the function.
     * \return The return value of the python function. Returns the Py_None
     * object If the module is not accessible, if the callable is not found
     * in the given module, or if the function fails to execute.
     **/
    static PyObject*    callObject(const std::string& callableName, const std::string& callableModule, PyObject* args, PyObject* kwargs = nullptr);

    /// returns the file information associated with the current frame.
    static std::string getStackAsString() ;

    /// returns the last entry in the stack so that we can provide information to user.
    static std::string getPythonCallingPointString() ;

    /// returns the calling point as a file info structure to be used with the message api.
    static sofa::helper::logging::FileInfo::SPtr getPythonCallingPointAsFileInfo() ;

    /// should the future scene loadings reload python modules?
    static void setAutomaticModuleReload( bool );

    /// excluding a module from automatic reload
    static void excludeModuleFromReload( const std::string& moduleName );

    /// to be able to react when a scene is loaded
    struct SceneLoaderListerner : public SceneLoader::Listener
    {
        void rightBeforeLoadingScene() override; // possibly unload python modules to force importing their eventual modifications
        static SceneLoaderListerner* getInstance() { static SceneLoaderListerner sceneLoaderListerner; return &sceneLoaderListerner; } // singleton
    private:
        SceneLoaderListerner(){}
    };

    /// use this RAII-class to ensure the gil is properly acquired and released
    /// in a scope. these should be surrounding any python code called from c++,
    /// i.e. in all the methods in PythonEnvironment and all the methods in
    /// PythonScriptController.
    class SOFA_SOFAPYTHON_API gil {
        const PyGILState_STATE state;
        const char* const trace;
    public:
        gil(const char* trace = nullptr);
        ~gil();
    };


    class SOFA_SOFAPYTHON_API no_gil {
        PyThreadState* const state;
        const char* const trace;
    public:
        no_gil(const char* trace = nullptr);
        ~no_gil();
    };

    struct system_exit : std::exception { };

private:
    static PythonEnvironmentData* getStaticData() ;
};


} // namespace simulation

} // namespace sofa


#endif // PYTHONENVIRONMENT_H
