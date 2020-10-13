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

## testing

You'll notice I hand craft some of the binary payloads. That's
purposeful, and I want tests to fail in case tags change (which won't
but I sleep with one eye open so...)

## plan

- [ ] Add a builder to make usage of lib a little more ergonomic
- [ ] Write extern C stuff to make it C portable

# licensing

Apache v2. See LICENSE.
