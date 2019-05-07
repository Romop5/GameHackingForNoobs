#!/bin/bash

#Use generate .tex
./generateTexUsingUmdoc.sh

# Create .pdf
pdflatex final.tex
pdflatex final.tex

# Copy to root dir

cp final.pdf ../book.pdf
