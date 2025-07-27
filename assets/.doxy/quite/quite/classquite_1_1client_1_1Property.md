

# Class quite::client::Property



[**ClassList**](annotated.md) **>** [**quite**](namespacequite.md) **>** [**client**](namespacequite_1_1client.md) **>** [**Property**](classquite_1_1client_1_1Property.md)










Inherited by the following classes: [quite::client::GrpcProperty](classquite_1_1client_1_1GrpcProperty.md)
































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**Property**](#function-property) () = default<br> |
|   | [**QUITE\_DISABLE\_COPY\_MOVE**](#function-quite_disable_copy_move) ([**Property**](classquite_1_1client_1_1Property.md)) <br> |
| virtual const std::string & | [**name**](#function-name) () const = 0<br> |
| virtual AsyncResult&lt; entt::meta\_any &gt; | [**read**](#function-read) () = 0<br> |
| virtual meta::TypeId | [**type\_id**](#function-type_id) () const = 0<br> |
| virtual const Result&lt; entt::meta\_any &gt; & | [**value**](#function-value) () const = 0<br> |
| virtual AsyncResult&lt; void &gt; | [**write**](#function-write) (entt::meta\_any value) = 0<br> |
| virtual  | [**~Property**](#function-property) () <br> |




























## Public Functions Documentation




### function Property 

```C++
quite::client::Property::Property () = default
```




<hr>



### function QUITE\_DISABLE\_COPY\_MOVE 

```C++
quite::client::Property::QUITE_DISABLE_COPY_MOVE (
    Property
) 
```




<hr>



### function name 

```C++
virtual const std::string & quite::client::Property::name () const = 0
```




<hr>



### function read 

```C++
virtual AsyncResult< entt::meta_any > quite::client::Property::read () = 0
```




<hr>



### function type\_id 

```C++
virtual meta::TypeId quite::client::Property::type_id () const = 0
```




<hr>



### function value 

```C++
virtual const Result< entt::meta_any > & quite::client::Property::value () const = 0
```




<hr>



### function write 

```C++
virtual AsyncResult< void > quite::client::Property::write (
    entt::meta_any value
) = 0
```




<hr>



### function ~Property 

```C++
virtual quite::client::Property::~Property () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `libs/client/include/quite/client/property.hpp`

