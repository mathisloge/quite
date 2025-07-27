

# Class quite::probe::QtProbeHandler



[**ClassList**](annotated.md) **>** [**quite**](namespacequite.md) **>** [**probe**](namespacequite_1_1probe.md) **>** [**QtProbeHandler**](classquite_1_1probe_1_1QtProbeHandler.md)








Inherits the following classes: [quite::proto::IProbeHandler](classquite_1_1proto_1_1IProbeHandler.md)
















## Public Types inherited from quite::proto::IProbeHandler

See [quite::proto::IProbeHandler](classquite_1_1proto_1_1IProbeHandler.md)

| Type | Name |
| ---: | :--- |
| typedef entt::dense\_map&lt; std::string, entt::meta\_any &gt; | [**PropertyMap**](classquite_1_1proto_1_1IProbeHandler.md#typedef-propertymap)  <br> |






































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**QtProbeHandler**](#function-qtprobehandler) (const [**ObjectTracker**](classquite_1_1probe_1_1ObjectTracker.md) & object\_tracker) <br> |
| virtual AsyncResult&lt; PropertyMap &gt; | [**fetch\_properties**](#function-fetch_properties) (ObjectId object\_id, std::vector&lt; std::string &gt; properties) override<br> |
| virtual AsyncResult&lt; std::vector&lt; [**ObjectReference**](structquite_1_1ObjectReference.md) &gt; &gt; | [**fetch\_windows**](#function-fetch_windows) () override<br> |
| virtual AsyncResult&lt; [**ObjectReference**](structquite_1_1ObjectReference.md) &gt; | [**find\_object**](#function-find_object) ([**ObjectQuery**](structquite_1_1ObjectQuery.md) query) override<br> |
| virtual AsyncResult&lt; entt::meta\_any &gt; | [**invoke\_method**](#function-invoke_method) (entt::meta\_any object, std::string qualified\_method\_signature, std::vector&lt; entt::meta\_any &gt; params) override<br> |
| virtual AsyncResult&lt; entt::meta\_any &gt; | [**object\_instance**](#function-object_instance) (ObjectId object\_id) override<br> |
| virtual AsyncResult&lt; void &gt; | [**set\_property**](#function-set_property) (ObjectId object\_id, std::string property, entt::meta\_any value) override<br> |
| virtual AsyncResult&lt; [**ImageData**](structquite_1_1proto_1_1IProbeHandler_1_1ImageData.md) &gt; | [**take\_snapshot**](#function-take_snapshot) (ObjectId object\_id) override<br> |


## Public Functions inherited from quite::proto::IProbeHandler

See [quite::proto::IProbeHandler](classquite_1_1proto_1_1IProbeHandler.md)

| Type | Name |
| ---: | :--- |
| virtual AsyncResult&lt; PropertyMap &gt; | [**fetch\_properties**](classquite_1_1proto_1_1IProbeHandler.md#function-fetch_properties) (ObjectId object\_id, std::vector&lt; std::string &gt; properties) = 0<br> |
| virtual AsyncResult&lt; std::vector&lt; [**ObjectReference**](structquite_1_1ObjectReference.md) &gt; &gt; | [**fetch\_windows**](classquite_1_1proto_1_1IProbeHandler.md#function-fetch_windows) () = 0<br> |
| virtual AsyncResult&lt; [**ObjectReference**](structquite_1_1ObjectReference.md) &gt; | [**find\_object**](classquite_1_1proto_1_1IProbeHandler.md#function-find_object) ([**ObjectQuery**](structquite_1_1ObjectQuery.md) query) = 0<br> |
| virtual AsyncResult&lt; entt::meta\_any &gt; | [**invoke\_method**](classquite_1_1proto_1_1IProbeHandler.md#function-invoke_method) (entt::meta\_any object, std::string qualified\_method\_signature, std::vector&lt; entt::meta\_any &gt; params) = 0<br> |
| virtual AsyncResult&lt; entt::meta\_any &gt; | [**object\_instance**](classquite_1_1proto_1_1IProbeHandler.md#function-object_instance) (ObjectId object\_id) = 0<br> |
| virtual AsyncResult&lt; void &gt; | [**set\_property**](classquite_1_1proto_1_1IProbeHandler.md#function-set_property) (ObjectId object\_id, std::string property, entt::meta\_any value) = 0<br> |
| virtual AsyncResult&lt; [**ImageData**](structquite_1_1proto_1_1IProbeHandler_1_1ImageData.md) &gt; | [**take\_snapshot**](classquite_1_1proto_1_1IProbeHandler.md#function-take_snapshot) (ObjectId object\_id) = 0<br> |
| virtual  | [**~IProbeHandler**](classquite_1_1proto_1_1IProbeHandler.md#function-iprobehandler) () = default<br> |






















































## Public Functions Documentation




### function QtProbeHandler 

```C++
explicit quite::probe::QtProbeHandler::QtProbeHandler (
    const ObjectTracker & object_tracker
) 
```




<hr>



### function fetch\_properties 

```C++
virtual AsyncResult< PropertyMap > quite::probe::QtProbeHandler::fetch_properties (
    ObjectId object_id,
    std::vector< std::string > properties
) override
```



Implements [*quite::proto::IProbeHandler::fetch\_properties*](classquite_1_1proto_1_1IProbeHandler.md#function-fetch_properties)


<hr>



### function fetch\_windows 

```C++
virtual AsyncResult< std::vector< ObjectReference > > quite::probe::QtProbeHandler::fetch_windows () override
```



Implements [*quite::proto::IProbeHandler::fetch\_windows*](classquite_1_1proto_1_1IProbeHandler.md#function-fetch_windows)


<hr>



### function find\_object 

```C++
virtual AsyncResult< ObjectReference > quite::probe::QtProbeHandler::find_object (
    ObjectQuery query
) override
```



Implements [*quite::proto::IProbeHandler::find\_object*](classquite_1_1proto_1_1IProbeHandler.md#function-find_object)


<hr>



### function invoke\_method 

```C++
virtual AsyncResult< entt::meta_any > quite::probe::QtProbeHandler::invoke_method (
    entt::meta_any object,
    std::string qualified_method_signature,
    std::vector< entt::meta_any > params
) override
```



Implements [*quite::proto::IProbeHandler::invoke\_method*](classquite_1_1proto_1_1IProbeHandler.md#function-invoke_method)


<hr>



### function object\_instance 

```C++
virtual AsyncResult< entt::meta_any > quite::probe::QtProbeHandler::object_instance (
    ObjectId object_id
) override
```



Implements [*quite::proto::IProbeHandler::object\_instance*](classquite_1_1proto_1_1IProbeHandler.md#function-object_instance)


<hr>



### function set\_property 

```C++
virtual AsyncResult< void > quite::probe::QtProbeHandler::set_property (
    ObjectId object_id,
    std::string property,
    entt::meta_any value
) override
```



Implements [*quite::proto::IProbeHandler::set\_property*](classquite_1_1proto_1_1IProbeHandler.md#function-set_property)


<hr>



### function take\_snapshot 

```C++
virtual AsyncResult< ImageData > quite::probe::QtProbeHandler::take_snapshot (
    ObjectId object_id
) override
```



Implements [*quite::proto::IProbeHandler::take\_snapshot*](classquite_1_1proto_1_1IProbeHandler.md#function-take_snapshot)


<hr>

------------------------------
The documentation for this class was generated from the following file `libs/probeqt/qt_probe_handler.hpp`

