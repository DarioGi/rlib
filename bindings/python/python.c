/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.21
 * 
 * This file is not intended to be easily readable and contains a number of 
 * coding conventions designed to improve portability and efficiency. Do not make
 * changes to this file unless you know what you are doing--modify the SWIG 
 * interface file instead. 
 * ----------------------------------------------------------------------------- */

#define SWIGPYTHON

#include "Python.h"

/*************************************************************** -*- c -*-
 * python/precommon.swg
 *
 * Rename all exported symbols from common.swg, to avoid symbol
 * clashes if multiple interpreters are included
 *
 ************************************************************************/

#define SWIG_TypeRegister    SWIG_Python_TypeRegister
#define SWIG_TypeCheck       SWIG_Python_TypeCheck
#define SWIG_TypeCast        SWIG_Python_TypeCast
#define SWIG_TypeDynamicCast SWIG_Python_TypeDynamicCast
#define SWIG_TypeName        SWIG_Python_TypeName
#define SWIG_TypeQuery       SWIG_Python_TypeQuery
#define SWIG_TypeClientData  SWIG_Python_TypeClientData
#define SWIG_PackData        SWIG_Python_PackData 
#define SWIG_UnpackData      SWIG_Python_UnpackData 


/***********************************************************************
 * common.swg
 *
 *     This file contains generic SWIG runtime support for pointer
 *     type checking as well as a few commonly used macros to control
 *     external linkage.
 *
 * Author : David Beazley (beazley@cs.uchicago.edu)
 *
 * Copyright (c) 1999-2000, The University of Chicago
 * 
 * This file may be freely redistributed without license or fee provided
 * this copyright message remains intact.
 ************************************************************************/

#include <string.h>

#if defined(_WIN32) || defined(__WIN32__) || defined(__CYGWIN__)
#  if defined(_MSC_VER) || defined(__GNUC__)
#    if defined(STATIC_LINKED)
#      define SWIGEXPORT(a) a
#      define SWIGIMPORT(a) extern a
#    else
#      define SWIGEXPORT(a) __declspec(dllexport) a
#      define SWIGIMPORT(a) extern a
#    endif
#  else
#    if defined(__BORLANDC__)
#      define SWIGEXPORT(a) a _export
#      define SWIGIMPORT(a) a _export
#    else
#      define SWIGEXPORT(a) a
#      define SWIGIMPORT(a) a
#    endif
#  endif
#else
#  define SWIGEXPORT(a) a
#  define SWIGIMPORT(a) a
#endif

#ifdef SWIG_GLOBAL
#  define SWIGRUNTIME(a) SWIGEXPORT(a)
#else
#  define SWIGRUNTIME(a) static a
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef void *(*swig_converter_func)(void *);
typedef struct swig_type_info *(*swig_dycast_func)(void **);

typedef struct swig_type_info {
  const char             *name;
  swig_converter_func     converter;
  const char             *str;
  void                   *clientdata;
  swig_dycast_func        dcast;
  struct swig_type_info  *next;
  struct swig_type_info  *prev;
} swig_type_info;

#ifdef SWIG_NOINCLUDE

SWIGIMPORT(swig_type_info *) SWIG_TypeRegister(swig_type_info *);
SWIGIMPORT(swig_type_info *) SWIG_TypeCheck(char *c, swig_type_info *);
SWIGIMPORT(void *)           SWIG_TypeCast(swig_type_info *, void *);
SWIGIMPORT(swig_type_info *) SWIG_TypeDynamicCast(swig_type_info *, void **);
SWIGIMPORT(const char *)     SWIG_TypeName(const swig_type_info *);
SWIGIMPORT(swig_type_info *) SWIG_TypeQuery(const char *);
SWIGIMPORT(void)             SWIG_TypeClientData(swig_type_info *, void *);
SWIGIMPORT(char *)           SWIG_PackData(char *, void *, int);
SWIGIMPORT(char *)           SWIG_UnpackData(char *, void *, int);

#else

static swig_type_info *swig_type_list = 0;

/* Register a type mapping with the type-checking */
SWIGRUNTIME(swig_type_info *)
SWIG_TypeRegister(swig_type_info *ti) {
  swig_type_info *tc, *head, *ret, *next;
  /* Check to see if this type has already been registered */
  tc = swig_type_list;
  while (tc) {
    if (strcmp(tc->name, ti->name) == 0) {
      /* Already exists in the table.  Just add additional types to the list */
      if (tc->clientdata) ti->clientdata = tc->clientdata;
      head = tc;
      next = tc->next;
      goto l1;
    }
    tc = tc->prev;
  }
  head = ti;
  next = 0;

  /* Place in list */
  ti->prev = swig_type_list;
  swig_type_list = ti;

  /* Build linked lists */
  l1:
  ret = head;
  tc = ti + 1;
  /* Patch up the rest of the links */
  while (tc->name) {
    head->next = tc;
    tc->prev = head;
    head = tc;
    tc++;
  }
  if (next) next->prev = head;
  head->next = next;
  return ret;
}

