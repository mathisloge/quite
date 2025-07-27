

# Class quite::proto::IProbeService



[**ClassList**](annotated.md) **>** [**quite**](namespacequite.md) **>** [**proto**](namespacequite_1_1proto.md) **>** [**IProbeService**](classquite_1_1proto_1_1IProbeService.md)










Inherited by the following classes: [quite::proto::ProbeServiceImpl](classquite_1_1proto_1_1ProbeServiceImpl.md)
































## Public Functions

| Type | Name |
| ---: | :--- |
| virtual AsyncResult&lt; [**ObjectReference**](structquite_1_1ObjectReference.md) &gt; | [**find\_object**](#function-find_object) ([**ObjectQuery**](structquite_1_1ObjectQuery.md) serach\_query) = 0<br> |
| virtual AsyncResult&lt; std::unordered\_map&lt; std::string, entt::meta\_any &gt; &gt; | [**get\_object\_properties**](#function-get_object_properties) (ObjectId object\_id, std::vector&lt; std::string &gt; properties) = 0<br> |
| virtual AsyncResult&lt; entt::meta\_any &gt; | [**invoke\_method**](#function-invoke_method) (ObjectId id, std::string method\_name, std::vector&lt; entt::meta\_any &gt; parameters) = 0<br> |
| virtual AsyncResult&lt; std::vector&lt; [**ObjectReference**](structquite_1_1ObjectReference.md) &gt; &gt; | [**query\_top\_level\_views**](#function-query_top_level_views) () = 0<br> |
| virtual AsyncResult&lt; void &gt; | [**set\_object\_property**](#function-set_object_property) (ObjectId object\_id, std::string property, entt::meta\_any value) = 0<br> |
| virtual AsyncResult&lt; [**Image**](classquite_1_1Image.md) &gt; | [**take\_snapshot**](#function-take_snapshot) (ObjectId id) = 0<br> |
| virtual  | [**~IProbeService**](#function-iprobeservice) () = default<br> |




























## Public Functions Documentation




### function find\_object 

```C++
virtual AsyncResult< ObjectReference > quite::proto::IProbeService::find_object (
    ObjectQuery serach_query
) = 0
```




<hr>



### function get\_object\_properties 

```C++
virtual AsyncResult< std::unordered_map< std::string, entt::meta_any > > quite::proto::IProbeService::get_object_properties (
    ObjectId object_id,
    std::vector< std::string > properties
) = 0
```




<hr>



### function invoke\_method 

```C++
virtual AsyncResult< entt::meta_any > quite::proto::IProbeService::invoke_method (
    ObjectId id,
    std::string method_name,
    std::vector< entt::meta_any > parameters
) = 0
```




<hr>



### function query\_top\_level\_views 

```C++
virtual AsyncResult< std::vector< ObjectReference > > quite::proto::IProbeService::query_top_level_views () = 0
```




<hr>



### function set\_object\_property 

```C++
virtual AsyncResult< void > quite::proto::IProbeService::set_object_property (
    ObjectId object_id,
    std::string property,
    entt::meta_any value
) = 0
```




<hr>



### function take\_snapshot 

```C++
virtual AsyncResult< Image > quite::proto::IProbeService::take_snapshot (
    ObjectId id
) = 0
```




<hr>



### function ~IProbeService 

```C++
virtual quite::proto::IProbeService::~IProbeService () = default
```




<hr>

------------------------------
The documentation for this class was generated from the following file `libs/protocol/include/quite/proto/client/probe_service.hpp`

