

# Class quite::test::Property



[**ClassList**](annotated.md) **>** [**quite**](namespacequite.md) **>** [**test**](namespacequite_1_1test.md) **>** [**Property**](classquite_1_1test_1_1Property.md)






















## Public Types

| Type | Name |
| ---: | :--- |
| typedef std::variant&lt; bool, std::uint64\_t, std::int64\_t, double, std::string, [**RemoteObject**](classquite_1_1test_1_1RemoteObject.md) &gt; | [**Value**](#typedef-value)  <br> |




















## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**Property**](#function-property) (std::shared\_ptr&lt; [**client::Property**](classquite_1_1client_1_1Property.md) &gt; property) <br> |
|  Property::Value | [**fetch**](#function-fetch) () <br> |
|  Property::Value | [**value**](#function-value) () const<br> |
|  Property::Value | [**wait\_for\_value**](#function-wait_for_value) (Property::Value target\_value, std::chrono::milliseconds timeout) <br>_Waits until the given target value has been reached or the time has been passed. Returns either the target value or the last fetched value after a timeout._  |
|  void | [**write**](#function-write) (Property::Value value) <br> |




























## Public Types Documentation




### typedef Value 

```C++
using quite::test::Property::Value =  std::variant<bool, std::uint64_t, std::int64_t, double, std::string, RemoteObject>;
```




<hr>
## Public Functions Documentation




### function Property 

```C++
explicit quite::test::Property::Property (
    std::shared_ptr< client::Property > property
) 
```




<hr>



### function fetch 

```C++
Property::Value quite::test::Property::fetch () 
```




<hr>



### function value 

```C++
Property::Value quite::test::Property::value () const
```




<hr>



### function wait\_for\_value 

_Waits until the given target value has been reached or the time has been passed. Returns either the target value or the last fetched value after a timeout._ 
```C++
Property::Value quite::test::Property::wait_for_value (
    Property::Value target_value,
    std::chrono::milliseconds timeout
) 
```





**Parameters:**


* `target_value` the desired value 
* `timeout` max time to wait 



**Returns:**

Property::Value either the target value or the last fetched value after a timeout 





        

<hr>



### function write 

```C++
void quite::test::Property::write (
    Property::Value value
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `libs/testing/include/quite/test/property.hpp`

