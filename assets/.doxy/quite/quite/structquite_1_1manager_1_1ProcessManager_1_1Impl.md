

# Struct quite::manager::ProcessManager::Impl



[**ClassList**](annotated.md) **>** [**quite**](namespacequite.md) **>** [**manager**](namespacequite_1_1manager.md) **>** [**ProcessManager**](classquite_1_1manager_1_1ProcessManager.md) **>** [**Impl**](structquite_1_1manager_1_1ProcessManager_1_1Impl.md)


























## Public Attributes

| Type | Name |
| ---: | :--- |
|  std::unordered\_map&lt; std::string, std::shared\_ptr&lt; [**Process**](classquite_1_1manager_1_1Process.md) &gt; &gt; | [**applications\_**](#variable-applications_)  <br> |
|  quite::asio\_impl::any\_io\_executor | [**executor\_**](#variable-executor_)  <br> |












































## Public Attributes Documentation




### variable applications\_ 

```C++
std::unordered_map<std::string, std::shared_ptr<Process> > quite::manager::ProcessManager::Impl::applications_;
```




<hr>



### variable executor\_ 

```C++
quite::asio_impl::any_io_executor quite::manager::ProcessManager::Impl::executor_;
```




<hr>

------------------------------
The documentation for this class was generated from the following file `libs/manager/src/process_manager.cpp`

