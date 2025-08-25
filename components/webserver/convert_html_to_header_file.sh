#!/bin/bash

#Check if filename was provided
if [ -z "$1" ]; then
    echo "Missing argument - filename!"
    echo "Usage: $0 <file.html>"
    exit 1
fi

# Input file
input_file="$1"

# Validate file exists
if [ ! -f "$input_file" ]; then
    echo "File not found: $input_file"
    exit 1
fi

# Ensure it's an HTML file
if [[ "$input_file" != *.html ]]; then
    echo "Input must be an HTML file"
    exit 1
fi

# Derive names
basename_no_ext=$(basename "$input_file" .html)
gzip_file="page_${basename_no_ext}.gz"
header_file="page_${basename_no_ext}.h"
macro_guard="PAGE_${basename_no_ext^^}_H"

# Compress HTML using gzip
gzip -c -9 "$input_file" > "$gzip_file"

# Generate header file
echo "🔧 Generating header file: $header_file"

{
    echo "#ifndef $macro_guard"
    echo "#define $macro_guard"
    echo ""
    echo "// This file was generated using gzip + xxd from $input_file"
    echo ""

    # Convert gzipped file to C array
    xxd -i -u "$gzip_file"

    echo ""
    echo "#endif  // $macro_guard"
} > "$header_file"

#Clean up temporary gzip file
rm -f "$gzip_file"

#Move to pages folder
pages_dir="../pages"
mkdir -p "$pages_dir"
mv "$header_file" "$pages_dir/"

echo "✅ Header generated: $pages_dir/$header_file"

