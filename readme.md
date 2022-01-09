# lc3_vm



## About

A virtual machine made to simulate the fictional [LC3](https://en.wikipedia.org/wiki/Little_Computer_3) computer, an educational computer architecture.

* Note: the current version that is implemented is only for Windows OS only.



## Build

Navigate to the `/src` folder and either run

```sh
make
```

or

```sh
gcc lc3.c -o lc3
```



## Example usage

```sh
./lc3.exe ../examples/2048.obj
```

```sh
./lc3.exe ../examples/rogue.obj
```



## Resources used

[Tutorial (C)](https://justinmeiners.github.io/lc3-vm/index.html)

[Tutorial (Rust)](https://www.rodrigoaraujo.me/posts/lets-build-an-lc-3-virtual-machine/)

[lc3 reference](https://justinmeiners.github.io/lc3-vm/supplies/lc3-isa.pdf)

[Input/Output slides](https://www.cis.upenn.edu/~milom/cse240-Fall05/handouts/Ch08.pdf)

### Example LC3 code

[2048 game](https://github.com/rpendleton/lc3-2048)

[lc3-rouge](https://github.com/justinmeiners/lc3-rogue)



## To do

- [ ] Refactor code to make it more cleaner
- [ ] Understand how the image file is loaded
- [ ] Understand how the OS specifics are implemented
- [ ] Learn LC3 Assembly