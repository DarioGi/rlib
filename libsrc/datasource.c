/*
 *  Copyright (C) 2003 SICOM Systems, INC.
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
 
#include <string.h>

#include "ralloc.h"
#include "rlib.h"
#include "input.h"

int rlib_add_datasource(rlib *r, char *input_name, struct input_filter *input) {
	r->inputs[r->inputs_count].input = input;
	r->inputs[r->inputs_count].name = input_name;
	r->inputs_count++;
	return 0;
}

int rlib_add_datasource_mysql(rlib *r, char *input_name, char *database_host, char *database_user, char *database_password, char *database_database) {
	void *mysql;

	r->inputs[r->inputs_count].input = rlib_mysql_new_input_filter();
	mysql = rlib_mysql_real_connect(r->inputs[r->inputs_count].input, database_host, database_user, database_password, database_database);
	r->inputs[r->inputs_count].name = input_name;
	if(mysql == NULL) {
		rlogit("ERROR: Could not connect to MYSQL\n");
		return -1;
	}
	
	r->inputs_count++;
	return 0;
}

int rlib_add_datasource_postgre(rlib *r, char *input_name, char *conn) {
	void *postgre;

	r->inputs[r->inputs_count].input = rlib_postgre_new_input_filter();
	postgre = rlib_postgre_connect(r->inputs[r->inputs_count].input, conn);
	r->inputs[r->inputs_count].name = input_name;
	if(postgre == NULL) {
		rlogit("ERROR: Could not connect to POSTGRE\n");
		return -1;
	}
	
	r->inputs_count++;
	return 0;
}
