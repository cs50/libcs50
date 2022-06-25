#!/bin/bash

RED='\033[0;31m'
GREEN='\033[0;32m'
NONE='\033[0m'

TIMEOUT_SECONDS=3

mkdir -p tests-out

run_tests() {
    local test_failed=0
    for run_file in *.run; do
        echo

        local basename="${run_file%%.*}"
        if [[ ! -r "$basename.desc" ]]; then
            red "Test name is missing for $run_file. Please add the test name to $basename.desc and try again."
            exit 1
        fi

        if [[ ! -r "$basename.out" ]]; then
            red "Expected output is missing for $run_file. Please add the expected output to $basename.out and try again."
            exit 1
        fi

        eval "timeout $TIMEOUT_SECONDS $(cat "$run_file")" > "tests-out/$basename.out"
        local exit_code=$?

        local test_name="${basename}: $(cat "$basename.desc")"
        if [[ $exit_code -eq 0 ]] && diff "$basename.out" "tests-out/$basename.out"; then
            echo -e "${GREEN}${test_name}${NONE}"
        else
            echo -e "${RED}${test_name}${NONE}"
            if [[ $exit_code -eq 124 ]]; then
                echo "  Timed out after $TIMEOUT_SECONDS seconds"
            else
                echo "  The actual output is in tests-out/$basename.out"
            fi
            test_failed=1
        fi
    done

    exit $test_failed
}

run_tests "$@"
