

# Class quite::test::ProbeManager



[**ClassList**](annotated.md) **>** [**quite**](namespacequite.md) **>** [**test**](namespacequite_1_1test.md) **>** [**ProbeManager**](classquite_1_1test_1_1ProbeManager.md)










































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**ProbeManager**](#function-probemanager-12) () <br> |
|   | [**ProbeManager**](#function-probemanager-22) ([**ProbeManager**](classquite_1_1test_1_1ProbeManager.md) &&) noexcept<br> |
|   | [**QUITE\_DISABLE\_COPY**](#function-quite_disable_copy) ([**ProbeManager**](classquite_1_1test_1_1ProbeManager.md)) <br> |
|  [**quite::test::Probe**](classquite_1_1test_1_1Probe.md) | [**connect\_to\_probe**](#function-connect_to_probe) (std::string name) <br> |
|  [**quite::test::Probe**](classquite_1_1test_1_1Probe.md) | [**launch\_probe\_application**](#function-launch_probe_application) (std::string name, const std::string & path\_to\_application, const std::vector&lt; std::string &gt; & args={}) <br> |
|  [**ProbeManager**](classquite_1_1test_1_1ProbeManager.md) & | [**operator=**](#function-operator) ([**ProbeManager**](classquite_1_1test_1_1ProbeManager.md) &&) noexcept<br> |
|   | [**~ProbeManager**](#function-probemanager) () <br> |




























## Public Functions Documentation




### function ProbeManager [1/2]

```C++
quite::test::ProbeManager::ProbeManager () 
```




<hr>



### function ProbeManager [2/2]

```C++
quite::test::ProbeManager::ProbeManager (
    ProbeManager &&
) noexcept
```




<hr>



### function QUITE\_DISABLE\_COPY 

```C++
quite::test::ProbeManager::QUITE_DISABLE_COPY (
    ProbeManager
) 
```




<hr>



### function connect\_to\_probe 

```C++
quite::test::Probe quite::test::ProbeManager::connect_to_probe (
    std::string name
) 
```




<hr>



### function launch\_probe\_application 

```C++
quite::test::Probe quite::test::ProbeManager::launch_probe_application (
    std::string name,
    const std::string & path_to_application,
    const std::vector< std::string > & args={}
) 
```




<hr>



### function operator= 

```C++
ProbeManager & quite::test::ProbeManager::operator= (
    ProbeManager &&
) noexcept
```




<hr>



### function ~ProbeManager 

```C++
quite::test::ProbeManager::~ProbeManager () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `libs/testing/include/quite/test/probe_manager.hpp`

