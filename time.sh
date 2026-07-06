#!/bin/bash

time_function() {
    local start=$EPOCHREALTIME
    
    # Execute the function passed as an argument
    "$@" 
    local exit_code=$?
    
    local end=$EPOCHREALTIME
    
    # Calculate the difference using 'bc' for floating-point math
    local elapsed=$(echo "$end - $start" | bc)
    
    echo "--------------------------------------"
    echo "Execution Time: $elapsed seconds"
    echo "--------------------------------------"
    
    return $exit_code
}

time_function ./ft_ls -R /
# time_function ls -R /