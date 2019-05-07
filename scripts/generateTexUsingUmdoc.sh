#!/bin/bash
OUTPUT_FILE_NAME=`pwd`"/final.tex"
echo "$TMPFILE"

# Convert to .tex
pushd .
cd ../src/ && umdoc -t -o "$OUTPUT_FILE_NAME"
RETVAL=$?
popd

if [ $RETVAL -eq 1 ]
then
    exit 1
fi

# HACK: disable sourcesandspro
sed -i "s/.*usepackage.*sourcesanspro/%&/" "$OUTPUT_FILE_NAME"
sed -i "s/.*usepackage.*sourcecodepro/%&/" "$OUTPUT_FILE_NAME"

# Copy SVGs

cp -R ../src/svgs .

# Convert SVGS to .pdf
find svgs | grep "\.svg" | sed "s/\.svg$//" | xargs -n1 -IFILE inkscape FILE.svg -A FILE.pdf
