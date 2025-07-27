

# Class quite::proto::ProbeServiceImpl



[**ClassList**](annotated.md) **>** [**quite**](namespacequite.md) **>** [**proto**](namespacequite_1_1proto.md) **>** [**ProbeServiceImpl**](classquite_1_1proto_1_1ProbeServiceImpl.md)








Inherits the following classes: [quite::proto::IProbeService](classquite_1_1proto_1_1IProbeService.md)






















































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**ProbeServiceImpl**](#function-probeserviceimpl) (std::shared\_ptr&lt; agrpc::GrpcContext &gt; grpc\_context, ProbeService::Stub & probe\_service\_stub, std::shared\_ptr&lt; [**IValueConverter**](classquite_1_1proto_1_1IValueConverter.md) &gt; value\_converter) <br> |
| virtual AsyncResult&lt; [**ObjectReference**](structquite_1_1ObjectReference.md) &gt; | [**find\_object**](#function-find_object) ([**ObjectQuery**](structquite_1_1ObjectQuery.md) serach\_query) override<br> |
| virtual AsyncResult&lt; std::unordered\_map&lt; std::string, entt::meta\_any &gt; &gt; | [**get\_object\_properties**](#function-get_object_properties) (ObjectId object\_id, std::vector&lt; std::string &gt; properties) override<br> |
| virtual AsyncResult&lt; entt::meta\_any &gt; | [**invoke\_method**](#function-invoke_method) (ObjectId id, std::string method\_name, std::vector&lt; entt::meta\_any &gt; parameters) override<br> |
| virtual AsyncResult&lt; std::vector&lt; [**ObjectReference**](structquite_1_1ObjectReference.md) &gt; &gt; | [**query\_top\_level\_views**](#function-query_top_level_views) () override<br> |
| virtual AsyncResult&lt; void &gt; | [**set\_object\_property**](#function-set_object_property) (ObjectId object\_id, std::string property, entt::meta\_any value) override<br> |
| virtual AsyncResult&lt; [**Image**](classquite_1_1Image.md) &gt; | [**take\_snapshot**](#function-take_snapshot) (ObjectId id) override<br> |


## Public Functions inherited from quite::proto::IProbeService

See [quite::proto::IProbeService](classquite_1_1proto_1_1IProbeService.md)

| Type | Name |
| ---: | :--- |
| virtual AsyncResult&lt; [**ObjectReference**](structquite_1_1ObjectReference.md) &gt; | [**find\_object**](classquite_1_1proto_1_1IProbeService.md#function-find_object) ([**ObjectQuery**](structquite_1_1ObjectQuery.md) serach\_query) = 0<br> |
| virtual AsyncResult&lt; std::unordered\_map&lt; std::string, entt::meta\_any &gt; &gt; | [**get\_object\_properties**](classquite_1_1proto_1_1IProbeService.md#function-get_object_properties) (ObjectId object\_id, std::vector&lt; std::string &gt; properties) = 0<br> |
| virtual AsyncResult&lt; entt::meta\_any &gt; | [**invoke\_method**](classquite_1_1proto_1_1IProbeService.md#function-invoke_method) (ObjectId id, std::string method\_name, std::vector&lt; entt::meta\_any &gt; parameters) = 0<br> |
| virtual AsyncResult&lt; std::vector&lt; [**ObjectReference**](structquite_1_1ObjectReference.md) &gt; &gt; | [**query\_top\_level\_views**](classquite_1_1proto_1_1IProbeService.md#function-query_top_level_views) () = 0<br> |
| virtual AsyncResult&lt; void &gt; | [**set\_object\_property**](classquite_1_1proto_1_1IProbeService.md#function-set_object_property) (ObjectId object\_id, std::string property, entt::meta\_any value) = 0<br> |
| virtual AsyncResult&lt; [**Image**](classquite_1_1Image.md) &gt; | [**take\_snapshot**](classquite_1_1proto_1_1IProbeService.md#function-take_snapshot) (ObjectId id) = 0<br> |
| virtual  | [**~IProbeService**](classquite_1_1proto_1_1IProbeService.md#function-iprobeservice) () = default<br> |






















































## Public Functions Documentation




### function ProbeServiceImpl 

```C++
explicit quite::proto::ProbeServiceImpl::ProbeServiceImpl (
    std::shared_ptr< agrpc::GrpcContext > grpc_context,
    ProbeService::Stub & probe_service_stub,
    std::shared_ptr< IValueConverter > value_converter
) 
```




<hr>



### function find\_object 

```C++
virtual AsyncResult< ObjectReference > quite::proto::ProbeServiceImpl::find_object (
    ObjectQuery serach_query
) override
```



Implements [*quite::proto::IProbeService::find\_object*](classquite_1_1proto_1_1IProbeService.md#function-find_object)


<hr>



### function get\_object\_properties 

```C++
virtual AsyncResult< std::unordered_map< std::string, entt::meta_any > > quite::proto::ProbeServiceImpl::get_object_properties (
    ObjectId object_id,
    std::vector< std::string > properties
) override
```



Implements [*quite::proto::IProbeService::get\_object\_properties*](classquite_1_1proto_1_1IProbeService.md#function-get_object_properties)


<hr>



### function invoke\_method 

```C++
virtual AsyncResult< entt::meta_any > quite::proto::ProbeServiceImpl::invoke_method (
    ObjectId id,
    std::string method_name,
    std::vector< entt::meta_any > parameters
) override
```



Implements [*quite::proto::IProbeService::invoke\_method*](classquite_1_1proto_1_1IProbeService.md#function-invoke_method)


<hr>



### function query\_top\_level\_views 

```C++
virtual AsyncResult< std::vector< ObjectReference > > quite::proto::ProbeServiceImpl::query_top_level_views () override
```



Implements [*quite::proto::IProbeService::query\_top\_level\_views*](classquite_1_1proto_1_1IProbeService.md#function-query_top_level_views)


<hr>



### function set\_object\_property 

```C++
virtual AsyncResult< void > quite::proto::ProbeServiceImpl::set_object_property (
    ObjectId object_id,
    std::string property,
    entt::meta_any value
) override
```



Implements [*quite::proto::IProbeService::set\_object\_property*](classquite_1_1proto_1_1IProbeService.md#function-set_object_property)


<hr>



### function take\_snapshot 

```C++
virtual AsyncResult< Image > quite::proto::ProbeServiceImpl::take_snapshot (
    ObjectId id
) override
```



Implements [*quite::proto::IProbeService::take\_snapshot*](classquite_1_1proto_1_1IProbeService.md#function-take_snapshot)


<hr>

------------------------------
The documentation for this class was generated from the following file `libs/protocol/src/client/probe_service_impl.hpp`

