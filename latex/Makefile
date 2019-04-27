
all : listings mwt.tex
	pdflatex mwt.tex && pdflatex mwt.tex

listings : listingcommands.tex ../cpp/include/*.h
	./getlistings.sh > listingcommands.tex
