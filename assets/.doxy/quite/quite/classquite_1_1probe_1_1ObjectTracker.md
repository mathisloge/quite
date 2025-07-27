

# Class quite::probe::ObjectTracker



[**ClassList**](annotated.md) **>** [**quite**](namespacequite.md) **>** [**probe**](namespacequite_1_1probe.md) **>** [**ObjectTracker**](classquite_1_1probe_1_1ObjectTracker.md)








Inherits the following classes: QObject


































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**ObjectTracker**](#function-objecttracker) () <br> |
|  void | [**add\_object**](#function-add_object) (QObject \* obj) <br> |
|  Result&lt; [**ObjectReference**](structquite_1_1ObjectReference.md) &gt; | [**find\_object**](#function-find_object) (const std::string & object\_name) const<br> |
|  Result&lt; [**ObjectReference**](structquite_1_1ObjectReference.md) &gt; | [**find\_object\_by\_query**](#function-find_object_by_query) (const [**ObjectQuery**](structquite_1_1ObjectQuery.md) & query) const<br> |
|  Result&lt; QObject \* &gt; | [**get\_object\_by\_id**](#function-get_object_by_id) (ObjectId obj\_id) const<br> |
|  void | [**remove\_object**](#function-remove_object) (QObject \* obj) <br> |
|  const std::unordered\_set&lt; QObject \* &gt; & | [**top\_level\_views**](#function-top_level_views) () const<br> |
|   | [**~ObjectTracker**](#function-objecttracker) () override<br> |




























## Public Functions Documentation




### function ObjectTracker 

```C++
quite::probe::ObjectTracker::ObjectTracker () 
```




<hr>



### function add\_object 

```C++
void quite::probe::ObjectTracker::add_object (
    QObject * obj
) 
```




<hr>



### function find\_object 

```C++
Result< ObjectReference > quite::probe::ObjectTracker::find_object (
    const std::string & object_name
) const
```




<hr>



### function find\_object\_by\_query 

```C++
Result< ObjectReference > quite::probe::ObjectTracker::find_object_by_query (
    const ObjectQuery & query
) const
```




<hr>



### function get\_object\_by\_id 

```C++
Result< QObject * > quite::probe::ObjectTracker::get_object_by_id (
    ObjectId obj_id
) const
```




<hr>



### function remove\_object 

```C++
void quite::probe::ObjectTracker::remove_object (
    QObject * obj
) 
```




<hr>



### function top\_level\_views 

```C++
const std::unordered_set< QObject * > & quite::probe::ObjectTracker::top_level_views () const
```




<hr>



### function ~ObjectTracker 

```C++
quite::probe::ObjectTracker::~ObjectTracker () override
```




<hr>

------------------------------
The documentation for this class was generated from the following file `libs/probeqt/object_tracker.hpp`

