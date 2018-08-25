faststats is a small library for counting _things_ in a program.
As such, it is suitable for storing statistics of the amount of
items processed in a system, of generated outputs, of errors found…

The statistics are stored in a System V shared memory segment which
is mapped into the program. All access (other than mapping/unmapping
the segment) are atomic, so statistics can be gathered from several
threads or even programs running on the same machine.
