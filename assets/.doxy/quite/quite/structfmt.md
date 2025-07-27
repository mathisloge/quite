

# Struct fmt

**template &lt;&gt;**



[**ClassList**](annotated.md) **>** [**fmt**](structfmt.md)








Inherits the following classes: formatter< quite::ErrorCode > fmt::formatter,  formatter< quite::Error > fmt::formatter,  formatter< quite::meta::Property > fmt::formatter,  formatter< quite::meta::Method > fmt::formatter,  formatter< quite::meta::ObjectType > fmt::formatter,  formatter< quite::meta::MapType > fmt::formatter,  formatter< quite::meta::ListType > fmt::formatter,  formatter< quite::meta::EnumType > fmt::formatter,  formatter< quite::meta::PrimitiveType > fmt::formatter,  formatter< quite::meta::Type > fmt::formatter,  formatter< quite::ObjectQuery > fmt::formatter












## Classes

| Type | Name |
| ---: | :--- |
| struct | [**formatter&lt; entt::meta\_any &gt;**](structfmt_1_1formatter_3_01entt_1_1meta__any_01_4.md) &lt;&gt;<br> |






















## Public Functions

| Type | Name |
| ---: | :--- |
|  auto | [**format**](#function-format-111) (quite::ErrorCode error\_code, format\_context & ctx) const<br> |
|  auto | [**format**](#function-format-211) (const [**quite::Error**](structquite_1_1Error.md) & error, format\_context & ctx) const<br> |
|  auto | [**format**](#function-format-311) (const [**quite::meta::Property**](structquite_1_1meta_1_1Property.md) & type, format\_context & ctx) const<br> |
|  auto | [**format**](#function-format-411) (const [**quite::meta::Method**](structquite_1_1meta_1_1Method.md) & type, format\_context & ctx) const<br> |
|  auto | [**format**](#function-format-511) (const [**quite::meta::ObjectType**](structquite_1_1meta_1_1ObjectType.md) & type, format\_context & ctx) const<br> |
|  auto | [**format**](#function-format-611) (const [**quite::meta::MapType**](structquite_1_1meta_1_1MapType.md) & type, format\_context & ctx) const<br> |
|  auto | [**format**](#function-format-711) (const [**quite::meta::ListType**](structquite_1_1meta_1_1ListType.md) & type, format\_context & ctx) const<br> |
|  auto | [**format**](#function-format-811) (const [**quite::meta::EnumType**](structquite_1_1meta_1_1EnumType.md) & type, format\_context & ctx) const<br> |
|  auto | [**format**](#function-format-911) (const quite::meta::PrimitiveType & type, format\_context & ctx) const<br> |
|  auto | [**format**](#function-format-1011) (const quite::meta::Type & type, format\_context & ctx) const<br> |
|  auto | [**format**](#function-format-1111) (const [**quite::ObjectQuery**](structquite_1_1ObjectQuery.md) & query, format\_context & ctx) const<br> |




























## Public Functions Documentation




### function format [1/11]

```C++
auto fmt::format (
    quite::ErrorCode error_code,
    format_context & ctx
) const
```




<hr>



### function format [2/11]

```C++
auto fmt::format (
    const quite::Error & error,
    format_context & ctx
) const
```




<hr>



### function format [3/11]

```C++
auto fmt::format (
    const quite::meta::Property & type,
    format_context & ctx
) const
```




<hr>



### function format [4/11]

```C++
auto fmt::format (
    const quite::meta::Method & type,
    format_context & ctx
) const
```




<hr>



### function format [5/11]

```C++
auto fmt::format (
    const quite::meta::ObjectType & type,
    format_context & ctx
) const
```




<hr>



### function format [6/11]

```C++
auto fmt::format (
    const quite::meta::MapType & type,
    format_context & ctx
) const
```




<hr>



### function format [7/11]

```C++
auto fmt::format (
    const quite::meta::ListType & type,
    format_context & ctx
) const
```




<hr>



### function format [8/11]

```C++
auto fmt::format (
    const quite::meta::EnumType & type,
    format_context & ctx
) const
```




<hr>



### function format [9/11]

```C++
auto fmt::format (
    const quite::meta::PrimitiveType & type,
    format_context & ctx
) const
```




<hr>



### function format [10/11]

```C++
auto fmt::format (
    const quite::meta::Type & type,
    format_context & ctx
) const
```




<hr>



### function format [11/11]

```C++
auto fmt::format (
    const quite::ObjectQuery & query,
    format_context & ctx
) const
```




<hr>

------------------------------
The documentation for this class was generated from the following file `libs/core/include/quite/error.hpp`

