

# Class quite::manager::ProcessImpl



[**ClassList**](annotated.md) **>** [**quite**](namespacequite.md) **>** [**manager**](namespacequite_1_1manager.md) **>** [**ProcessImpl**](classquite_1_1manager_1_1ProcessImpl.md)








Inherits the following classes: [quite::manager::Process](classquite_1_1manager_1_1Process.md)






















































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**ProcessImpl**](#function-processimpl) (boost::process::v2::process && process) <br> |
| virtual AsyncResult&lt; int &gt; | [**async\_wait\_exit**](#function-async_wait_exit) () override<br> |
| virtual int | [**exit\_code**](#function-exit_code) () override<br> |
| virtual bool | [**is\_running**](#function-is_running) () override<br> |
| virtual Result&lt; void &gt; | [**request\_exit**](#function-request_exit) () override<br> |
| virtual Result&lt; void &gt; | [**terminate**](#function-terminate) () override<br> |


## Public Functions inherited from quite::manager::Process

See [quite::manager::Process](classquite_1_1manager_1_1Process.md)

| Type | Name |
| ---: | :--- |
| virtual AsyncResult&lt; int &gt; | [**async\_wait\_exit**](classquite_1_1manager_1_1Process.md#function-async_wait_exit) () = 0<br> |
| virtual int | [**exit\_code**](classquite_1_1manager_1_1Process.md#function-exit_code) () = 0<br> |
| virtual bool | [**is\_running**](classquite_1_1manager_1_1Process.md#function-is_running) () = 0<br> |
| virtual Result&lt; void &gt; | [**request\_exit**](classquite_1_1manager_1_1Process.md#function-request_exit) () = 0<br> |
| virtual Result&lt; void &gt; | [**terminate**](classquite_1_1manager_1_1Process.md#function-terminate) () = 0<br> |
| virtual  | [**~Process**](classquite_1_1manager_1_1Process.md#function-process) () = default<br> |






















































## Public Functions Documentation




### function ProcessImpl 

```C++
explicit quite::manager::ProcessImpl::ProcessImpl (
    boost::process::v2::process && process
) 
```




<hr>



### function async\_wait\_exit 

```C++
virtual AsyncResult< int > quite::manager::ProcessImpl::async_wait_exit () override
```



Implements [*quite::manager::Process::async\_wait\_exit*](classquite_1_1manager_1_1Process.md#function-async_wait_exit)


<hr>



### function exit\_code 

```C++
virtual int quite::manager::ProcessImpl::exit_code () override
```



Implements [*quite::manager::Process::exit\_code*](classquite_1_1manager_1_1Process.md#function-exit_code)


<hr>



### function is\_running 

```C++
virtual bool quite::manager::ProcessImpl::is_running () override
```



Implements [*quite::manager::Process::is\_running*](classquite_1_1manager_1_1Process.md#function-is_running)


<hr>



### function request\_exit 

```C++
virtual Result< void > quite::manager::ProcessImpl::request_exit () override
```



Implements [*quite::manager::Process::request\_exit*](classquite_1_1manager_1_1Process.md#function-request_exit)


<hr>



### function terminate 

```C++
virtual Result< void > quite::manager::ProcessImpl::terminate () override
```



Implements [*quite::manager::Process::terminate*](classquite_1_1manager_1_1Process.md#function-terminate)


<hr>

------------------------------
The documentation for this class was generated from the following file `libs/manager/src/process_impl.hpp`

