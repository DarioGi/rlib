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
 * 
 * $Id$s
 *
 * This module implements the C language API (Application Programming Interface)
 * for the RLIB library functions.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <locale.h>
#include <langinfo.h>

#include "config.h"
#include "rlib.h"
#include "rlib_input.h"

#ifndef CODESET
#define CODESET _NL_CTYPE_CODESET_NAME
#endif

rlib * rlib_init_with_environment(struct environment_filter *environment) {
	gchar *lc_encoding;
	rlib *r;
	
	init_signals();

	r = g_new0(rlib, 1);

	if(environment == NULL)
		rlib_new_c_environment(r);
	else
		ENVIRONMENT(r) = environment;
	lc_encoding = nl_langinfo(CODESET);
	if (lc_encoding != NULL) {
		rlib_set_encodings(r, lc_encoding, lc_encoding, lc_encoding);
	}
#if !DISABLE_UTF8
	make_all_locales_utf8();
#endif
//	strcpy(r->pdf_encoding, "WinAnsiEncoding");
	return r;
}


rlib * rlib_init() {
	return rlib_init_with_environment(NULL);
}

gint rlib_add_query_pointer_as(rlib *r, gchar *input_source, gchar *sql, gchar *name) {
	gint i;
	if(r->queries_count > (RLIB_MAXIMUM_QUERIES-1)) {
		return -1;
	}

	r->queries[r->queries_count].sql = sql;
	r->queries[r->queries_count].name = g_strdup(name);
	for(i=0;i<r->inputs_count;i++) {
		if(!strcmp(r->inputs[i].name, input_source)) {
			r->queries[r->queries_count].input = r->inputs[i].input;
		}
	}
	
	r->queries_count++;
	return r->queries_count;
}


gint rlib_add_query_as(rlib *r, gchar *input_source, gchar *sql, gchar *name) {
	gint i;
	if(r->queries_count > (RLIB_MAXIMUM_QUERIES-1)) {
		return -1;
	}

	r->queries[r->queries_count].sql = g_strdup(sql);
	r->queries[r->queries_count].name = g_strdup(name);
	for(i=0;i<r->inputs_count;i++) {
		if(!strcmp(r->inputs[i].name, input_source)) {
			r->queries[r->queries_count].input = r->inputs[i].input;
		}
	}
	
	r->queries_count++;
	return r->queries_count;
}

gint rlib_add_report(rlib *r, gchar *name, gchar *mainloop) {
	if(r->reports_count > (RLIB_MAXIMUM_REPORTS-1)) {
		return - 1;
	}
	r->reportstorun[r->reports_count].name = g_strdup(name);
	r->reportstorun[r->reports_count].query = g_strdup(mainloop);
	r->reports_count++;
	return r->reports_count;
}

gint rlib_execute(rlib *r) {
	gint i,j;
	char newfile[MAXSTRLEN];

	r->now = time(NULL);
	for(i=0;i<r->queries_count;i++) {
		r->results[i].input = r->queries[i].input;

		r->results[i].result = INPUT(r,i)->new_result_from_query(INPUT(r,i), r->queries[i].sql);
		if(r->results[i].result == NULL) {
			rlogit("Failed To Run A Query [%s]\n", r->queries[i].sql);
			return -1;
		}
		r->results[i].name =  r->queries[i].name;
	}

	LIBXML_TEST_VERSION

	xmlKeepBlanksDefault(0);
	for(i=0;i<r->reports_count;i++) {
		sprintf(newfile, "%s.rlib", r->reportstorun[i].name);
		if((r->reports[i] = load_report(newfile)) == NULL)
			r->reports[i] = parse_report_file(r->reportstorun[i].name);
		r->reports[i]->mainloop_query = -1;
		if(r->reportstorun[i].query != NULL) {
			for(j=0;j<r->queries_count;j++) {
				if(!strcmp(r->queries[j].name, r->reportstorun[i].query)) {
					r->reports[i]->mainloop_query = j;
					break;
				}					
			}
		}
		xmlCleanupParser();		
		if(r->reports[i] == NULL) {
			//TODO:FREE REPORT AND ALL ABOVE REPORTS
			rlogit("Failed to run a Report\n");
			return -1;
		}
	}
	
	make_report(r);	
	rlib_finalize(r);
	return 0;
}


