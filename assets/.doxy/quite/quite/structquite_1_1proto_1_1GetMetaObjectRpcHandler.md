

# Struct quite::proto::GetMetaObjectRpcHandler



[**ClassList**](annotated.md) **>** [**quite**](namespacequite.md) **>** [**proto**](namespacequite_1_1proto.md) **>** [**GetMetaObjectRpcHandler**](structquite_1_1proto_1_1GetMetaObjectRpcHandler.md)


























## Public Attributes

| Type | Name |
| ---: | :--- |
|  [**ServiceHandle**](classquite_1_1ServiceHandle.md)&lt; [**meta::MetaRegistry**](classquite_1_1meta_1_1MetaRegistry.md) &gt; | [**meta\_registry**](#variable-meta_registry)  <br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|  exec::task&lt; void &gt; | [**operator()**](#function-operator()) (FindTypeRPC & rpc, const FindTypeRPC::Request & request) <br> |




























## Public Attributes Documentation




### variable meta\_registry 

```C++
ServiceHandle<meta::MetaRegistry> quite::proto::GetMetaObjectRpcHandler::meta_registry;
```




<hr>
## Public Functions Documentation




### function operator() 

```C++
exec::task< void > quite::proto::GetMetaObjectRpcHandler::operator() (
    FindTypeRPC & rpc,
    const FindTypeRPC::Request & request
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `libs/protocol/src/probe/rpc_meta_find_type.hpp`

