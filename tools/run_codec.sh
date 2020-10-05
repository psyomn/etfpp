#!/usr/bin/env bash
./bazel-bin/bin/example-encode
./test/data/binary_file_to_term.erl *.etf
