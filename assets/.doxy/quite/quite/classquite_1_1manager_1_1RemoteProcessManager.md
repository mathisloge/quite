

# Class quite::manager::RemoteProcessManager



[**ClassList**](annotated.md) **>** [**quite**](namespacequite.md) **>** [**manager**](namespacequite_1_1manager.md) **>** [**RemoteProcessManager**](classquite_1_1manager_1_1RemoteProcessManager.md)








Inherits the following classes: [quite::manager::BasicProcessManager](classquite_1_1manager_1_1BasicProcessManager.md)


Inherited by the following classes: [quite::manager::ProcessManagerClient](classquite_1_1manager_1_1ProcessManagerClient.md)














## Public Types inherited from quite::manager::BasicProcessManager

See [quite::manager::BasicProcessManager](classquite_1_1manager_1_1BasicProcessManager.md)

| Type | Name |
| ---: | :--- |
| typedef std::unordered\_map&lt; std::string, std::string &gt; | [**Environment**](classquite_1_1manager_1_1BasicProcessManager.md#typedef-environment)  <br> |






































## Public Functions

| Type | Name |
| ---: | :--- |
| virtual AsyncResult&lt; [**ProcessHandle**](classquite_1_1manager_1_1ProcessHandle.md) &gt; | [**application**](#function-application) ([**ProcessId**](structquite_1_1manager_1_1ProcessId.md) name) override<br>_Tries to lookup the application with the given id._  |
|  AsyncResult&lt; Environment &gt; | [**current\_remote\_environment**](#function-current_remote_environment) () <br>_Tries to fetch the remote environment from the connected process manager._  |
| virtual AsyncResult&lt; std::filesystem::path &gt; | [**find\_executable**](#function-find_executable) (std::filesystem::path exe\_name, Environment environment) override<br>_Tries to find the given executable in the PATH equivalent environment entry._  |
| virtual AsyncResult&lt; [**ProcessHandle**](classquite_1_1manager_1_1ProcessHandle.md) &gt; | [**launch\_application**](#function-launch_application) ([**ProcessId**](structquite_1_1manager_1_1ProcessId.md) id, std::string path\_to\_application, std::vector&lt; std::string &gt; args, Environment environment) override<br>_Launches the application but does not preloads any probe. Can be used to start arbitrary installed programs._  |


## Public Functions inherited from quite::manager::BasicProcessManager

See [quite::manager::BasicProcessManager](classquite_1_1manager_1_1BasicProcessManager.md)

| Type | Name |
| ---: | :--- |
| virtual AsyncResult&lt; [**ProcessHandle**](classquite_1_1manager_1_1ProcessHandle.md) &gt; | [**application**](classquite_1_1manager_1_1BasicProcessManager.md#function-application) ([**ProcessId**](structquite_1_1manager_1_1ProcessId.md) name) = 0<br>_Tries to lookup the application with the given id._  |
| virtual AsyncResult&lt; std::filesystem::path &gt; | [**find\_executable**](classquite_1_1manager_1_1BasicProcessManager.md#function-find_executable) (std::filesystem::path exe\_name, Environment environment) = 0<br>_Tries to find the given executable in the PATH equivalent environment entry._  |
| virtual AsyncResult&lt; [**ProcessHandle**](classquite_1_1manager_1_1ProcessHandle.md) &gt; | [**launch\_application**](classquite_1_1manager_1_1BasicProcessManager.md#function-launch_application) ([**ProcessId**](structquite_1_1manager_1_1ProcessId.md) id, std::string path\_to\_application, std::vector&lt; std::string &gt; args, Environment environment) = 0<br>_Launches the application but does not preloads any probe. Can be used to start arbitrary installed programs._  |
| virtual  | [**~BasicProcessManager**](classquite_1_1manager_1_1BasicProcessManager.md#function-basicprocessmanager) () <br> |




## Public Static Functions inherited from quite::manager::BasicProcessManager

See [quite::manager::BasicProcessManager](classquite_1_1manager_1_1BasicProcessManager.md)

| Type | Name |
| ---: | :--- |
|  [**ProcessHandle**](classquite_1_1manager_1_1ProcessHandle.md) | [**noop\_process**](classquite_1_1manager_1_1BasicProcessManager.md#function-noop_process) () <br>_Creates a process handle with does nothing, always finished with exit code 0._  |


















































## Public Functions Documentation




### function application 

_Tries to lookup the application with the given id._ 
```C++
virtual AsyncResult< ProcessHandle > quite::manager::RemoteProcessManager::application (
    ProcessId name
) override
```





**Parameters:**


* `name` the id of the application (which was used to launch or attach a application) 



**Returns:**

Result&lt;ProcessHandle&gt; An instance of an application or a not found error otherwise 





        
Implements [*quite::manager::BasicProcessManager::application*](classquite_1_1manager_1_1BasicProcessManager.md#function-application)


<hr>



### function current\_remote\_environment 

_Tries to fetch the remote environment from the connected process manager._ 
```C++
AsyncResult< Environment > quite::manager::RemoteProcessManager::current_remote_environment () 
```





**Returns:**

AsyncResult&lt;Environment&gt; 





        

<hr>



### function find\_executable 

_Tries to find the given executable in the PATH equivalent environment entry._ 
```C++
virtual AsyncResult< std::filesystem::path > quite::manager::RemoteProcessManager::find_executable (
    std::filesystem::path exe_name,
    Environment environment
) override
```





**Parameters:**


* `exe_name` the application name 
* `environment` the environment to search in 



**Returns:**

Result&lt;std::filesystem::path&gt; either an error or the absolute path to the executable 





        
Implements [*quite::manager::BasicProcessManager::find\_executable*](classquite_1_1manager_1_1BasicProcessManager.md#function-find_executable)


<hr>



### function launch\_application 

_Launches the application but does not preloads any probe. Can be used to start arbitrary installed programs._ 
```C++
virtual AsyncResult< ProcessHandle > quite::manager::RemoteProcessManager::launch_application (
    ProcessId id,
    std::string path_to_application,
    std::vector< std::string > args,
    Environment environment
) override
```





**Parameters:**


* `id` a user defined id (name) to retrieve a handle later on 
* `path_to_application` 
* `args` 
* `environment` 



**Returns:**

[**ProcessHandle**](classquite_1_1manager_1_1ProcessHandle.md) 





        
Implements [*quite::manager::BasicProcessManager::launch\_application*](classquite_1_1manager_1_1BasicProcessManager.md#function-launch_application)


<hr>

------------------------------
The documentation for this class was generated from the following file `libs/manager/src/remote_process_manager.hpp`

