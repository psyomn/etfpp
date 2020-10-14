# etfpp

A simple C++ library that helps you build and encode Erlang structures
(ETF).

## support

- [x] Version
- [x] SmallInteger
- [x] Integer
- [x] Float
- [x] Atom
- [x] SmallTuple
- [x] LargeTuple
- [x] Map
- [x] Nil
- [x] String
- [x] List
- [x] Binary
- [ ] SmallBig
- [ ] LargeBig
- [x] SmallAtom
- [x] BitBinary
- [x] NewFloat
- [x] AtomUtf8
- [x] SmallAtomUtf8

## probably will not support

Not sure I really want to support these for what I'm doing right now,
but maybe in the future.

- [ ] AtomCacheRef
- [ ] Fun
- [ ] NewFun
- [ ] Export
- [ ] NewReference
- [ ] Reference
- [ ] Port
- [ ] Pid

## building

    bazel build ...
    bazel test ...

If you want to run a quick check (bazel build is a prereq):

    ./tools/run_codec.sh

## sample output

This is what you get when you run the sample binary built with
bazel. It will generate a bunch of etf files that you can then
parse using `file:read_file(...)`, and then converting the binary with
`term_to_binary(...)` in Erlang.

    psyomn$ ./tools/run_codec.sh
    file-0.etf: [{}]
    file-1.etf: [123.123]
    file-2.etf: [<<"hello world this is a binary">>]
    file-3.etf: [{1,2,3,<<"hello">>}]
    file-4.etf: [one,two,three,ÿapple]
    file-5.etf: [<<170,187,204,110:7>>]
    file-6.etf: ['\x{1F00}\x{3BC}\x{3BC}\x{3BF}\x{3C5}\x{3B4}\x{3B9}\x{1F72}\x{3C2}']
    file-7.etf: ['\x{394}\x{3B9}\x{3BF}\x{3B3}\x{3AD}\x{3BD}\x{3B7}\x{3C2}']
    file-8.etf: [123.123]
    file-9.etf: [#{1 => 2}]
    psyomn$ cat ./tools/run_codec.sh
    #!/usr/bin/env bash
    ./bazel-bin/bin/example-encode
    ./test/data/binary_file_to_term.erl *.etf

The weirdness you see above in file 6, and file 7, are utf8 encoded
atoms. They don't render well when printing but if you read file files
from the interpreter, you get:

    1> {ok, C1} = file:read_file("file-6.etf").
    {ok,<<131,108,0,0,0,1,118,0,20,225,188,128,206,188,206,
          188,206,191,207,133,206,180,206,185,225,189,178,...>>}
    2> binary_to_term(C1).
    ['ἀμμουδιὲς']
    3> {ok, C2} = file:read_file("file-7.etf").
    {ok,<<131,108,0,0,0,1,119,16,206,148,206,185,206,191,206,
          179,206,173,206,189,206,183,207,130,106>>}
    4> binary_to_term(C2).
    ['Διογένης']

## testing

You'll notice I hand craft some of the binary payloads. That's
purposeful, and I want tests to fail in case tags change (which won't
but I sleep with one eye open so...)

## plan

- [ ] Add a builder to make usage of lib a little more ergonomic
- [ ] Write extern C stuff to make it C portable

# licensing

Apache v2. See LICENSE.
