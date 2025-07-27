

# Class quite::meta::MetaRegistry



[**ClassList**](annotated.md) **>** [**quite**](namespacequite.md) **>** [**meta**](namespacequite_1_1meta.md) **>** [**MetaRegistry**](classquite_1_1meta_1_1MetaRegistry.md)










Inherited by the following classes: [quite::probe::QtMetaRegistry](classquite_1_1probe_1_1QtMetaRegistry.md),  [quite::proto::MetaRegistryImpl](classquite_1_1proto_1_1MetaRegistryImpl.md)
































## Public Functions

| Type | Name |
| ---: | :--- |
| virtual AsyncResult&lt; meta::Type &gt; | [**lookup\_type**](#function-lookup_type) (meta::TypeId type\_id) = 0<br> |
| virtual  | [**~MetaRegistry**](#function-metaregistry) () = default<br> |




























## Public Functions Documentation




### function lookup\_type 

```C++
virtual AsyncResult< meta::Type > quite::meta::MetaRegistry::lookup_type (
    meta::TypeId type_id
) = 0
```




<hr>



### function ~MetaRegistry 

```C++
virtual quite::meta::MetaRegistry::~MetaRegistry () = default
```




<hr>

------------------------------
The documentation for this class was generated from the following file `libs/core/include/quite/meta/meta_registry.hpp`

