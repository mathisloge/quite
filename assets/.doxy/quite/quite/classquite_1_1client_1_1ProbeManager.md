

# Class quite::client::ProbeManager



[**ClassList**](annotated.md) **>** [**quite**](namespacequite.md) **>** [**client**](namespacequite_1_1client.md) **>** [**ProbeManager**](classquite_1_1client_1_1ProbeManager.md)




















## Classes

| Type | Name |
| ---: | :--- |
| struct | [**Impl**](structquite_1_1client_1_1ProbeManager_1_1Impl.md) <br> |






















## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**ProbeManager**](#function-probemanager-12) () <br> |
|   | [**ProbeManager**](#function-probemanager-22) ([**ProbeManager**](classquite_1_1client_1_1ProbeManager.md) &&) noexcept<br> |
|   | [**QUITE\_DISABLE\_COPY**](#function-quite_disable_copy) ([**ProbeManager**](classquite_1_1client_1_1ProbeManager.md)) <br> |
|  [**ProbeHandle**](classquite_1_1client_1_1ProbeHandle.md) | [**connect**](#function-connect) ([**manager::ProcessHandle**](classquite_1_1manager_1_1ProcessHandle.md) handle, const std::string & connection\_url) <br> |
|  [**ProbeManager**](classquite_1_1client_1_1ProbeManager.md) & | [**operator=**](#function-operator) ([**ProbeManager**](classquite_1_1client_1_1ProbeManager.md) &&) noexcept<br> |
|   | [**~ProbeManager**](#function-probemanager) () <br> |




























## Public Functions Documentation




### function ProbeManager [1/2]

```C++
quite::client::ProbeManager::ProbeManager () 
```




<hr>



### function ProbeManager [2/2]

```C++
quite::client::ProbeManager::ProbeManager (
    ProbeManager &&
) noexcept
```




<hr>



### function QUITE\_DISABLE\_COPY 

```C++
quite::client::ProbeManager::QUITE_DISABLE_COPY (
    ProbeManager
) 
```




<hr>



### function connect 

```C++
ProbeHandle quite::client::ProbeManager::connect (
    manager::ProcessHandle handle,
    const std::string & connection_url
) 
```




<hr>



### function operator= 

```C++
ProbeManager & quite::client::ProbeManager::operator= (
    ProbeManager &&
) noexcept
```




<hr>



### function ~ProbeManager 

```C++
quite::client::ProbeManager::~ProbeManager () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `libs/client/include/quite/client/probe_manager.hpp`

