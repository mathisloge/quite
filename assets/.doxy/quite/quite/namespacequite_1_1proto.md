

# Namespace quite::proto



[**Namespace List**](namespaces.md) **>** [**quite**](namespacequite.md) **>** [**proto**](namespacequite_1_1proto.md)




















## Classes

| Type | Name |
| ---: | :--- |
| class | [**Client**](classquite_1_1proto_1_1Client.md) <br> |
| struct | [**FindObjectRpcHandler**](structquite_1_1proto_1_1FindObjectRpcHandler.md) <br> |
| struct | [**GetMetaObjectRpcHandler**](structquite_1_1proto_1_1GetMetaObjectRpcHandler.md) <br> |
| struct | [**GetObjectPropertiesRpcHandler**](structquite_1_1proto_1_1GetObjectPropertiesRpcHandler.md) <br> |
| struct | [**GetViewsRpcHandler**](structquite_1_1proto_1_1GetViewsRpcHandler.md) <br> |
| class | [**GrpcManager**](classquite_1_1proto_1_1GrpcManager.md) <br> |
| class | [**IProbeHandler**](classquite_1_1proto_1_1IProbeHandler.md) <br> |
| class | [**IProbeService**](classquite_1_1proto_1_1IProbeService.md) <br> |
| class | [**IValueConverter**](classquite_1_1proto_1_1IValueConverter.md) <br> |
| struct | [**InvokeMethodRpcHandler**](structquite_1_1proto_1_1InvokeMethodRpcHandler.md) <br> |
| class | [**MetaRegistryImpl**](classquite_1_1proto_1_1MetaRegistryImpl.md) <br> |
| struct | [**MouseActionRpcHandler**](structquite_1_1proto_1_1MouseActionRpcHandler.md) <br> |
| class | [**MouseInjectorImpl**](classquite_1_1proto_1_1MouseInjectorImpl.md) <br> |
| class | [**ProbeClient**](classquite_1_1proto_1_1ProbeClient.md) <br> |
| class | [**ProbeClientImpl**](classquite_1_1proto_1_1ProbeClientImpl.md) <br> |
| class | [**ProbeServiceImpl**](classquite_1_1proto_1_1ProbeServiceImpl.md) <br> |
| class | [**ProbeValueConverter**](classquite_1_1proto_1_1ProbeValueConverter.md) <br> |
| struct | [**ProtocolVisitor**](structquite_1_1proto_1_1ProtocolVisitor.md) <br> |
| class | [**Server**](classquite_1_1proto_1_1Server.md) <br> |
| struct | [**SetObjectPropertyRpcHandler**](structquite_1_1proto_1_1SetObjectPropertyRpcHandler.md) <br> |
| struct | [**SnapshotRpcHandler**](structquite_1_1proto_1_1SnapshotRpcHandler.md) <br> |


## Public Types

