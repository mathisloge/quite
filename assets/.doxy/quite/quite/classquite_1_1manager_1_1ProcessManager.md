

# Class quite::manager::ProcessManager



[**ClassList**](annotated.md) **>** [**quite**](namespacequite.md) **>** [**manager**](namespacequite_1_1manager.md) **>** [**ProcessManager**](classquite_1_1manager_1_1ProcessManager.md)








Inherits the following classes: [quite::manager::BasicProcessManager](classquite_1_1manager_1_1BasicProcessManager.md)












## Classes

| Type | Name |
| ---: | :--- |
| struct | [**Impl**](structquite_1_1manager_1_1ProcessManager_1_1Impl.md) <br> |




## Public Types inherited from quite::manager::BasicProcessManager

See [quite::manager::BasicProcessManager](classquite_1_1manager_1_1BasicProcessManager.md)

| Type | Name |
| ---: | :--- |
| typedef std::unordered\_map&lt; std::string, std::string &gt; | [**Environment**](classquite_1_1manager_1_1BasicProcessManager.md#typedef-environment)  <br> |






































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**ProcessManager**](#function-processmanager) (asio\_impl::thread\_pool::executor\_type executor) <br> |
|   | [**QUITE\_DEFAULT\_MOVE**](#function-quite_default_move) ([**ProcessManager**](classquite_1_1manager_1_1ProcessManager.md)) <br> |
|   | [**QUITE\_DISABLE\_COPY**](#function-quite_disable_copy) ([**ProcessManager**](classquite_1_1manager_1_1ProcessManager.md)) <br> |
| virtual AsyncResult&lt; [**ProcessHandle**](classquite_1_1manager_1_1ProcessHandle.md) &gt; | [**application**](#function-application) ([**ProcessId**](structquite_1_1manager_1_1ProcessId.md) id) override<br>_Tries to lookup the application with the given id._  |
| virtual AsyncResult&lt; std::filesystem::path &gt; | [**find\_executable**](#function-find_executable) (std::filesystem::path exe\_name, Environment environment=[**current\_environment**](classquite_1_1manager_1_1ProcessManager.md#function-current_environment)()) override<br>_Tries to find the given executable in the PATH equivalent environment entry._  |
| virtual AsyncResult&lt; [**ProcessHandle**](classquite_1_1manager_1_1ProcessHandle.md) &gt; | [**launch\_application**](#function-launch_application) ([**ProcessId**](structquite_1_1manager_1_1ProcessId.md) id, std::string path\_to\_application, std::vector&lt; std::string &gt; args={}, Environment environment=[**current\_environment**](classquite_1_1manager_1_1ProcessManager.md#function-current_environment)()) override<br>_Launches the application but does not preloads any probe. Can be used to start arbitrary installed programs._  |
|   | [**~ProcessManager**](#function-processmanager) () override<br> |


## Public Functions inherited from quite::manager::BasicProcessManager

See [quite::manager::BasicProcessManager](classquite_1_1manager_1_1BasicProcessManager.md)

| Type | Name |
| ---: | :--- |
| virtual AsyncResult&lt; [**ProcessHandle**](classquite_1_1manager_1_1ProcessHandle.md) &gt; | [**application**](classquite_1_1manager_1_1BasicProcessManager.md#function-application) ([**ProcessId**](structquite_1_1manager_1_1ProcessId.md) name) = 0<br>_Tries to lookup the application with the given id._  |
| virtual AsyncResult&lt; std::filesystem::path &gt; | [**find\_executable**](classquite_1_1manager_1_1BasicProcessManager.md#function-find_executable) (std::filesystem::path exe\_name, Environment environment) = 0<br>_Tries to find the given executable in the PATH equivalent environment entry._  |
| virtual AsyncResult&lt; [**ProcessHandle**](classquite_1_1manager_1_1ProcessHandle.md) &gt; | [**launch\_application**](classquite_1_1manager_1_1BasicProcessManager.md#function-launch_application) ([**ProcessId**](structquite_1_1manager_1_1ProcessId.md) id, std::string path\_to\_application, std::vector&lt; std::string &gt; args, Environment environment) = 0<br>_Launches the application but does not preloads any probe. Can be used to start arbitrary installed programs._  |
| virtual  | [**~BasicProcessManager**](classquite_1_1manager_1_1BasicProcessManager.md#function-basicprocessmanager) () <br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  Environment | [**current\_environment**](#function-current_environment) () <br>_Returns the current environment of the running process where the_ [_**ProcessManager**_](classquite_1_1manager_1_1ProcessManager.md) _lives._ |


## Public Static Functions inherited from quite::manager::BasicProcessManager

See [quite::manager::BasicProcessManager](classquite_1_1manager_1_1BasicProcessManager.md)

| Type | Name |
| ---: | :--- |
|  [**ProcessHandle**](classquite_1_1manager_1_1ProcessHandle.md) | [**noop\_process**](classquite_1_1manager_1_1BasicProcessManager.md#function-noop_process) () <br>_Creates a process handle with does nothing, always finished with exit code 0._  |


















































## Public Functions Documentation




### function ProcessManager 

```C++
explicit quite::manager::ProcessManager::ProcessManager (
    asio_impl::thread_pool::executor_type executor
) 
```




<hr>



### function QUITE\_DEFAULT\_MOVE 

```C++
quite::manager::ProcessManager::QUITE_DEFAULT_MOVE (
    ProcessManager
) 
```




<hr>



### function QUITE\_DISABLE\_COPY 

```C++
quite::manager::ProcessManager::QUITE_DISABLE_COPY (
    ProcessManager
) 
```




<hr>



### function application 

_Tries to lookup the application with the given id._ 
```C++
virtual AsyncResult< ProcessHandle > quite::manager::ProcessManager::application (
    ProcessId id
) override
```





**Parameters:**


* `id` the id of the application (which was used to launch or attach a application) 



**Returns:**

Result&lt;ProcessHandle&gt; An instance of an application or a not found error otherwise 





        
Implements [*quite::manager::BasicProcessManager::application*](classquite_1_1manager_1_1BasicProcessManager.md#function-application)


<hr>



### function find\_executable 

_Tries to find the given executable in the PATH equivalent environment entry._ 
```C++
virtual AsyncResult< std::filesystem::path > quite::manager::ProcessManager::find_executable (
    std::filesystem::path exe_name,
    Environment environment=current_environment ()
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
virtual AsyncResult< ProcessHandle > quite::manager::ProcessManager::launch_application (
    ProcessId id,
    std::string path_to_application,
    std::vector< std::string > args={},
    Environment environment=current_environment ()
) override
```





**Parameters:**


* `id_name` a user defined id (name) to retrieve a handle later on 
* `path_to_application` 
* `args` 
* `environment` 



**Returns:**

[**ProcessHandle**](classquite_1_1manager_1_1ProcessHandle.md) 





        
Implements [*quite::manager::BasicProcessManager::launch\_application*](classquite_1_1manager_1_1BasicProcessManager.md#function-launch_application)


<hr>



### function ~ProcessManager 

```C++
quite::manager::ProcessManager::~ProcessManager () override
```




<hr>
## Public Static Functions Documentation




### function current\_environment 

_Returns the current environment of the running process where the_ [_**ProcessManager**_](classquite_1_1manager_1_1ProcessManager.md) _lives._
```C++
static Environment quite::manager::ProcessManager::current_environment () 
```





**Returns:**

Environment 





        

<hr>

------------------------------
The documentation for this class was generated from the following file `libs/manager/include/quite/manager/process_manager.hpp`

