This tutorial is online, [here](https://github.com/correctcomputation/libjpeg_tutorial). The text here refers to commit hashes in that tutorial, but they are not necessary for carrying it out by hand, here.

# Begin

This tutorial will demonstrate the 3C conversion process by converting
a small C program into Checked C. The program uses the C library
[libjpeg](http://www.ijg.org/) to read a JPEG image file provided as a command
line argument, and write it to standard output in
[PPM format](https://en.wikipedia.org/wiki/Netpbm#PPM_example). The program
being converted is adapted from sample code provided as part of the libjpeg
distribution.

This tutorial is intended to specifically demonstrate how 3C can be used to
port programs that interact with existing C libraries. For a first
tutorial on 3C, see our port of
[tiny-bignum-c](https://github.com/correctcomputation/checkedc-tiny-bignum-c).

# Requirements

For conversion of C code into Checked C and compilation of Checked C to C, both
`3c` and the Checked C version of `clang` must be built from the repository
[correctcomputation/checkedc-clang](https://github.com/correctcomputation/checkedc-clang).
The Checked C standard library headers from
[correctcomputation/checkedc](https://github.com/correctcomputation/checkedc/)
are also required. These should already be available if 3C was built according
to the
[3C build instructions](https://github.com/correctcomputation/checkedc-clang/blob/main/clang/docs/checkedc/3C/INSTALL.md).
This tutorial uses these repositories at commits
[2a0df40](https://github.com/correctcomputation/checkedc-clang/commit/2a0df403e4c803edecbe8ed6019320d7b170708a) and
[7c6f388](https://github.com/correctcomputation/checkedc/commit/7c6f388a816bcca14cf2144f9b78b6e27957a09d)
respectively.

The premise of this tutorial is to convert C code that depends on libjpeg, so
the library should be installed. On Ubunutu, it can be installed with
`sudo apt install libjpeg-dev`. (This should installed in the docker image.)

The makefile and conversion script included with this tutorial assume that the
`3c` Checked C version of `clang` are on your path. If you cloned 3c into your
home directory and built it according to the instructions linked above, then
the path can be configured with
```bash
export PATH="~/checkedc-clang/build/bin/:$PATH"
```

# Initial Conversion

The tutorial begins with unconverted code on
<a href="https://github.com/correctcomputation/libjpeg_tutorial/commit/START_COMMIT" data-commit-start="true">this commit</a>.
To convert the sample program, we will execute 3C through the provided
`convert_all.sh` script. This script invokes 3C on the source file with
some options to control the specifics of the conversion process. (The
purpose of the options is explained in the [tiny-bignum-c tutorial](https://github.com/correctcomputation/checkedc-tiny-bignum-c).

Here we assume that you do not know beforehand that you will need to create a new
checked header file for libjpeg, and show how to determine that it is
necessary. If this is known ahead of time, the conversion script could be
modified to include the options required for converting with the libjpeg header
file from the beginning.

The command in `convert_all.sh` can be simple because only one source file is
being converted, and there are no complicated compiler flags that need to be
provided.
```bash
#!/bin/bash
3c -alltypes -warn-root-cause -output-dir=out ./to_ppm.c --
```

Running the conversion script (`./convert_all.sh`)  will execute the initial
conversion and place the converted files in `./out/` according to the specified
`-output-dir`. The converted code is left in the output directory for the
moment because subsequent changes will be applied to the original, unconverted,
code. The converted code will be copied from the output directory when we are
happy with the progress of the conversion, and want to begin making final
adjustments to the Checked C code.

```{.bash file=tutorial.sh}
./convert_all.sh
git add out
git commit -m "[3c] Initial conversion"
```
<a href="https://github.com/correctcomputation/libjpeg_tutorial/commit/" data-commit-subject="Initial">(view changes)</a>.


# Converting `jpeglib.h`

Running the conversion script also emitted *root cause diagnostics* as specified
by the `-warn-root-cause` option. These diagnostics identify code patterns
that have specifically prevented a pointer from being made checked (it
remains "wild"); this code is a root cause in the sense that it directly affects
the identified pointer (which in turn may affect other pointers with a dataflow
relationship). To decide how to proceed with the conversion,
we can examine the information in the root-cause diagnostics.
By far, the most common root cause of wildness is that there are
function declarations in unwritable files. These functions are declared in the
system version of the libjpeg header file (`jpeglib.h`) which is located
outside of the current directory. By default, 3C considers files outside the
current directory "unwritable", and so will never make changes to such files.
Before we can have 3C infer Checked C declarations for these functions, we
first need to create a local, writable copy of the header so that 3C can
rewrite it.

For consistency, a copy of the header file is already included with this
tutorial, but, in general, the header file should be a copy of the system
version of the header file. In this case, we would need to create a local
include directory and copy the system header into it:
```bash
mkdir include
cp /usr/include/jpeglib.h ./include
```
The local include directory and header file already exist, so we only need to
update the conversion script so that the local header is found before the
system header. Edit `convert_all.sh` to append `-I ./include/` to the end of
the argument list. This must be placed after the dashes (`--`) which denote the
end of arguments passed to 3C and the start of arguments passed to clang. For
this tutorial, we have included patch files for this and all other necessary
manual changes.

```{.bash file=tutorial.sh}
git apply < patches/update_include.patch
git add convert_all.sh
git commit -m "[Manual] Update include path"
```
<a href="https://github.com/correctcomputation/libjpeg_tutorial/commit/" data-commit-subject="Update include path">(view changes)</a>.

Re-running `./convert_all.sh` will attempt conversion again, but this time with
the writable copy of `jpeglib.h`, so 3C is capable of making changes to it. This
resolves the "unwritable file" root causes, but they are replaced by root
causes due to "undefined functions".

```{.bash file=tutorial.sh}
./convert_all.sh
git add out
git commit -m "[3C] Convert with local header"
```
<a href="https://github.com/correctcomputation/libjpeg_tutorial/commit/" data-commit-subject="Convert with local header">(view changes)</a>.

By default, 3C will not rewrite the types of functions that are not defined. To
make it infer the types of such functions, 3C can be given the flag
`-infer-types-for-undefs`. This disables constraints that are typically
generated which force all undefined functions to remain unchecked, allowing
Checked C types to be inferred and added to the header as so-called
"interop types" (itypes).

There are some important limitations to this flag:

- 3C will still only infer types for functions that are declared in files that
  it is able to rewrite. In particular, this means that functions defined in
  system library headers will not be automatically converted to use itypes.
  This is why a local copy of `jpeglib.h` was created in the same directory
  as the code being converted in the previous steps. This allows 3C to rewrite
  the declaration, so checked types will be inferred.
- 3C will still treat any undefined function as internally unsafe. This means
  that an undefined function will only be converted to an `itype` type, and
  never a fully checked type. If the body of the function is later made
  available, 3C can be rerun on the code and will rewrite itypes into fully checked types.
- 3c is not able to examine the bodies of the functions, so inferred pointer
  types and array bounds are not guaranteed to be correct. The compiler will
  check that the functions are called in accordance with the inferred types,
  but doing so risks missing spatial safety violations when the types do not
  accurately specify the behavior of the implementation. For this reason, the
  inferred types must be validated against the implementation or the behavior
  specified in available documentation.

To proceed with conversion of the libjpeg header file (`jpeglib.h`) we must
now update the options passed to 3C to enable conversion of undefined
functions. Update `convert_all.sh` again to add `-infer-types-for-undefs` to
the list of options passed to 3C. When making this edit, be careful to add
the option before the two dashes `--` which mark the end of the options passed
to 3C.

```{.bash file=tutorial.sh}
git apply < patches/add_option.patch
git add convert_all.sh
git commit -m "[Manual] Add new option"
```
<a href="https://github.com/correctcomputation/libjpeg_tutorial/commit/" data-commit-subject="Add new option">(view changes)</a>.

Running the 3C conversion for a third time and examining the root cause
diagnostics will show that the undefined functions are no longer reported as
causes of wildness.

```{.bash file=tutorial.sh}
./convert_all.sh
git add out
git commit -m "[3C] Convert with new option"
```
<a href="https://github.com/correctcomputation/libjpeg_tutorial/commit/" data-commit-subject="Convert with new option">(view changes)</a>.

# A Final Root Cause

After this point, the conversion can proceed using the same process
described in the tiny-bignum-c tutorial. Any remaining root causes of unchecked
pointers will be resolved before committing to using the converted version of
the code, and finally placing the entire program in a checked region to finish
conversion.

One of the root causes that remains indicates that a pointer is declared in a
macro. 3C cannot rewrite inside macros, so we must either fully expand the
macro, so that 3C can annotate each expansion individually, or manually add
Checked C annotations inside the macros.

In this case, the macro `jpeg_common_fields` is used to declare the fields of
a structure. It is easy to add an itype to the field declarations so that each
structure defined using the macro is now defined with itypes on its fields.
Only two of the fields (`err` and `mem`) are actually relevant to the current
conversion. Itypes should be added onto these fields so that they are now
declared as `struct jpeg_error_mgr *err : itype(_Ptr<struct jpeg_error_mgr>)`
and `struct jpeg_memory_mgr *mem : itype(_Ptr<struct jpeg_memory_mgr>)`
respectively. The conversion script should then be run again to propagate the
change.

```{.bash file=tutorial.sh}
git apply < patches/insert_itypes.patch
git add ./include/jpeglib.h
git commit -m "[Manual] Add itypes in macro"
```
<a href="https://github.com/correctcomputation/libjpeg_tutorial/commit/" data-commit-subject="Add itypes in macro">(view changes)</a>.

```{.bash file=tutorial.sh}
./convert_all.sh
git add out
git commit -m "[3C] Convert with itypes in macro"
```
<a href="https://github.com/correctcomputation/libjpeg_tutorial/commit/" data-commit-subject="Convert with itypes in macro">(view changes)</a>.

At this point, the major issues preventing conversion of the example program
(unwritable code, undefined functions, and `struct` fields defined in macros)
have been resolved. A few unchecked pointers remain, but these are either in
the header file only, or can be fixed individually in the partially converted
code. To do this, the converted versions of the source files need to be copied
into the working directory.

```{.bash file=tutorial.sh}
cp -r ./out/* .
git add include/jpeglib.h to_ppm.c
git commit -m "[Manual] Copy converted files"
```
<a href="https://github.com/correctcomputation/libjpeg_tutorial/commit/" data-commit-subject="Copy converted files">(view changes)</a>.

# Compiling the Converted Code

Attempting to compile the code by executing `make` in its current state will
show that a few manual fixes need to be made to the converted code.

A few of the errors are syntax errors introduced by 3C while rewriting the header
file. These are not interesting and can be fixed easily. The other, more
interesting, error is raised in `to_ppm.c`.

3C infers that a pointer is an array, but is unable to infer any bounds.
Checked C raises an error when the pointer is later accessed at constant index
`0`. Due to the constant index, the length of the array must be at least `1`.
It is not used anywhere else, so the bounds of the array can be exactly
`count(1)`. This pointer is actually a two dimensional array
(`_Array_ptr<_Array_ptr<unsigned char>>`), but Checked C only supports bounds
on the outer array pointer. The lack of bounds on the nested pointers will need
to be addressed before the program can be considered fully checked.

With bounds added onto the array Checked C now checks that the bounds are
preserved on assignment to the array. There is an assignment to the array from
the return value of a function declared in `jpeglib.h`. 3C did not infer bounds
for this function, so they must now be added manually. The function is passed
a number of rows and the size of each row. As noted above, the array pointer is
a two-dimensional array, and we cannot annotate the inner array, so its length
is equal to the number of rows (`count(numrows)`). This is consistent with the
actual arguments at the function call: `numrows` is `1`, and the return value
is expected to have bounds `count(1)`.

The final error complains about an unsafe cast from a `struct jpeg_error_mgr`
pointer to `struct my_error_mgr`. While the cast isn't safe, the size of
`struct my_error_mgr` is at least as large as `struct jpeg_error_mgr`, so we
can instruct Checked C to accept the cast with explicit bounds checking by
replacing the cast `(my_error_ptr)` with
a `_Dynamic_bounds_cast<my_error_ptr>`, so
```c
my_error_ptr myerr = (my_error_ptr) cinfo->err;
```
becomes
```c
my_error_ptr myerr = _Dynamic_bounds_cast<my_error_ptr>(cinfo->err);
```

The exact fixes are captured in the patch file:

```{.bash file=tutorial.sh}
git apply < patches/fix_errors.patch
git add include/jpeglib.h to_ppm.c
git commit -m  "[Manual] Fix errors in converted code."
make
```
<a href="https://github.com/correctcomputation/libjpeg_tutorial/commit/" data-commit-subject="Fix errors in converted code">(view changes)</a>.

# Finishing the Conversion

With the initial conversion working, the final goal is to "fully convert" the
source file, where full conversion means enabling the `CHECKED_SCOPE` pragma
while having a minimal number of `_Unchecked` regions in the program.

Add `#pragma CHECKED_SCOPE on` at the top of `to_ppm.c`, before the function
definitions but after all `#include`s. Attempting to compile again with `make`
after adding the pragma reveals new errors raised by the Checked C compiler.

```{.bash file=tutorial.sh}
git apply < patches/add_pragma.patch
git add to_ppm.c
git commit -m "[Manual] Add CHECKED_SCOPE pragma."
make || true
```
<a href="https://github.com/correctcomputation/libjpeg_tutorial/commit/" data-commit-subject="Add CHECKED_SCOPE pragma">(view changes)</a>.

The first error is a result of a bounds cast inserted by 3C during conversion.
Before turning the `CHECKED_SCOPE` pragma on, we fixed a different error by
adding a dynamic cast so that Checked C would check a
bound at run time. Here, an `_Assume_bounds_cast` was added by 3C to avoid checking
a bound that cannot be verified even at run time. This is clearly unsafe, and
so it is not allowed in a checked region. Ideally, we would be able to
refactor the code to avoid needing the `_Assume_bounds_cast`, but that is not possible
without a substantial change to the functions exported by libjpeg. libjpeg
works with two dimensional arrays, but Checked C currently does not have
a mechanism for annotating bounds on the inner array pointers. We need to place
the `_Assume_bounds_cast` in an unchecked region before the Checked C compiler will
accept the program.

The simplest approach would be to place the whole statement with the cast in an
unchecked block, but this would result in the function call and array access
being unchecked, which should be avoided. Instead, the statement is split so
that only the unsafe cast is unchecked, minimizing the amount of code in
unchecked blocks. The statement
```c
put_scanline_someplace(_Assume_bounds_cast<JSAMPROW >(buffer[0],  count(row_stride)), row_stride);
```
is split into four statements.
```c
JSAMPROW row_unkb : bounds(unknown) = buffer[0];
JSAMPROW row : count(row_stride) = 0;
_Unchecked {
  row = _Assume_bounds_cast<JSAMPROW>(row_unkb,  count(row_stride));
}
put_scanline_someplace(row, row_stride);
```

Another compiler error is raised because libjpeg using the standard library
header `setjmp.h` for error handling. This header file does not yet have
a checked version, so we need to surround calls to its functions in
`_Unchecked` blocks.

The exact fixes required are again provided in a patch file.

```{.bash file=tutorial.sh}
git apply < patches/pragma_fixes.patch
git add -u
git commit -m  "[Manual] Fix errors in checked scope."
```
<a href="https://github.com/correctcomputation/libjpeg_tutorial/commit/" data-commit-subject="Fix errors in checked scope">(view changes)</a>.

With these changes, the program compiles successfully with the `CHECKED_SCOPE`
pragma enabled. As a final step, we can check that the program can run without
error on sample input.

```{.bash file=tutorial.sh}
make
./to_ppm test.jpg | display
```
