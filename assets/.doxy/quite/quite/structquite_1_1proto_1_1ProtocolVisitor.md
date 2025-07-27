

# Struct quite::proto::ProtocolVisitor



[**ClassList**](annotated.md) **>** [**quite**](namespacequite.md) **>** [**proto**](namespacequite_1_1proto.md) **>** [**ProtocolVisitor**](structquite_1_1proto_1_1ProtocolVisitor.md)


























## Public Attributes

| Type | Name |
| ---: | :--- |
|  MetaType & | [**proto**](#variable-proto)  <br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|  void | [**operator()**](#function-operator()-15) (const meta::PrimitiveType & meta) <br> |
|  void | [**operator()**](#function-operator()-25) (const [**meta::ListType**](structquite_1_1meta_1_1ListType.md) & meta) <br> |
|  void | [**operator()**](#function-operator()-35) (const [**meta::MapType**](structquite_1_1meta_1_1MapType.md) & meta) <br> |
|  void | [**operator()**](#function-operator()-45) (const meta::EnumTypePtr & meta) <br> |
|  void | [**operator()**](#function-operator()-55) (const meta::ObjectTypePtr & meta) <br> |




























## Public Attributes Documentation




### variable proto 

```C++
MetaType& quite::proto::ProtocolVisitor::proto;
```




<hr>
## Public Functions Documentation




### function operator() [1/5]

```C++
inline void quite::proto::ProtocolVisitor::operator() (
    const meta::PrimitiveType & meta
) 
```




<hr>



### function operator() [2/5]

```C++
inline void quite::proto::ProtocolVisitor::operator() (
    const meta::ListType & meta
) 
```




<hr>



### function operator() [3/5]

```C++
inline void quite::proto::ProtocolVisitor::operator() (
    const meta::MapType & meta
) 
```




<hr>



### function operator() [4/5]

```C++
inline void quite::proto::ProtocolVisitor::operator() (
    const meta::EnumTypePtr & meta
) 
```




<hr>



### function operator() [5/5]

```C++
inline void quite::proto::ProtocolVisitor::operator() (
    const meta::ObjectTypePtr & meta
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `libs/protocol/src/meta_converters.cpp`

