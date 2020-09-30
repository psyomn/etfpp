#!/usr/bin/env escript

main(FileNames) ->
    io:format("~p~n", [FileNames]),
    WithContents = lists:map(fun(F) -> read_file(F) end, FileNames),
    WithBinary = lists:map(fun(F) -> to_binary(F) end, WithContents),
    _ = lists:map(fun(F) -> generate_file(F) end, WithBinary).

read_file(FileName) ->
    {ok, Contents} = file:consult(FileName),
    {FileName, Contents}.

to_binary({FileName, Content}) ->
    {FileName, term_to_binary(Content)}.

generate_file({FileName, BinaryContents}) ->
    io:format("filename : ~p~n", [FileName]),
    [NewName, _Ext] = string:split(FileName, "."),
    io:format("write ~p~n", [NewName ++ ".etf"]),
    ok = file:write_file(NewName ++ ".etf", BinaryContents).
