#!/bin/bash

TMPFILE=`mktemp /tmp/XXX.md`

echo "$TMPFILE"

# Concatenate
cat ../src/*.md  > "$TMPFILE"

# Convert to .tex
umdoc -t "$TMPFILE" -o final.tex
RETVAL=$?

if [ $RETVAL -eq 0 ]
then
    exit 1
do

# HACK: disable sourcesandspro
sed -i "s/.*usepackage.*sourcesanspro/%&/" final.tex
sed -i "s/.*usepackage.*sourcecodepro/%&/" final.tex

exit 0
