

# Class quite::client::BasicProbe



[**ClassList**](annotated.md) **>** [**quite**](namespacequite.md) **>** [**client**](namespacequite_1_1client.md) **>** [**BasicProbe**](classquite_1_1client_1_1BasicProbe.md)








Inherits the following classes: [quite::client::Probe](classquite_1_1client_1_1Probe.md)


Inherited by the following classes: [quite::client::GrpcProbe](classquite_1_1client_1_1GrpcProbe.md)




















































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**BasicProbe**](#function-basicprobe) ([**manager::ProcessHandle**](classquite_1_1manager_1_1ProcessHandle.md) process) <br> |
| virtual AsyncResult&lt; void &gt; | [**exit**](#function-exit) () override<br> |
|  [**manager::Process**](classquite_1_1manager_1_1Process.md) & | [**process**](#function-process) () <br> |


## Public Functions inherited from quite::client::Probe

See [quite::client::Probe](classquite_1_1client_1_1Probe.md)

| Type | Name |
| ---: | :--- |
|   | [**Probe**](classquite_1_1client_1_1Probe.md#function-probe) () = default<br> |
|   | [**QUITE\_DISABLE\_COPY\_MOVE**](classquite_1_1client_1_1Probe.md#function-quite_disable_copy_move) ([**Probe**](classquite_1_1client_1_1Probe.md)) <br> |
| virtual AsyncResult&lt; void &gt; | [**exit**](classquite_1_1client_1_1Probe.md#function-exit) () = 0<br> |
| virtual AsyncResult&lt; RemoteObjectPtr &gt; | [**find\_object**](classquite_1_1client_1_1Probe.md#function-find_object) ([**ObjectQuery**](structquite_1_1ObjectQuery.md) query) = 0<br> |
| virtual AsyncResult&lt; std::vector&lt; RemoteObjectPtr &gt; &gt; | [**get\_views**](classquite_1_1client_1_1Probe.md#function-get_views) () = 0<br> |
| virtual [**meta::MetaRegistry**](classquite_1_1meta_1_1MetaRegistry.md) & | [**meta\_registry**](classquite_1_1client_1_1Probe.md#function-meta_registry) () = 0<br> |
| virtual AsyncResult&lt; void &gt; | [**wait\_for\_started**](classquite_1_1client_1_1Probe.md#function-wait_for_started) (std::chrono::seconds timeout) = 0<br> |
| virtual  | [**~Probe**](classquite_1_1client_1_1Probe.md#function-probe) () = default<br> |






















































## Public Functions Documentation




### function BasicProbe 

```C++
explicit quite::client::BasicProbe::BasicProbe (
    manager::ProcessHandle process
) 
```




<hr>



### function exit 

```C++
virtual AsyncResult< void > quite::client::BasicProbe::exit () override
```



Implements [*quite::client::Probe::exit*](classquite_1_1client_1_1Probe.md#function-exit)


<hr>



### function process 

```C++
manager::Process & quite::client::BasicProbe::process () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `libs/client/src/basic_probe.hpp`

