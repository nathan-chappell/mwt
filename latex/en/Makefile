export TEXINPUTS=../tex//:

presentation: presentation.tex
	pdflatex presentation.tex
	pdflatex presentation.tex

cur: thesis.pdf

all: thesis.pdf presentation

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

pgfjobs:
	pdflatex -shell-escape --jobname=jobProofFlowChart thesis.tex
	pdflatex -shell-escape --jobname=jobHCone thesis.tex
	pdflatex -shell-escape --jobname=jobVCone thesis.tex
	pdflatex -shell-escape --jobname=jobHPoly thesis.tex
	pdflatex -shell-escape --jobname=jobVPoly thesis.tex
	pdflatex -shell-escape --jobname=jobHPolytope thesis.tex
	pdflatex -shell-escape --jobname=jobVPolytope thesis.tex
	pdflatex -shell-escape --jobname=jobNotFullDim thesis.tex
	pdflatex -shell-escape --jobname=jobNotPointed thesis.tex
