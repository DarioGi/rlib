/*
 *  Copyright (C) 2003-2005 SICOM Systems, INC.
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
 
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <time.h>
#include <locale.h>

#include "config.h"

#ifdef RLIB_HAVE_MONETARY_H 
#include <monetary.h>
#endif

#include "rlib.h"
#include "pcode.h"
#include "rlib_langinfo.h"


/*
* Formats numbers in money format using locale parameters and moneyformat codes
*/
gint rlib_format_money(rlib *r, gchar **dest,const gchar *moneyformat, gint64 x) { 
	gint result;
	*dest = g_malloc(MAXSTRLEN);
#ifdef RLIB_WIN32
	result = 0;
	(*dest)[0] = 0;
#else
	gdouble d = ((gdouble) x) / RLIB_DECIMAL_PRECISION;
	result = strfmon(*dest, MAXSTRLEN - 1, moneyformat, d);
#endif	
	return (result >= 0)? strlen(*dest) : 0;
}

gint rlib_format_number(rlib *r, gchar **dest, const gchar *fmt, gint64 x) {
	double d = (((double) x) / (double)RLIB_DECIMAL_PRECISION);
	*dest = g_strdup_printf(fmt, d);
	return TRUE;
}

static gint rlib_string_sprintf(rlib *r, gchar **dest, gchar *fmtstr, struct rlib_value *rval) {
	gchar *value = RLIB_VALUE_GET_AS_STRING(rval);
	*dest = g_strdup_printf(fmtstr, value);
	return TRUE;
}

gint rlib_number_sprintf(rlib *r, gchar **dest, gchar *fmtstr, const struct rlib_value *rval, gint special_format, gchar *infix, gint line_number) {
	gint dec=0;
	gint left_padzero=0;
	gint left_pad=0;
	gint right_padzero=1;
	gint right_pad=0;
	gint where=0;
	gint commatize=0;
	gchar *c;
	gchar *radixchar = nl_langinfo(RADIXCHAR);
	
	*dest = g_malloc(MAXSTRLEN);

	for(c=fmtstr;*c && (*c != 'd');c++) {
		if(*c=='$') {
			commatize=1;
		}
		if(*c=='%') {
			where=0;
		} else if(*c=='.') {
			dec=1;
			where=1;
		} else if(isdigit(*c)) {		
			if(where==0) {
				if(left_pad == 0 && (*c-'0') == 0)
					left_padzero = 1;
				left_pad *= 10;
				left_pad += (*c-'0');
			} else {
				right_pad *= 10;
				right_pad += (*c-'0');
			}
		}	
	}
	if (!left_pad)
		left_padzero = 1;
	if (!right_pad)
		right_padzero = 1;
	if(rval != NULL) {
		gchar fleft[20];
		gchar fright[20];
		
		if(left_pad > 20) {
			r_error(r, "FORMATTING ERROR ON LINE %d: %s\n", line_number, infix);
			r_error(r, "FORMATTING ERROR:  LEFT PAD IS WAY TO BIG! (%d)\n", left_pad);
			left_pad = 20;
		} 
		if(right_pad > 20) {
			r_error(r, "FORMATTING ERROR ON LINE %d: %s\n", line_number, infix);
			r_error(r, "FORMATTING ERROR:  LEFT PAD IS WAY TO BIG! (%d)\n", right_pad);			
			right_pad = 20;
		} 
		
		gchar *left_holding = g_malloc0(left_pad + 16);
		gchar *right_holding = g_malloc0(right_pad + 16);
		gint ptr=0;
		gint64 left, right;
		left = RLIB_VALUE_GET_AS_NUMBER(rval) / RLIB_DECIMAL_PRECISION;
		if(special_format)
			left = llabs(left);
		fleft[ptr++]='%';
		if(left_padzero)
			fleft[ptr++]='0';
		if(left_pad)
			if(commatize)
				sprintf(fleft +ptr, "%d'lld", left_pad);
			else
				sprintf(fleft +ptr, "%dlld", left_pad);
		else {
			if(commatize)
				fleft[ptr++] = '\'';
			fleft[ptr++] = 'l';
			fleft[ptr++] = 'l';
			fleft[ptr++] = 'd';
			fleft[ptr++] = '\0';
		}
		if(left_pad == 0 && left == 0) {
			left_holding[0] = '0';
			left_holding[1] = 0;			
		} else {
			sprintf(left_holding, fleft, left);
		}
		strcpy(*dest, left_holding);
		(*dest)[strlen(left_holding)] = '\0';
		if(dec) {
			ptr=0;
			if(!special_format && RLIB_VALUE_GET_AS_NUMBER(rval) < 0 && left == 0) {
				gchar tmp[MAXSTRLEN];
				sprintf(tmp, "-%s", left_holding);
				strcpy(left_holding, tmp);
				strcpy(*dest, left_holding);
				(*dest)[strlen(left_holding)] = '\0';
			}
				
			right = llabs(RLIB_VALUE_GET_AS_NUMBER(rval)) % RLIB_DECIMAL_PRECISION;
			fright[ptr++]='%';
			if(right_padzero)
				fright[ptr++]='0';
			if(right_pad)
				sprintf(&fright[ptr], "%dlld", right_pad);
			else {
				fright[ptr++] = 'l';
				fright[ptr++] = 'l';
				fright[ptr++] = 'd';
				fright[ptr++] = '\0';
			}
			right /= tentothe(RLIB_FXP_PRECISION-right_pad);
			sprintf(right_holding, fright, right);
			strcat(*dest, radixchar);
			strcat(*dest, right_holding);
		}
		g_free(left_holding);
		g_free(right_holding);
	}
	return strlen(*dest);
}

