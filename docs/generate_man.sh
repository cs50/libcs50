#!/bin/sh

# Translate the AsciiDoc source FILE or FILE(s) into the backend output format (e.g., HTML 5, DocBook 4.5, etc.)
# Get asciidoctor at https://github.com/asciidoctor/asciidoctor
# Alternately, since asciidoctor is a Ruby gem, you can just
# `gem install asciidocs`

asciidoctor -d manpage -b manpage -D ./man *.adoc
