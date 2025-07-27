

# Class quite::proto::ProbeClientImpl



[**ClassList**](annotated.md) **>** [**quite**](namespacequite.md) **>** [**proto**](namespacequite_1_1proto.md) **>** [**ProbeClientImpl**](classquite_1_1proto_1_1ProbeClientImpl.md)








Inherits the following classes: [quite::proto::ProbeClient](classquite_1_1proto_1_1ProbeClient.md)






















































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**ProbeClientImpl**](#function-probeclientimpl) ([**GrpcManager**](classquite_1_1proto_1_1GrpcManager.md) & grpc\_manager, std::string connection\_url, std::shared\_ptr&lt; [**IValueConverter**](classquite_1_1proto_1_1IValueConverter.md) &gt; value\_converter) <br> |
| virtual [**meta::MetaRegistry**](classquite_1_1meta_1_1MetaRegistry.md) & | [**meta\_registry**](#function-meta_registry) () override<br> |
| virtual [**core::IMouseInjector**](classquite_1_1core_1_1IMouseInjector.md) & | [**mouse\_injector**](#function-mouse_injector) () override<br> |
| virtual [**IProbeService**](classquite_1_1proto_1_1IProbeService.md) & | [**probe\_service**](#function-probe_service) () override<br> |
| virtual AsyncResult&lt; void &gt; | [**wait\_for\_connected**](#function-wait_for_connected) (std::chrono::seconds timeout) override<br> |


## Public Functions inherited from quite::proto::ProbeClient

See [quite::proto::ProbeClient](classquite_1_1proto_1_1ProbeClient.md)

| Type | Name |
| ---: | :--- |
|   | [**ProbeClient**](classquite_1_1proto_1_1ProbeClient.md#function-probeclient) () <br> |
|   | [**QUITE\_DISABLE\_COPY\_MOVE**](classquite_1_1proto_1_1ProbeClient.md#function-quite_disable_copy_move) ([**ProbeClient**](classquite_1_1proto_1_1ProbeClient.md)) <br> |
| virtual [**meta::MetaRegistry**](classquite_1_1meta_1_1MetaRegistry.md) & | [**meta\_registry**](classquite_1_1proto_1_1ProbeClient.md#function-meta_registry) () = 0<br> |
| virtual [**core::IMouseInjector**](classquite_1_1core_1_1IMouseInjector.md) & | [**mouse\_injector**](classquite_1_1proto_1_1ProbeClient.md#function-mouse_injector) () = 0<br> |
| virtual [**IProbeService**](classquite_1_1proto_1_1IProbeService.md) & | [**probe\_service**](classquite_1_1proto_1_1ProbeClient.md#function-probe_service) () = 0<br> |
| virtual AsyncResult&lt; void &gt; | [**wait\_for\_connected**](classquite_1_1proto_1_1ProbeClient.md#function-wait_for_connected) (std::chrono::seconds timeout) = 0<br> |
| virtual  | [**~ProbeClient**](classquite_1_1proto_1_1ProbeClient.md#function-probeclient) () <br> |






















































## Public Functions Documentation




### function ProbeClientImpl 

```C++
quite::proto::ProbeClientImpl::ProbeClientImpl (
    GrpcManager & grpc_manager,
    std::string connection_url,
    std::shared_ptr< IValueConverter > value_converter
) 
```




<hr>



### function meta\_registry 

```C++
virtual meta::MetaRegistry & quite::proto::ProbeClientImpl::meta_registry () override
```



Implements [*quite::proto::ProbeClient::meta\_registry*](classquite_1_1proto_1_1ProbeClient.md#function-meta_registry)


<hr>



### function mouse\_injector 

```C++
virtual core::IMouseInjector & quite::proto::ProbeClientImpl::mouse_injector () override
```



Implements [*quite::proto::ProbeClient::mouse\_injector*](classquite_1_1proto_1_1ProbeClient.md#function-mouse_injector)


<hr>



### function probe\_service 

```C++
virtual IProbeService & quite::proto::ProbeClientImpl::probe_service () override
```



Implements [*quite::proto::ProbeClient::probe\_service*](classquite_1_1proto_1_1ProbeClient.md#function-probe_service)


<hr>



### function wait\_for\_connected 

```C++
virtual AsyncResult< void > quite::proto::ProbeClientImpl::wait_for_connected (
    std::chrono::seconds timeout
) override
```



Implements [*quite::proto::ProbeClient::wait\_for\_connected*](classquite_1_1proto_1_1ProbeClient.md#function-wait_for_connected)


<hr>

------------------------------
The documentation for this class was generated from the following file `libs/protocol/src/client/probe_client_impl.hpp`

