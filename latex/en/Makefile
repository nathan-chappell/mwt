export TEXINPUTS=../tex//:

cur: thesis.pdf

all: thesis.pdf presentation

presentation: presentation.tex
	pdflatex presentation.tex
	pdflatex presentation.tex

# LaTeX must be run multiple times to get references right
thesis.pdf: thesis.tex $(wildcard *.tex) thesis.xmpdata listings
	pdflatex $<
	pdflatex $<
	#bibtex thesis
	#pdflatex $<

clean:
	rm -f *.log *.dvi *.aux *.toc *.lof *.lot *.out *.bbl *.blg *.xmpi
	#rm -f thesis.pdf

listings :
	./getlistings.sh > listingcommands.tex
