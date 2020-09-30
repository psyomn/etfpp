# genrule(
#     name = "do_term_to_binary_file",
#
#     tools = [":term_to_binary_file.erl"],
#
#     srcs = [
#          ":simple.term",
#          ":floats.term",
#     ],
#
#     cmd = "HOME=erlexec_requires_a_home_set_i_guess $(location :term_to_binary_file.erl) $(location *)",
#
#     outs = [
#          ":simple.etf",
#          ":floats.etf",
#     ],
# )