static gint rlib_format_string_default(rlib *r, struct rlib_report_field *rf, struct rlib_value *rval, gchar **dest) {
	if(RLIB_VALUE_IS_NUMBER(rval)) {
#ifdef _64BIT_
		*dest = g_strdup_printf("%ld", RLIB_FXP_TO_NORMAL_LONG_LONG(RLIB_VALUE_GET_AS_NUMBER(rval)));
#else
		*dest = g_strdup_printf("%lld", RLIB_FXP_TO_NORMAL_LONG_LONG(RLIB_VALUE_GET_AS_NUMBER(rval)));
#endif
	} else if(RLIB_VALUE_IS_STRING(rval)) {
		if(RLIB_VALUE_GET_AS_STRING(rval) == NULL)
			*dest = NULL;
		else
			*dest = g_strdup_printf("%s", RLIB_VALUE_GET_AS_STRING(rval));
	} else if(RLIB_VALUE_IS_DATE(rval))  {
		struct rlib_datetime *dt = &RLIB_VALUE_GET_AS_DATE(rval);
		rlib_datetime_format(r, dest, dt, "%m/%d/%Y");
	} else {
		*dest = g_strdup_printf("!ERR_F");
		return FALSE;
	}
	return TRUE;
}

gint rlib_format_string(rlib *r, gchar **dest, struct rlib_report_field *rf, struct rlib_value *rval) {
	gchar current_locale[MAXSTRLEN];
	current_locale[0] = 0;
	
	if(r->special_locale != NULL) {
		gchar *tmp;
		tmp = setlocale(LC_ALL, NULL);
		if(tmp == NULL)
			current_locale[0] = 0;
		else
			strcpy(current_locale, tmp);
		setlocale(LC_ALL, r->special_locale);
	}
	if(rf->xml_format.xml == NULL) {
		rlib_format_string_default(r, rf, rval, dest);
	} else {
		gchar *formatstring;
		struct rlib_value rval_fmtstr2, *rval_fmtstr=&rval_fmtstr2;
		rval_fmtstr = rlib_execute_pcode(r, &rval_fmtstr2, rf->format_code, rval);
		if(!RLIB_VALUE_IS_STRING(rval_fmtstr)) {
			*dest = g_strdup_printf("!ERR_F_F");
			rlib_value_free(rval_fmtstr);
			setlocale(LC_ALL, current_locale);
			return FALSE;
		} else {
			formatstring = RLIB_VALUE_GET_AS_STRING(rval_fmtstr);
			if(formatstring == NULL) {
				rlib_format_string_default(r, rf, rval, dest);
			} else {
				if (*formatstring == '!') {
					gboolean result;
					gchar *tfmt = formatstring + 1;
					gboolean goodfmt = TRUE;
					switch (*tfmt) {
					case '$': /* Format as money */
						if (RLIB_VALUE_IS_NUMBER(rval)) {
							result = rlib_format_money(r, dest, tfmt + 1, RLIB_VALUE_GET_AS_NUMBER(rval));
							setlocale(LC_ALL, current_locale);
							return result;
						}
						++formatstring;
						break;
					case '#': /* Format as number */
						if (RLIB_VALUE_IS_NUMBER(rval)) {
							result = rlib_format_number(r, dest, tfmt + 1, RLIB_VALUE_GET_AS_NUMBER(rval));
							setlocale(LC_ALL, current_locale);
							return result;
						}
						++formatstring;
						break;
					case '@': /* Format as time/date */
						if(RLIB_VALUE_IS_DATE(rval)) {
							struct rlib_datetime *dt = &RLIB_VALUE_GET_AS_DATE(rval);
							rlib_datetime_format(r, dest, dt, tfmt + 1);
						}
						break;
					default:
						goodfmt = FALSE;
						break;
					}
					if (goodfmt) {
						setlocale(LC_ALL, current_locale);
						return TRUE;
					}
				}
				if(RLIB_VALUE_IS_DATE(rval)) {
					rlib_datetime_format(r, dest, &RLIB_VALUE_GET_AS_DATE(rval), formatstring);
				} else {	
					gint i=0,/*j=0,pos=0,*/fpos=0;
					gchar fmtstr[20];
					gint special_format=0;
					gchar *idx;
					gint len_formatstring;
					idx = strchr(formatstring, ':');
					fmtstr[0] = 0;
					if(idx != NULL && RLIB_VALUE_IS_NUMBER(rval)) {
						formatstring = g_strdup(formatstring);
						idx = strchr(formatstring, ':');
						special_format=1;
						if(RLIB_VALUE_GET_AS_NUMBER(rval) >= 0)
							idx[0] = '\0';
						else
							formatstring = idx+1;				
					}

					len_formatstring = strlen(formatstring);

					for(i=0;i<len_formatstring;i++) {
						if(formatstring[i] == '%' && ((i+1) < len_formatstring && formatstring[i+1] != '%')) {
							int tchar;
							while(formatstring[i] != 's' && formatstring[i] != 'd' && i <=len_formatstring) {
								fmtstr[fpos++] = formatstring[i++];
							}
							fmtstr[fpos++] = formatstring[i];
							fmtstr[fpos] = '\0';
							tchar = fmtstr[fpos - 1];
							if ((tchar == 'd') || (tchar == 'i') || (tchar == 'n')) {
								if(RLIB_VALUE_IS_NUMBER(rval)) {
									rlib_number_sprintf(r, dest, fmtstr, rval, special_format, (gchar *)rf->xml_format.xml, rf->xml_format.line);
								} else {
									*dest = g_strdup_printf("!ERR_F_D");
									rlib_value_free(rval_fmtstr);
									setlocale(LC_ALL, current_locale);
									return FALSE;
								}
							} else if (tchar == 's') {
								if(RLIB_VALUE_IS_STRING(rval)) {
									rlib_string_sprintf(r, dest, fmtstr, rval);
								} else {
									*dest = g_strdup_printf("!ERR_F_S");
									rlib_value_free(rval_fmtstr);
									setlocale(LC_ALL, current_locale);
									return FALSE;
								}
							}
						} else {
//TODO: How to handle this???
//							buf[pos++] = formatstring[i];
//							if(formatstring[i] == '%')
//								i++;
						}
					}
//TODO: HOW TO HANDLE THIS					
//					buf[pos++] = '\0'; 
				}

			}
			rlib_value_free(rval_fmtstr);
		}
	}
	setlocale(LC_ALL, current_locale);
	return TRUE;
}

