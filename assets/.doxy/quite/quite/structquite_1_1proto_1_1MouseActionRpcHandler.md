

# Struct quite::proto::MouseActionRpcHandler



[**ClassList**](annotated.md) **>** [**quite**](namespacequite.md) **>** [**proto**](namespacequite_1_1proto.md) **>** [**MouseActionRpcHandler**](structquite_1_1proto_1_1MouseActionRpcHandler.md)


























## Public Attributes

| Type | Name |
| ---: | :--- |
|  [**ServiceHandle**](classquite_1_1ServiceHandle.md)&lt; [**core::IMouseInjector**](classquite_1_1core_1_1IMouseInjector.md) &gt; | [**mouse\_injector**](#variable-mouse_injector)  <br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|  exec::task&lt; void &gt; | [**operator()**](#function-operator()) (MouseActionRPC & rpc, const MouseActionRPC::Request & request) const<br> |




























## Public Attributes Documentation




### variable mouse\_injector 

```C++
ServiceHandle<core::IMouseInjector> quite::proto::MouseActionRpcHandler::mouse_injector;
```




<hr>
## Public Functions Documentation




### function operator() 

```C++
exec::task< void > quite::proto::MouseActionRpcHandler::operator() (
    MouseActionRPC & rpc,
    const MouseActionRPC::Request & request
) const
```




<hr>

------------------------------
The documentation for this class was generated from the following file `libs/protocol/src/probe/rpc_mouse_injection.hpp`

