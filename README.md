
# Compiling
Requires make and GCC or Clang

Run `make ijvm` to build the ijvm binary

You can enable the debug print (`dprintf`) found in `include/util.h` by
setting the `-DDEBUG` compiler flag (e.g., `make clean && make testbasic CFLAGS=-DDEBUG`).

# Running a binary
Run an IJVM program using `./ijvm binary`. For example `./ijvm files/advanced/Tanenbaum.ijvm`.
