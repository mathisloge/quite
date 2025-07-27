

# Class quite::QThreadScheduler



[**ClassList**](annotated.md) **>** [**quite**](namespacequite.md) **>** [**QThreadScheduler**](classquite_1_1QThreadScheduler.md)




















## Classes

| Type | Name |
| ---: | :--- |
| struct | [**DefaultEnv**](structquite_1_1QThreadScheduler_1_1DefaultEnv.md) <br> |
| class | [**QThreadSender**](classquite_1_1QThreadScheduler_1_1QThreadSender.md) <br> |






















## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**QThreadScheduler**](#function-qthreadscheduler) (QThread \* thread) <br> |
|  bool | [**operator==**](#function-operator) (const [**QThreadScheduler**](classquite_1_1QThreadScheduler.md) & b) noexcept const<br> |
|  [**DefaultEnv**](structquite_1_1QThreadScheduler_1_1DefaultEnv.md) | [**query**](#function-query) (stdexec::get\_env\_t) noexcept<br> |
|  auto | [**schedule**](#function-schedule) () noexcept const<br> |
|  QThread \* | [**thread**](#function-thread) () <br> |




























## Public Functions Documentation




### function QThreadScheduler 

```C++
inline explicit quite::QThreadScheduler::QThreadScheduler (
    QThread * thread
) 
```




<hr>



### function operator== 

```C++
bool quite::QThreadScheduler::operator== (
    const QThreadScheduler & b
) noexcept const
```




<hr>



### function query 

```C++
inline DefaultEnv quite::QThreadScheduler::query (
    stdexec::get_env_t
) noexcept
```




<hr>



### function schedule 

```C++
inline auto quite::QThreadScheduler::schedule () noexcept const
```




<hr>



### function thread 

```C++
inline QThread * quite::QThreadScheduler::thread () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `libs/probeqt/qtstdexec.h`