/* Check the typename */
SWIGRUNTIME(swig_type_info *) 
SWIG_TypeCheck(char *c, swig_type_info *ty) {
  swig_type_info *s;
  if (!ty) return 0;        /* Void pointer */
  s = ty->next;             /* First element always just a name */
  do {
    if (strcmp(s->name,c) == 0) {
      if (s == ty->next) return s;
      /* Move s to the top of the linked list */
      s->prev->next = s->next;
      if (s->next) {
        s->next->prev = s->prev;
      }
      /* Insert s as second element in the list */
      s->next = ty->next;
      if (ty->next) ty->next->prev = s;
      ty->next = s;
      s->prev = ty;
      return s;
    }
    s = s->next;
  } while (s && (s != ty->next));
  return 0;
}

/* Cast a pointer up an inheritance hierarchy */
SWIGRUNTIME(void *) 
SWIG_TypeCast(swig_type_info *ty, void *ptr) {
  if ((!ty) || (!ty->converter)) return ptr;
  return (*ty->converter)(ptr);
}

/* Set the clientdata field for a type */
SWIGRUNTIME(void)
SWIG_TypeClientData(swig_type_info *ti, void *clientdata) {
  swig_type_info *tc, *equiv;
  if (ti->clientdata == clientdata) return;
  ti->clientdata = clientdata;
  equiv = ti->next;
  while (equiv) {
    if (!equiv->converter) {
      tc = swig_type_list;
      while (tc) {
        if ((strcmp(tc->name, equiv->name) == 0))
          SWIG_TypeClientData(tc,clientdata);
        tc = tc->prev;
      }
    }
    equiv = equiv->next;
  }
}

/* Pack binary data into a string */
SWIGRUNTIME(char *)
SWIG_PackData(char *c, void *ptr, int sz) {
  static char hex[17] = "0123456789abcdef";
  int i;
  unsigned char *u = (unsigned char *) ptr;
  register unsigned char uu;
  for (i = 0; i < sz; i++,u++) {
    uu = *u;
    *(c++) = hex[(uu & 0xf0) >> 4];
    *(c++) = hex[uu & 0xf];
  }
  return c;
}

/* Unpack binary data from a string */
SWIGRUNTIME(char *)
SWIG_UnpackData(char *c, void *ptr, int sz) {
  register unsigned char uu = 0;
  register int d;
  unsigned char *u = (unsigned char *) ptr;
  int i;
  for (i = 0; i < sz; i++, u++) {
    d = *(c++);
    if ((d >= '0') && (d <= '9'))
      uu = ((d - '0') << 4);
    else if ((d >= 'a') && (d <= 'f'))
      uu = ((d - ('a'-10)) << 4);
    d = *(c++);
    if ((d >= '0') && (d <= '9'))
      uu |= (d - '0');
    else if ((d >= 'a') && (d <= 'f'))
      uu |= (d - ('a'-10));
    *u = uu;
  }
  return c;
}

#endif

#ifdef __cplusplus
}
#endif

/***********************************************************************
 * python.swg
 *
 *     This file contains the runtime support for Python modules
 *     and includes code for managing global variables and pointer
 *     type checking.
 *
 * Author : David Beazley (beazley@cs.uchicago.edu)
 ************************************************************************/

#include "Python.h"

