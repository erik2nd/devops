#!/bin/bash

source system_info
source output_data

output_data

read -p "Do you want to save data to file? (Y/N): " answer

if [[ "$answer" =~ ^[Yy]$ ]]; then
    filename=$(date +"%d_%m_%y_%H_%M_%S.status")
    output_data > "$filename"
    echo "Data saved to $filename"
fi
