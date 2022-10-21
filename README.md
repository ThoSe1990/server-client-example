# A Server-Client Example

This is a simple server-client example with boost.asio. Find the corresponding Blog post here: www.codingwiththomas.com/blog/boost-asio-server-client-example

## Build

Use conan to include boost into this project and use cmake to build:

```
conan install . -if build --build missing
cmake -S . -B ./build
cmake --build ./build
```