#ifdef __cplusplus
extern "C" {
#endif

#define SWIG_PY_INT     1
#define SWIG_PY_FLOAT   2
#define SWIG_PY_STRING  3
#define SWIG_PY_POINTER 4
#define SWIG_PY_BINARY  5

/* Flags for pointer conversion */

#define SWIG_POINTER_EXCEPTION     0x1
#define SWIG_POINTER_DISOWN        0x2

/* Exception handling in wrappers */
#define SWIG_fail   goto fail

/* Constant information structure */
typedef struct swig_const_info {
    int type;
    char *name;
    long lvalue;
    double dvalue;
    void   *pvalue;
    swig_type_info **ptype;
} swig_const_info;

/* Common SWIG API */
#define SWIG_ConvertPtr(obj, pp, type, flags) \
  SWIG_Python_ConvertPtr(obj, pp, type, flags)
#define SWIG_NewPointerObj(p, type, flags) \
  SWIG_Python_NewPointerObj(p, type, flags)
#define SWIG_MustGetPtr(p, type, argnum, flags) \
  SWIG_Python_MustGetPtr(p, type, argnum, flags)

/* Python-specific SWIG API */
#define SWIG_newvarlink() \
  SWIG_Python_newvarlink()
#define SWIG_addvarlink(p, name, get_attr, set_attr) \
  SWIG_Python_addvarlink(p, name, get_attr, set_attr)
#define SWIG_ConvertPacked(obj, ptr, sz, ty, flags) \
  SWIG_Python_ConvertPacked(obj, ptr, sz, ty, flags)
#define SWIG_NewPackedObj(ptr, sz, type) \
  SWIG_Python_NewPackedObj(ptr, sz, type)
#define SWIG_InstallConstants(d, constants) \
  SWIG_Python_InstallConstants(d, constants)

#ifdef SWIG_NOINCLUDE

SWIGIMPORT(int)               SWIG_Python_ConvertPtr(PyObject *, void **, swig_type_info *, int);
SWIGIMPORT(PyObject *)        SWIG_Python_NewPointerObj(void *, swig_type_info *,int own);
SWIGIMPORT(void *)            SWIG_Python_MustGetPtr(PyObject *, swig_type_info *, int, int);
SWIGIMPORT(PyObject *)        SWIG_Python_newvarlink(void);
SWIGIMPORT(void)              SWIG_Python_addvarlink(PyObject *, char *, PyObject *(*)(void), int (*)(PyObject *));
SWIGIMPORT(int)               SWIG_Python_ConvertPacked(PyObject *, void *, int sz, swig_type_info *, int);
SWIGIMPORT(PyObject *)        SWIG_Python_NewPackedObj(void *, int sz, swig_type_info *);
SWIGIMPORT(void)              SWIG_Python_InstallConstants(PyObject *d, swig_const_info constants[]);

#else

/* -----------------------------------------------------------------------------
 * global variable support code.
 * ----------------------------------------------------------------------------- */

typedef struct swig_globalvar {   
  char       *name;                  /* Name of global variable */
  PyObject *(*get_attr)(void);       /* Return the current value */
  int       (*set_attr)(PyObject *); /* Set the value */
  struct swig_globalvar *next;
} swig_globalvar;

typedef struct swig_varlinkobject {
  PyObject_HEAD
  swig_globalvar *vars;
} swig_varlinkobject;

static PyObject *
swig_varlink_repr(swig_varlinkobject *v) {
  v = v;
  return PyString_FromString("<Global variables>");
}

static int
swig_varlink_print(swig_varlinkobject *v, FILE *fp, int flags) {
  swig_globalvar  *var;
  flags = flags;
  fprintf(fp,"Global variables { ");
  for (var = v->vars; var; var=var->next) {
    fprintf(fp,"%s", var->name);
    if (var->next) fprintf(fp,", ");
  }
  fprintf(fp," }\n");
  return 0;
}

static PyObject *
swig_varlink_getattr(swig_varlinkobject *v, char *n) {
  swig_globalvar *var = v->vars;
  while (var) {
    if (strcmp(var->name,n) == 0) {
      return (*var->get_attr)();
    }
    var = var->next;
  }
  PyErr_SetString(PyExc_NameError,"Unknown C global variable");
  return NULL;
}

static int
swig_varlink_setattr(swig_varlinkobject *v, char *n, PyObject *p) {
  swig_globalvar *var = v->vars;
  while (var) {
    if (strcmp(var->name,n) == 0) {
      return (*var->set_attr)(p);
    }
    var = var->next;
  }
  PyErr_SetString(PyExc_NameError,"Unknown C global variable");
  return 1;
}

statichere PyTypeObject varlinktype = {
  PyObject_HEAD_INIT(0)              
  0,
  (char *)"swigvarlink",              /* Type name    */
  sizeof(swig_varlinkobject),         /* Basic size   */
  0,                                  /* Itemsize     */
  0,                                  /* Deallocator  */ 
  (printfunc) swig_varlink_print,     /* Print        */
  (getattrfunc) swig_varlink_getattr, /* get attr     */
  (setattrfunc) swig_varlink_setattr, /* Set attr     */
  0,                                  /* tp_compare   */
  (reprfunc) swig_varlink_repr,       /* tp_repr      */    
  0,                                  /* tp_as_number */
  0,                                  /* tp_as_mapping*/
  0,                                  /* tp_hash      */
};

/* Create a variable linking object for use later */
SWIGRUNTIME(PyObject *)
SWIG_Python_newvarlink(void) {
  swig_varlinkobject *result = 0;
  result = PyMem_NEW(swig_varlinkobject,1);
  varlinktype.ob_type = &PyType_Type;    /* Patch varlinktype into a PyType */
  result->ob_type = &varlinktype;
  result->vars = 0;
  result->ob_refcnt = 0;
  Py_XINCREF((PyObject *) result);
  return ((PyObject*) result);
}

/* Convert a pointer value */
SWIGRUNTIME(int)
SWIG_Python_ConvertPtr(PyObject *obj, void **ptr, swig_type_info *ty, int flags) {
  swig_type_info *tc;
  char  *c = 0;
  static PyObject *SWIG_this = 0;
  int    newref = 0;
  PyObject  *pyobj = 0;

  if (!obj) return 0;
  if (obj == Py_None) {
    *ptr = 0;
    return 0;
  }
#ifdef SWIG_COBJECT_TYPES
  if (!(PyCObject_Check(obj))) {
    if (!SWIG_this)
      SWIG_this = PyString_FromString("this");
    pyobj = obj;
    obj = PyObject_GetAttr(obj,SWIG_this);
    newref = 1;
    if (!obj) goto type_error;
    if (!PyCObject_Check(obj)) {
      Py_DECREF(obj);
      goto type_error;
    }
  }  
  *ptr = PyCObject_AsVoidPtr(obj);
  c = (char *) PyCObject_GetDesc(obj);
  if (newref) Py_DECREF(obj);
  goto cobject;
#else
  if (!(PyString_Check(obj))) {
    if (!SWIG_this)
      SWIG_this = PyString_FromString("this");
    pyobj = obj;
    obj = PyObject_GetAttr(obj,SWIG_this);
    newref = 1;
    if (!obj) goto type_error;
    if (!PyString_Check(obj)) {
      Py_DECREF(obj);
      goto type_error;
    }
  } 
  c = PyString_AsString(obj);
  /* Pointer values must start with leading underscore */
  if (*c != '_') {
    *ptr = (void *) 0;
    if (strcmp(c,"NULL") == 0) {
      if (newref) { Py_DECREF(obj); }
      return 0;
    } else {
      if (newref) { Py_DECREF(obj); }
      goto type_error;
    }
  }
  c++;
  c = SWIG_UnpackData(c,ptr,sizeof(void *));
  if (newref) { Py_DECREF(obj); }
#endif

#ifdef SWIG_COBJECT_TYPES
cobject:
#endif

  if (ty) {
    tc = SWIG_TypeCheck(c,ty);
    if (!tc) goto type_error;
    *ptr = SWIG_TypeCast(tc,(void*) *ptr);
  }

  if ((pyobj) && (flags & SWIG_POINTER_DISOWN)) {
    PyObject *zero = PyInt_FromLong(0);
    PyObject_SetAttrString(pyobj,(char*)"thisown",zero);
    Py_DECREF(zero);
  }
  return 0;

type_error:
  if (flags & SWIG_POINTER_EXCEPTION) {
    if (ty && c) {
      char *temp = (char *) malloc(64+strlen(ty->name)+strlen(c));
      sprintf(temp,"Type error. Got %s, expected %s", c, ty->name);
      PyErr_SetString(PyExc_TypeError, temp);
      free((char *) temp);
    } else {
      PyErr_SetString(PyExc_TypeError,"Expected a pointer");
    }
  }
  return -1;
}

/* Create a new pointer object */
SWIGRUNTIME(PyObject *)
SWIG_Python_NewPointerObj(void *ptr, swig_type_info *type, int own) {
  PyObject *robj;
  if (!ptr) {
    Py_INCREF(Py_None);
    return Py_None;
  }
#ifdef SWIG_COBJECT_TYPES
  robj = PyCObject_FromVoidPtrAndDesc((void *) ptr, (char *) type->name, NULL);
#else
  {
    char result[1024];
    char *r = result;
    *(r++) = '_';
    r = SWIG_PackData(r,&ptr,sizeof(void *));
    strcpy(r,type->name);
    robj = PyString_FromString(result);
  }
#endif
  if (!robj || (robj == Py_None)) return robj;
  if (type->clientdata) {
    PyObject *inst;
    PyObject *args = Py_BuildValue((char*)"(O)", robj);
    Py_DECREF(robj);
    inst = PyObject_CallObject((PyObject *) type->clientdata, args);
    Py_DECREF(args);
    if (inst) {
      if (own) {
        PyObject *n = PyInt_FromLong(1);
        PyObject_SetAttrString(inst,(char*)"thisown",n);
        Py_DECREF(n);
      }
      robj = inst;
    }
  }
  return robj;
}

SWIGRUNTIME(PyObject *)
SWIG_Python_NewPackedObj(void *ptr, int sz, swig_type_info *type) {
  char result[1024];
  char *r = result;
  if ((2*sz + 1 + strlen(type->name)) > 1000) return 0;
  *(r++) = '_';
  r = SWIG_PackData(r,ptr,sz);
  strcpy(r,type->name);
  return PyString_FromString(result);
}

/* Install Constants */
SWIGRUNTIME(void)
SWIG_Python_InstallConstants(PyObject *d, swig_const_info constants[]) {
  int i;
  PyObject *obj;
  for (i = 0; constants[i].type; i++) {
    switch(constants[i].type) {
    case SWIG_PY_INT:
      obj = PyInt_FromLong(constants[i].lvalue);
      break;
    case SWIG_PY_FLOAT:
      obj = PyFloat_FromDouble(constants[i].dvalue);
      break;
    case SWIG_PY_STRING:
      obj = PyString_FromString((char *) constants[i].pvalue);
      break;
    case SWIG_PY_POINTER:
      obj = SWIG_NewPointerObj(constants[i].pvalue, *(constants[i]).ptype,0);
      break;
    case SWIG_PY_BINARY:
      obj = SWIG_NewPackedObj(constants[i].pvalue, constants[i].lvalue, *(constants[i].ptype));
      break;
    default:
      obj = 0;
      break;
    }
    if (obj) {
      PyDict_SetItemString(d,constants[i].name,obj);
      Py_DECREF(obj);
    }
  }
}

#endif

/* Contract support */

#define SWIG_contract_assert(expr, msg) if (!(expr)) { PyErr_SetString(PyExc_RuntimeError, (char *) msg ); goto fail; } else

#ifdef __cplusplus
}
#endif


