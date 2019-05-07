#!/bin/bash

#TMPFILE=`mktemp /tmp/XXX.md`
OUTPUT_FILE_NAME=`pwd`"/final.tex"
echo "$TMPFILE"

# Convert to .tex
pushd .
cd ../src/ && umdoc -t -o "$OUTPUT_FILE_NAME"
popd

# HACK: disable sourcesandspro
sed -i "s/.*usepackage.*sourcesanspro/%&/" "$OUTPUT_FILE_NAME"
sed -i "s/.*usepackage.*sourcecodepro/%&/" "$OUTPUT_FILE_NAME"

# To .pdf

pdflatex "$OUTPUT_FILE_NAME"

