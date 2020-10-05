#!/usr/bin/env escript

main(Args) ->
    lists:map(fun(X) -> io:format("~s: ~p~n", [X, file_to_term(X)]) end, Args).

file_to_term(FileName) ->
    {ok, Contents} = file:read_file(FileName),
    binary_to_term(Contents).
