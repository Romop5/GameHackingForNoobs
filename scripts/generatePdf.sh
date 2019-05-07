#!/bin/bash

#Use generate .tex
./generateTexUsingUmdoc.sh
RETVAL=$?
if [ $RETVAL -eq 1 ]
then
    exit 1
fi 

# Create .pdf
pdflatex final.tex
pdflatex final.tex

# Copy to root dir

cp final.pdf ../book.pdf
