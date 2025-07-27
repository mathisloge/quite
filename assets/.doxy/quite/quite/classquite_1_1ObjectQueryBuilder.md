

# Class quite::ObjectQueryBuilder



[**ClassList**](annotated.md) **>** [**quite**](namespacequite.md) **>** [**ObjectQueryBuilder**](classquite_1_1ObjectQueryBuilder.md)










































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**ObjectQueryBuilder**](#function-objectquerybuilder) () <br> |
|   | [**shared\_ptr&lt; ObjectQuery &gt;**](#function-shared_ptr<-objectquery->) () const<br> |
|  [**ObjectQueryBuilder**](classquite_1_1ObjectQueryBuilder.md) & | [**with\_parent**](#function-with_parent) (std::shared\_ptr&lt; [**ObjectQuery**](structquite_1_1ObjectQuery.md) &gt; parent) <br> |
|  [**ObjectQueryBuilder**](classquite_1_1ObjectQueryBuilder.md) & | [**with\_property**](#function-with_property-16) (std::initializer\_list&lt; std::pair&lt; std::string, entt::meta\_any &gt; &gt; props) <br> |
|  [**ObjectQueryBuilder**](classquite_1_1ObjectQueryBuilder.md) & | [**with\_property**](#function-with_property-26) (std::string key, std::int64\_t value) <br> |
|  [**ObjectQueryBuilder**](classquite_1_1ObjectQueryBuilder.md) & | [**with\_property**](#function-with_property-36) (std::string key, std::uint64\_t value) <br> |
|  [**ObjectQueryBuilder**](classquite_1_1ObjectQueryBuilder.md) & | [**with\_property**](#function-with_property-46) (std::string key, double value) <br> |
|  [**ObjectQueryBuilder**](classquite_1_1ObjectQueryBuilder.md) & | [**with\_property**](#function-with_property-56) (std::string key, bool value) <br> |
|  [**ObjectQueryBuilder**](classquite_1_1ObjectQueryBuilder.md) & | [**with\_property**](#function-with_property-66) (std::string key, std::string value) <br> |
|  [**ObjectQueryBuilder**](classquite_1_1ObjectQueryBuilder.md) & | [**with\_type**](#function-with_type) (std::string type\_name) <br> |




























## Public Functions Documentation




### function ObjectQueryBuilder 

```C++
quite::ObjectQueryBuilder::ObjectQueryBuilder () 
```




<hr>



### function shared\_ptr&lt; ObjectQuery &gt; 

```C++
quite::ObjectQueryBuilder::shared_ptr< ObjectQuery > () const
```




<hr>



### function with\_parent 

```C++
ObjectQueryBuilder & quite::ObjectQueryBuilder::with_parent (
    std::shared_ptr< ObjectQuery > parent
) 
```




<hr>



### function with\_property [1/6]

```C++
ObjectQueryBuilder & quite::ObjectQueryBuilder::with_property (
    std::initializer_list< std::pair< std::string, entt::meta_any > > props
) 
```




<hr>



### function with\_property [2/6]

```C++
ObjectQueryBuilder & quite::ObjectQueryBuilder::with_property (
    std::string key,
    std::int64_t value
) 
```




<hr>



### function with\_property [3/6]

```C++
ObjectQueryBuilder & quite::ObjectQueryBuilder::with_property (
    std::string key,
    std::uint64_t value
) 
```




<hr>



### function with\_property [4/6]

```C++
ObjectQueryBuilder & quite::ObjectQueryBuilder::with_property (
    std::string key,
    double value
) 
```




<hr>



### function with\_property [5/6]

```C++
ObjectQueryBuilder & quite::ObjectQueryBuilder::with_property (
    std::string key,
    bool value
) 
```




<hr>



### function with\_property [6/6]

```C++
ObjectQueryBuilder & quite::ObjectQueryBuilder::with_property (
    std::string key,
    std::string value
) 
```




<hr>



### function with\_type 

```C++
ObjectQueryBuilder & quite::ObjectQueryBuilder::with_type (
    std::string type_name
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `libs/core/include/quite/value/object_query.hpp`

