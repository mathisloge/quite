

# Class quite::client::GrpcValueConverter



[**ClassList**](annotated.md) **>** [**quite**](namespacequite.md) **>** [**client**](namespacequite_1_1client.md) **>** [**GrpcValueConverter**](classquite_1_1client_1_1GrpcValueConverter.md)








Inherits the following classes: [quite::proto::IValueConverter](classquite_1_1proto_1_1IValueConverter.md)






















































## Public Functions

| Type | Name |
| ---: | :--- |
| virtual entt::meta\_any | [**from**](#function-from) ([**ObjectReference**](structquite_1_1ObjectReference.md) ref) override const<br> |
|  void | [**set\_client**](#function-set_client) (std::shared\_ptr&lt; [**proto::ProbeClient**](classquite_1_1proto_1_1ProbeClient.md) &gt; client) <br> |


## Public Functions inherited from quite::proto::IValueConverter

See [quite::proto::IValueConverter](classquite_1_1proto_1_1IValueConverter.md)

| Type | Name |
| ---: | :--- |
| virtual entt::meta\_any | [**from**](classquite_1_1proto_1_1IValueConverter.md#function-from) ([**ObjectReference**](structquite_1_1ObjectReference.md) ref) const = 0<br> |
| virtual  | [**~IValueConverter**](classquite_1_1proto_1_1IValueConverter.md#function-ivalueconverter) () = default<br> |






















































## Public Functions Documentation




### function from 

```C++
virtual entt::meta_any quite::client::GrpcValueConverter::from (
    ObjectReference ref
) override const
```



Implements [*quite::proto::IValueConverter::from*](classquite_1_1proto_1_1IValueConverter.md#function-from)


<hr>



### function set\_client 

```C++
void quite::client::GrpcValueConverter::set_client (
    std::shared_ptr< proto::ProbeClient > client
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `libs/client/src/grpc_impl/grpc_value.hpp`

