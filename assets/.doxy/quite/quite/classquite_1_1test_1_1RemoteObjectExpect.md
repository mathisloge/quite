

# Class quite::test::RemoteObjectExpect



[**ClassList**](annotated.md) **>** [**quite**](namespacequite.md) **>** [**test**](namespacequite_1_1test.md) **>** [**RemoteObjectExpect**](classquite_1_1test_1_1RemoteObjectExpect.md)








Inherits the following classes: [quite::test::IExpectBuilder](structquite_1_1test_1_1IExpectBuilder.md)






















































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**RemoteObjectExpect**](#function-remoteobjectexpect) ([**RemoteObject**](classquite_1_1test_1_1RemoteObject.md) remote\_object) <br> |
| virtual bool | [**to\_have\_screenshot**](#function-to_have_screenshot) (const std::string & name) override<br> |


## Public Functions inherited from quite::test::IExpectBuilder

See [quite::test::IExpectBuilder](structquite_1_1test_1_1IExpectBuilder.md)

| Type | Name |
| ---: | :--- |
| virtual bool | [**to\_have\_screenshot**](structquite_1_1test_1_1IExpectBuilder.md#function-to_have_screenshot) (const std::string & name) = 0<br> |
| virtual  | [**~IExpectBuilder**](structquite_1_1test_1_1IExpectBuilder.md#function-iexpectbuilder) () = default<br> |






















































## Public Functions Documentation




### function RemoteObjectExpect 

```C++
inline quite::test::RemoteObjectExpect::RemoteObjectExpect (
    RemoteObject remote_object
) 
```




<hr>



### function to\_have\_screenshot 

```C++
inline virtual bool quite::test::RemoteObjectExpect::to_have_screenshot (
    const std::string & name
) override
```



Implements [*quite::test::IExpectBuilder::to\_have\_screenshot*](structquite_1_1test_1_1IExpectBuilder.md#function-to_have_screenshot)


<hr>

------------------------------
The documentation for this class was generated from the following file `libs/testing/src/expect.cpp`

