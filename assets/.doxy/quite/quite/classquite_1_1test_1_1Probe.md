

# Class quite::test::Probe



[**ClassList**](annotated.md) **>** [**quite**](namespacequite.md) **>** [**test**](namespacequite_1_1test.md) **>** [**Probe**](classquite_1_1test_1_1Probe.md)










































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**Probe**](#function-probe-12) ([**Probe**](classquite_1_1test_1_1Probe.md) &&) noexcept<br> |
|   | [**QUITE\_DISABLE\_COPY**](#function-quite_disable_copy) ([**Probe**](classquite_1_1test_1_1Probe.md)) <br> |
|  void | [**exit**](#function-exit) () <br> |
|  [**RemoteObject**](classquite_1_1test_1_1RemoteObject.md) | [**find\_object**](#function-find_object) ([**ObjectQuery**](structquite_1_1ObjectQuery.md) query) <br> |
|  [**Probe**](classquite_1_1test_1_1Probe.md) & | [**operator=**](#function-operator) ([**Probe**](classquite_1_1test_1_1Probe.md) &&) noexcept<br> |
|  [**RemoteObject**](classquite_1_1test_1_1RemoteObject.md) | [**try\_find\_object**](#function-try_find_object) ([**ObjectQuery**](structquite_1_1ObjectQuery.md) query, std::chrono::milliseconds timeout) <br> |
|  void | [**wait\_for\_connected**](#function-wait_for_connected) (std::chrono::seconds timeout) <br> |
|   | [**~Probe**](#function-probe) () <br> |




























## Public Functions Documentation




### function Probe [1/2]

```C++
quite::test::Probe::Probe (
    Probe &&
) noexcept
```




<hr>



### function QUITE\_DISABLE\_COPY 

```C++
quite::test::Probe::QUITE_DISABLE_COPY (
    Probe
) 
```




<hr>



### function exit 

```C++
void quite::test::Probe::exit () 
```




<hr>



### function find\_object 

```C++
RemoteObject quite::test::Probe::find_object (
    ObjectQuery query
) 
```




<hr>



### function operator= 

```C++
Probe & quite::test::Probe::operator= (
    Probe &&
) noexcept
```




<hr>



### function try\_find\_object 

```C++
RemoteObject quite::test::Probe::try_find_object (
    ObjectQuery query,
    std::chrono::milliseconds timeout
) 
```




<hr>



### function wait\_for\_connected 

```C++
void quite::test::Probe::wait_for_connected (
    std::chrono::seconds timeout
) 
```




<hr>



### function ~Probe 

```C++
quite::test::Probe::~Probe () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `libs/testing/include/quite/test/probe.hpp`

