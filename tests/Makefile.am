## bindings/php/Makefile.am for RLIB

## Copyright (c) 2003-2006 SICOM Systems Inc (bdoan@sicompos.com)
## rlib is free software; you can redistribute it and/or modify
## it under the terms of the GNU General Public License as published by
## the Free Software Foundation; either version 2, or (at your option)
## any later version.

## rlib is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU General Public License for more details.

## You should have received a copy of the GNU General Public License
## along with this program; if not, write to the Free Software
## Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
## 02111-1307, USA.

## Report bugs to rlib-devel@lists.sourceforge.net
##
## Process this file with automake to produce Makefile.in

AM_CFLAGS = $(RLIB_CFLAGS) -I${top_srcdir}/libsrc

if HAVE_MYSQL
MYSQL_INPUT=test1 test3
endif

if HAVE_POSTGRES
POSTGRES_INPUT=test2
endif

noinst_PROGRAMS = \
	$(MYSQL_INPUT) \
	$(POSTGRES_INPUT)

test1_SOURCES= test1.c
test1_LDADD = $(top_builddir)/libsrc/libr.la $(RLIB_LIBS)

test2_SOURCES= test2.c
test2_LDADD = $(top_builddir)/libsrc/libr.la $(RLIB_LIBS)

test3_SOURCES= test3.c
test3_LDADD = $(top_builddir)/libsrc/libr.la $(RLIB_LIBS)
