

# Struct quite::proto::SetObjectPropertyRpcHandler



[**ClassList**](annotated.md) **>** [**quite**](namespacequite.md) **>** [**proto**](namespacequite_1_1proto.md) **>** [**SetObjectPropertyRpcHandler**](structquite_1_1proto_1_1SetObjectPropertyRpcHandler.md)


























## Public Attributes

| Type | Name |
| ---: | :--- |
|  [**ProbeHandlerHandle**](classquite_1_1ServiceHandle.md) | [**probe\_handler**](#variable-probe_handler)  <br> |
|  [**ServiceHandle**](classquite_1_1ServiceHandle.md)&lt; [**ValueRegistry**](classquite_1_1ValueRegistry.md) &gt; | [**value\_registry**](#variable-value_registry)  <br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|  exec::task&lt; void &gt; | [**operator()**](#function-operator()) (SetObjectPropertyRPC & rpc, const SetObjectPropertyRPC::Request & request) <br> |




























## Public Attributes Documentation




### variable probe\_handler 

```C++
ProbeHandlerHandle quite::proto::SetObjectPropertyRpcHandler::probe_handler;
```




<hr>



### variable value\_registry 

```C++
ServiceHandle<ValueRegistry> quite::proto::SetObjectPropertyRpcHandler::value_registry;
```




<hr>
## Public Functions Documentation




### function operator() 

```C++
exec::task< void > quite::proto::SetObjectPropertyRpcHandler::operator() (
    SetObjectPropertyRPC & rpc,
    const SetObjectPropertyRPC::Request & request
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `libs/protocol/src/probe/rpc_set_object_property.hpp`