gchar * rlib_get_content_type_as_text(rlib *r) {
	static char buf[256];
#ifdef HAVE_LIBCPDF	
	if(r->format == RLIB_CONTENT_TYPE_PDF) {
		sprintf(buf, "Content-Type: application/pdf\nContent-Length: %ld%c", OUTPUT(r)->rlib_get_output_length(r), 10);
		return buf;
	}
#endif
	if(r->format == RLIB_CONTENT_TYPE_CSV) {
		return RLIB_WEB_CONTENT_TYPE_CSV;
	} else {
		const char *charset = (r->current_output_encoder)? 
					rlib_char_encoder_get_name(r->current_output_encoder)
					: "UTF-8";
		if(r->format == RLIB_CONTENT_TYPE_HTML) {
			g_snprintf(buf, sizeof(buf), RLIB_WEB_CONTENT_TYPE_HTML, charset);
			return buf;
		} else {
			g_snprintf(buf, sizeof(buf), RLIB_WEB_CONTENT_TYPE_TEXT, charset);
			return buf;
		}
	}
	r_error("Content type code unknown");
	return "Oops!!!";
}

gint rlib_spool(rlib *r) {
	OUTPUT(r)->rlib_spool_private(r);
	return 0;
}

gint rlib_set_output_format(rlib *r, int format) {
	r->format = format;
	return 0;
}

gint rlib_add_resultset_follower(rlib *r, gchar *leader, gchar *follower) {
	gint ptr_leader = -1, ptr_follower = -1;
	gint x;

	if(r->resultset_followers_count > (RLIB_MAXIMUM_FOLLOWERS-1)) {
		return -1;
	}

	for(x=0;x<r->queries_count;x++) {
		if(!strcmp(r->queries[x].name, leader))
			ptr_leader = x;
		if(!strcmp(r->queries[x].name, follower))
			ptr_follower = x;
	}
	
	if(ptr_leader == -1) {
		rlogit("rlib_add_resultset_follower: Could not find leader!\n");
		return -1;
	}
	if(ptr_follower == -1) {
		rlogit("rlib_add_resultset_follower: Could not find follower!\n");
		return -1;
	}
	if(ptr_follower == ptr_leader) {
		rlogit("rlib_add_resultset_follower: Followes can't be leaders ;)!\n");
		return -1;
	}
	r->followers[r->resultset_followers_count].leader = ptr_leader;
	r->followers[r->resultset_followers_count++].follower = ptr_follower;

	return 0;
}

gint rlib_set_output_format_from_text(rlib *r, gchar *name) {
		r->format = RLIB_FORMAT_TXT;

#ifdef HAVE_LIBCPDF	
	if(!strcasecmp(name, "PDF"))
		r->format = RLIB_FORMAT_PDF;
#endif
	if(!strcasecmp(name, "HTML"))
		r->format = RLIB_FORMAT_HTML;
	if(!strcasecmp(name, "TXT"))
		r->format = RLIB_FORMAT_TXT;
	if(!strcasecmp(name, "CSV"))
		r->format = RLIB_FORMAT_CSV;
	if(!strcasecmp(name, "XML"))
		r->format = RLIB_FORMAT_XML;
	return 0;
}

gchar *rlib_get_output(rlib *r) {
	return OUTPUT(r)->rlib_get_output(r);
}

gint rlib_get_output_length(rlib *r) {
	return OUTPUT(r)->rlib_get_output_length(r);
}

/**
 *	Add name/value pair to the memory constants.
 *  Saves copies of the name and value, NOT pointers.
 */
gint rlib_add_parameter(rlib *r, const gchar *name, const gchar *value) {
	char buf[MAXSTRLEN];
	gint result = 1;
	rlib_hashtable_ptr ht = r->htParameters;
	
	if (!ht) { //If no hashtable - add one
		ht = r->htParameters = rlib_hashtable_new_copyboth();
	}
	if (ht) {
//This encodes both the name and value in UTF8 from whatever the source is written in.
		g_strlcpy(buf, rlib_char_encoder_encode(r->param_encoder, name), sizeof(buf));
		rlib_hashtable_insert(ht, (gpointer) buf, (gpointer) rlib_char_encoder_encode(r->param_encoder, value));
#if 0
//The rlib_hashtable_new_copyboth() hashtable already duplicates the strings (see docs above)
rlib_hashtable_insert(ht, (gpointer) g_strdup(name), (gpointer) g_strdup(value));
#endif
result = 0;
	}
	return result;
}


