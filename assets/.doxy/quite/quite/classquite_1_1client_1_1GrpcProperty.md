

# Class quite::client::GrpcProperty



[**ClassList**](annotated.md) **>** [**quite**](namespacequite.md) **>** [**client**](namespacequite_1_1client.md) **>** [**GrpcProperty**](classquite_1_1client_1_1GrpcProperty.md)








Inherits the following classes: [quite::client::Property](classquite_1_1client_1_1Property.md)






















































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**GrpcProperty**](#function-grpcproperty) (std::shared\_ptr&lt; [**GrpcRemoteObject**](classquite_1_1client_1_1GrpcRemoteObject.md) &gt; parent, std::string name, entt::meta\_any initial\_value) <br> |
|   | [**QUITE\_DISABLE\_COPY\_MOVE**](#function-quite_disable_copy_move) ([**GrpcProperty**](classquite_1_1client_1_1GrpcProperty.md)) <br> |
| virtual const std::string & | [**name**](#function-name) () override const<br> |
| virtual AsyncResult&lt; entt::meta\_any &gt; | [**read**](#function-read) () override<br> |
| virtual meta::TypeId | [**type\_id**](#function-type_id) () override const<br> |
| virtual const Result&lt; entt::meta\_any &gt; & | [**value**](#function-value) () override const<br> |
| virtual AsyncResult&lt; void &gt; | [**write**](#function-write) (entt::meta\_any value) override<br> |
|   | [**~GrpcProperty**](#function-grpcproperty) () override<br> |


## Public Functions inherited from quite::client::Property

See [quite::client::Property](classquite_1_1client_1_1Property.md)

| Type | Name |
| ---: | :--- |
|   | [**Property**](classquite_1_1client_1_1Property.md#function-property) () = default<br> |
|   | [**QUITE\_DISABLE\_COPY\_MOVE**](classquite_1_1client_1_1Property.md#function-quite_disable_copy_move) ([**Property**](classquite_1_1client_1_1Property.md)) <br> |
| virtual const std::string & | [**name**](classquite_1_1client_1_1Property.md#function-name) () const = 0<br> |
| virtual AsyncResult&lt; entt::meta\_any &gt; | [**read**](classquite_1_1client_1_1Property.md#function-read) () = 0<br> |
| virtual meta::TypeId | [**type\_id**](classquite_1_1client_1_1Property.md#function-type_id) () const = 0<br> |
| virtual const Result&lt; entt::meta\_any &gt; & | [**value**](classquite_1_1client_1_1Property.md#function-value) () const = 0<br> |
| virtual AsyncResult&lt; void &gt; | [**write**](classquite_1_1client_1_1Property.md#function-write) (entt::meta\_any value) = 0<br> |
| virtual  | [**~Property**](classquite_1_1client_1_1Property.md#function-property) () <br> |






















































## Public Functions Documentation




### function GrpcProperty 

```C++
explicit quite::client::GrpcProperty::GrpcProperty (
    std::shared_ptr< GrpcRemoteObject > parent,
    std::string name,
    entt::meta_any initial_value
) 
```




<hr>



### function QUITE\_DISABLE\_COPY\_MOVE 

```C++
quite::client::GrpcProperty::QUITE_DISABLE_COPY_MOVE (
    GrpcProperty
) 
```




<hr>



### function name 

```C++
virtual const std::string & quite::client::GrpcProperty::name () override const
```



Implements [*quite::client::Property::name*](classquite_1_1client_1_1Property.md#function-name)


<hr>



### function read 

```C++
virtual AsyncResult< entt::meta_any > quite::client::GrpcProperty::read () override
```



Implements [*quite::client::Property::read*](classquite_1_1client_1_1Property.md#function-read)


<hr>



### function type\_id 

```C++
virtual meta::TypeId quite::client::GrpcProperty::type_id () override const
```



Implements [*quite::client::Property::type\_id*](classquite_1_1client_1_1Property.md#function-type_id)


<hr>



### function value 

```C++
virtual const Result< entt::meta_any > & quite::client::GrpcProperty::value () override const
```



Implements [*quite::client::Property::value*](classquite_1_1client_1_1Property.md#function-value)


<hr>



### function write 

```C++
virtual AsyncResult< void > quite::client::GrpcProperty::write (
    entt::meta_any value
) override
```



Implements [*quite::client::Property::write*](classquite_1_1client_1_1Property.md#function-write)


<hr>



### function ~GrpcProperty 

```C++
quite::client::GrpcProperty::~GrpcProperty () override
```




<hr>

------------------------------
The documentation for this class was generated from the following file `libs/client/src/grpc_impl/grpc_property.hpp`

