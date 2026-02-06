## Build

The OOC compiler can be built with `make` if the following prerequisites are installed:
 
- make
 
- gcc (build-essential)

- binutils

If bear is installed one can generate a Clangd configuration file in their build with `bear -- make` instead.

## Usage

The command `./ooc path/file.oc` will turn `file.oc` into a runnable executable.

The command can be run with the following options:

- `--asm` or `-a` - Outputs a human readable assembly file, can specify a path after it

- `--out` or `-o` - Specify an output path/filename for the executable

By default the compiler will output the object and executable file to the current directory.

## Syntax

To view information on OOC's syntax, go [here](doc/SYNTAX.md).

## References

Followed along with this [YouTube series](https://youtube.com/playlist?list=PLUDlas_Zy_qC7c5tCgTMYq2idyyT241qs&si=Pxv7xFqu3rYnc1m-).

Used this [blog post](https://benhoyt.com/writings/hash-table-in-c/) as a guide for making a hash table.

