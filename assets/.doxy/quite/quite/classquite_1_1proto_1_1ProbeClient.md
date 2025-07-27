

# Class quite::proto::ProbeClient



[**ClassList**](annotated.md) **>** [**quite**](namespacequite.md) **>** [**proto**](namespacequite_1_1proto.md) **>** [**ProbeClient**](classquite_1_1proto_1_1ProbeClient.md)










Inherited by the following classes: [quite::proto::ProbeClientImpl](classquite_1_1proto_1_1ProbeClientImpl.md)
































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**ProbeClient**](#function-probeclient) () <br> |
|   | [**QUITE\_DISABLE\_COPY\_MOVE**](#function-quite_disable_copy_move) ([**ProbeClient**](classquite_1_1proto_1_1ProbeClient.md)) <br> |
| virtual [**meta::MetaRegistry**](classquite_1_1meta_1_1MetaRegistry.md) & | [**meta\_registry**](#function-meta_registry) () = 0<br> |
| virtual [**core::IMouseInjector**](classquite_1_1core_1_1IMouseInjector.md) & | [**mouse\_injector**](#function-mouse_injector) () = 0<br> |
| virtual [**IProbeService**](classquite_1_1proto_1_1IProbeService.md) & | [**probe\_service**](#function-probe_service) () = 0<br> |
| virtual AsyncResult&lt; void &gt; | [**wait\_for\_connected**](#function-wait_for_connected) (std::chrono::seconds timeout) = 0<br> |
| virtual  | [**~ProbeClient**](#function-probeclient) () <br> |




























## Public Functions Documentation




### function ProbeClient 

```C++
quite::proto::ProbeClient::ProbeClient () 
```




<hr>



### function QUITE\_DISABLE\_COPY\_MOVE 

```C++
quite::proto::ProbeClient::QUITE_DISABLE_COPY_MOVE (
    ProbeClient
) 
```




<hr>



### function meta\_registry 

```C++
virtual meta::MetaRegistry & quite::proto::ProbeClient::meta_registry () = 0
```




<hr>



### function mouse\_injector 

```C++
virtual core::IMouseInjector & quite::proto::ProbeClient::mouse_injector () = 0
```




<hr>



### function probe\_service 

```C++
virtual IProbeService & quite::proto::ProbeClient::probe_service () = 0
```




<hr>



### function wait\_for\_connected 

```C++
virtual AsyncResult< void > quite::proto::ProbeClient::wait_for_connected (
    std::chrono::seconds timeout
) = 0
```




<hr>



### function ~ProbeClient 

```C++
virtual quite::proto::ProbeClient::~ProbeClient () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `libs/protocol/include/quite/proto/client/probe_client.hpp`

