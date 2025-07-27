

# Namespace quite::client



[**Namespace List**](namespaces.md) **>** [**quite**](namespacequite.md) **>** [**client**](namespacequite_1_1client.md)




















## Classes

| Type | Name |
| ---: | :--- |
| class | [**BasicProbe**](classquite_1_1client_1_1BasicProbe.md) <br> |
| class | [**GrpcProbe**](classquite_1_1client_1_1GrpcProbe.md) <br> |
| class | [**GrpcProperty**](classquite_1_1client_1_1GrpcProperty.md) <br> |
| class | [**GrpcRemoteObject**](classquite_1_1client_1_1GrpcRemoteObject.md) <br> |
| class | [**GrpcValueConverter**](classquite_1_1client_1_1GrpcValueConverter.md) <br> |
| class | [**Probe**](classquite_1_1client_1_1Probe.md) <br> |
| class | [**ProbeHandle**](classquite_1_1client_1_1ProbeHandle.md) <br> |
| class | [**ProbeManager**](classquite_1_1client_1_1ProbeManager.md) <br> |
| class | [**Property**](classquite_1_1client_1_1Property.md) <br> |
| class | [**RemoteObject**](classquite_1_1client_1_1RemoteObject.md) <br> |


## Public Types

| Type | Name |
| ---: | :--- |
| typedef std::uint64\_t | [**ObjectId**](#typedef-objectid)  <br> |
| typedef std::shared\_ptr&lt; [**Property**](classquite_1_1client_1_1Property.md) &gt; | [**PropertyPtr**](#typedef-propertyptr)  <br> |
| typedef std::shared\_ptr&lt; [**RemoteObject**](classquite_1_1client_1_1RemoteObject.md) &gt; | [**RemoteObjectPtr**](#typedef-remoteobjectptr)  <br> |




















## Public Functions

| Type | Name |
| ---: | :--- |
|  QUITE\_CLIENT\_EXPORT execpools::asio\_thread\_pool & | [**asio\_context**](#function-asio_context) () <br> |
|  AsyncResult&lt; nlohmann::json &gt; QUITE\_CLIENT\_EXPORT | [**dump\_properties**](#function-dump_properties) (RemoteObjectPtr remote\_object, std::vector&lt; std::string &gt; properties) <br> |




























## Public Types Documentation




### typedef ObjectId 

```C++
using quite::client::ObjectId = typedef std::uint64_t;
```




<hr>



### typedef PropertyPtr 

```C++
using quite::client::PropertyPtr = typedef std::shared_ptr<Property>;
```




<hr>



### typedef RemoteObjectPtr 

```C++
using quite::client::RemoteObjectPtr = typedef std::shared_ptr<RemoteObject>;
```




<hr>
## Public Functions Documentation




### function asio\_context 

```C++
QUITE_CLIENT_EXPORT execpools::asio_thread_pool & quite::client::asio_context () 
```




<hr>



### function dump\_properties 

```C++
AsyncResult< nlohmann::json > QUITE_CLIENT_EXPORT quite::client::dump_properties (
    RemoteObjectPtr remote_object,
    std::vector< std::string > properties
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `libs/client/include/quite/client/probe.hpp`

