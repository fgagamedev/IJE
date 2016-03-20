#!/bin/bash
set -o posix

LINE_LENGTH=80
EXTENSIONS=h,cpp
VERBOSITY=0

# FILTERS+=-build/class,
# FILTERS+=-build/c++11,
# FILTERS+=-build/deprecated,
# FILTERS+=-build/endif_comment,
# FILTERS+=-build/explicit_make_pair,
# FILTERS+=-build/forward_decl,
FILTERS+=-build/header_guard,
# FILTERS+=-build/include,
# FILTERS+=-build/include_alpha,
# FILTERS+=-build/include_order,
# FILTERS+=-build/include_what_you_use,
# FILTERS+=-build/namespaces,
# FILTERS+=-build/printf_format,
# FILTERS+=-build/storage_class,
FILTERS+=-legal/copyright,
# FILTERS+=-readability/alt_tokens,
FILTERS+=-readability/braces,
# FILTERS+=-readability/casting,
# FILTERS+=-readability/check,
# FILTERS+=-readability/constructors,
# FILTERS+=-readability/fn_size,
# FILTERS+=-readability/function,
# FILTERS+=-readability/inheritance,
FILTERS+=-readability/multiline_comment,
# FILTERS+=-readability/multiline_string,
# FILTERS+=-readability/namespace,
# FILTERS+=-readability/nolint,
# FILTERS+=-readability/nul,
# FILTERS+=-readability/strings,
# FILTERS+=-readability/todo,
# FILTERS+=-readability/utf8,
# FILTERS+=-runtime/arrays,
# FILTERS+=-runtime/casting,
# FILTERS+=-runtime/explicit,
# FILTERS+=-runtime/int,
# FILTERS+=-runtime/init,
# FILTERS+=-runtime/invalid_increment,
# FILTERS+=-runtime/member_string_references,
# FILTERS+=-runtime/memset,
# FILTERS+=-runtime/indentation_namespace,
# FILTERS+=-runtime/operator,
# FILTERS+=-runtime/printf,
# FILTERS+=-runtime/printf_format,
# FILTERS+=-runtime/references,
# FILTERS+=-runtime/string,
# FILTERS+=-runtime/threadsafe_fn,
# FILTERS+=-runtime/vlog,
FILTERS+=-whitespace/blank_line,
FILTERS+=-whitespace/braces,
# FILTERS+=-whitespace/comma,
FILTERS+=-whitespace/comments,
# FILTERS+=-whitespace/empty_conditional_body,
# FILTERS+=-whitespace/empty_loop_body,
# FILTERS+=-whitespace/end_of_line,
# FILTERS+=-whitespace/ending_newline,
# FILTERS+=-whitespace/forcolon,
# FILTERS+=-whitespace/indent,
# FILTERS+=-whitespace/line_length,
FILTERS+=-whitespace/newline,
# FILTERS+=-whitespace/operators,
# FILTERS+=-whitespace/parens,
# FILTERS+=-whitespace/semicolon,
FILTERS+=-whitespace/tab,
# FILTERS+=-whitespace/todo,

# src/
touch cpplint_src.log
./cpplint.py --linelength=${LINE_LENGTH} --extensions=${EXTENSIONS} --verbose=${VERBOSITY}\
    --filter=${FILTERS} src/*.* 2> cpplint_src.log

# include/
touch cpplint_include.log
./cpplint.py --linelength=${LINE_LENGTH} --extensions=${EXTENSIONS} --verbose=${VERBOSITY}\
    --filter=${FILTERS} include/*/*.* 2> cpplint_include.log
