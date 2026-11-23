# SPDX-License-Identifier: BSD-2-Clause

# Copyright (C) 2026 embedded brains GmbH & Co. KG

DOT_SOURCES = $(wildcard *.dot)

PUML_SOURCES = $(wildcard *.puml)

TEX_SOURCES = $(wildcard *.tex)

all: $(DOT_SOURCES:.dot=.png) $(DOT_SOURCES:.dot=.pdf) \
  $(PUML_SOURCES:.puml=.png) $(PUML_SOURCES:.puml=.pdf) \
  $(TEX_SOURCES:.tex=.pdf) $(TEX_SOURCES:.tex=.svg)

%.eps: %.dot
	dot -Teps $^ -o$@

%.pdf: %.dot
	dot -Tpdf $^ -o$@

%.png: %.dot
	dot -Tpng $^ -o$@

%.pdf: %.puml
	plantuml -tpdf $^

%.png: %.puml
	plantuml -tpng $^

%.pdf: %.tex
	pdflatex -interaction=nonstopmode -halt-on-error $<
	rm -f $*.aux $*.log

%.svg: %.pdf
	dvisvgm --pdf --no-fonts --exact-bbox -o $@ $<
