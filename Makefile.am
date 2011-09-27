AUTOMAKE_OPTIONS = subdir-objects

localedir = $(datadir)/locale

AM_LDFLAGS  =
AM_CFLAGS =

ACLOCAL_AMFLAGS = -I m4

bin_PROGRAMS =
lib_LTLIBRARIES =
man1_MANS =
pkgdata_DATA =

noinst_bin_PROGRAMS =
noinst_LIBRARIES =

noinst_bindir =

EXTRA_DIST = config.rpath ChangeLog
CLEANFILES =
SUBDIRS =

############################# ChangeLog #######################################

ChangeLog:
	git log > ChangeLog

dist-hook: ChangeLog

.PHONY: ChangeLog

EXTRA_DIST += ChangeLog

############################# applications ####################################

bin_PROGRAMS += klatt
man1_MANS += klatt.man

klatt_LDADD = -lm
klatt_SOURCES = klatt.c parwave.c
