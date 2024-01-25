#!/bin/bash

# Directory containing your output files
myout_dir="./myout"

# Directory containing expected output files
out_dir="./out"

# Loop through all .myout files in the myout directory
for myout_file in "$myout_dir"/*.myout; do
    # Extract the base filename without the extension
    base_name=$(basename "$myout_file" .myout)

    # Construct the corresponding filename in the out directory
    out_file="$out_dir/$base_name.out"

    # Check if the corresponding file exists in the out directory
    if [ ! -f "$out_file" ]; then
        echo "No corresponding file for $myout_file in out directory"
        continue
    fi

    # Compare the files, ignoring whitespace differences
    if ! diff -w -q "$myout_file" "$out_file" > /dev/null; then
        echo "Files differ (ignoring whitespace): $myout_file"
    fi
done

echo "Comparison complete."
