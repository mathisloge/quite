

# Class quite::client::GrpcRemoteObject



[**ClassList**](annotated.md) **>** [**quite**](namespacequite.md) **>** [**client**](namespacequite_1_1client.md) **>** [**GrpcRemoteObject**](classquite_1_1client_1_1GrpcRemoteObject.md)








Inherits the following classes: std::enable_shared_from_this< GrpcRemoteObject >,  [quite::client::RemoteObject](classquite_1_1client_1_1RemoteObject.md)






















































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**GrpcRemoteObject**](#function-grpcremoteobject) ([**ObjectReference**](structquite_1_1ObjectReference.md) reference, std::shared\_ptr&lt; [**proto::ProbeClient**](classquite_1_1proto_1_1ProbeClient.md) &gt; client) <br> |
| virtual AsyncResult&lt; std::unordered\_map&lt; std::string, PropertyPtr &gt; &gt; | [**fetch\_properties**](#function-fetch_properties) (std::vector&lt; std::string &gt; properties) override<br> |
|  AsyncResult&lt; entt::meta\_any &gt; | [**fetch\_property**](#function-fetch_property) (std::string property\_name) <br> |
| virtual AsyncResult&lt; void &gt; | [**invoke\_method**](#function-invoke_method) (std::string method\_name) override<br> |
| virtual AsyncResult&lt; void &gt; | [**mouse\_action**](#function-mouse_action) () override<br> |
| virtual AsyncResult&lt; PropertyPtr &gt; | [**property**](#function-property) (std::string property\_name) override<br> |
| virtual AsyncResult&lt; [**Image**](classquite_1_1Image.md) &gt; | [**take\_snapshot**](#function-take_snapshot) () override<br> |
| virtual meta::TypeId | [**type\_id**](#function-type_id) () override const<br> |
| virtual AsyncResult&lt; void &gt; | [**write\_property**](#function-write_property) (std::string property\_name, entt::meta\_any value) override<br> |


## Public Functions inherited from quite::client::RemoteObject

See [quite::client::RemoteObject](classquite_1_1client_1_1RemoteObject.md)

| Type | Name |
| ---: | :--- |
|   | [**RemoteObject**](classquite_1_1client_1_1RemoteObject.md#function-remoteobject) (ObjectId id) <br> |
| virtual AsyncResult&lt; std::unordered\_map&lt; std::string, PropertyPtr &gt; &gt; | [**fetch\_properties**](classquite_1_1client_1_1RemoteObject.md#function-fetch_properties) (std::vector&lt; std::string &gt; properties) = 0<br> |
|  ObjectId | [**id**](classquite_1_1client_1_1RemoteObject.md#function-id) () noexcept const<br> |
| virtual AsyncResult&lt; void &gt; | [**invoke\_method**](classquite_1_1client_1_1RemoteObject.md#function-invoke_method) (std::string method\_name) = 0<br> |
| virtual AsyncResult&lt; void &gt; | [**mouse\_action**](classquite_1_1client_1_1RemoteObject.md#function-mouse_action) () = 0<br> |
| virtual AsyncResult&lt; PropertyPtr &gt; | [**property**](classquite_1_1client_1_1RemoteObject.md#function-property) (std::string property\_name) = 0<br> |
| virtual AsyncResult&lt; [**Image**](classquite_1_1Image.md) &gt; | [**take\_snapshot**](classquite_1_1client_1_1RemoteObject.md#function-take_snapshot) () = 0<br> |
| virtual meta::TypeId | [**type\_id**](classquite_1_1client_1_1RemoteObject.md#function-type_id) () const = 0<br> |
| virtual AsyncResult&lt; void &gt; | [**write\_property**](classquite_1_1client_1_1RemoteObject.md#function-write_property) (std::string property\_name, entt::meta\_any value) = 0<br> |
| virtual  | [**~RemoteObject**](classquite_1_1client_1_1RemoteObject.md#function-remoteobject) () <br> |






















































## Public Functions Documentation




### function GrpcRemoteObject 

```C++
explicit quite::client::GrpcRemoteObject::GrpcRemoteObject (
    ObjectReference reference,
    std::shared_ptr< proto::ProbeClient > client
) 
```




<hr>



### function fetch\_properties 

```C++
virtual AsyncResult< std::unordered_map< std::string, PropertyPtr > > quite::client::GrpcRemoteObject::fetch_properties (
    std::vector< std::string > properties
) override
```



Implements [*quite::client::RemoteObject::fetch\_properties*](classquite_1_1client_1_1RemoteObject.md#function-fetch_properties)


<hr>



### function fetch\_property 

```C++
AsyncResult< entt::meta_any > quite::client::GrpcRemoteObject::fetch_property (
    std::string property_name
) 
```




<hr>



### function invoke\_method 

```C++
virtual AsyncResult< void > quite::client::GrpcRemoteObject::invoke_method (
    std::string method_name
) override
```



Implements [*quite::client::RemoteObject::invoke\_method*](classquite_1_1client_1_1RemoteObject.md#function-invoke_method)


<hr>



### function mouse\_action 

```C++
virtual AsyncResult< void > quite::client::GrpcRemoteObject::mouse_action () override
```



Implements [*quite::client::RemoteObject::mouse\_action*](classquite_1_1client_1_1RemoteObject.md#function-mouse_action)


<hr>



### function property 

```C++
virtual AsyncResult< PropertyPtr > quite::client::GrpcRemoteObject::property (
    std::string property_name
) override
```



Implements [*quite::client::RemoteObject::property*](classquite_1_1client_1_1RemoteObject.md#function-property)


<hr>



### function take\_snapshot 

```C++
virtual AsyncResult< Image > quite::client::GrpcRemoteObject::take_snapshot () override
```



Implements [*quite::client::RemoteObject::take\_snapshot*](classquite_1_1client_1_1RemoteObject.md#function-take_snapshot)


<hr>



### function type\_id 

```C++
virtual meta::TypeId quite::client::GrpcRemoteObject::type_id () override const
```



Implements [*quite::client::RemoteObject::type\_id*](classquite_1_1client_1_1RemoteObject.md#function-type_id)


<hr>



### function write\_property 

```C++
virtual AsyncResult< void > quite::client::GrpcRemoteObject::write_property (
    std::string property_name,
    entt::meta_any value
) override
```



Implements [*quite::client::RemoteObject::write\_property*](classquite_1_1client_1_1RemoteObject.md#function-write_property)


<hr>

------------------------------
The documentation for this class was generated from the following file `libs/client/src/grpc_impl/grpc_remote_object.hpp`

