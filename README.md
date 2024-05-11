Attempt at recreating an interface for a point of sale system in GTK. 

Build instructions:

## Linux
```
gcc $( pkg-config --cflags gtk4 ) -o POSApplication main.c $( pkg-config --libs gtk4 )
```
## Windows
```
gcc $(pkg-config --cflags gtk4) -o POSApplication main.c shop.h shop.c $(pkg-config --libs gtk4)
```
Mockup:
![hnk5ozei17vc1](https://github.com/vancha/GTKPOS/assets/9658702/145e44b9-e493-4f59-804d-7cc2057d51b4)
