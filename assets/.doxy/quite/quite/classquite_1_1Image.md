

# Class quite::Image



[**ClassList**](annotated.md) **>** [**quite**](namespacequite.md) **>** [**Image**](classquite_1_1Image.md)




















## Classes

| Type | Name |
| ---: | :--- |
| class | [**Impl**](classquite_1_1Image_1_1Impl.md) <br> |






















## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**Image**](#function-image-15) () <br> |
|   | [**Image**](#function-image-25) (std::vector&lt; std::byte &gt; image\_data, std::uint32\_t width, std::uint32\_t height, int channels) <br> |
|   | [**Image**](#function-image-35) (const std::filesystem::path & filename) <br> |
|   | [**Image**](#function-image-45) ([**Image**](classquite_1_1Image.md) && other) noexcept<br> |
|   | [**Image**](#function-image-55) (const [**Image**](classquite_1_1Image.md) & other) <br> |
|  [**ImageView**](structquite_1_1ImageView.md) | [**data**](#function-data) () const<br> |
|  [**Image**](classquite_1_1Image.md) & | [**operator=**](#function-operator) ([**Image**](classquite_1_1Image.md) && other) noexcept<br> |
|  [**Image**](classquite_1_1Image.md) & | [**operator=**](#function-operator_1) (const [**Image**](classquite_1_1Image.md) & other) <br> |
|  void | [**save\_to**](#function-save_to) (const std::filesystem::path & destination) const<br> |
| virtual  | [**~Image**](#function-image) () <br> |




























## Public Functions Documentation




### function Image [1/5]

```C++
quite::Image::Image () 
```




<hr>



### function Image [2/5]

```C++
explicit quite::Image::Image (
    std::vector< std::byte > image_data,
    std::uint32_t width,
    std::uint32_t height,
    int channels
) 
```




<hr>



### function Image [3/5]

```C++
explicit quite::Image::Image (
    const std::filesystem::path & filename
) 
```




<hr>



### function Image [4/5]

```C++
quite::Image::Image (
    Image && other
) noexcept
```




<hr>



### function Image [5/5]

```C++
quite::Image::Image (
    const Image & other
) 
```




<hr>



### function data 

```C++
ImageView quite::Image::data () const
```




<hr>



### function operator= 

```C++
Image & quite::Image::operator= (
    Image && other
) noexcept
```




<hr>



### function operator= 

```C++
Image & quite::Image::operator= (
    const Image & other
) 
```




<hr>



### function save\_to 

```C++
void quite::Image::save_to (
    const std::filesystem::path & destination
) const
```




<hr>



### function ~Image 

```C++
virtual quite::Image::~Image () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `libs/core/include/quite/image.hpp`

