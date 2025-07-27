

# Class quite::Image::Impl



[**ClassList**](annotated.md) **>** [**quite**](namespacequite.md) **>** [**Image**](classquite_1_1Image.md) **>** [**Impl**](classquite_1_1Image_1_1Impl.md)


























## Public Attributes

| Type | Name |
| ---: | :--- |
|  int | [**channels\_**](#variable-channels_)  <br> |
|  std::uint32\_t | [**height\_**](#variable-height_)  <br> |
|  std::vector&lt; std::byte &gt; | [**image\_data\_**](#variable-image_data_)  <br> |
|  std::uint32\_t | [**width\_**](#variable-width_)  <br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**Impl**](#function-impl) (std::vector&lt; std::byte &gt; image\_data, std::uint32\_t width, std::uint32\_t height, int channels) <br> |
|   | [**~Impl**](#function-impl) () = default<br> |




























## Public Attributes Documentation




### variable channels\_ 

```C++
int quite::Image::Impl::channels_;
```




<hr>



### variable height\_ 

```C++
std::uint32_t quite::Image::Impl::height_;
```




<hr>



### variable image\_data\_ 

```C++
std::vector<std::byte> quite::Image::Impl::image_data_;
```




<hr>



### variable width\_ 

```C++
std::uint32_t quite::Image::Impl::width_;
```




<hr>
## Public Functions Documentation




### function Impl 

```C++
inline explicit quite::Image::Impl::Impl (
    std::vector< std::byte > image_data,
    std::uint32_t width,
    std::uint32_t height,
    int channels
) 
```




<hr>



### function ~Impl 

```C++
quite::Image::Impl::~Impl () = default
```




<hr>

------------------------------
The documentation for this class was generated from the following file `libs/core/src/image.cpp`