gchar *rlib_align_text(rlib *r, gchar **my_rtn, gchar *src, gint align, gint width) {
	gint len = 0;
	gchar *rtn;

	if(src != NULL)
		len = r_strlen(src);

	if(len > width) {
		rtn = *my_rtn = g_strdup(src);
	} else {
		rtn = *my_rtn  = g_malloc(width + 1);
		memset(rtn, 0, width+1);
		strcpy(rtn, src);
	}

	if(!OUTPUT(r)->do_align)
		return rtn;

	if(align == RLIB_ALIGN_LEFT || width == -1) {
	} else {
		if(align == RLIB_ALIGN_RIGHT) {        
			gint x = width - len;
			if(x > 0) {
				memset(rtn, ' ', x);
				g_strlcpy(rtn+x, src, width);
			}
		}
		if(align == RLIB_ALIGN_CENTER) {
			if(!(width > 0 && len > width)) {
				gint x = (width - len)/2;
				if(x > 0) {
					memset(rtn, ' ', x);
					g_strlcpy(rtn+x, src, width);
				}
			}
		}
	}
	return rtn;
}

GSList * rlib_format_split_string(rlib *r, gchar *data, gint width, gint max_lines, gchar new_line, gchar space, gint *line_count) {
	gint slen;
	gint spot = 0;
	gint end = 0;
	gint i;
	gint line_spot = 0;
	gboolean at_the_end = FALSE;
	GSList *list = NULL;
	
	slen = strlen(data);
	while(1) {
		gchar *this_line = g_malloc(width);
		memset(this_line, 0, width);
		end = spot + width-1;
		if(end > slen) {
			end = slen;
			at_the_end = TRUE;
		}
	
		line_spot = 0;
		for(i=spot;i<end;i++) {
			spot++;
			if(data[i] == new_line) 
				break;
			this_line[line_spot++] = data[i];
		}
		
		if(!at_the_end) {
			while(data[i] != space && data[i] != new_line) {
				this_line[--line_spot] = ' ';
				i--;
				spot--;
			}
			if(data[spot] == ' ')
				spot++;
		}
	
		list = g_slist_append(list, this_line);
		*line_count = *line_count + 1;
//r_error(r, "THIS LINE = %s\n", this_line);

		if(at_the_end == TRUE)
			break;
	
	}
	return list;
}
