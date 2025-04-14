#!/bin/bash

source validate_input

param="$1"

if [[ "$param" =~ ^[0-9]+$ ]]; then
    echo "Incorrect input: parameter must not be a number"
    exit 1
fi

echo "Passed parameter: $param"
