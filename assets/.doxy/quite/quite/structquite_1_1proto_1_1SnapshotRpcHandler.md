

# Struct quite::proto::SnapshotRpcHandler



[**ClassList**](annotated.md) **>** [**quite**](namespacequite.md) **>** [**proto**](namespacequite_1_1proto.md) **>** [**SnapshotRpcHandler**](structquite_1_1proto_1_1SnapshotRpcHandler.md)


























## Public Attributes

| Type | Name |
| ---: | :--- |
|  [**ProbeHandlerHandle**](classquite_1_1ServiceHandle.md) | [**probe\_handler**](#variable-probe_handler)  <br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|  exec::task&lt; void &gt; | [**operator()**](#function-operator()) (RpcSnapshot & rpc, const RpcSnapshot::Request & request) const<br> |




























## Public Attributes Documentation




### variable probe\_handler 

```C++
ProbeHandlerHandle quite::proto::SnapshotRpcHandler::probe_handler;
```




<hr>
## Public Functions Documentation




### function operator() 

```C++
exec::task< void > quite::proto::SnapshotRpcHandler::operator() (
    RpcSnapshot & rpc,
    const RpcSnapshot::Request & request
) const
```




<hr>

------------------------------
The documentation for this class was generated from the following file `libs/protocol/src/probe/rpc_snapshot.hpp`

