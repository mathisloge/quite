

# Class quite::ServiceHandle

**template &lt;typename T&gt;**



[**ClassList**](annotated.md) **>** [**quite**](namespacequite.md) **>** [**ServiceHandle**](classquite_1_1ServiceHandle.md)



_A lightweight handle for accessing shared service instances._ [More...](#detailed-description)

* `#include <service_handle.hpp>`

















## Public Types

| Type | Name |
| ---: | :--- |
| typedef T | [**Type**](#typedef-type)  <br> |




















## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**ServiceHandle**](#function-servicehandle-13) () = default<br>_Constructs an empty_ [_**ServiceHandle**_](classquite_1_1ServiceHandle.md) _._ |
|   | [**ServiceHandle**](#function-servicehandle-23) (std::shared\_ptr&lt; T &gt; service) <br>_Constructs a_ [_**ServiceHandle**_](classquite_1_1ServiceHandle.md) _from a shared\_ptr to a service._ |
|   | [**ServiceHandle**](#function-servicehandle-33) (std::in\_place\_t, Args &&... args) <br>_Constructs a_ [_**ServiceHandle**_](classquite_1_1ServiceHandle.md) _with a new service instance._ |
|   | [**operator bool**](#function-operator-bool) () const<br>_Checks if the handle refers to a valid service._  |
|  T & | [**operator\***](#function-operator) () const<br>_Dereferences the handle to access the service instance._  |
|  T \* | [**operator-&gt;**](#function-operator_1) () const<br>_Provides pointer-like access to the underlying service._  |




























## Detailed Description


[**ServiceHandle**](classquite_1_1ServiceHandle.md) provides pointer-like semantics for accessing services managed via std::shared\_ptr. It is intended to be used as a safe, convenient wrapper for dependency injection or service locator patterns.




**Template parameters:**


* `T` The service type. 




    
## Public Types Documentation




### typedef Type 

```C++
using quite::ServiceHandle< T >::Type =  T;
```




<hr>
## Public Functions Documentation




### function ServiceHandle [1/3]

_Constructs an empty_ [_**ServiceHandle**_](classquite_1_1ServiceHandle.md) _._
```C++
quite::ServiceHandle::ServiceHandle () = default
```




<hr>



### function ServiceHandle [2/3]

_Constructs a_ [_**ServiceHandle**_](classquite_1_1ServiceHandle.md) _from a shared\_ptr to a service._
```C++
inline explicit quite::ServiceHandle::ServiceHandle (
    std::shared_ptr< T > service
) 
```





**Parameters:**


* `service` The shared\_ptr managing the service instance. 




        

<hr>



### function ServiceHandle [3/3]

_Constructs a_ [_**ServiceHandle**_](classquite_1_1ServiceHandle.md) _with a new service instance._
```C++
template<typename... Args>
inline explicit quite::ServiceHandle::ServiceHandle (
    std::in_place_t,
    Args &&... args
) 
```





**Template parameters:**


* `Args` Types of arguments to pass to the service constructor. 



**Parameters:**


* `args` Arguments to construct the service instance. 




        

<hr>



### function operator bool 

_Checks if the handle refers to a valid service._ 
```C++
inline explicit quite::ServiceHandle::operator bool () const
```





**Returns:**

true if the handle is non-empty, false otherwise. 





        

<hr>



### function operator\* 

_Dereferences the handle to access the service instance._ 
```C++
inline T & quite::ServiceHandle::operator* () const
```





**Returns:**

Reference to the service instance. 





        

<hr>



### function operator-&gt; 

_Provides pointer-like access to the underlying service._ 
```C++
inline T * quite::ServiceHandle::operator-> () const
```





**Returns:**

Pointer to the service instance, or nullptr if empty. 





        

<hr>

------------------------------
The documentation for this class was generated from the following file `libs/core/include/quite/service_handle.hpp`

