

# Class quite::manager::BasicProcessManager



[**ClassList**](annotated.md) **>** [**quite**](namespacequite.md) **>** [**manager**](namespacequite_1_1manager.md) **>** [**BasicProcessManager**](classquite_1_1manager_1_1BasicProcessManager.md)










Inherited by the following classes: [quite::manager::ProcessManager](classquite_1_1manager_1_1ProcessManager.md),  [quite::manager::RemoteProcessManager](classquite_1_1manager_1_1RemoteProcessManager.md)












## Public Types

| Type | Name |
| ---: | :--- |
| typedef std::unordered\_map&lt; std::string, std::string &gt; | [**Environment**](#typedef-environment)  <br> |




















## Public Functions

| Type | Name |
| ---: | :--- |
| virtual AsyncResult&lt; [**ProcessHandle**](classquite_1_1manager_1_1ProcessHandle.md) &gt; | [**application**](#function-application) ([**ProcessId**](structquite_1_1manager_1_1ProcessId.md) name) = 0<br>_Tries to lookup the application with the given id._  |
| virtual AsyncResult&lt; std::filesystem::path &gt; | [**find\_executable**](#function-find_executable) (std::filesystem::path exe\_name, Environment environment) = 0<br>_Tries to find the given executable in the PATH equivalent environment entry._  |
| virtual AsyncResult&lt; [**ProcessHandle**](classquite_1_1manager_1_1ProcessHandle.md) &gt; | [**launch\_application**](#function-launch_application) ([**ProcessId**](structquite_1_1manager_1_1ProcessId.md) id, std::string path\_to\_application, std::vector&lt; std::string &gt; args, Environment environment) = 0<br>_Launches the application but does not preloads any probe. Can be used to start arbitrary installed programs._  |
| virtual  | [**~BasicProcessManager**](#function-basicprocessmanager) () <br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  [**ProcessHandle**](classquite_1_1manager_1_1ProcessHandle.md) | [**noop\_process**](#function-noop_process) () <br>_Creates a process handle with does nothing, always finished with exit code 0._  |


























## Public Types Documentation




### typedef Environment 

```C++
using quite::manager::BasicProcessManager::Environment =  std::unordered_map<std::string, std::string>;
```




<hr>
## Public Functions Documentation




### function application 

_Tries to lookup the application with the given id._ 
```C++
virtual AsyncResult< ProcessHandle > quite::manager::BasicProcessManager::application (
    ProcessId name
) = 0
```





**Parameters:**


* `name` the id of the application (which was used to launch or attach a application) 



**Returns:**

Result&lt;ProcessHandle&gt; An instance of an application or a not found error otherwise 





        

<hr>



### function find\_executable 

_Tries to find the given executable in the PATH equivalent environment entry._ 
```C++
virtual AsyncResult< std::filesystem::path > quite::manager::BasicProcessManager::find_executable (
    std::filesystem::path exe_name,
    Environment environment
) = 0
```





**Parameters:**


* `exe_name` the application name 
* `environment` the environment to search in 



**Returns:**

Result&lt;std::filesystem::path&gt; either an error or the absolute path to the executable 





        

<hr>



### function launch\_application 

_Launches the application but does not preloads any probe. Can be used to start arbitrary installed programs._ 
```C++
virtual AsyncResult< ProcessHandle > quite::manager::BasicProcessManager::launch_application (
    ProcessId id,
    std::string path_to_application,
    std::vector< std::string > args,
    Environment environment
) = 0
```





**Parameters:**


* `id` a user defined id (name) to retrieve a handle later on 
* `path_to_application` 
* `args` 
* `environment` 



**Returns:**

[**ProcessHandle**](classquite_1_1manager_1_1ProcessHandle.md) 





        

<hr>



### function ~BasicProcessManager 

```C++
virtual quite::manager::BasicProcessManager::~BasicProcessManager () 
```




<hr>
## Public Static Functions Documentation




### function noop\_process 

_Creates a process handle with does nothing, always finished with exit code 0._ 
```C++
static ProcessHandle quite::manager::BasicProcessManager::noop_process () 
```





**Returns:**

[**ProcessHandle**](classquite_1_1manager_1_1ProcessHandle.md) 





        

<hr>

------------------------------
The documentation for this class was generated from the following file `libs/manager/include/quite/manager/basic_process_manager.hpp`

