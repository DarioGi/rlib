/*
 *  Copyright (C) 2003-2016 SICOM Systems, INC.
 *
 *  Authors: Bob Doan <bdoan@sicompos.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of version 2 of the GNU General Public
 * License as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this program; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */
#ifndef _RLIB_INPUT_H_
#define _RLIB_INPUT_H_

#include <glib.h>

#include <rlib.h>

struct input_info {
	char charset[64];
	GIConv encoder;
};

typedef struct input_filter input_filter;
struct input_filter {
	gpointer r;
	gpointer private;
	struct input_info info;
	gint (*free)(gpointer);
	gint (*connect_local_with_credentials)(gpointer, const gchar *, const gchar *, const gchar *);
	gint (*connect_with_credentials)(gpointer, const gchar *, guint, const gchar *, const gchar *, const gchar*);
	gint (*connect_with_connstr)(gpointer, const gchar *);
	gint (*input_close)(gpointer);
	gpointer (*new_result_from_query)(gpointer, gpointer);
	gint (*first)(gpointer, gpointer);
	gint (*next)(gpointer, gpointer);
	gint (*previous)(gpointer, gpointer);
	gint (*last)(gpointer, gpointer);
	gint (*isdone)(gpointer, gpointer);
	const gchar * (*get_error)(gpointer);
	gchar * (*get_field_value_as_string)(gpointer, gpointer, gpointer);
	gpointer (*resolve_field_pointer)(gpointer, gpointer, gchar *);
	void (*free_result)(gpointer, gpointer);
	void (*free_query)(gpointer, gpointer);
	gint (*set_encoding)(gpointer);
};

struct rlib_query {
	gchar *sql;
	gint sql_allocated;
	gchar *name;
	struct input_filter *input;
	gpointer *private;
};

gint rlib_add_datasource(rlib *r, const gchar *input_name, struct input_filter *input);

#endif /* _RLIB_INPUT_H_ */
