#!/bin/bash

test_id=$1
here_dir=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )

test_dir="${here_dir}/tests"
outputs_dir="${here_dir}/outputs"

command=""
argument=""

prefix="${test_id:0:1}"
number="${test_id:1}"
number=$(( $number - 1))

case $prefix in
  p) if ((number>=0 && number < 31))
      then
        command="${test_dir}/cjson_add"
        argument="${number}"
      elif ((number >= 31 && number < 41))
      then
        command="${test_dir}/compare_tests"
        argument=$(( $number - 31 ))
      elif ((number >= 41 && number < 48))
      then
        command="${test_dir}/minify_tests"
        argument=$(( $number - 41 ))
      elif ((number >= 48 && number < 52))
      then
        command="${test_dir}/parse_array"
        argument=$(( $number - 48 ))
      elif ((number >= 52 && number < 54))
      then
        command="${test_dir}/parse_hex4"
        argument=$(( $number - 52 ))
      elif ((number >= 54 && number < 59))
      then
        command="${test_dir}/parse_number"
        argument=$(( $number - 54 ))
      elif ((number >= 59 && number < 63))
      then
        command="${test_dir}/parse_object"
        argument=$(( $number - 59 ))
      elif ((number >= 63 && number < 69))
      then
        command="${test_dir}/parse_string"
        argument=$(( $number - 63 ))
      elif ((number >= 69 && number < 76))
      then
        command="${test_dir}/parse_value"
        argument=$(( $number - 69 ))
      elif ((number >= 76 && number < 82))
      then
        command="${test_dir}/parse_with_opts"
        argument=$(( $number - 76 ))
      elif ((number >= 82 && number < 85))
      then
        command="${test_dir}/print_array"
        argument=$(( $number - 82 ))
      elif ((number >= 85 && number < 91))
      then
        command="${test_dir}/print_number"
        argument=$(( $number - 85 ))
      elif ((number >= 91 && number < 94))
      then
        command="${test_dir}/print_object"
        argument=$(( $number - 91 ))
      elif ((number >= 94 && number < 97))
      then
        command="${test_dir}/print_string"
        argument=$(( $number - 94 ))
      elif ((number >= 97 && number < 104))
      then
        command="${test_dir}/print_value"
        argument=$(( $number - 97 ))
      elif ((number >= 104 && number < 116))
      then
        command="${test_dir}/misc_tests"
        argument=$(( $number - 104 ))
      elif ((number >= 116 && number < 130))
      then
        command="${test_dir}/misc_tests"
        argument=$(( $number - 104 + 1))
      fi ;;

  n) if ((number>=0 && number < 1))
     then
      command="${test_dir}/misc_tests"
      argument=12   
     fi ;;
esac

temp="$(mktemp)"
echo $temp
# trap 'rm -f $temp' 0

"${command}" "${argument}" > ${temp}; command_status=$?
grep -q PASS ${temp}; pass_status=$?
grep -q FAIL ${temp}; fail_status=$?

! (( command_status || pass_status || !fail_status))