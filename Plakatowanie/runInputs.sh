#!/bin/bash

# Directory containing input files
input_dir="./in"

# Directory for output files
output_dir="./myout"

# Check if the output directory exists, if not create it
if [ ! -d "$output_dir" ]; then
    mkdir -p "$output_dir"
fi

# Loop through all .in files in the input directory
for input_file in "$input_dir"/*.in; do
    echo "Processing file: $input_file"

    # Extract the base filename without the extension
    base_name=$(basename "$input_file" .in)

    # Construct the output filename
    output_file="$output_dir/$base_name.myout"

    echo "Running prog with $input_file, output to $output_file"

    # Run the program with the input file and redirect output to the output file
    if ! ./prog < "$input_file" > "$output_file"; then
        echo "Error running prog with $input_file"
        exit 1
    fi

    echo "Output for $input_file created."
done

echo "Processing complete."
