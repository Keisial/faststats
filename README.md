faststats is a small library for counting _things_ in a program.
As such, it is suitable for storing statistics of the amount of
items processed in a system, of generated outputs, of errors found…

The statistics are stored in a System V shared memory segment which
is mapped into the program. All access (other than mapping/unmapping
the segment) are atomic, so statistics can be gathered from several
threads or even programs running on the same machine.

How to use
==========

Add faststats.c to your compilation units and include faststats.h
on the file that is going to call the faststats functions.

Initialise the library using `faststats_init(filename)` (non MT-safe,
call once at the beginning of your program). It accepts a filename that
is used to parametrise the memory segment, so that multiple programs
can use the same library without colliding (see `ftok(3)`).
The statistics are **not** stored in that file, but in a shared memory
segment. Also rebooting the machine will clear them, so you will probably
wish to extract the values periodically and copy them somewhere else.

There are several operations that can be performed:

* faststats_read
* faststats_store
* faststats_add
* faststats_sub

All of them receive an index parameter that lets you save multiple type
of statistics on a single memory segment. There are about 512 slots
available, depending on your architecture and the data type chosen, call
`faststats_max_index()` to find out the maximum this code was compiled to.
