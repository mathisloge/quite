

# Class quite::client::Probe



[**ClassList**](annotated.md) **>** [**quite**](namespacequite.md) **>** [**client**](namespacequite_1_1client.md) **>** [**Probe**](classquite_1_1client_1_1Probe.md)










Inherited by the following classes: [quite::client::BasicProbe](classquite_1_1client_1_1BasicProbe.md)
































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**Probe**](#function-probe) () = default<br> |
|   | [**QUITE\_DISABLE\_COPY\_MOVE**](#function-quite_disable_copy_move) ([**Probe**](classquite_1_1client_1_1Probe.md)) <br> |
| virtual AsyncResult&lt; void &gt; | [**exit**](#function-exit) () = 0<br> |
| virtual AsyncResult&lt; RemoteObjectPtr &gt; | [**find\_object**](#function-find_object) ([**ObjectQuery**](structquite_1_1ObjectQuery.md) query) = 0<br> |
| virtual AsyncResult&lt; std::vector&lt; RemoteObjectPtr &gt; &gt; | [**get\_views**](#function-get_views) () = 0<br> |
| virtual [**meta::MetaRegistry**](classquite_1_1meta_1_1MetaRegistry.md) & | [**meta\_registry**](#function-meta_registry) () = 0<br> |
| virtual AsyncResult&lt; void &gt; | [**wait\_for\_started**](#function-wait_for_started) (std::chrono::seconds timeout) = 0<br> |
| virtual  | [**~Probe**](#function-probe) () = default<br> |




























## Public Functions Documentation




### function Probe 

```C++
quite::client::Probe::Probe () = default
```




<hr>



### function QUITE\_DISABLE\_COPY\_MOVE 

```C++
quite::client::Probe::QUITE_DISABLE_COPY_MOVE (
    Probe
) 
```




<hr>



### function exit 

```C++
virtual AsyncResult< void > quite::client::Probe::exit () = 0
```




<hr>



### function find\_object 

```C++
virtual AsyncResult< RemoteObjectPtr > quite::client::Probe::find_object (
    ObjectQuery query
) = 0
```




<hr>



### function get\_views 

```C++
virtual AsyncResult< std::vector< RemoteObjectPtr > > quite::client::Probe::get_views () = 0
```




<hr>



### function meta\_registry 

```C++
virtual meta::MetaRegistry & quite::client::Probe::meta_registry () = 0
```




<hr>



### function wait\_for\_started 

```C++
virtual AsyncResult< void > quite::client::Probe::wait_for_started (
    std::chrono::seconds timeout
) = 0
```




<hr>



### function ~Probe 

```C++
virtual quite::client::Probe::~Probe () = default
```




<hr>

------------------------------
The documentation for this class was generated from the following file `libs/client/include/quite/client/probe.hpp`

