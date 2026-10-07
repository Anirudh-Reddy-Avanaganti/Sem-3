

# 4. Run your pdftk command
if pdftk "$1" cat $(python3 slides.py "$1") output "$2"; then
    echo "Successfully created ${out_file}"
    
    # 5. Safely delete the source file only if pdftk succeeded
    rm "$1"
    echo "Removed source file: $1"
else
    echo "Error: pdftk processing failed. Source file preserved."
    return 1
fi


