

# Struct quite::ObjectQuery



[**ClassList**](annotated.md) **>** [**quite**](namespacequite.md) **>** [**ObjectQuery**](structquite_1_1ObjectQuery.md)






















## Public Types

| Type | Name |
| ---: | :--- |
| typedef std::unordered\_map&lt; std::string, entt::meta\_any &gt; | [**PropertyMap**](#typedef-propertymap)  <br> |




## Public Attributes

| Type | Name |
| ---: | :--- |
|  std::shared\_ptr&lt; [**ObjectQuery**](structquite_1_1ObjectQuery.md) &gt; | [**container**](#variable-container)  <br> |
|  PropertyMap | [**properties**](#variable-properties)  <br> |
|  std::string | [**type\_name**](#variable-type_name)  <br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**ObjectQuery**](#function-objectquery-14) () = default<br> |
|   | [**ObjectQuery**](#function-objectquery-24) (const [**ObjectQuery**](structquite_1_1ObjectQuery.md) & other) = default<br> |
|   | [**ObjectQuery**](#function-objectquery-34) ([**ObjectQuery**](structquite_1_1ObjectQuery.md) && other) noexcept<br> |
|   | [**ObjectQuery**](#function-objectquery-44) (const [**ObjectQueryBuilder**](classquite_1_1ObjectQueryBuilder.md) & builder) <br> |
|  [**ObjectQuery**](structquite_1_1ObjectQuery.md) & | [**operator=**](#function-operator) (const [**ObjectQuery**](structquite_1_1ObjectQuery.md) & other) = default<br> |
|  [**ObjectQuery**](structquite_1_1ObjectQuery.md) & | [**operator=**](#function-operator_1) ([**ObjectQuery**](structquite_1_1ObjectQuery.md) && other) noexcept<br> |
|   | [**~ObjectQuery**](#function-objectquery) () = default<br> |




























## Public Types Documentation




### typedef PropertyMap 

```C++
using quite::ObjectQuery::PropertyMap =  std::unordered_map<std::string, entt::meta_any>;
```




<hr>
## Public Attributes Documentation




### variable container 

```C++
std::shared_ptr<ObjectQuery> quite::ObjectQuery::container;
```




<hr>



### variable properties 

```C++
PropertyMap quite::ObjectQuery::properties;
```




<hr>



### variable type\_name 

```C++
std::string quite::ObjectQuery::type_name;
```




<hr>
## Public Functions Documentation




### function ObjectQuery [1/4]

```C++
quite::ObjectQuery::ObjectQuery () = default
```




<hr>



### function ObjectQuery [2/4]

```C++
quite::ObjectQuery::ObjectQuery (
    const ObjectQuery & other
) = default
```




<hr>



### function ObjectQuery [3/4]

```C++
quite::ObjectQuery::ObjectQuery (
    ObjectQuery && other
) noexcept
```




<hr>



### function ObjectQuery [4/4]

```C++
quite::ObjectQuery::ObjectQuery (
    const ObjectQueryBuilder & builder
) 
```




<hr>



### function operator= 

```C++
ObjectQuery & quite::ObjectQuery::operator= (
    const ObjectQuery & other
) = default
```




<hr>



### function operator= 

```C++
ObjectQuery & quite::ObjectQuery::operator= (
    ObjectQuery && other
) noexcept
```




<hr>



### function ~ObjectQuery 

```C++
quite::ObjectQuery::~ObjectQuery () = default
```




<hr>

------------------------------
The documentation for this class was generated from the following file `libs/core/include/quite/value/object_query.hpp`

