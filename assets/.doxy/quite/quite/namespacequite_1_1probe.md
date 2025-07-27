

# Namespace quite::probe



[**Namespace List**](namespaces.md) **>** [**quite**](namespacequite.md) **>** [**probe**](namespacequite_1_1probe.md)




















## Classes

| Type | Name |
| ---: | :--- |
| class | [**MetaAdapter**](classquite_1_1probe_1_1MetaAdapter.md) <br> |
| class | [**MethodInvoker**](classquite_1_1probe_1_1MethodInvoker.md) <br> |
| class | [**MouseInjector**](classquite_1_1probe_1_1MouseInjector.md) <br> |
| class | [**ObjectTracker**](classquite_1_1probe_1_1ObjectTracker.md) <br> |
| class | [**ProbeContext**](classquite_1_1probe_1_1ProbeContext.md) <br> |
| class | [**QtMetaRegistry**](classquite_1_1probe_1_1QtMetaRegistry.md) <br> |
| class | [**QtProbeHandler**](classquite_1_1probe_1_1QtProbeHandler.md) <br> |






















## Public Functions

| Type | Name |
| ---: | :--- |
|  constexpr QObject \* | [**from\_object\_id**](#function-from_object_id) (ObjectId obj\_id) <br> |
|  void | [**register\_converters**](#function-register_converters) ([**ValueRegistry**](classquite_1_1ValueRegistry.md) & value\_registry) <br> |
|  AsyncResult&lt; QImage &gt; | [**take\_snapshot\_of\_qobject**](#function-take_snapshot_of_qobject) (QObject \* object) <br> |
|  constexpr ObjectId | [**to\_object\_id**](#function-to_object_id) (const QObject \* obj) <br> |
|  const QMetaObject \* | [**try\_get\_qt\_meta\_object**](#function-try_get_qt_meta_object) (const QObject \* object) <br> |
|  QMetaType | [**try\_get\_qt\_meta\_type**](#function-try_get_qt_meta_type) (const QMetaObject \* meta\_object) <br> |
|  QMetaType | [**try\_get\_qt\_meta\_type**](#function-try_get_qt_meta_type) (const QObject \* object) <br> |




























## Public Functions Documentation




### function from\_object\_id 

```C++
constexpr QObject * quite::probe::from_object_id (
    ObjectId obj_id
) 
```




<hr>



### function register\_converters 

```C++
void quite::probe::register_converters (
    ValueRegistry & value_registry
) 
```




<hr>



### function take\_snapshot\_of\_qobject 

```C++
AsyncResult< QImage > quite::probe::take_snapshot_of_qobject (
    QObject * object
) 
```




<hr>



### function to\_object\_id 

```C++
constexpr ObjectId quite::probe::to_object_id (
    const QObject * obj
) 
```




<hr>



### function try\_get\_qt\_meta\_object 

```C++
const QMetaObject * quite::probe::try_get_qt_meta_object (
    const QObject * object
) 
```




<hr>



### function try\_get\_qt\_meta\_type 

```C++
QMetaType quite::probe::try_get_qt_meta_type (
    const QMetaObject * meta_object
) 
```




<hr>



### function try\_get\_qt\_meta\_type 

```C++
QMetaType quite::probe::try_get_qt_meta_type (
    const QObject * object
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `libs/probeqt/injector/mouse_injector.cpp`

