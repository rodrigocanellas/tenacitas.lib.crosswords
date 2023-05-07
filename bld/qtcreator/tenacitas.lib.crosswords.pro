TEMPLATE = subdirs

SUBDIRS = \
    tst


include (../../../tenacitas.bld/qtcreator/common.pri)

DISTFILES += \
    $$BASE_DIR/tenacitas.lib.crosswords/README.md

HEADERS +=  \
    $$BASE_DIR/tenacitas.lib.crosswords/alg/assembler.h \
    $$BASE_DIR/tenacitas.lib.crosswords/evt/events.h \
    $$BASE_DIR/tenacitas.lib.crosswords/typ/grid.h
