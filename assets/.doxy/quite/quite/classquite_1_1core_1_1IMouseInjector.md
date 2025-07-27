

# Class quite::core::IMouseInjector



[**ClassList**](annotated.md) **>** [**quite**](namespacequite.md) **>** [**core**](namespacequite_1_1core.md) **>** [**IMouseInjector**](classquite_1_1core_1_1IMouseInjector.md)










Inherited by the following classes: [quite::probe::MouseInjector](classquite_1_1probe_1_1MouseInjector.md),  [quite::proto::MouseInjectorImpl](classquite_1_1proto_1_1MouseInjectorImpl.md)
































## Public Functions

| Type | Name |
| ---: | :--- |
| virtual AsyncResult&lt; void &gt; | [**single\_action**](#function-single_action) (ObjectId target\_id, [**MouseAction**](structquite_1_1core_1_1MouseAction.md) action) = 0<br> |
| virtual  | [**~IMouseInjector**](#function-imouseinjector) () = default<br> |




























## Public Functions Documentation




### function single\_action 

```C++
virtual AsyncResult< void > quite::core::IMouseInjector::single_action (
    ObjectId target_id,
    MouseAction action
) = 0
```




<hr>



### function ~IMouseInjector 

```C++
virtual quite::core::IMouseInjector::~IMouseInjector () = default
```




<hr>

------------------------------
The documentation for this class was generated from the following file `libs/core/include/quite/injectors/mouse_injector.hpp`

