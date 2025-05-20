#!/bin/bash

test_id=$1
here_dir=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )

test_dir="${here_dir}/tests"
outputs_dir="${here_dir}/outputs"

case $test_id in
  p1)
    "${test_dir}/cjson_add" |& grep FAIL &> /dev/null; test $? -eq 1 && exit 0;;
  p2)
    "${test_dir}/compare_tests" |& grep FAIL &> /dev/null; test $? -eq 1 && exit 0;;
  p3)
    "${test_dir}/json-patch-tests" |& grep FAIL &> /dev/null; test $? -eq 1 && exit 0;;
  p4)
    "${test_dir}/minify_tests" |& grep FAIL &> /dev/null; test $? -eq 1 && exit 0;;
  p5)
    "${test_dir}/misc_tests" |& grep FAIL &> /dev/null; test $? -eq 1 && exit 0;;
  p6)
    "${test_dir}/parse_array" |& grep FAIL &> /dev/null; test $? -eq 1 && exit 0;;
  p7)
    "${test_dir}/parse_hex4" |& grep FAIL &> /dev/null; test $? -eq 1 && exit 0;;
  p8)
    "${test_dir}/parse_number" |& grep FAIL &> /dev/null; test $? -eq 1 && exit 0;;
  p9)
    "${test_dir}/parse_object" |& grep FAIL &> /dev/null; test $? -eq 1 && exit 0;;
  p10)
    "${test_dir}/parse_string" |& grep FAIL &> /dev/null; test $? -eq 1 && exit 0;;
  p11)
    "${test_dir}/parse_value" |& grep FAIL &> /dev/null; test $? -eq 1 && exit 0;;
  p12)
    "${test_dir}/parse_with_opts" |& grep FAIL &> /dev/null; test $? -eq 1 && exit 0;;
  p13)
    "${test_dir}/print_array" |& grep FAIL &> /dev/null; test $? -eq 1 && exit 0;;
  p14)
    "${test_dir}/print_number" |& grep FAIL &> /dev/null; test $? -eq 1 && exit 0;;
  p15)
    "${test_dir}/print_object" |& grep FAIL &> /dev/null; test $? -eq 1 && exit 0;;
  p16)
    "${test_dir}/print_string" |& grep FAIL &> /dev/null; test $? -eq 1 && exit 0;;
  p17)
    "${test_dir}/print_value" |& grep FAIL &> /dev/null; test $? -eq 1 && exit 0;;
  p18)
    "${test_dir}/readme_examples" |& grep FAIL &> /dev/null; test $? -eq 1 && exit 0;;
esac

exit 1