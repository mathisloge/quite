

# Class quite::proto::Client



[**ClassList**](annotated.md) **>** [**quite**](namespacequite.md) **>** [**proto**](namespacequite_1_1proto.md) **>** [**Client**](classquite_1_1proto_1_1Client.md)




















## Classes

| Type | Name |
| ---: | :--- |
| struct | [**Impl**](structquite_1_1proto_1_1Client_1_1Impl.md) <br> |






















## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**Client**](#function-client) (entt::locator&lt; [**ValueRegistry**](classquite_1_1ValueRegistry.md) &gt;::node\_type value\_registry) <br> |
|   | [**QUITE\_DISABLE\_COPY\_MOVE**](#function-quite_disable_copy_move) ([**Client**](classquite_1_1proto_1_1Client.md)) <br> |
|  std::shared\_ptr&lt; [**ProbeClient**](classquite_1_1proto_1_1ProbeClient.md) &gt; | [**create\_probe\_client**](#function-create_probe_client) (std::shared\_ptr&lt; [**IValueConverter**](classquite_1_1proto_1_1IValueConverter.md) &gt; value\_converter, std::string connection\_url) <br> |
|   | [**~Client**](#function-client) () <br> |




























## Public Functions Documentation




### function Client 

```C++
explicit quite::proto::Client::Client (
    entt::locator< ValueRegistry >::node_type value_registry
) 
```




<hr>



### function QUITE\_DISABLE\_COPY\_MOVE 

```C++
quite::proto::Client::QUITE_DISABLE_COPY_MOVE (
    Client
) 
```




<hr>



### function create\_probe\_client 

```C++
std::shared_ptr< ProbeClient > quite::proto::Client::create_probe_client (
    std::shared_ptr< IValueConverter > value_converter,
    std::string connection_url
) 
```




<hr>



### function ~Client 

```C++
quite::proto::Client::~Client () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `libs/protocol/include/quite/proto/client/client.hpp`

