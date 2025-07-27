

# Class quite::manager::ProcessManagerClient



[**ClassList**](annotated.md) **>** [**quite**](namespacequite.md) **>** [**manager**](namespacequite_1_1manager.md) **>** [**ProcessManagerClient**](classquite_1_1manager_1_1ProcessManagerClient.md)








Inherits the following classes: [quite::manager::RemoteProcessManager](classquite_1_1manager_1_1RemoteProcessManager.md)


















## Public Types inherited from quite::manager::BasicProcessManager

See [quite::manager::BasicProcessManager](classquite_1_1manager_1_1BasicProcessManager.md)

| Type | Name |
| ---: | :--- |
| typedef std::unordered\_map&lt; std::string, std::string &gt; | [**Environment**](classquite_1_1manager_1_1BasicProcessManager.md#typedef-environment)  <br> |
























































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**ProcessManagerClient**](#function-processmanagerclient) () <br> |
|   | [**QUITE\_DEFAULT\_MOVE**](#function-quite_default_move) ([**ProcessManagerClient**](classquite_1_1manager_1_1ProcessManagerClient.md)) <br> |
|   | [**QUITE\_DISABLE\_COPY**](#function-quite_disable_copy) ([**ProcessManagerClient**](classquite_1_1manager_1_1ProcessManagerClient.md)) <br> |
|  Result&lt; [**ProcessHandle**](classquite_1_1manager_1_1ProcessHandle.md) &gt; | [**application**](#function-application) (const [**ProcessId**](structquite_1_1manager_1_1ProcessId.md) & id) override<br> |
|  AsyncResult&lt; Environment &gt; | [**current\_environment**](#function-current_environment) () <br> |
| virtual Result&lt; std::filesystem::path &gt; | [**find\_executable**](#function-find_executable) (std::filesystem::path exe\_name, Environment environment) override<br>_Tries to find the given executable in the PATH equivalent environment entry._  |
|  Result&lt; [**ProcessHandle**](classquite_1_1manager_1_1ProcessHandle.md) &gt; | [**launch\_application**](#function-launch_application) ([**ProcessId**](structquite_1_1manager_1_1ProcessId.md) id, const std::string & path\_to\_application, const std::vector&lt; std::string &gt; & args, const Environment & environment) override<br> |
|   | [**~ProcessManagerClient**](#function-processmanagerclient) () override<br> |


## Public Functions inherited from quite::manager::RemoteProcessManager

See [quite::manager::RemoteProcessManager](classquite_1_1manager_1_1RemoteProcessManager.md)

| Type | Name |
| ---: | :--- |
| virtual AsyncResult&lt; [**ProcessHandle**](classquite_1_1manager_1_1ProcessHandle.md) &gt; | [**application**](classquite_1_1manager_1_1RemoteProcessManager.md#function-application) ([**ProcessId**](structquite_1_1manager_1_1ProcessId.md) name) override<br>_Tries to lookup the application with the given id._  |
|  AsyncResult&lt; Environment &gt; | [**current\_remote\_environment**](classquite_1_1manager_1_1RemoteProcessManager.md#function-current_remote_environment) () <br>_Tries to fetch the remote environment from the connected process manager._  |
| virtual AsyncResult&lt; std::filesystem::path &gt; | [**find\_executable**](classquite_1_1manager_1_1RemoteProcessManager.md#function-find_executable) (std::filesystem::path exe\_name, Environment environment) override<br>_Tries to find the given executable in the PATH equivalent environment entry._  |
| virtual AsyncResult&lt; [**ProcessHandle**](classquite_1_1manager_1_1ProcessHandle.md) &gt; | [**launch\_application**](classquite_1_1manager_1_1RemoteProcessManager.md#function-launch_application) ([**ProcessId**](structquite_1_1manager_1_1ProcessId.md) id, std::string path\_to\_application, std::vector&lt; std::string &gt; args, Environment environment) override<br>_Launches the application but does not preloads any probe. Can be used to start arbitrary installed programs._  |


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




### function ProcessManagerClient 

```C++
explicit quite::manager::ProcessManagerClient::ProcessManagerClient () 
```




<hr>



### function QUITE\_DEFAULT\_MOVE 

```C++
quite::manager::ProcessManagerClient::QUITE_DEFAULT_MOVE (
    ProcessManagerClient
) 
```




<hr>



### function QUITE\_DISABLE\_COPY 

```C++
quite::manager::ProcessManagerClient::QUITE_DISABLE_COPY (
    ProcessManagerClient
) 
```




<hr>



### function application 

```C++
Result< ProcessHandle > quite::manager::ProcessManagerClient::application (
    const ProcessId & id
) override
```




<hr>



### function current\_environment 

```C++
AsyncResult< Environment > quite::manager::ProcessManagerClient::current_environment () 
```




<hr>



### function find\_executable 

_Tries to find the given executable in the PATH equivalent environment entry._ 
```C++
virtual Result< std::filesystem::path > quite::manager::ProcessManagerClient::find_executable (
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

```C++
Result< ProcessHandle > quite::manager::ProcessManagerClient::launch_application (
    ProcessId id,
    const std::string & path_to_application,
    const std::vector< std::string > & args,
    const Environment & environment
) override
```




<hr>



### function ~ProcessManagerClient 

```C++
quite::manager::ProcessManagerClient::~ProcessManagerClient () override
```




<hr>

------------------------------
The documentation for this class was generated from the following file `libs/manager/src/process_manager_client.hpp`

