

# Class quite::proto::MouseInjectorImpl



[**ClassList**](annotated.md) **>** [**quite**](namespacequite.md) **>** [**proto**](namespacequite_1_1proto.md) **>** [**MouseInjectorImpl**](classquite_1_1proto_1_1MouseInjectorImpl.md)








Inherits the following classes: [quite::core::IMouseInjector](classquite_1_1core_1_1IMouseInjector.md)






















































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**MouseInjectorImpl**](#function-mouseinjectorimpl) (std::shared\_ptr&lt; agrpc::GrpcContext &gt; grpc\_context, ProbeService::Stub & probe\_service\_stub) <br> |
| virtual AsyncResult&lt; void &gt; | [**single\_action**](#function-single_action) (ObjectId target\_id, [**core::MouseAction**](structquite_1_1core_1_1MouseAction.md) action) override<br> |


## Public Functions inherited from quite::core::IMouseInjector

See [quite::core::IMouseInjector](classquite_1_1core_1_1IMouseInjector.md)

| Type | Name |
| ---: | :--- |
| virtual AsyncResult&lt; void &gt; | [**single\_action**](classquite_1_1core_1_1IMouseInjector.md#function-single_action) (ObjectId target\_id, [**MouseAction**](structquite_1_1core_1_1MouseAction.md) action) = 0<br> |
| virtual  | [**~IMouseInjector**](classquite_1_1core_1_1IMouseInjector.md#function-imouseinjector) () = default<br> |






















































## Public Functions Documentation




### function MouseInjectorImpl 

```C++
explicit quite::proto::MouseInjectorImpl::MouseInjectorImpl (
    std::shared_ptr< agrpc::GrpcContext > grpc_context,
    ProbeService::Stub & probe_service_stub
) 
```




<hr>



### function single\_action 

```C++
virtual AsyncResult< void > quite::proto::MouseInjectorImpl::single_action (
    ObjectId target_id,
    core::MouseAction action
) override
```



Implements [*quite::core::IMouseInjector::single\_action*](classquite_1_1core_1_1IMouseInjector.md#function-single_action)


<hr>

------------------------------
The documentation for this class was generated from the following file `libs/protocol/src/client/mouse_injector_impl.hpp`

