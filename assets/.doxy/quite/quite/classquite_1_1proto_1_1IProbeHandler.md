

# Class quite::proto::IProbeHandler



[**ClassList**](annotated.md) **>** [**quite**](namespacequite.md) **>** [**proto**](namespacequite_1_1proto.md) **>** [**IProbeHandler**](classquite_1_1proto_1_1IProbeHandler.md)










Inherited by the following classes: [quite::probe::QtProbeHandler](classquite_1_1probe_1_1QtProbeHandler.md)










## Classes

| Type | Name |
| ---: | :--- |
| struct | [**ImageData**](structquite_1_1proto_1_1IProbeHandler_1_1ImageData.md) <br> |


## Public Types

| Type | Name |
| ---: | :--- |
| typedef entt::dense\_map&lt; std::string, entt::meta\_any &gt; | [**PropertyMap**](#typedef-propertymap)  <br> |




















## Public Functions

| Type | Name |
| ---: | :--- |
| virtual AsyncResult&lt; PropertyMap &gt; | [**fetch\_properties**](#function-fetch_properties) (ObjectId object\_id, std::vector&lt; std::string &gt; properties) = 0<br> |
| virtual AsyncResult&lt; std::vector&lt; [**ObjectReference**](structquite_1_1ObjectReference.md) &gt; &gt; | [**fetch\_windows**](#function-fetch_windows) () = 0<br> |
| virtual AsyncResult&lt; [**ObjectReference**](structquite_1_1ObjectReference.md) &gt; | [**find\_object**](#function-find_object) ([**ObjectQuery**](structquite_1_1ObjectQuery.md) query) = 0<br> |
| virtual AsyncResult&lt; entt::meta\_any &gt; | [**invoke\_method**](#function-invoke_method) (entt::meta\_any object, std::string qualified\_method\_signature, std::vector&lt; entt::meta\_any &gt; params) = 0<br> |
| virtual AsyncResult&lt; entt::meta\_any &gt; | [**object\_instance**](#function-object_instance) (ObjectId object\_id) = 0<br> |
| virtual AsyncResult&lt; void &gt; | [**set\_property**](#function-set_property) (ObjectId object\_id, std::string property, entt::meta\_any value) = 0<br> |
| virtual AsyncResult&lt; [**ImageData**](structquite_1_1proto_1_1IProbeHandler_1_1ImageData.md) &gt; | [**take\_snapshot**](#function-take_snapshot) (ObjectId object\_id) = 0<br> |
| virtual  | [**~IProbeHandler**](#function-iprobehandler) () = default<br> |




























## Public Types Documentation




### typedef PropertyMap 

```C++
using quite::proto::IProbeHandler::PropertyMap =  entt::dense_map<std::string, entt::meta_any>;
```




<hr>
## Public Functions Documentation




### function fetch\_properties 

```C++
virtual AsyncResult< PropertyMap > quite::proto::IProbeHandler::fetch_properties (
    ObjectId object_id,
    std::vector< std::string > properties
) = 0
```




<hr>



### function fetch\_windows 

```C++
virtual AsyncResult< std::vector< ObjectReference > > quite::proto::IProbeHandler::fetch_windows () = 0
```




<hr>



### function find\_object 

```C++
virtual AsyncResult< ObjectReference > quite::proto::IProbeHandler::find_object (
    ObjectQuery query
) = 0
```




<hr>



### function invoke\_method 

```C++
virtual AsyncResult< entt::meta_any > quite::proto::IProbeHandler::invoke_method (
    entt::meta_any object,
    std::string qualified_method_signature,
    std::vector< entt::meta_any > params
) = 0
```




<hr>



### function object\_instance 

```C++
virtual AsyncResult< entt::meta_any > quite::proto::IProbeHandler::object_instance (
    ObjectId object_id
) = 0
```




<hr>



### function set\_property 

```C++
virtual AsyncResult< void > quite::proto::IProbeHandler::set_property (
    ObjectId object_id,
    std::string property,
    entt::meta_any value
) = 0
```




<hr>



### function take\_snapshot 

```C++
virtual AsyncResult< ImageData > quite::proto::IProbeHandler::take_snapshot (
    ObjectId object_id
) = 0
```




<hr>



### function ~IProbeHandler 

```C++
virtual quite::proto::IProbeHandler::~IProbeHandler () = default
```




<hr>

------------------------------
The documentation for this class was generated from the following file `libs/protocol/include/quite/proto/probe/probe_handler.hpp`

