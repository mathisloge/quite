

# Namespace quite



[**Namespace List**](namespaces.md) **>** [**quite**](namespacequite.md)


















## Namespaces

| Type | Name |
| ---: | :--- |
| namespace | [**client**](namespacequite_1_1client.md) <br> |
| namespace | [**core**](namespacequite_1_1core.md) <br> |
| namespace | [**manager**](namespacequite_1_1manager.md) <br> |
| namespace | [**meta**](namespacequite_1_1meta.md) <br> |
| namespace | [**probe**](namespacequite_1_1probe.md) <br> |
| namespace | [**proto**](namespacequite_1_1proto.md) <br> |
| namespace | [**test**](namespacequite_1_1test.md) <br> |
| namespace | [**testing**](namespacequite_1_1testing.md) <br> |


## Classes

| Type | Name |
| ---: | :--- |
| class | [**Context**](classquite_1_1Context.md) <br> |
| struct | [**Error**](structquite_1_1Error.md) <br> |
| struct | [**GenericClass**](structquite_1_1GenericClass.md) <br> |
| struct | [**GrpcServer**](structquite_1_1GrpcServer.md) <br> |
| class | [**Image**](classquite_1_1Image.md) <br> |
| struct | [**ImageCompareResult**](structquite_1_1ImageCompareResult.md) <br> |
| struct | [**ImageView**](structquite_1_1ImageView.md) <br> |
| struct | [**ObjectMeta**](structquite_1_1ObjectMeta.md) <br> |
| struct | [**ObjectQuery**](structquite_1_1ObjectQuery.md) <br> |
| class | [**ObjectQueryBuilder**](classquite_1_1ObjectQueryBuilder.md) <br> |
| struct | [**ObjectReference**](structquite_1_1ObjectReference.md) <br> |
| struct | [**PixelCompareOptions**](structquite_1_1PixelCompareOptions.md) <br> |
| class | [**QObjectOperationState**](classquite_1_1QObjectOperationState.md) &lt;class Recv, class QObj, class Ret, Args&gt;<br> |
| class | [**QObjectSender**](classquite_1_1QObjectSender.md) &lt;class QObj, class Ret, Args&gt;<br> |
| class | [**QThreadOperationState**](classquite_1_1QThreadOperationState.md) &lt;class Recv&gt;<br> |
| class | [**QThreadScheduler**](classquite_1_1QThreadScheduler.md) <br> |
| class | [**ServiceHandle**](classquite_1_1ServiceHandle.md) &lt;typename T&gt;<br>_A lightweight handle for accessing shared service instances._  |
| class | [**ValueRegistry**](classquite_1_1ValueRegistry.md) <br> |
| struct | [**Vector2**](structquite_1_1Vector2.md) <br> |


## Public Types

