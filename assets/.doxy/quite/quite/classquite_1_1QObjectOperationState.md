

# Class quite::QObjectOperationState

**template &lt;class Recv, class QObj, class Ret, class... Args&gt;**



[**ClassList**](annotated.md) **>** [**quite**](namespacequite.md) **>** [**QObjectOperationState**](classquite_1_1QObjectOperationState.md)






















## Public Types

| Type | Name |
| ---: | :--- |
| typedef Ret(QObj::\*)(Args...) | [**m\_ptr\_type**](#typedef-m_ptr_type)  <br> |
| typedef stdexec::operation\_state\_t | [**operation\_state\_concept**](#typedef-operation_state_concept)  <br> |




















## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**QObjectOperationState**](#function-qobjectoperationstate) (Recv && receiver, QObj \* obj, m\_ptr\_type ptr) <br> |
|  void | [**start**](#function-start) () noexcept<br> |




























## Public Types Documentation




### typedef m\_ptr\_type 

```C++
using quite::QObjectOperationState< Recv, QObj, Ret, Args >::m_ptr_type =  Ret (QObj::*)(Args...);
```




<hr>



### typedef operation\_state\_concept 

```C++
using quite::QObjectOperationState< Recv, QObj, Ret, Args >::operation_state_concept =  stdexec::operation_state_t;
```




<hr>
## Public Functions Documentation




### function QObjectOperationState 

```C++
inline quite::QObjectOperationState::QObjectOperationState (
    Recv && receiver,
    QObj * obj,
    m_ptr_type ptr
) 
```




<hr>



### function start 

```C++
inline void quite::QObjectOperationState::start () noexcept
```




<hr>

------------------------------
The documentation for this class was generated from the following file `libs/probeqt/qtstdexec.h`

