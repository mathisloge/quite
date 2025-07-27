

# Class quite::QObjectSender

**template &lt;class QObj, class Ret, class... Args&gt;**



[**ClassList**](annotated.md) **>** [**quite**](namespacequite.md) **>** [**QObjectSender**](classquite_1_1QObjectSender.md)






















## Public Types

| Type | Name |
| ---: | :--- |
| typedef Ret(QObj::\*)(Args...) | [**MemberPointer**](#typedef-memberpointer)  <br> |
| typedef stdexec::completion\_signatures&lt; stdexec::set\_value\_t(Args...), stdexec::set\_error\_t(std::exception\_ptr), stdexec::set\_stopped\_t()&gt; | [**completion\_signatures**](#typedef-completion_signatures)  <br> |
| typedef void | [**is\_sender**](#typedef-is_sender)  <br> |




















## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**QObjectSender**](#function-qobjectsender) (QObj \* obj, MemberPointer ptr) <br> |
|  [**QObjectOperationState**](classquite_1_1QObjectOperationState.md)&lt; Recv, QObj, Ret, Args... &gt; | [**connect**](#function-connect) (Recv && receiver) <br> |
|  MemberPointer | [**member\_ptr**](#function-member_ptr) () <br> |
|  QObj \* | [**object**](#function-object) () <br> |




























## Public Types Documentation




### typedef MemberPointer 

```C++
using quite::QObjectSender< QObj, Ret, Args >::MemberPointer =  Ret (QObj::*)(Args...);
```




<hr>



### typedef completion\_signatures 

```C++
using quite::QObjectSender< QObj, Ret, Args >::completion_signatures =  stdexec::completion_signatures<stdexec::set_value_t(Args...), stdexec::set_error_t(std::exception_ptr), stdexec::set_stopped_t()>;
```




<hr>



### typedef is\_sender 

```C++
using quite::QObjectSender< QObj, Ret, Args >::is_sender =  void;
```




<hr>
## Public Functions Documentation




### function QObjectSender 

```C++
inline quite::QObjectSender::QObjectSender (
    QObj * obj,
    MemberPointer ptr
) 
```




<hr>



### function connect 

```C++
template<class Recv>
inline QObjectOperationState < Recv, QObj, Ret, Args... > quite::QObjectSender::connect (
    Recv && receiver
) 
```




<hr>



### function member\_ptr 

```C++
inline MemberPointer quite::QObjectSender::member_ptr () 
```




<hr>



### function object 

```C++
inline QObj * quite::QObjectSender::object () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `libs/probeqt/qtstdexec.h`