| Type | Name |
| ---: | :--- |
| typedef exec::task&lt; Result&lt; T &gt; &gt; | [**AsyncResult**](#typedef-asyncresult)  <br> |
| enum  | [**ErrorCode**](#enum-errorcode)  <br> |
| typedef std::uint64\_t | [**ObjectId**](#typedef-objectid)  <br> |
| typedef std::span&lt; std::byte &gt; | [**PixelData**](#typedef-pixeldata)  <br> |
| typedef std::expected&lt; T, [**Error**](structquite_1_1Error.md) &gt; | [**Result**](#typedef-result)  <br>_Alias for a result type that holds either a value of type T or an_ [_**Error**_](structquite_1_1Error.md) _._ |




## Public Attributes

| Type | Name |
| ---: | :--- |
|  class QUITE\_CORE\_EXPORT | [**ObjectQueryBuilder**](#variable-objectquerybuilder)  <br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|  entt::dense\_map&lt; std::string, entt::meta\_any &gt; | [**collect\_properties**](#function-collect_properties) ([**ObjectMeta**](structquite_1_1ObjectMeta.md) object\_meta, std::span&lt; const std::string &gt; property\_names) <br> |
|  QUITE\_CORE\_EXPORT quill::Logger \* | [**create\_logger**](#function-create_logger) (std::string\_view logger\_name) <br> |
|  QUITE\_CORE\_EXPORT auto | [**get\_executor**](#function-get_executor) () <br>_Returns the executor associated with the global ASIO thread pool._  |
|  constexpr auto | [**make\_error\_result**](#function-make_error_result) (const ErrorCode code, MessageT && message) <br>_Helper function to create an error result._  |
|  QUITE\_CORE\_EXPORT [**ObjectQueryBuilder**](classquite_1_1ObjectQueryBuilder.md) | [**make\_query**](#function-make_query) () <br> |
|  QUITE\_CORE\_EXPORT Result&lt; [**ImageCompareResult**](structquite_1_1ImageCompareResult.md) &gt; | [**pixel\_match**](#function-pixel_match) (const [**ImageView**](structquite_1_1ImageView.md) & expected\_img, const [**ImageView**](structquite_1_1ImageView.md) & actual\_img, const [**PixelCompareOptions**](structquite_1_1PixelCompareOptions.md) & options={}) <br> |
|  [**QObjectSender**](classquite_1_1QObjectSender.md)&lt; QObj, Ret, Args... &gt; | [**qobject\_as\_sender**](#function-qobject_as_sender) (QObj \* obj, Ret(QObj::\*)(Args...) ptr) <br> |
|  auto | [**qobject\_as\_tuple\_sender**](#function-qobject_as_tuple_sender) (QObj \* obj, Ret(QObj::\*)(Args...) ptr) <br> |
|  [**QThreadScheduler**](classquite_1_1QThreadScheduler.md) | [**qthread\_as\_scheduler**](#function-qthread_as_scheduler) (QThread \* thread) <br> |
|  [**QThreadScheduler**](classquite_1_1QThreadScheduler.md) | [**qthread\_as\_scheduler**](#function-qthread_as_scheduler) (QThread & thread) <br> |
|  std::pair&lt; std::string, entt::meta\_any &gt; | [**read\_property**](#function-read_property) (const QVariant property\_value, const QMetaProperty & property) <br> |
|  PROBE\_EXPORT void | [**setup\_hooks**](#function-setup_hooks) () <br> |
|  void | [**setup\_hooks**](#function-setup_hooks) ([**GrpcServer**](structquite_1_1GrpcServer.md) server\_config) <br> |
|  QUITE\_CORE\_EXPORT void | [**setup\_logger**](#function-setup_logger) (bool log\_to\_file=false) <br> |
|  QUITE\_CORE\_EXPORT execpools::asio\_thread\_pool & | [**thread\_pool**](#function-thread_pool) () <br>_Returns a reference to the global ASIO thread pool._  |
|  void | [**to\_json**](#function-to_json) (json & j, const [**GenericClass**](structquite_1_1GenericClass.md) & v) <br> |
|  Result&lt; void &gt; | [**write\_property**](#function-write_property) (const [**ObjectMeta**](structquite_1_1ObjectMeta.md) & meta, const std::string & property\_name, const entt::meta\_any & property\_value) <br> |




























## Public Types Documentation




### typedef AsyncResult 

```C++
using quite::AsyncResult = typedef exec::task<Result<T> >;
```




<hr>



### enum ErrorCode 

```C++
enum quite::ErrorCode {
    unknown,
    cancelled,
    invalid_argument,
    deadline_exceeded,
    not_found,
    failed_precondition,
    aborted,
    unimplemented,
    unavailable
};
```




<hr>



### typedef ObjectId 

```C++
using quite::ObjectId = typedef std::uint64_t;
```




<hr>



### typedef PixelData 

```C++
using quite::PixelData = typedef std::span<std::byte>;
```




<hr>



### typedef Result 

_Alias for a result type that holds either a value of type T or an_ [_**Error**_](structquite_1_1Error.md) _._
```C++
using quite::Result = typedef std::expected<T, Error>;
```



This is a convenience alias for std::expected&lt;T, Error&gt;, used to represent the result of an operation that may fail with a [**quite::Error**](structquite_1_1Error.md).




**Template parameters:**


* `T` The type of the expected value on success. 




        

<hr>
## Public Attributes Documentation




### variable ObjectQueryBuilder 

```C++
class QUITE_CORE_EXPORT quite::ObjectQueryBuilder;
```




<hr>
## Public Functions Documentation




### function collect\_properties 

```C++
entt::dense_map< std::string, entt::meta_any > quite::collect_properties (
    ObjectMeta object_meta,
    std::span< const std::string > property_names
) 
```




<hr>



### function create\_logger 

```C++
QUITE_CORE_EXPORT quill::Logger * quite::create_logger (
    std::string_view logger_name
) 
```




<hr>



### function get\_executor 

_Returns the executor associated with the global ASIO thread pool._ 
```C++
QUITE_CORE_EXPORT auto quite::get_executor () 
```



This executor can be used to schedule tasks on the global thread pool.




**Returns:**

The executor object from the global thread pool. 





        

<hr>



### function make\_error\_result 

_Helper function to create an error result._ 
```C++
template<typename MessageT>
constexpr auto quite::make_error_result (
    const ErrorCode code,
    MessageT && message
) 
```



Constructs a std::unexpected containing a [**quite::Error**](structquite_1_1Error.md) with the given code and message.




**Template parameters:**


* `MessageT` The type of the error message (deduced). 



**Parameters:**


* `code` The error code. 
* `message` The error message. 



**Returns:**

std::unexpected&lt;Error&gt; containing the error. 





        

<hr>



### function make\_query 

```C++
QUITE_CORE_EXPORT ObjectQueryBuilder quite::make_query () 
```




<hr>



### function pixel\_match 

```C++
QUITE_CORE_EXPORT Result< ImageCompareResult > quite::pixel_match (
    const ImageView & expected_img,
    const ImageView & actual_img,
    const PixelCompareOptions & options={}
) 
```




<hr>



### function qobject\_as\_sender 

```C++
template<class QObj, class Ret, class... Args>
inline QObjectSender < QObj, Ret, Args... > quite::qobject_as_sender (
    QObj * obj,
    Ret(QObj::*)(Args...) ptr
) 
```




<hr>



### function qobject\_as\_tuple\_sender 

```C++
template<class QObj, class Ret, class... Args>
inline auto quite::qobject_as_tuple_sender (
    QObj * obj,
    Ret(QObj::*)(Args...) ptr
) 
```




<hr>



### function qthread\_as\_scheduler 

```C++
inline QThreadScheduler quite::qthread_as_scheduler (
    QThread * thread
) 
```




<hr>



### function qthread\_as\_scheduler 

```C++
inline QThreadScheduler quite::qthread_as_scheduler (
    QThread & thread
) 
```




<hr>



### function read\_property 

```C++
std::pair< std::string, entt::meta_any > quite::read_property (
    const QVariant property_value,
    const QMetaProperty & property
) 
```




<hr>



### function setup\_hooks 

```C++
PROBE_EXPORT void quite::setup_hooks () 
```




<hr>



### function setup\_hooks 

```C++
void quite::setup_hooks (
    GrpcServer server_config
) 
```




<hr>



### function setup\_logger 

```C++
QUITE_CORE_EXPORT void quite::setup_logger (
    bool log_to_file=false
) 
```




<hr>



### function thread\_pool 

_Returns a reference to the global ASIO thread pool._ 
```C++
QUITE_CORE_EXPORT execpools::asio_thread_pool & quite::thread_pool () 
```



This thread pool is managed as a singleton and is used for all asynchronous operations that require an ASIO execution context within the quite framework.




**Returns:**

Reference to the global execpools::asio\_thread\_pool instance. 





        

<hr>



### function to\_json 

```C++
void quite::to_json (
    json & j,
    const GenericClass & v
) 
```




<hr>



### function write\_property 

```C++
Result< void > quite::write_property (
    const ObjectMeta & meta,
    const std::string & property_name,
    const entt::meta_any & property_value
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `libs/client/include/quite/client/probe.hpp`

