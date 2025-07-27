

# Class quite::proto::Server



[**ClassList**](annotated.md) **>** [**quite**](namespacequite.md) **>** [**proto**](namespacequite_1_1proto.md) **>** [**Server**](classquite_1_1proto_1_1Server.md)




















## Classes

| Type | Name |
| ---: | :--- |
| class | [**Impl**](classquite_1_1proto_1_1Server_1_1Impl.md) <br> |






















## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**QUITE\_DISABLE\_COPY**](#function-quite_disable_copy) ([**Server**](classquite_1_1proto_1_1Server.md)) <br> |
|   | [**Server**](#function-server-12) (std::string server\_address, [**ServiceHandle**](classquite_1_1ServiceHandle.md)&lt; [**IProbeHandler**](classquite_1_1proto_1_1IProbeHandler.md) &gt; probe\_handler, [**ServiceHandle**](classquite_1_1ServiceHandle.md)&lt; [**core::IMouseInjector**](classquite_1_1core_1_1IMouseInjector.md) &gt; mouse\_injector, [**ServiceHandle**](classquite_1_1ServiceHandle.md)&lt; [**meta::MetaRegistry**](classquite_1_1meta_1_1MetaRegistry.md) &gt; meta\_registry, [**ServiceHandle**](classquite_1_1ServiceHandle.md)&lt; [**ValueRegistry**](classquite_1_1ValueRegistry.md) &gt; value\_registry) <br> |
|   | [**Server**](#function-server-22) ([**Server**](classquite_1_1proto_1_1Server.md) && server) noexcept<br> |
|  [**Server**](classquite_1_1proto_1_1Server.md) & | [**operator=**](#function-operator) ([**Server**](classquite_1_1proto_1_1Server.md) && server) noexcept<br> |
|   | [**~Server**](#function-server) () <br> |




























## Public Functions Documentation




### function QUITE\_DISABLE\_COPY 

```C++
quite::proto::Server::QUITE_DISABLE_COPY (
    Server
) 
```




<hr>



### function Server [1/2]

```C++
quite::proto::Server::Server (
    std::string server_address,
    ServiceHandle < IProbeHandler > probe_handler,
    ServiceHandle < core::IMouseInjector > mouse_injector,
    ServiceHandle < meta::MetaRegistry > meta_registry,
    ServiceHandle < ValueRegistry > value_registry
) 
```




<hr>



### function Server [2/2]

```C++
quite::proto::Server::Server (
    Server && server
) noexcept
```




<hr>



### function operator= 

```C++
Server & quite::proto::Server::operator= (
    Server && server
) noexcept
```




<hr>



### function ~Server 

```C++
quite::proto::Server::~Server () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `libs/protocol/include/quite/proto/probe/server.hpp`

