

# Struct quite::proto::InvokeMethodRpcHandler



[**ClassList**](annotated.md) **>** [**quite**](namespacequite.md) **>** [**proto**](namespacequite_1_1proto.md) **>** [**InvokeMethodRpcHandler**](structquite_1_1proto_1_1InvokeMethodRpcHandler.md)


























## Public Attributes

| Type | Name |
| ---: | :--- |
|  [**ProbeHandlerHandle**](classquite_1_1ServiceHandle.md) | [**probe\_handler**](#variable-probe_handler)  <br> |
|  [**ServiceHandle**](classquite_1_1ServiceHandle.md)&lt; [**ValueRegistry**](classquite_1_1ValueRegistry.md) &gt; | [**value\_registry**](#variable-value_registry)  <br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|  exec::task&lt; void &gt; | [**operator()**](#function-operator()) (InvokeMethodRPC & rpc, const InvokeMethodRPC::Request & request) const<br> |




























## Public Attributes Documentation




### variable probe\_handler 

```C++
ProbeHandlerHandle quite::proto::InvokeMethodRpcHandler::probe_handler;
```




<hr>



### variable value\_registry 

```C++
ServiceHandle<ValueRegistry> quite::proto::InvokeMethodRpcHandler::value_registry;
```




<hr>
## Public Functions Documentation




### function operator() 

```C++
exec::task< void > quite::proto::InvokeMethodRpcHandler::operator() (
    InvokeMethodRPC & rpc,
    const InvokeMethodRPC::Request & request
) const
```




<hr>

------------------------------
The documentation for this class was generated from the following file `libs/protocol/src/probe/rpc_invoke_method.hpp`

