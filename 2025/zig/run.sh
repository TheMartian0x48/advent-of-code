#!/bin/bash

day=$1
question=$2

# Prompt for day if not provided
if [ -z "$day" ]; then
    read -p "Enter day (1-25): " day
fi

# Prompt for question if not provided
if [ -z "$question" ]; then
    read -p "Enter question (1 or 2): " question
fi

# Validate inputs
if [[ ! "$day" =~ ^[0-9]+$ ]] || [ "$day" -lt 1 ] || [ "$day" -gt 25 ]; then
    echo "Error: Day must be a number between 1 and 25."
    exit 1
fi

if [[ ! "$question" =~ ^[1-2]$ ]]; then
    echo "Error: Question must be 1 or 2."
    exit 1
fi

# Pad day with leading zero if needed
padded_day=$(printf "%02d" $day)

source_file="day-${padded_day}-${question}.zig"
input_file="day-${padded_day}.in"

if [ ! -f "$source_file" ]; then
    echo "Error: Source file $source_file not found."
    exit 1
fi

if [ ! -f "$input_file" ]; then
    echo "Warning: Input file $input_file not found."
fi

echo "Running $source_file with input $input_file..."
zig run "$source_file" -- "$input_file"
