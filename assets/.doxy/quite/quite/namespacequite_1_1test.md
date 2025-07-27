

# Namespace quite::test



[**Namespace List**](namespaces.md) **>** [**quite**](namespacequite.md) **>** [**test**](namespacequite_1_1test.md)




















## Classes

| Type | Name |
| ---: | :--- |
| struct | [**IExpectBuilder**](structquite_1_1test_1_1IExpectBuilder.md) <br> |
| class | [**Probe**](classquite_1_1test_1_1Probe.md) <br> |
| class | [**ProbeManager**](classquite_1_1test_1_1ProbeManager.md) <br> |
| class | [**Property**](classquite_1_1test_1_1Property.md) <br> |
| class | [**RemoteException**](classquite_1_1test_1_1RemoteException.md) <br> |
| class | [**RemoteObject**](classquite_1_1test_1_1RemoteObject.md) <br> |
| class | [**RemoteObjectExpect**](classquite_1_1test_1_1RemoteObjectExpect.md) <br> |






















## Public Functions

| Type | Name |
| ---: | :--- |
|  void | [**create\_screenshot\_expect**](#function-create_screenshot_expect) ([**RemoteObject**](classquite_1_1test_1_1RemoteObject.md) obj, const std::string & name) <br> |
|  QUITE\_TEST\_EXPORT std::unique\_ptr&lt; [**IExpectBuilder**](structquite_1_1test_1_1IExpectBuilder.md) &gt; | [**expect**](#function-expect) ([**RemoteObject**](classquite_1_1test_1_1RemoteObject.md) remote\_object) <br> |
|  bool | [**has\_screenshot\_expect**](#function-has_screenshot_expect) (const std::string & name) <br> |
|  constexpr void | [**throw\_unexpected**](#function-throw_unexpected) (const Result&lt; T &gt; & result) <br> |
|  bool | [**verify\_screenshot\_expect**](#function-verify_screenshot_expect) ([**RemoteObject**](classquite_1_1test_1_1RemoteObject.md) obj, const std::string & name) <br> |




























## Public Functions Documentation




### function create\_screenshot\_expect 

```C++
void quite::test::create_screenshot_expect (
    RemoteObject obj,
    const std::string & name
) 
```




<hr>



### function expect 

```C++
QUITE_TEST_EXPORT std::unique_ptr< IExpectBuilder > quite::test::expect (
    RemoteObject remote_object
) 
```




<hr>



### function has\_screenshot\_expect 

```C++
bool quite::test::has_screenshot_expect (
    const std::string & name
) 
```




<hr>



### function throw\_unexpected 

```C++
template<typename T>
constexpr void quite::test::throw_unexpected (
    const Result< T > & result
) 
```




<hr>



### function verify\_screenshot\_expect 

```C++
bool quite::test::verify_screenshot_expect (
    RemoteObject obj,
    const std::string & name
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `libs/testing/include/quite/test/exceptions.hpp`

