

# Class quite::ValueRegistry



[**ClassList**](annotated.md) **>** [**quite**](namespacequite.md) **>** [**ValueRegistry**](classquite_1_1ValueRegistry.md)






















## Public Types

| Type | Name |
| ---: | :--- |
| typedef entt::dense\_map&lt; entt::id\_type, std::string &gt; | [**PropertyNameMap**](#typedef-propertynamemap)  <br> |




















## Public Functions

| Type | Name |
| ---: | :--- |
|  entt::meta\_ctx & | [**context**](#function-context) () const<br> |
|  entt::id\_type | [**named\_property**](#function-named_property) (std::string name) <br> |
|  const PropertyNameMap & | [**property\_names**](#function-property_names) () const<br> |




























## Public Types Documentation




### typedef PropertyNameMap 

```C++
using quite::ValueRegistry::PropertyNameMap =  entt::dense_map<entt::id_type, std::string>;
```




<hr>
## Public Functions Documentation




### function context 

```C++
entt::meta_ctx & quite::ValueRegistry::context () const
```




<hr>



### function named\_property 

```C++
entt::id_type quite::ValueRegistry::named_property (
    std::string name
) 
```




<hr>



### function property\_names 

```C++
const PropertyNameMap & quite::ValueRegistry::property_names () const
```




<hr>

------------------------------
The documentation for this class was generated from the following file `libs/core/include/quite/value/value_registry.hpp`

