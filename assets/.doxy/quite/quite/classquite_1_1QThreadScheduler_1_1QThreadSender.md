

# Class quite::QThreadScheduler::QThreadSender



[**ClassList**](annotated.md) **>** [**quite**](namespacequite.md) **>** [**QThreadScheduler**](classquite_1_1QThreadScheduler.md) **>** [**QThreadSender**](classquite_1_1QThreadScheduler_1_1QThreadSender.md)






















## Public Types

| Type | Name |
| ---: | :--- |
| typedef stdexec::completion\_signatures&lt; stdexec::set\_value\_t(), stdexec::set\_error\_t(std::exception\_ptr)&gt; | [**completion\_signatures**](#typedef-completion_signatures)  <br> |
| typedef void | [**is\_sender**](#typedef-is_sender)  <br> |




















## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**QThreadSender**](#function-qthreadsender) (QThread \* thread) <br> |
|  [**QThreadOperationState**](classquite_1_1QThreadOperationState.md)&lt; Recv &gt; | [**connect**](#function-connect) (Recv && receiver) <br> |
|  [**DefaultEnv**](structquite_1_1QThreadScheduler_1_1DefaultEnv.md) | [**query**](#function-query) (stdexec::get\_env\_t) noexcept const<br> |
|  QThread \* | [**thread**](#function-thread) () <br> |




























## Public Types Documentation




### typedef completion\_signatures 

```C++
using quite::QThreadScheduler::QThreadSender::completion_signatures =  stdexec::completion_signatures<stdexec::set_value_t(), stdexec::set_error_t(std::exception_ptr)>;
```




<hr>



### typedef is\_sender 

```C++
using quite::QThreadScheduler::QThreadSender::is_sender =  void;
```




<hr>
## Public Functions Documentation




### function QThreadSender 

```C++
inline explicit quite::QThreadScheduler::QThreadSender::QThreadSender (
    QThread * thread
) 
```




<hr>



### function connect 

```C++
template<class Recv>
inline QThreadOperationState < Recv > quite::QThreadScheduler::QThreadSender::connect (
    Recv && receiver
) 
```




<hr>



### function query 

```C++
inline DefaultEnv quite::QThreadScheduler::QThreadSender::query (
    stdexec::get_env_t
) noexcept const
```




<hr>



### function thread 

```C++
inline QThread * quite::QThreadScheduler::QThreadSender::thread () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `libs/probeqt/qtstdexec.h`

