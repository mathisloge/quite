

# Namespace quite::meta



[**Namespace List**](namespaces.md) **>** [**quite**](namespacequite.md) **>** [**meta**](namespacequite_1_1meta.md)




















## Classes

| Type | Name |
| ---: | :--- |
| struct | [**EnumType**](structquite_1_1meta_1_1EnumType.md) <br> |
| struct | [**ListType**](structquite_1_1meta_1_1ListType.md) <br> |
| struct | [**MapType**](structquite_1_1meta_1_1MapType.md) <br> |
| class | [**MetaRegistry**](classquite_1_1meta_1_1MetaRegistry.md) <br> |
| struct | [**Method**](structquite_1_1meta_1_1Method.md) <br> |
| struct | [**ObjectType**](structquite_1_1meta_1_1ObjectType.md) <br> |
| struct | [**Property**](structquite_1_1meta_1_1Property.md) <br> |


## Public Types

| Type | Name |
| ---: | :--- |
| typedef std::unique\_ptr&lt; [**EnumType**](structquite_1_1meta_1_1EnumType.md) &gt; | [**EnumTypePtr**](#typedef-enumtypeptr)  <br> |
| typedef std::unique\_ptr&lt; [**ObjectType**](structquite_1_1meta_1_1ObjectType.md) &gt; | [**ObjectTypePtr**](#typedef-objecttypeptr)  <br> |
| enum  | [**PrimitiveType**](#enum-primitivetype)  <br> |
| typedef std::variant&lt; PrimitiveType, [**ListType**](structquite_1_1meta_1_1ListType.md), [**MapType**](structquite_1_1meta_1_1MapType.md), EnumTypePtr, ObjectTypePtr &gt; | [**Type**](#typedef-type)  <br> |
| typedef std::uint64\_t | [**TypeId**](#typedef-typeid)  <br> |
















































## Public Types Documentation




### typedef EnumTypePtr 

```C++
using quite::meta::EnumTypePtr = typedef std::unique_ptr<EnumType>;
```




<hr>



### typedef ObjectTypePtr 

```C++
using quite::meta::ObjectTypePtr = typedef std::unique_ptr<ObjectType>;
```




<hr>



### enum PrimitiveType 

```C++
enum quite::meta::PrimitiveType {
    type_unknown = 0,
    type_void,
    type_int,
    type_uint,
    type_float,
    type_double,
    type_bool,
    type_string
};
```




<hr>



### typedef Type 

```C++
using quite::meta::Type = typedef std::variant<PrimitiveType, ListType, MapType, EnumTypePtr, ObjectTypePtr>;
```




<hr>



### typedef TypeId 

```C++
using quite::meta::TypeId = typedef std::uint64_t;
```




<hr>

------------------------------
The documentation for this class was generated from the following file `libs/core/include/quite/meta/meta_registry.hpp`

