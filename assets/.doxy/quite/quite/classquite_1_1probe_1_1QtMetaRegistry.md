

# Class quite::probe::QtMetaRegistry



[**ClassList**](annotated.md) **>** [**quite**](namespacequite.md) **>** [**probe**](namespacequite_1_1probe.md) **>** [**QtMetaRegistry**](classquite_1_1probe_1_1QtMetaRegistry.md)








Inherits the following classes: [quite::meta::MetaRegistry](classquite_1_1meta_1_1MetaRegistry.md)






















































## Public Functions

| Type | Name |
| ---: | :--- |
| virtual AsyncResult&lt; meta::Type &gt; | [**lookup\_type**](#function-lookup_type) (meta::TypeId type\_id) override<br> |


## Public Functions inherited from quite::meta::MetaRegistry

See [quite::meta::MetaRegistry](classquite_1_1meta_1_1MetaRegistry.md)

| Type | Name |
| ---: | :--- |
| virtual AsyncResult&lt; meta::Type &gt; | [**lookup\_type**](classquite_1_1meta_1_1MetaRegistry.md#function-lookup_type) (meta::TypeId type\_id) = 0<br> |
| virtual  | [**~MetaRegistry**](classquite_1_1meta_1_1MetaRegistry.md#function-metaregistry) () = default<br> |






















































## Public Functions Documentation




### function lookup\_type 

```C++
virtual AsyncResult< meta::Type > quite::probe::QtMetaRegistry::lookup_type (
    meta::TypeId type_id
) override
```



Implements [*quite::meta::MetaRegistry::lookup\_type*](classquite_1_1meta_1_1MetaRegistry.md#function-lookup_type)


<hr>

------------------------------
The documentation for this class was generated from the following file `libs/probeqt/qt_meta_registry.hpp`

