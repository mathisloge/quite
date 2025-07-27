

# Class quite::client::RemoteObject



[**ClassList**](annotated.md) **>** [**quite**](namespacequite.md) **>** [**client**](namespacequite_1_1client.md) **>** [**RemoteObject**](classquite_1_1client_1_1RemoteObject.md)










Inherited by the following classes: [quite::client::GrpcRemoteObject](classquite_1_1client_1_1GrpcRemoteObject.md)
































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**RemoteObject**](#function-remoteobject) (ObjectId id) <br> |
| virtual AsyncResult&lt; std::unordered\_map&lt; std::string, PropertyPtr &gt; &gt; | [**fetch\_properties**](#function-fetch_properties) (std::vector&lt; std::string &gt; properties) = 0<br> |
|  ObjectId | [**id**](#function-id) () noexcept const<br> |
| virtual AsyncResult&lt; void &gt; | [**invoke\_method**](#function-invoke_method) (std::string method\_name) = 0<br> |
| virtual AsyncResult&lt; void &gt; | [**mouse\_action**](#function-mouse_action) () = 0<br> |
| virtual AsyncResult&lt; PropertyPtr &gt; | [**property**](#function-property) (std::string property\_name) = 0<br> |
| virtual AsyncResult&lt; [**Image**](classquite_1_1Image.md) &gt; | [**take\_snapshot**](#function-take_snapshot) () = 0<br> |
| virtual meta::TypeId | [**type\_id**](#function-type_id) () const = 0<br> |
| virtual AsyncResult&lt; void &gt; | [**write\_property**](#function-write_property) (std::string property\_name, entt::meta\_any value) = 0<br> |
| virtual  | [**~RemoteObject**](#function-remoteobject) () <br> |




























## Public Functions Documentation




### function RemoteObject 

```C++
explicit quite::client::RemoteObject::RemoteObject (
    ObjectId id
) 
```




<hr>



### function fetch\_properties 

```C++
virtual AsyncResult< std::unordered_map< std::string, PropertyPtr > > quite::client::RemoteObject::fetch_properties (
    std::vector< std::string > properties
) = 0
```




<hr>



### function id 

```C++
ObjectId quite::client::RemoteObject::id () noexcept const
```




<hr>



### function invoke\_method 

```C++
virtual AsyncResult< void > quite::client::RemoteObject::invoke_method (
    std::string method_name
) = 0
```




<hr>



### function mouse\_action 

```C++
virtual AsyncResult< void > quite::client::RemoteObject::mouse_action () = 0
```




<hr>



### function property 

```C++
virtual AsyncResult< PropertyPtr > quite::client::RemoteObject::property (
    std::string property_name
) = 0
```




<hr>



### function take\_snapshot 

```C++
virtual AsyncResult< Image > quite::client::RemoteObject::take_snapshot () = 0
```




<hr>



### function type\_id 

```C++
virtual meta::TypeId quite::client::RemoteObject::type_id () const = 0
```




<hr>



### function write\_property 

```C++
virtual AsyncResult< void > quite::client::RemoteObject::write_property (
    std::string property_name,
    entt::meta_any value
) = 0
```




<hr>



### function ~RemoteObject 

```C++
virtual quite::client::RemoteObject::~RemoteObject () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `libs/client/include/quite/client/remote_object.hpp`

