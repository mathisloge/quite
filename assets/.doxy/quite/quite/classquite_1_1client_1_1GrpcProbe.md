

# Class quite::client::GrpcProbe



[**ClassList**](annotated.md) **>** [**quite**](namespacequite.md) **>** [**client**](namespacequite_1_1client.md) **>** [**GrpcProbe**](classquite_1_1client_1_1GrpcProbe.md)








Inherits the following classes: [quite::client::BasicProbe](classquite_1_1client_1_1BasicProbe.md)










































































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**GrpcProbe**](#function-grpcprobe) ([**manager::ProcessHandle**](classquite_1_1manager_1_1ProcessHandle.md) process, [**proto::Client**](classquite_1_1proto_1_1Client.md) & client, std::string connection\_uri) <br> |
| virtual AsyncResult&lt; std::shared\_ptr&lt; [**RemoteObject**](classquite_1_1client_1_1RemoteObject.md) &gt; &gt; | [**find\_object**](#function-find_object) ([**ObjectQuery**](structquite_1_1ObjectQuery.md) query) override<br> |
| virtual AsyncResult&lt; std::vector&lt; std::shared\_ptr&lt; [**RemoteObject**](classquite_1_1client_1_1RemoteObject.md) &gt; &gt; &gt; | [**get\_views**](#function-get_views) () override<br> |
| virtual [**meta::MetaRegistry**](classquite_1_1meta_1_1MetaRegistry.md) & | [**meta\_registry**](#function-meta_registry) () override<br> |
| virtual AsyncResult&lt; void &gt; | [**wait\_for\_started**](#function-wait_for_started) (std::chrono::seconds timeout) override<br> |


## Public Functions inherited from quite::client::BasicProbe

See [quite::client::BasicProbe](classquite_1_1client_1_1BasicProbe.md)

| Type | Name |
| ---: | :--- |
|   | [**BasicProbe**](classquite_1_1client_1_1BasicProbe.md#function-basicprobe) ([**manager::ProcessHandle**](classquite_1_1manager_1_1ProcessHandle.md) process) <br> |
| virtual AsyncResult&lt; void &gt; | [**exit**](classquite_1_1client_1_1BasicProbe.md#function-exit) () override<br> |
|  [**manager::Process**](classquite_1_1manager_1_1Process.md) & | [**process**](classquite_1_1client_1_1BasicProbe.md#function-process) () <br> |


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




### function GrpcProbe 

```C++
explicit quite::client::GrpcProbe::GrpcProbe (
    manager::ProcessHandle process,
    proto::Client & client,
    std::string connection_uri
) 
```




<hr>



### function find\_object 

```C++
virtual AsyncResult< std::shared_ptr< RemoteObject > > quite::client::GrpcProbe::find_object (
    ObjectQuery query
) override
```



Implements [*quite::client::Probe::find\_object*](classquite_1_1client_1_1Probe.md#function-find_object)


<hr>



### function get\_views 

```C++
virtual AsyncResult< std::vector< std::shared_ptr< RemoteObject > > > quite::client::GrpcProbe::get_views () override
```



Implements [*quite::client::Probe::get\_views*](classquite_1_1client_1_1Probe.md#function-get_views)


<hr>



### function meta\_registry 

```C++
virtual meta::MetaRegistry & quite::client::GrpcProbe::meta_registry () override
```



Implements [*quite::client::Probe::meta\_registry*](classquite_1_1client_1_1Probe.md#function-meta_registry)


<hr>



### function wait\_for\_started 

```C++
virtual AsyncResult< void > quite::client::GrpcProbe::wait_for_started (
    std::chrono::seconds timeout
) override
```



Implements [*quite::client::Probe::wait\_for\_started*](classquite_1_1client_1_1Probe.md#function-wait_for_started)


<hr>

------------------------------
The documentation for this class was generated from the following file `libs/client/src/grpc_impl/grpc_probe.hpp`