| Type | Name |
| ---: | :--- |
| typedef agrpc::ServerRPC&lt;&quite::proto::ProbeService::AsyncService::RequestFindObject &gt; | [**FindObjectRPC**](#typedef-findobjectrpc)  <br> |
| typedef agrpc::ServerRPC&lt;&quite::proto::MetaService::AsyncService::RequestFindType &gt; | [**FindTypeRPC**](#typedef-findtyperpc)  <br> |
| typedef agrpc::ServerRPC&lt;&quite::proto::ProbeService::AsyncService::RequestGetObjectProperties &gt; | [**GetObjectPropertiesRPC**](#typedef-getobjectpropertiesrpc)  <br> |
| typedef agrpc::ServerRPC&lt;&quite::proto::ProbeService::AsyncService::RequestGetViews &gt; | [**GetViewsRPC**](#typedef-getviewsrpc)  <br> |
| typedef agrpc::ServerRPC&lt;&quite::proto::ProbeService::AsyncService::RequestInvokeMethod &gt; | [**InvokeMethodRPC**](#typedef-invokemethodrpc)  <br> |
| typedef agrpc::ServerRPC&lt;&quite::proto::ProbeService::AsyncService::RequestMouseAction &gt; | [**MouseActionRPC**](#typedef-mouseactionrpc)  <br> |
| typedef [**ServiceHandle**](classquite_1_1ServiceHandle.md)&lt; [**IProbeHandler**](classquite_1_1proto_1_1IProbeHandler.md) &gt; | [**ProbeHandlerHandle**](#typedef-probehandlerhandle)  <br> |
| typedef agrpc::ServerRPC&lt;&quite::proto::ProbeService::AsyncService::RequestCreateScreenshot &gt; | [**RpcSnapshot**](#typedef-rpcsnapshot)  <br> |
| typedef agrpc::ServerRPC&lt;&quite::proto::ProbeService::AsyncService::RequestSetObjectProperty &gt; | [**SetObjectPropertyRPC**](#typedef-setobjectpropertyrpc)  <br> |




















## Public Functions

| Type | Name |
| ---: | :--- |
|  void | [**configure\_client\_context**](#function-configure_client_context) (grpc::ClientContext & client\_context) <br> |
|  entt::meta\_any | [**convert\_value**](#function-convert_value) (const [**ValueRegistry**](classquite_1_1ValueRegistry.md) & value\_registry, const [**IValueConverter**](classquite_1_1proto_1_1IValueConverter.md) & converter, const Value & value) <br> |
|  Value | [**create\_value**](#function-create_value) (const [**ValueRegistry**](classquite_1_1ValueRegistry.md) & value\_registry, const entt::meta\_any & any) <br> |
|  meta::PrimitiveType | [**from\_protocol**](#function-from_protocol) (const MetaPrimitiveType & type) <br> |
|  [**meta::ListType**](structquite_1_1meta_1_1ListType.md) | [**from\_protocol**](#function-from_protocol) (const MetaListType & type) <br> |
|  [**meta::MapType**](structquite_1_1meta_1_1MapType.md) | [**from\_protocol**](#function-from_protocol) (const MetaMapType & type) <br> |
|  meta::ObjectTypePtr | [**from\_protocol**](#function-from_protocol) (const MetaObjectType & type) <br> |
|  meta::EnumTypePtr | [**from\_protocol**](#function-from_protocol) (const MetaEnumType & type) <br> |
|  [**Error**](structquite_1_1Error.md) | [**grpc\_status2result**](#function-grpc_status2result) (const grpc::Status & error) <br> |
|  agrpc::detail::RPCHandlerSender&lt; GetObjectPropertiesRPC, [**GetObjectPropertiesRpcHandler**](structquite_1_1proto_1_1GetObjectPropertiesRpcHandler.md) &gt; | [**make\_rpc\_fetch\_object\_properties**](#function-make_rpc_fetch_object_properties) (agrpc::GrpcContext & grpc\_context, quite::proto::ProbeService::AsyncService & service, [**ProbeHandlerHandle**](classquite_1_1ServiceHandle.md) probe\_handler, [**ServiceHandle**](classquite_1_1ServiceHandle.md)&lt; [**ValueRegistry**](classquite_1_1ValueRegistry.md) &gt; value\_registry) <br> |
|  agrpc::detail::RPCHandlerSender&lt; GetViewsRPC, [**GetViewsRpcHandler**](structquite_1_1proto_1_1GetViewsRpcHandler.md) &gt; | [**make\_rpc\_fetch\_windows**](#function-make_rpc_fetch_windows) (agrpc::GrpcContext & grpc\_context, quite::proto::ProbeService::AsyncService & service, [**ProbeHandlerHandle**](classquite_1_1ServiceHandle.md) probe\_handler) <br> |
|  agrpc::detail::RPCHandlerSender&lt; FindObjectRPC, [**FindObjectRpcHandler**](structquite_1_1proto_1_1FindObjectRpcHandler.md) &gt; | [**make\_rpc\_find\_object**](#function-make_rpc_find_object) (agrpc::GrpcContext & grpc\_context, quite::proto::ProbeService::AsyncService & service, [**ProbeHandlerHandle**](classquite_1_1ServiceHandle.md) probe\_handler, [**ServiceHandle**](classquite_1_1ServiceHandle.md)&lt; [**ValueRegistry**](classquite_1_1ValueRegistry.md) &gt; value\_registry) <br> |
|  agrpc::detail::RPCHandlerSender&lt; InvokeMethodRPC, [**InvokeMethodRpcHandler**](structquite_1_1proto_1_1InvokeMethodRpcHandler.md) &gt; | [**make\_rpc\_invoke\_method**](#function-make_rpc_invoke_method) (agrpc::GrpcContext & grpc\_context, quite::proto::ProbeService::AsyncService & service, [**ProbeHandlerHandle**](classquite_1_1ServiceHandle.md) probe\_handler, [**ServiceHandle**](classquite_1_1ServiceHandle.md)&lt; [**ValueRegistry**](classquite_1_1ValueRegistry.md) &gt; value\_registry) <br> |
|  agrpc::detail::RPCHandlerSender&lt; FindTypeRPC, [**GetMetaObjectRpcHandler**](structquite_1_1proto_1_1GetMetaObjectRpcHandler.md) &gt; | [**make\_rpc\_meta\_find\_type**](#function-make_rpc_meta_find_type) (agrpc::GrpcContext & grpc\_context, quite::proto::MetaService::AsyncService & service, [**ServiceHandle**](classquite_1_1ServiceHandle.md)&lt; [**meta::MetaRegistry**](classquite_1_1meta_1_1MetaRegistry.md) &gt; meta\_registry) <br> |
|  agrpc::detail::RPCHandlerSender&lt; MouseActionRPC, [**MouseActionRpcHandler**](structquite_1_1proto_1_1MouseActionRpcHandler.md) &gt; | [**make\_rpc\_mouse\_injection**](#function-make_rpc_mouse_injection) (agrpc::GrpcContext & grpc\_context, quite::proto::ProbeService::AsyncService & service, [**ServiceHandle**](classquite_1_1ServiceHandle.md)&lt; [**core::IMouseInjector**](classquite_1_1core_1_1IMouseInjector.md) &gt; mouse\_injector) <br> |
|  agrpc::detail::RPCHandlerSender&lt; SetObjectPropertyRPC, [**SetObjectPropertyRpcHandler**](structquite_1_1proto_1_1SetObjectPropertyRpcHandler.md) &gt; | [**make\_rpc\_set\_object\_property**](#function-make_rpc_set_object_property) (agrpc::GrpcContext & grpc\_context, quite::proto::ProbeService::AsyncService & service, [**ProbeHandlerHandle**](classquite_1_1ServiceHandle.md) probe\_handler, [**ServiceHandle**](classquite_1_1ServiceHandle.md)&lt; [**ValueRegistry**](classquite_1_1ValueRegistry.md) &gt; value\_registry) <br> |
|  agrpc::detail::RPCHandlerSender&lt; RpcSnapshot, [**SnapshotRpcHandler**](structquite_1_1proto_1_1SnapshotRpcHandler.md) &gt; | [**make\_rpc\_snapshot**](#function-make_rpc_snapshot) (agrpc::GrpcContext & grpc\_context, quite::proto::ProbeService::AsyncService & service, [**ProbeHandlerHandle**](classquite_1_1ServiceHandle.md) probe\_handler) <br> |
|  grpc::Status | [**result2grpc\_status**](#function-result2grpc_status) (const [**Error**](structquite_1_1Error.md) & error) <br> |
|  void | [**to\_protocol**](#function-to_protocol) (const meta::Type & type, MetaType & proto) <br> |




























## Public Types Documentation




### typedef FindObjectRPC 

```C++
using quite::proto::FindObjectRPC = typedef agrpc::ServerRPC<&quite::proto::ProbeService::AsyncService::RequestFindObject>;
```




<hr>



### typedef FindTypeRPC 

```C++
using quite::proto::FindTypeRPC = typedef agrpc::ServerRPC<&quite::proto::MetaService::AsyncService::RequestFindType>;
```




<hr>



### typedef GetObjectPropertiesRPC 

```C++
using quite::proto::GetObjectPropertiesRPC = typedef agrpc::ServerRPC<&quite::proto::ProbeService::AsyncService::RequestGetObjectProperties>;
```




<hr>



### typedef GetViewsRPC 

```C++
using quite::proto::GetViewsRPC = typedef agrpc::ServerRPC<&quite::proto::ProbeService::AsyncService::RequestGetViews>;
```




<hr>



### typedef InvokeMethodRPC 

```C++
using quite::proto::InvokeMethodRPC = typedef agrpc::ServerRPC<&quite::proto::ProbeService::AsyncService::RequestInvokeMethod>;
```




<hr>



### typedef MouseActionRPC 

```C++
using quite::proto::MouseActionRPC = typedef agrpc::ServerRPC<&quite::proto::ProbeService::AsyncService::RequestMouseAction>;
```




<hr>



### typedef ProbeHandlerHandle 

```C++
using quite::proto::ProbeHandlerHandle = typedef ServiceHandle<IProbeHandler>;
```




<hr>



### typedef RpcSnapshot 

```C++
using quite::proto::RpcSnapshot = typedef agrpc::ServerRPC<&quite::proto::ProbeService::AsyncService::RequestCreateScreenshot>;
```




<hr>



### typedef SetObjectPropertyRPC 

```C++
using quite::proto::SetObjectPropertyRPC = typedef agrpc::ServerRPC<&quite::proto::ProbeService::AsyncService::RequestSetObjectProperty>;
```




<hr>
## Public Functions Documentation




### function configure\_client\_context 

```C++
void quite::proto::configure_client_context (
    grpc::ClientContext & client_context
) 
```




<hr>



### function convert\_value 

```C++
entt::meta_any quite::proto::convert_value (
    const ValueRegistry & value_registry,
    const IValueConverter & converter,
    const Value & value
) 
```




<hr>



### function create\_value 

```C++
Value quite::proto::create_value (
    const ValueRegistry & value_registry,
    const entt::meta_any & any
) 
```




<hr>



### function from\_protocol 

```C++
meta::PrimitiveType quite::proto::from_protocol (
    const MetaPrimitiveType & type
) 
```




<hr>



### function from\_protocol 

```C++
meta::ListType quite::proto::from_protocol (
    const MetaListType & type
) 
```




<hr>



### function from\_protocol 

```C++
meta::MapType quite::proto::from_protocol (
    const MetaMapType & type
) 
```




<hr>



### function from\_protocol 

```C++
meta::ObjectTypePtr quite::proto::from_protocol (
    const MetaObjectType & type
) 
```




<hr>



### function from\_protocol 

```C++
meta::EnumTypePtr quite::proto::from_protocol (
    const MetaEnumType & type
) 
```




<hr>



### function grpc\_status2result 

```C++
Error quite::proto::grpc_status2result (
    const grpc::Status & error
) 
```




<hr>



### function make\_rpc\_fetch\_object\_properties 

```C++
agrpc::detail::RPCHandlerSender< GetObjectPropertiesRPC, GetObjectPropertiesRpcHandler > quite::proto::make_rpc_fetch_object_properties (
    agrpc::GrpcContext & grpc_context,
    quite::proto::ProbeService::AsyncService & service,
    ProbeHandlerHandle probe_handler,
    ServiceHandle < ValueRegistry > value_registry
) 
```




<hr>



### function make\_rpc\_fetch\_windows 

```C++
agrpc::detail::RPCHandlerSender< GetViewsRPC, GetViewsRpcHandler > quite::proto::make_rpc_fetch_windows (
    agrpc::GrpcContext & grpc_context,
    quite::proto::ProbeService::AsyncService & service,
    ProbeHandlerHandle probe_handler
) 
```




<hr>



### function make\_rpc\_find\_object 

```C++
agrpc::detail::RPCHandlerSender< FindObjectRPC, FindObjectRpcHandler > quite::proto::make_rpc_find_object (
    agrpc::GrpcContext & grpc_context,
    quite::proto::ProbeService::AsyncService & service,
    ProbeHandlerHandle probe_handler,
    ServiceHandle < ValueRegistry > value_registry
) 
```




<hr>



### function make\_rpc\_invoke\_method 

```C++
agrpc::detail::RPCHandlerSender< InvokeMethodRPC, InvokeMethodRpcHandler > quite::proto::make_rpc_invoke_method (
    agrpc::GrpcContext & grpc_context,
    quite::proto::ProbeService::AsyncService & service,
    ProbeHandlerHandle probe_handler,
    ServiceHandle < ValueRegistry > value_registry
) 
```




<hr>



### function make\_rpc\_meta\_find\_type 

```C++
agrpc::detail::RPCHandlerSender< FindTypeRPC, GetMetaObjectRpcHandler > quite::proto::make_rpc_meta_find_type (
    agrpc::GrpcContext & grpc_context,
    quite::proto::MetaService::AsyncService & service,
    ServiceHandle < meta::MetaRegistry > meta_registry
) 
```




<hr>



### function make\_rpc\_mouse\_injection 

```C++
agrpc::detail::RPCHandlerSender< MouseActionRPC, MouseActionRpcHandler > quite::proto::make_rpc_mouse_injection (
    agrpc::GrpcContext & grpc_context,
    quite::proto::ProbeService::AsyncService & service,
    ServiceHandle < core::IMouseInjector > mouse_injector
) 
```




<hr>



### function make\_rpc\_set\_object\_property 

```C++
agrpc::detail::RPCHandlerSender< SetObjectPropertyRPC, SetObjectPropertyRpcHandler > quite::proto::make_rpc_set_object_property (
    agrpc::GrpcContext & grpc_context,
    quite::proto::ProbeService::AsyncService & service,
    ProbeHandlerHandle probe_handler,
    ServiceHandle < ValueRegistry > value_registry
) 
```




<hr>



### function make\_rpc\_snapshot 

```C++
agrpc::detail::RPCHandlerSender< RpcSnapshot, SnapshotRpcHandler > quite::proto::make_rpc_snapshot (
    agrpc::GrpcContext & grpc_context,
    quite::proto::ProbeService::AsyncService & service,
    ProbeHandlerHandle probe_handler
) 
```




<hr>



### function result2grpc\_status 

```C++
grpc::Status quite::proto::result2grpc_status (
    const Error & error
) 
```




<hr>



### function to\_protocol 

```C++
void quite::proto::to_protocol (
    const meta::Type & type,
    MetaType & proto
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `libs/protocol/include/quite/proto/client/client.hpp`

