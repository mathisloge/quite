

# Class quite::probe::MouseInjector



[**ClassList**](annotated.md) **>** [**quite**](namespacequite.md) **>** [**probe**](namespacequite_1_1probe.md) **>** [**MouseInjector**](classquite_1_1probe_1_1MouseInjector.md)








Inherits the following classes: [quite::core::IMouseInjector](classquite_1_1core_1_1IMouseInjector.md)






















































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**MouseInjector**](#function-mouseinjector) (const [**ObjectTracker**](classquite_1_1probe_1_1ObjectTracker.md) & object\_tracker) <br> |
| virtual AsyncResult&lt; void &gt; | [**single\_action**](#function-single_action) (ObjectId target\_id, [**core::MouseAction**](structquite_1_1core_1_1MouseAction.md) action) override<br> |
|   | [**~MouseInjector**](#function-mouseinjector) () override<br> |


## Public Functions inherited from quite::core::IMouseInjector

See [quite::core::IMouseInjector](classquite_1_1core_1_1IMouseInjector.md)

| Type | Name |
| ---: | :--- |
| virtual AsyncResult&lt; void &gt; | [**single\_action**](classquite_1_1core_1_1IMouseInjector.md#function-single_action) (ObjectId target\_id, [**MouseAction**](structquite_1_1core_1_1MouseAction.md) action) = 0<br> |
| virtual  | [**~IMouseInjector**](classquite_1_1core_1_1IMouseInjector.md#function-imouseinjector) () = default<br> |






















































## Public Functions Documentation




### function MouseInjector 

```C++
explicit quite::probe::MouseInjector::MouseInjector (
    const ObjectTracker & object_tracker
) 
```




<hr>



### function single\_action 

```C++
virtual AsyncResult< void > quite::probe::MouseInjector::single_action (
    ObjectId target_id,
    core::MouseAction action
) override
```



Implements [*quite::core::IMouseInjector::single\_action*](classquite_1_1core_1_1IMouseInjector.md#function-single_action)


<hr>



### function ~MouseInjector 

```C++
quite::probe::MouseInjector::~MouseInjector () override
```




<hr>

------------------------------
The documentation for this class was generated from the following file `libs/probeqt/injector/mouse_injector.hpp`

