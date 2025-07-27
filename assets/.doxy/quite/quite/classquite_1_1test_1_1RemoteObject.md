

# Class quite::test::RemoteObject



[**ClassList**](annotated.md) **>** [**quite**](namespacequite.md) **>** [**test**](namespacequite_1_1test.md) **>** [**RemoteObject**](classquite_1_1test_1_1RemoteObject.md)










































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**RemoteObject**](#function-remoteobject) (std::shared\_ptr&lt; [**client::RemoteObject**](classquite_1_1client_1_1RemoteObject.md) &gt; object) <br> |
|  void | [**invoke\_method**](#function-invoke_method) (std::string method\_name) <br> |
|  void | [**mouse\_action**](#function-mouse_action) () <br> |
|  bool | [**operator==**](#function-operator) (const [**RemoteObject**](classquite_1_1test_1_1RemoteObject.md) & rhs) const<br> |
|  [**Property**](classquite_1_1test_1_1Property.md) | [**property**](#function-property) (std::string name) <br> |
|  [**Image**](classquite_1_1Image.md) | [**take\_snapshot**](#function-take_snapshot) () <br> |
|  std::shared\_ptr&lt; [**client::RemoteObject**](classquite_1_1client_1_1RemoteObject.md) &gt; | [**underlying\_object**](#function-underlying_object) () <br> |




























## Public Functions Documentation




### function RemoteObject 

```C++
explicit quite::test::RemoteObject::RemoteObject (
    std::shared_ptr< client::RemoteObject > object
) 
```




<hr>



### function invoke\_method 

```C++
void quite::test::RemoteObject::invoke_method (
    std::string method_name
) 
```




<hr>



### function mouse\_action 

```C++
void quite::test::RemoteObject::mouse_action () 
```




<hr>



### function operator== 

```C++
bool quite::test::RemoteObject::operator== (
    const RemoteObject & rhs
) const
```




<hr>



### function property 

```C++
Property quite::test::RemoteObject::property (
    std::string name
) 
```




<hr>



### function take\_snapshot 

```C++
Image quite::test::RemoteObject::take_snapshot () 
```




<hr>



### function underlying\_object 

```C++
std::shared_ptr< client::RemoteObject > quite::test::RemoteObject::underlying_object () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `libs/testing/include/quite/test/remote_object.hpp`

