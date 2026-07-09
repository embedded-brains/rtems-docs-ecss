# SPDX-License-Identifier: BSD-2-Clause

# Copyright (C) 2026 embedded brains GmbH & Co. KG

DOT_SOURCES = $(wildcard *.dot)

PUML_SOURCES = $(wildcard *.puml)

all: $(DOT_SOURCES:.dot=.png) $(DOT_SOURCES:.dot=.pdf) \
  $(PUML_SOURCES:.puml=.png) $(PUML_SOURCES:.puml=.pdf)

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
