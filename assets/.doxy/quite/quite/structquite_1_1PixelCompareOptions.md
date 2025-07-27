

# Struct quite::PixelCompareOptions



[**ClassList**](annotated.md) **>** [**quite**](namespacequite.md) **>** [**PixelCompareOptions**](structquite_1_1PixelCompareOptions.md)


























## Public Attributes

| Type | Name |
| ---: | :--- |
|  float | [**alpha**](#variable-alpha)   = `{0.1}`<br> |
|  std::array&lt; uint8\_t, 3 &gt; | [**anti\_aliased\_color**](#variable-anti_aliased_color)   = `{255, 255, 0}`<br> |
|  std::array&lt; uint8\_t, 3 &gt; | [**diff\_color**](#variable-diff_color)   = `{255, 0, 0}`<br> |
|  std::optional&lt; std::array&lt; uint8\_t, 3 &gt; &gt; | [**diff\_color\_alt**](#variable-diff_color_alt)  <br> |
|  bool | [**diff\_mask**](#variable-diff_mask)   = `{false}`<br> |
|  bool | [**skip\_anti\_aliasing**](#variable-skip_anti_aliasing)   = `{false}`<br> |
|  float | [**threshold**](#variable-threshold)   = `{0.1}`<br> |












































## Public Attributes Documentation




### variable alpha 

```C++
float quite::PixelCompareOptions::alpha;
```




<hr>



### variable anti\_aliased\_color 

```C++
std::array<uint8_t, 3> quite::PixelCompareOptions::anti_aliased_color;
```




<hr>



### variable diff\_color 

```C++
std::array<uint8_t, 3> quite::PixelCompareOptions::diff_color;
```




<hr>



### variable diff\_color\_alt 

```C++
std::optional<std::array<uint8_t, 3> > quite::PixelCompareOptions::diff_color_alt;
```




<hr>



### variable diff\_mask 

```C++
bool quite::PixelCompareOptions::diff_mask;
```




<hr>



### variable skip\_anti\_aliasing 

```C++
bool quite::PixelCompareOptions::skip_anti_aliasing;
```




<hr>



### variable threshold 

```C++
float quite::PixelCompareOptions::threshold;
```




<hr>

------------------------------
The documentation for this class was generated from the following file `libs/core/include/quite/image_utils.hpp`