/*
*  Returns TRUE if locale was actually set, otherwise, FALSE
*/
gint rlib_set_locale(rlib *r, gchar *locale) {
	gchar *cur;
	
#if DISABLE_UTF8
	cur = setlocale(LC_ALL, locale);
#else
	cur = setlocale(LC_ALL, make_utf8_locale(locale));
#endif

	if (!cur) {
		r_error("Locale could not be changed to %s by rlib_set_locale", locale);
		return FALSE;
	}
#if 0
	lc_encoding = nl_langinfo(CODESET);
	if (lc_encoding != NULL) {
		rlib_set_encodings(r, lc_encoding, lc_encoding, lc_encoding);
		r_info("Encoding changed to locale %s lang=%s in rlib_set_locale", cur, lc_encoding);
	}		
#endif
	r_debug("Locale set to: %s", locale);
	return (cur)? TRUE : FALSE;
}


void rlib_init_profiler() {
	g_mem_set_vtable(glib_mem_profiler_table);
}


void rlib_dump_profile_stdout(gint profilenum) {
	printf("\nRLIB memory profile #%d:\n", profilenum);
	g_mem_profile();
	fflush(stdout);
}

void rlib_dump_profile(gint profilenum, const gchar *filename) {
	FILE *newout = NULL;
	int fd;
	
	fflush(stdout);
	fd = dup(STDOUT_FILENO); /* get a dup of current stdout */
	if (fd < 0) {
		rlogit("Unable to dup stdout");
		return;
	}
	if (filename) {
		newout = freopen(filename, "ab", stdout);
	}
	if (!newout) dup2(STDERR_FILENO, STDOUT_FILENO); /* Use stderr */
	rlib_dump_profile_stdout(profilenum);
	if (newout) {
		fclose(newout);
	} else {
		rlogit("Could not open memory profile file: %s. Used stderr instead", filename);
	}
	dup2(fd, STDOUT_FILENO); /* restore original stdout and close the dup fd */
	close(fd);
}

/**
 * put calls to this where you want to debug, then just set a breakpoint here.
 */
void rlib_trap() {
	return;
}


void rlib_set_report_output_encoding(rlib *r, int rptnum, const char *encoding) {
	if ((rptnum >= 0) && (rptnum < r->reports_count)) {
		struct rlib_report *rr = r->reports[rptnum];

		rlib_char_encoder_destroy(&rr->output_encoder);
		rr->output_encoder = rlib_char_encoder_new(encoding, TRUE);
	}
}


void rlib_set_output_encoding(rlib *r, const char *encoding) {
	rlib_char_encoder_destroy(&r->output_encoder);
	r->output_encoder = rlib_char_encoder_new(encoding, TRUE);
}

void rlib_set_pdf_font_directories(rlib *r, const char *d1, const char *d2) {
	if (d1) g_strlcpy(r->pdf_fontdir1, d1, sizeof(r->pdf_fontdir1) - 1);
	else *r->pdf_fontdir1 = '\0';
	if (d2) g_strlcpy(r->pdf_fontdir2, d2, sizeof(r->pdf_fontdir2) - 1);
	else *r->pdf_fontdir2 = '\0';
	if (d1 && !d2) strcpy(r->pdf_fontdir2, d1);
	if (d2 && !d1) strcpy(r->pdf_fontdir1, d2);
}

void rlib_set_pdf_font(rlib *r, const char *encoding, const char *fontname) {
	if (encoding) {
		g_strlcpy(r->pdf_encoding, encoding, sizeof(r->pdf_encoding));
		r_debug("PDF font set to %s", fontname);
	}
	if (fontname) {
		g_strlcpy(r->pdf_fontname, fontname, sizeof(r->pdf_fontname));
		r_debug("PDF encoding set to %s", encoding);
	}
}


