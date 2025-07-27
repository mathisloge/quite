

# Class quite::proto::MetaRegistryImpl



[**ClassList**](annotated.md) **>** [**quite**](namespacequite.md) **>** [**proto**](namespacequite_1_1proto.md) **>** [**MetaRegistryImpl**](classquite_1_1proto_1_1MetaRegistryImpl.md)








Inherits the following classes: [quite::meta::MetaRegistry](classquite_1_1meta_1_1MetaRegistry.md)






















































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**MetaRegistryImpl**](#function-metaregistryimpl) (std::shared\_ptr&lt; agrpc::GrpcContext &gt; grpc\_context, MetaService::Stub & meta\_service\_stub) <br> |
| virtual AsyncResult&lt; meta::Type &gt; | [**lookup\_type**](#function-lookup_type) (meta::TypeId type\_id) override<br> |


## Public Functions inherited from quite::meta::MetaRegistry

See [quite::meta::MetaRegistry](classquite_1_1meta_1_1MetaRegistry.md)

| Type | Name |
| ---: | :--- |
| virtual AsyncResult&lt; meta::Type &gt; | [**lookup\_type**](classquite_1_1meta_1_1MetaRegistry.md#function-lookup_type) (meta::TypeId type\_id) = 0<br> |
| virtual  | [**~MetaRegistry**](classquite_1_1meta_1_1MetaRegistry.md#function-metaregistry) () = default<br> |






















































## Public Functions Documentation




### function MetaRegistryImpl 

```C++
explicit quite::proto::MetaRegistryImpl::MetaRegistryImpl (
    std::shared_ptr< agrpc::GrpcContext > grpc_context,
    MetaService::Stub & meta_service_stub
) 
```




<hr>



### function lookup\_type 

```C++
virtual AsyncResult< meta::Type > quite::proto::MetaRegistryImpl::lookup_type (
    meta::TypeId type_id
) override
```



Implements [*quite::meta::MetaRegistry::lookup\_type*](classquite_1_1meta_1_1MetaRegistry.md#function-lookup_type)


<hr>

------------------------------
The documentation for this class was generated from the following file `libs/protocol/src/client/meta_registry_impl.hpp`