/* -------- TYPES TABLE (BEGIN) -------- */

#define  SWIGTYPE_p_rlib swig_types[0] 
static swig_type_info *swig_types[2];

/* -------- TYPES TABLE (END) -------- */


/*-----------------------------------------------
              @(target):= _librlib.so
  ------------------------------------------------*/
#define SWIG_init    initlibrlib

#define SWIG_name    "librlib"

#include <rlib.h>
 
#ifdef __cplusplus
extern "C" {
#endif
static PyObject *_wrap_rlib_init(PyObject *self, PyObject *args) {
    PyObject *resultobj;
    rlib *result;
    
    if(!PyArg_ParseTuple(args,(char *)":rlib_init")) goto fail;
    result = (rlib *)rlib_init();
    
    resultobj = SWIG_NewPointerObj((void *) result, SWIGTYPE_p_rlib, 0);
    return resultobj;
    fail:
    return NULL;
}


static PyObject *_wrap_rlib_add_datasource_mysql(PyObject *self, PyObject *args) {
    PyObject *resultobj;
    rlib *arg1 = (rlib *) 0 ;
    char *arg2 ;
    char *arg3 ;
    char *arg4 ;
    char *arg5 ;
    char *arg6 ;
    int result;
    PyObject * obj0 = 0 ;
    
    if(!PyArg_ParseTuple(args,(char *)"Osssss:rlib_add_datasource_mysql",&obj0,&arg2,&arg3,&arg4,&arg5,&arg6)) goto fail;
    if ((SWIG_ConvertPtr(obj0,(void **) &arg1, SWIGTYPE_p_rlib,SWIG_POINTER_EXCEPTION | 0 )) == -1) SWIG_fail;
    result = (int)rlib_add_datasource_mysql(arg1,arg2,arg3,arg4,arg5,arg6);
    
    resultobj = PyInt_FromLong((long)result);
    return resultobj;
    fail:
    return NULL;
}


static PyObject *_wrap_rlib_add_datasource_postgre(PyObject *self, PyObject *args) {
    PyObject *resultobj;
    rlib *arg1 = (rlib *) 0 ;
    char *arg2 ;
    char *arg3 ;
    int result;
    PyObject * obj0 = 0 ;
    
    if(!PyArg_ParseTuple(args,(char *)"Oss:rlib_add_datasource_postgre",&obj0,&arg2,&arg3)) goto fail;
    if ((SWIG_ConvertPtr(obj0,(void **) &arg1, SWIGTYPE_p_rlib,SWIG_POINTER_EXCEPTION | 0 )) == -1) SWIG_fail;
    result = (int)rlib_add_datasource_postgre(arg1,arg2,arg3);
    
    resultobj = PyInt_FromLong((long)result);
    return resultobj;
    fail:
    return NULL;
}


static PyObject *_wrap_rlib_add_query_as(PyObject *self, PyObject *args) {
    PyObject *resultobj;
    rlib *arg1 = (rlib *) 0 ;
    char *arg2 ;
    char *arg3 ;
    char *arg4 ;
    int result;
    PyObject * obj0 = 0 ;
    
    if(!PyArg_ParseTuple(args,(char *)"Osss:rlib_add_query_as",&obj0,&arg2,&arg3,&arg4)) goto fail;
    if ((SWIG_ConvertPtr(obj0,(void **) &arg1, SWIGTYPE_p_rlib,SWIG_POINTER_EXCEPTION | 0 )) == -1) SWIG_fail;
    result = (int)rlib_add_query_as(arg1,arg2,arg3,arg4);
    
    resultobj = PyInt_FromLong((long)result);
    return resultobj;
    fail:
    return NULL;
}


static PyObject *_wrap_rlib_add_report(PyObject *self, PyObject *args) {
    PyObject *resultobj;
    rlib *arg1 = (rlib *) 0 ;
    char *arg2 ;
    char *arg3 ;
    int result;
    PyObject * obj0 = 0 ;
    
    if(!PyArg_ParseTuple(args,(char *)"Oss:rlib_add_report",&obj0,&arg2,&arg3)) goto fail;
    if ((SWIG_ConvertPtr(obj0,(void **) &arg1, SWIGTYPE_p_rlib,SWIG_POINTER_EXCEPTION | 0 )) == -1) SWIG_fail;
    result = (int)rlib_add_report(arg1,arg2,arg3);
    
    resultobj = PyInt_FromLong((long)result);
    return resultobj;
    fail:
    return NULL;
}


static PyObject *_wrap_rlib_execute(PyObject *self, PyObject *args) {
    PyObject *resultobj;
    rlib *arg1 = (rlib *) 0 ;
    int result;
    PyObject * obj0 = 0 ;
    
    if(!PyArg_ParseTuple(args,(char *)"O:rlib_execute",&obj0)) goto fail;
    if ((SWIG_ConvertPtr(obj0,(void **) &arg1, SWIGTYPE_p_rlib,SWIG_POINTER_EXCEPTION | 0 )) == -1) SWIG_fail;
    result = (int)rlib_execute(arg1);
    
    resultobj = PyInt_FromLong((long)result);
    return resultobj;
    fail:
    return NULL;
}


static PyObject *_wrap_rlib_set_output_format_from_text(PyObject *self, PyObject *args) {
    PyObject *resultobj;
    rlib *arg1 = (rlib *) 0 ;
    char *arg2 ;
    int result;
    PyObject * obj0 = 0 ;
    
    if(!PyArg_ParseTuple(args,(char *)"Os:rlib_set_output_format_from_text",&obj0,&arg2)) goto fail;
    if ((SWIG_ConvertPtr(obj0,(void **) &arg1, SWIGTYPE_p_rlib,SWIG_POINTER_EXCEPTION | 0 )) == -1) SWIG_fail;
    result = (int)rlib_set_output_format_from_text(arg1,arg2);
    
    resultobj = PyInt_FromLong((long)result);
    return resultobj;
    fail:
    return NULL;
}


static PyObject *_wrap_rlib_spool(PyObject *self, PyObject *args) {
    PyObject *resultobj;
    rlib *arg1 = (rlib *) 0 ;
    int result;
    PyObject * obj0 = 0 ;
    
    if(!PyArg_ParseTuple(args,(char *)"O:rlib_spool",&obj0)) goto fail;
    if ((SWIG_ConvertPtr(obj0,(void **) &arg1, SWIGTYPE_p_rlib,SWIG_POINTER_EXCEPTION | 0 )) == -1) SWIG_fail;
    result = (int)rlib_spool(arg1);
    
    resultobj = PyInt_FromLong((long)result);
    return resultobj;
    fail:
    return NULL;
}


static PyObject *_wrap_rlib_free(PyObject *self, PyObject *args) {
    PyObject *resultobj;
    rlib *arg1 = (rlib *) 0 ;
    int result;
    PyObject * obj0 = 0 ;
    
    if(!PyArg_ParseTuple(args,(char *)"O:rlib_free",&obj0)) goto fail;
    if ((SWIG_ConvertPtr(obj0,(void **) &arg1, SWIGTYPE_p_rlib,SWIG_POINTER_EXCEPTION | 0 )) == -1) SWIG_fail;
    result = (int)rlib_free(arg1);
    
    resultobj = PyInt_FromLong((long)result);
    return resultobj;
    fail:
    return NULL;
}


static PyObject *_wrap_rlib_get_output(PyObject *self, PyObject *args) {
    PyObject *resultobj;
    rlib *arg1 = (rlib *) 0 ;
    char *result;
    PyObject * obj0 = 0 ;
    
    if(!PyArg_ParseTuple(args,(char *)"O:rlib_get_output",&obj0)) goto fail;
    if ((SWIG_ConvertPtr(obj0,(void **) &arg1, SWIGTYPE_p_rlib,SWIG_POINTER_EXCEPTION | 0 )) == -1) SWIG_fail;
    result = (char *)rlib_get_output(arg1);
    
    resultobj = result ? PyString_FromString(result) : Py_BuildValue((char*)"");
    return resultobj;
    fail:
    return NULL;
}


static PyObject *_wrap_rlib_get_output_length(PyObject *self, PyObject *args) {
    PyObject *resultobj;
    rlib *arg1 = (rlib *) 0 ;
    long result;
    PyObject * obj0 = 0 ;
    
    if(!PyArg_ParseTuple(args,(char *)"O:rlib_get_output_length",&obj0)) goto fail;
    if ((SWIG_ConvertPtr(obj0,(void **) &arg1, SWIGTYPE_p_rlib,SWIG_POINTER_EXCEPTION | 0 )) == -1) SWIG_fail;
    result = (long)rlib_get_output_length(arg1);
    
    resultobj = PyInt_FromLong((long)result);
    return resultobj;
    fail:
    return NULL;
}


static PyObject *_wrap_rlib_mysql_report(PyObject *self, PyObject *args) {
    PyObject *resultobj;
    char *arg1 ;
    char *arg2 ;
    char *arg3 ;
    char *arg4 ;
    char *arg5 ;
    char *arg6 ;
    char *arg7 ;
    int result;
    
    if(!PyArg_ParseTuple(args,(char *)"sssssss:rlib_mysql_report",&arg1,&arg2,&arg3,&arg4,&arg5,&arg6,&arg7)) goto fail;
    result = (int)rlib_mysql_report(arg1,arg2,arg3,arg4,arg5,arg6,arg7);
    
    resultobj = PyInt_FromLong((long)result);
    return resultobj;
    fail:
    return NULL;
}


static PyObject *_wrap_rlib_postgre_report(PyObject *self, PyObject *args) {
    PyObject *resultobj;
    char *arg1 ;
    char *arg2 ;
    char *arg3 ;
    char *arg4 ;
    int result;
    
    if(!PyArg_ParseTuple(args,(char *)"ssss:rlib_postgre_report",&arg1,&arg2,&arg3,&arg4)) goto fail;
    result = (int)rlib_postgre_report(arg1,arg2,arg3,arg4);
    
    resultobj = PyInt_FromLong((long)result);
    return resultobj;
    fail:
    return NULL;
}


static PyObject *_wrap_rlib_add_datasource_odbc(PyObject *self, PyObject *args) {
    PyObject *resultobj;
    rlib *arg1 = (rlib *) 0 ;
    char *arg2 ;
    char *arg3 ;
    char *arg4 ;
    char *arg5 ;
    int result;
    PyObject * obj0 = 0 ;
    
    if(!PyArg_ParseTuple(args,(char *)"Ossss:rlib_add_datasource_odbc",&obj0,&arg2,&arg3,&arg4,&arg5)) goto fail;
    if ((SWIG_ConvertPtr(obj0,(void **) &arg1, SWIGTYPE_p_rlib,SWIG_POINTER_EXCEPTION | 0 )) == -1) SWIG_fail;
    result = (int)rlib_add_datasource_odbc(arg1,arg2,arg3,arg4,arg5);
    
    resultobj = PyInt_FromLong((long)result);
    return resultobj;
    fail:
    return NULL;
}


static PyObject *_wrap_rlib_add_resultset_follower(PyObject *self, PyObject *args) {
    PyObject *resultobj;
    rlib *arg1 = (rlib *) 0 ;
    char *arg2 ;
    char *arg3 ;
    int result;
    PyObject * obj0 = 0 ;
    
    if(!PyArg_ParseTuple(args,(char *)"Oss:rlib_add_resultset_follower",&obj0,&arg2,&arg3)) goto fail;
    if ((SWIG_ConvertPtr(obj0,(void **) &arg1, SWIGTYPE_p_rlib,SWIG_POINTER_EXCEPTION | 0 )) == -1) SWIG_fail;
    result = (int)rlib_add_resultset_follower(arg1,arg2,arg3);
    
    resultobj = PyInt_FromLong((long)result);
    return resultobj;
    fail:
    return NULL;
}


static PyObject *_wrap_rlib_add_parameter(PyObject *self, PyObject *args) {
    PyObject *resultobj;
    rlib *arg1 = (rlib *) 0 ;
    char *arg2 ;
    char *arg3 ;
    int result;
    PyObject * obj0 = 0 ;
    
    if(!PyArg_ParseTuple(args,(char *)"Oss:rlib_add_parameter",&obj0,&arg2,&arg3)) goto fail;
    if ((SWIG_ConvertPtr(obj0,(void **) &arg1, SWIGTYPE_p_rlib,SWIG_POINTER_EXCEPTION | 0 )) == -1) SWIG_fail;
    result = (int)rlib_add_parameter(arg1,(char const *)arg2,(char const *)arg3);
    
    resultobj = PyInt_FromLong((long)result);
    return resultobj;
    fail:
    return NULL;
}


static PyObject *_wrap_rlib_version(PyObject *self, PyObject *args) {
    PyObject *resultobj;
    char *result;
    
    if(!PyArg_ParseTuple(args,(char *)":rlib_version")) goto fail;
    result = (char *)rlib_version();
    
    resultobj = result ? PyString_FromString(result) : Py_BuildValue((char*)"");
    return resultobj;
    fail:
    return NULL;
}


static PyObject *_wrap_rlib_set_output_encoding(PyObject *self, PyObject *args) {
    PyObject *resultobj;
    rlib *arg1 = (rlib *) 0 ;
    char *arg2 ;
    PyObject * obj0 = 0 ;
    
    if(!PyArg_ParseTuple(args,(char *)"Os:rlib_set_output_encoding",&obj0,&arg2)) goto fail;
    if ((SWIG_ConvertPtr(obj0,(void **) &arg1, SWIGTYPE_p_rlib,SWIG_POINTER_EXCEPTION | 0 )) == -1) SWIG_fail;
    rlib_set_output_encoding(arg1,(char const *)arg2);
    
    Py_INCREF(Py_None); resultobj = Py_None;
    return resultobj;
    fail:
    return NULL;
}


static PyObject *_wrap_rlib_set_report_output_encoding(PyObject *self, PyObject *args) {
    PyObject *resultobj;
    rlib *arg1 = (rlib *) 0 ;
    int arg2 ;
    char *arg3 ;
    PyObject * obj0 = 0 ;
    
    if(!PyArg_ParseTuple(args,(char *)"Ois:rlib_set_report_output_encoding",&obj0,&arg2,&arg3)) goto fail;
    if ((SWIG_ConvertPtr(obj0,(void **) &arg1, SWIGTYPE_p_rlib,SWIG_POINTER_EXCEPTION | 0 )) == -1) SWIG_fail;
    rlib_set_report_output_encoding(arg1,arg2,(char const *)arg3);
    
    Py_INCREF(Py_None); resultobj = Py_None;
    return resultobj;
    fail:
    return NULL;
}


static PyObject *_wrap_rlib_set_pdf_font(PyObject *self, PyObject *args) {
    PyObject *resultobj;
    rlib *arg1 = (rlib *) 0 ;
    char *arg2 ;
    char *arg3 ;
    PyObject * obj0 = 0 ;
    
    if(!PyArg_ParseTuple(args,(char *)"Oss:rlib_set_pdf_font",&obj0,&arg2,&arg3)) goto fail;
    if ((SWIG_ConvertPtr(obj0,(void **) &arg1, SWIGTYPE_p_rlib,SWIG_POINTER_EXCEPTION | 0 )) == -1) SWIG_fail;
    rlib_set_pdf_font(arg1,(char const *)arg2,(char const *)arg3);
    
    Py_INCREF(Py_None); resultobj = Py_None;
    return resultobj;
    fail:
    return NULL;
}


static PyObject *_wrap_rlib_set_pdf_font_directories(PyObject *self, PyObject *args) {
    PyObject *resultobj;
    rlib *arg1 = (rlib *) 0 ;
    char *arg2 ;
    char *arg3 ;
    PyObject * obj0 = 0 ;
    
    if(!PyArg_ParseTuple(args,(char *)"Oss:rlib_set_pdf_font_directories",&obj0,&arg2,&arg3)) goto fail;
    if ((SWIG_ConvertPtr(obj0,(void **) &arg1, SWIGTYPE_p_rlib,SWIG_POINTER_EXCEPTION | 0 )) == -1) SWIG_fail;
    rlib_set_pdf_font_directories(arg1,(char const *)arg2,(char const *)arg3);
    
    Py_INCREF(Py_None); resultobj = Py_None;
    return resultobj;
    fail:
    return NULL;
}


static PyMethodDef SwigMethods[] = {
	 { (char *)"rlib_init", _wrap_rlib_init, METH_VARARGS },
	 { (char *)"rlib_add_datasource_mysql", _wrap_rlib_add_datasource_mysql, METH_VARARGS },
	 { (char *)"rlib_add_datasource_postgre", _wrap_rlib_add_datasource_postgre, METH_VARARGS },
	 { (char *)"rlib_add_query_as", _wrap_rlib_add_query_as, METH_VARARGS },
	 { (char *)"rlib_add_report", _wrap_rlib_add_report, METH_VARARGS },
	 { (char *)"rlib_execute", _wrap_rlib_execute, METH_VARARGS },
	 { (char *)"rlib_set_output_format_from_text", _wrap_rlib_set_output_format_from_text, METH_VARARGS },
	 { (char *)"rlib_spool", _wrap_rlib_spool, METH_VARARGS },
	 { (char *)"rlib_free", _wrap_rlib_free, METH_VARARGS },
	 { (char *)"rlib_get_output", _wrap_rlib_get_output, METH_VARARGS },
	 { (char *)"rlib_get_output_length", _wrap_rlib_get_output_length, METH_VARARGS },
	 { (char *)"rlib_mysql_report", _wrap_rlib_mysql_report, METH_VARARGS },
	 { (char *)"rlib_postgre_report", _wrap_rlib_postgre_report, METH_VARARGS },
	 { (char *)"rlib_add_datasource_odbc", _wrap_rlib_add_datasource_odbc, METH_VARARGS },
	 { (char *)"rlib_add_resultset_follower", _wrap_rlib_add_resultset_follower, METH_VARARGS },
	 { (char *)"rlib_add_parameter", _wrap_rlib_add_parameter, METH_VARARGS },
	 { (char *)"rlib_version", _wrap_rlib_version, METH_VARARGS },
	 { (char *)"rlib_set_output_encoding", _wrap_rlib_set_output_encoding, METH_VARARGS },
	 { (char *)"rlib_set_report_output_encoding", _wrap_rlib_set_report_output_encoding, METH_VARARGS },
	 { (char *)"rlib_set_pdf_font", _wrap_rlib_set_pdf_font, METH_VARARGS },
	 { (char *)"rlib_set_pdf_font_directories", _wrap_rlib_set_pdf_font_directories, METH_VARARGS },
	 { NULL, NULL }
};


/* -------- TYPE CONVERSION AND EQUIVALENCE RULES (BEGIN) -------- */

static swig_type_info _swigt__p_rlib[] = {{"_p_rlib", 0, "rlib *", 0},{"_p_rlib"},{0}};

static swig_type_info *swig_types_initial[] = {
_swigt__p_rlib, 
0
};


/* -------- TYPE CONVERSION AND EQUIVALENCE RULES (END) -------- */

static swig_const_info swig_const_table[] = {
{0}};

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C"
#endif
SWIGEXPORT(void) SWIG_init(void) {
    static PyObject *SWIG_globals = 0; 
    static int       typeinit = 0;
    PyObject *m, *d;
    int       i;
    if (!SWIG_globals) SWIG_globals = SWIG_newvarlink();
    m = Py_InitModule((char *) SWIG_name, SwigMethods);
    d = PyModule_GetDict(m);
    
    if (!typeinit) {
        for (i = 0; swig_types_initial[i]; i++) {
            swig_types[i] = SWIG_TypeRegister(swig_types_initial[i]);
        }
        typeinit = 1;
    }
    SWIG_InstallConstants(d,swig_const_table);
    
}

