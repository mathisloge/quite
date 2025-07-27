

# Class quite::QThreadOperationState

**template &lt;class Recv&gt;**



[**ClassList**](annotated.md) **>** [**quite**](namespacequite.md) **>** [**QThreadOperationState**](classquite_1_1QThreadOperationState.md)






















## Public Types

| Type | Name |
| ---: | :--- |
| typedef stdexec::operation\_state\_t | [**operation\_state\_concept**](#typedef-operation_state_concept)  <br> |




















## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**QThreadOperationState**](#function-qthreadoperationstate) (Recv && receiver, QThread \* thread) <br> |
|   | [**Q\_DISABLE\_COPY\_MOVE**](#function-q_disable_copy_move) ([**QThreadOperationState**](classquite_1_1QThreadOperationState.md)) <br> |
|  void | [**start**](#function-start) () noexcept<br> |
|   | [**~QThreadOperationState**](#function-qthreadoperationstate) () = default<br> |




























## Public Types Documentation




### typedef operation\_state\_concept 

```C++
using quite::QThreadOperationState< Recv >::operation_state_concept =  stdexec::operation_state_t;
```




<hr>
## Public Functions Documentation




### function QThreadOperationState 

```C++
inline quite::QThreadOperationState::QThreadOperationState (
    Recv && receiver,
    QThread * thread
) 
```




<hr>



### function Q\_DISABLE\_COPY\_MOVE 

```C++
quite::QThreadOperationState::Q_DISABLE_COPY_MOVE (
    QThreadOperationState
) 
```




<hr>



### function start 

```C++
inline void quite::QThreadOperationState::start () noexcept
```




<hr>



### function ~QThreadOperationState 

```C++
quite::QThreadOperationState::~QThreadOperationState () = default
```




<hr>

------------------------------
The documentation for this class was generated from the following file `libs/probeqt/qtstdexec.h`

