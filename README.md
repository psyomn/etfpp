# etfpp

A simple C++ library that helps you build and encode Erlang structures
(ETF).

## support

- [x] Version
- [ ] AtomCacheRef
- [x] SmallInteger
- [x] Integer
- [x] Float
- [x] Atom
- [ ] Reference
- [ ] Port
- [ ] Pid
- [x] SmallTuple
- [x] LargeTuple
- [ ] Map
- [x] Nil
- [x] String
- [x] List
- [x] Binary
- [ ] SmallBig
- [ ] LargeBig
- [ ] NewReference
- [x] SmallAtom
- [ ] Fun
- [ ] NewFun
- [ ] Export
- [x] BitBinary
- [ ] NewFloat
- [x] AtomUtf8
- [ ] SmallAtomUtf8

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
