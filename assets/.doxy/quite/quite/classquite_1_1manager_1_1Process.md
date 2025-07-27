

# Class quite::manager::Process



[**ClassList**](annotated.md) **>** [**quite**](namespacequite.md) **>** [**manager**](namespacequite_1_1manager.md) **>** [**Process**](classquite_1_1manager_1_1Process.md)










Inherited by the following classes: [quite::manager::NoopProcess](classquite_1_1manager_1_1NoopProcess.md),  [quite::manager::ProcessImpl](classquite_1_1manager_1_1ProcessImpl.md)
































## Public Functions

| Type | Name |
| ---: | :--- |
| virtual AsyncResult&lt; int &gt; | [**async\_wait\_exit**](#function-async_wait_exit) () = 0<br> |
| virtual int | [**exit\_code**](#function-exit_code) () = 0<br> |
| virtual bool | [**is\_running**](#function-is_running) () = 0<br> |
| virtual Result&lt; void &gt; | [**request\_exit**](#function-request_exit) () = 0<br> |
| virtual Result&lt; void &gt; | [**terminate**](#function-terminate) () = 0<br> |
| virtual  | [**~Process**](#function-process) () = default<br> |




























## Public Functions Documentation




### function async\_wait\_exit 

```C++
virtual AsyncResult< int > quite::manager::Process::async_wait_exit () = 0
```




<hr>



### function exit\_code 

```C++
virtual int quite::manager::Process::exit_code () = 0
```




<hr>



### function is\_running 

```C++
virtual bool quite::manager::Process::is_running () = 0
```




<hr>



### function request\_exit 

```C++
virtual Result< void > quite::manager::Process::request_exit () = 0
```




<hr>



### function terminate 

```C++
virtual Result< void > quite::manager::Process::terminate () = 0
```




<hr>



### function ~Process 

```C++
virtual quite::manager::Process::~Process () = default
```




<hr>

------------------------------
The documentation for this class was generated from the following file `libs/manager/include/quite/manager/process.hpp`