/**
 * Sets the default encoding that is used by the datasource so RLIB 
 * knows how to properly handle its data. Use this function 
 * The default is to assume that input from the database is in the 
 * same locale as the current system locale.
 */
void rlib_set_database_encoding(rlib *r, const char *encoding) {
	rlib_char_encoder_destroy(&r->db_encoder);
	r->db_encoder = rlib_char_encoder_new(encoding, FALSE);
}


gint rlib_set_datasource_encoding(rlib *r, gchar *input_name, gchar *encoding) {
	int i;
	struct input_filter *tif;
	
	for (i=0;i<r->inputs_count;i++) {
		tif = r->inputs[i].input;
		if (strcmp(r->inputs[i].name, input_name) == 0) {
			rlib_char_encoder_destroy(&tif->info.encoder);
			tif->info.encoder = rlib_char_encoder_new(encoding, FALSE);
#if 0
			r->inputs[i].input->input_decoder = iconv_open(RLIB_ENCODING, decoding);
			if (r->inputs[i].input->input_decoder == (iconv_t) -1)  {
				rlogit("Error.. invalid decoding [%s]\n", decoding);
				return -1;			
			}
#endif
			return 0;
		}
	}
	rlogit("Error.. datasource [%s] does not exist\n", input_name);
	return -1;
}


/**
 * Sets the encoding that is used by the parameters so RLIB knows how to 
 * properly handle them. This is used for all reports/inputs, etc.
 * The default is to assume that input from parameter values is UTF8. 
 */
void rlib_set_parameter_encoding(rlib *r, const char *encoding) {
	rlib_char_encoder_destroy(&r->param_encoder);
	r->param_encoder = rlib_char_encoder_new(encoding, FALSE);
}


/**
 * Sets the DEFAULT encodings for multiple data sources in one function.
 */
void rlib_set_encodings(rlib *r, const char *outputencoding, const char *dbencoding, const char *paramencoding) {
	if (outputencoding && *outputencoding) {
		r_debug("Setting output encoding to %s", outputencoding);
		rlib_set_output_encoding(r, outputencoding);
	}
	if (dbencoding && *dbencoding) {
		rlib_set_database_encoding(r, dbencoding);
	}
	if (paramencoding && *paramencoding) {
		rlib_set_parameter_encoding(r, paramencoding);
	}
}


#ifdef VERSION
gchar *cpdf_version(void);
gchar *rlib_version(void) {
#if 0
#if DISABLE_UTF8
gchar *charset="8859-1";
#else
gchar *charset="UTF8";
#endif
r_debug("rlib_version: version=[%s], CHARSET=%s, CPDF=%s", VERSION, charset, cpdf_version());
#endif
	return VERSION;
}
#else
gchar *rlib_version(void) {
	return "Unknown";
}
#endif


#if HAVE_MYSQL
gint rlib_mysql_report(gchar *hostname, gchar *username, gchar *password, gchar *database, gchar *xmlfilename, gchar *sqlquery, 
gchar *outputformat) {
	rlib *r;
	r = rlib_init();
	if(rlib_add_datasource_mysql(r, "mysql", hostname, username, password, database) == -1)
		return -1;
	rlib_add_query_as(r, "mysql", sqlquery, "example");
	rlib_add_report(r, xmlfilename, "example");
	rlib_set_output_format_from_text(r, outputformat);
	if(rlib_execute(r) == -1)
		return -1;
	rlib_spool(r);
	rlib_free(r);
	return 0;
}
#endif

#if HAVE_POSTGRE
gint rlib_postgre_report(gchar *connstr, gchar *xmlfilename, gchar *sqlquery, gchar *outputformat) {
	rlib *r;
	r = rlib_init();
	if(rlib_add_datasource_postgre(r, "postgre", connstr) == -1)
		return -1;
	rlib_add_query_as(r, "postgre", sqlquery, "example");
	rlib_add_report(r, xmlfilename, "example");
	rlib_set_output_format_from_text(r, outputformat);
	if(rlib_execute(r) == -1)
		return -1;
	rlib_spool(r);
	rlib_free(r);
	return 0;
}
#endif
