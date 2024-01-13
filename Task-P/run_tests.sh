# Take input for the number N
read -p "Enter the value of N: " N

# Loop through files from 1 to N
for ((i=1; i<=N; i++)); do
    input_file="in${i}.txt"
    output_file="mout${i}.txt"
    expected_output_file="out${i}.txt"

    # Check if input file exists
    if [ -e "$input_file" ]; then
        # Run the program with input from inN.txt and save output to moutN.txt
        ./prog < "$input_file" > "$output_file"
        echo "Output for $input_file is saved to $output_file."

        # Compare the output with expected output
        if [ -e "$expected_output_file" ]; then
            if diff -w "$output_file" "$expected_output_file"; then
                echo "Files $output_file and $expected_output_file are identical.";
    		rm $output_file		
	    else
                echo "Files $output_file and $expected_output_file are different."
            fi
	    echo ""
        else
            echo "Expected output file $expected_output_file does not exist for iteration $i."
        fi
    else
        echo "Input file $input_file does not exist for iteration $i."
    fi
done
