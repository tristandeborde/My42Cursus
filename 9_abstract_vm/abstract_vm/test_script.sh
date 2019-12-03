#!/bin/bash
#
# Perform test for Abstract_VM 42's project.
# 
# author: cmaxime@student.42.fr
#
# The return value of the executable should be 0 if success
# and other values if an error occured.

# Colors
CEND="\x1B[0m"
CRED="\x1B[38;5;9m"
CWHITE="\x1B[97m"
CBLUE="\x1B[93m"
CGREEN="\x1B[38;5;10m"

# Testing configs
MAKE_CMD=("make fclean" "make" "make re -j18" "make" "make clean")
EXEC="./avm"

#######################################
# Print output of the executable
# Globals:
#   None
# Arguments:
#   output
# Returns:
#   None
#######################################
function print_output () {
  if [ "$1" = "" ]; then
    printf "$CWHITE%s$CEND\n" "No Output"
  else
    printf "$CWHITE%s\n" "--- Output -------"
    printf "%s $CEND\n\n" "$1"
  fi
}

#######################################
# Print usage
# Globals:
#   None
# Arguments:
#   None
# Returns:
#   None
#######################################
function print_usage () {
  echo "usage: ./abstract_vm.sh [options] ... [-v | -V]"
  echo "Options:"
  echo "--makefile    : run Makefile tests"
  echo "--binary-test : run 42's correction test"
  echo "--unittest    : run unit-testing suite"
  echo "--all         : run all test"
}

#Options loading

VERBOSE=0
MAKE_TEST=0
ALL=0
BINARY_TEST=0
UNITTEST=0
errors=0

for arg in "$@"; do
  if [ "$arg" = "-v" ] && [ "$VERBOSE" -le 1 ]; then
    VERBOSE=1
  elif [ "$arg" = "-V" ] && [ "$VERBOSE" -le 2 ]; then
    VERBOSE=2
  elif [ "$arg" = "--makefile" ]; then
    MAKE_TEST=1
  elif [ "$arg" = "--all" ]; then
    ALL=1
  elif [ "$arg" = "--binary-test" ]; then
    BINARY_TEST=1
  elif [ "$arg" = "--unittest" ]; then
    UNITTEST=1
  else
    printf "./abstract_vm.sh: illegal option -- %s\n" "$arg"
    print_usage
    exit 1
  fi
done

if [ "$MAKE_TEST" -eq 0 ] && [ "$BINARY_TEST" -eq 0 ] && [ "$UNITTEST" -eq 0 ] && [ "$ALL" -eq 0 ]; then
  print_usage
  exit 0
fi

# Compilation test
if [ "$MAKE_TEST" -eq 1 ] || [ "$ALL" -eq 1 ]; then
  printf "[$CBLUE%15s$CEND ]\n" "Makefile"
  for test in "${MAKE_CMD[@]}"; do
    $test
    ret=$?
    if [ "$ret" -ne 0 ]; then
      printf "[$CRED%6s$CEND ] %s\n" "ERROR" "$test"
      exit 1
    fi
  done
  if [ "$ALL" -ne 1 ]; then
    exit 0
  fi
fi

# Check if the executable exist
if [ ! -f $EXEC ]; then
  printf "$CWHITE%s %s$CEND\n" "$EXEC" "does not exist."
  exit 1
fi


if [ "$UNITTEST" -eq 1 ] || [ "$ALL" -eq 1 ]; then

  # Error test
  printf "[$CBLUE%15s$CEND ]\n" "Bad files"
  for file in "test/exceptions"/*.asm; do
    output=$($EXEC "$file")
    ret=$?
    file="$(echo "$file" | rev | cut -d'/' -f1 | rev)"
    if [ "$ret" -eq 0 ]; then
      errors=$((errors + 1))
      printf "[$CRED%6s$CEND ] %s\n" "ERROR" "$file"
      if [ $VERBOSE -gt 0 ]; then
        print_output "$output"
      fi
    else
      printf "[$CGREEN%6s$CEND ] %s\n" "OK" "$file"
      if [ $VERBOSE -gt 1 ]; then
        print_output "$output"
      fi
    fi
  done

  # Good test
  printf "[$CBLUE%15s$CEND ]\n" "Good files"
  for file in "test/valid"/*.asm; do
    output=$($EXEC "$file")
    ret=$?
    file="$(echo "$file" | rev | cut -d'/' -f1 | rev)"
    if [ "$ret" -ne 0 ]; then
      errors=$((errors + 1))
      printf "[$CRED%6s$CEND ] %s\n" "ERROR" "$file"
      if [ $VERBOSE -gt 0 ]; then
        print_output "$output"
      fi
    else
      printf "[$CGREEN%6s$CEND ] %s\n" "OK" "$file"
      if [ $VERBOSE -gt 1 ]; then
        print_output "$output"
      fi
    fi
  done
fi

if [ "$BINARY_TEST" -eq 1 ] || [ "$ALL" -eq 1 ]; then
  printf "[$CBLUE%15s$CEND ]\n" "Binary Hackers"
  for file in "test/binaryhackers"/*.asm; do
    output=$($EXEC "$file")
    file="$(echo "$file" | rev | cut -d'/' -f1 | rev)"
    printf "%s\n" "$file"
    print_output "$output"
  done
fi

if [ "$errors" -gt 0 ]; then
  printf "$CRED%s %s$CEND\n" "$errors" "errors"
  exit 1
fi

exit 0
