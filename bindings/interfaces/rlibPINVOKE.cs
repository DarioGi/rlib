//------------------------------------------------------------------------------
// <auto-generated />
//
// This file was automatically generated by SWIG (http://www.swig.org).
// Version 3.0.7
//
// Do not make changes to this file unless you know what you are doing--modify
// the SWIG interface file instead.
//------------------------------------------------------------------------------


class rlibPINVOKE {

  protected class SWIGExceptionHelper {

    public delegate void ExceptionDelegate(string message);
    public delegate void ExceptionArgumentDelegate(string message, string paramName);

    static ExceptionDelegate applicationDelegate = new ExceptionDelegate(SetPendingApplicationException);
    static ExceptionDelegate arithmeticDelegate = new ExceptionDelegate(SetPendingArithmeticException);
    static ExceptionDelegate divideByZeroDelegate = new ExceptionDelegate(SetPendingDivideByZeroException);
    static ExceptionDelegate indexOutOfRangeDelegate = new ExceptionDelegate(SetPendingIndexOutOfRangeException);
    static ExceptionDelegate invalidCastDelegate = new ExceptionDelegate(SetPendingInvalidCastException);
    static ExceptionDelegate invalidOperationDelegate = new ExceptionDelegate(SetPendingInvalidOperationException);
    static ExceptionDelegate ioDelegate = new ExceptionDelegate(SetPendingIOException);
    static ExceptionDelegate nullReferenceDelegate = new ExceptionDelegate(SetPendingNullReferenceException);
    static ExceptionDelegate outOfMemoryDelegate = new ExceptionDelegate(SetPendingOutOfMemoryException);
    static ExceptionDelegate overflowDelegate = new ExceptionDelegate(SetPendingOverflowException);
    static ExceptionDelegate systemDelegate = new ExceptionDelegate(SetPendingSystemException);

    static ExceptionArgumentDelegate argumentDelegate = new ExceptionArgumentDelegate(SetPendingArgumentException);
    static ExceptionArgumentDelegate argumentNullDelegate = new ExceptionArgumentDelegate(SetPendingArgumentNullException);
    static ExceptionArgumentDelegate argumentOutOfRangeDelegate = new ExceptionArgumentDelegate(SetPendingArgumentOutOfRangeException);

    [global::System.Runtime.InteropServices.DllImport("rlibcsharp", EntryPoint="SWIGRegisterExceptionCallbacks_rlib")]
    public static extern void SWIGRegisterExceptionCallbacks_rlib(
                                ExceptionDelegate applicationDelegate,
                                ExceptionDelegate arithmeticDelegate,
                                ExceptionDelegate divideByZeroDelegate, 
                                ExceptionDelegate indexOutOfRangeDelegate, 
                                ExceptionDelegate invalidCastDelegate,
                                ExceptionDelegate invalidOperationDelegate,
                                ExceptionDelegate ioDelegate,
                                ExceptionDelegate nullReferenceDelegate,
                                ExceptionDelegate outOfMemoryDelegate, 
                                ExceptionDelegate overflowDelegate, 
                                ExceptionDelegate systemExceptionDelegate);

    [global::System.Runtime.InteropServices.DllImport("rlibcsharp", EntryPoint="SWIGRegisterExceptionArgumentCallbacks_rlib")]
    public static extern void SWIGRegisterExceptionCallbacksArgument_rlib(
                                ExceptionArgumentDelegate argumentDelegate,
                                ExceptionArgumentDelegate argumentNullDelegate,
                                ExceptionArgumentDelegate argumentOutOfRangeDelegate);

    static void SetPendingApplicationException(string message) {
      SWIGPendingException.Set(new global::System.ApplicationException(message, SWIGPendingException.Retrieve()));
    }
    static void SetPendingArithmeticException(string message) {
      SWIGPendingException.Set(new global::System.ArithmeticException(message, SWIGPendingException.Retrieve()));
    }
    static void SetPendingDivideByZeroException(string message) {
      SWIGPendingException.Set(new global::System.DivideByZeroException(message, SWIGPendingException.Retrieve()));
    }
    static void SetPendingIndexOutOfRangeException(string message) {
      SWIGPendingException.Set(new global::System.IndexOutOfRangeException(message, SWIGPendingException.Retrieve()));
    }
    static void SetPendingInvalidCastException(string message) {
      SWIGPendingException.Set(new global::System.InvalidCastException(message, SWIGPendingException.Retrieve()));
    }
    static void SetPendingInvalidOperationException(string message) {
      SWIGPendingException.Set(new global::System.InvalidOperationException(message, SWIGPendingException.Retrieve()));
    }
    static void SetPendingIOException(string message) {
      SWIGPendingException.Set(new global::System.IO.IOException(message, SWIGPendingException.Retrieve()));
    }
    static void SetPendingNullReferenceException(string message) {
      SWIGPendingException.Set(new global::System.NullReferenceException(message, SWIGPendingException.Retrieve()));
    }
    static void SetPendingOutOfMemoryException(string message) {
      SWIGPendingException.Set(new global::System.OutOfMemoryException(message, SWIGPendingException.Retrieve()));
    }
    static void SetPendingOverflowException(string message) {
      SWIGPendingException.Set(new global::System.OverflowException(message, SWIGPendingException.Retrieve()));
    }
    static void SetPendingSystemException(string message) {
      SWIGPendingException.Set(new global::System.SystemException(message, SWIGPendingException.Retrieve()));
    }

    static void SetPendingArgumentException(string message, string paramName) {
      SWIGPendingException.Set(new global::System.ArgumentException(message, paramName, SWIGPendingException.Retrieve()));
    }
    static void SetPendingArgumentNullException(string message, string paramName) {
      global::System.Exception e = SWIGPendingException.Retrieve();
      if (e != null) message = message + " Inner Exception: " + e.Message;
      SWIGPendingException.Set(new global::System.ArgumentNullException(paramName, message));
    }
    static void SetPendingArgumentOutOfRangeException(string message, string paramName) {
      global::System.Exception e = SWIGPendingException.Retrieve();
      if (e != null) message = message + " Inner Exception: " + e.Message;
      SWIGPendingException.Set(new global::System.ArgumentOutOfRangeException(paramName, message));
    }

    static SWIGExceptionHelper() {
      SWIGRegisterExceptionCallbacks_rlib(
                                applicationDelegate,
                                arithmeticDelegate,
                                divideByZeroDelegate,
                                indexOutOfRangeDelegate,
                                invalidCastDelegate,
                                invalidOperationDelegate,
                                ioDelegate,
                                nullReferenceDelegate,
                                outOfMemoryDelegate,
                                overflowDelegate,
                                systemDelegate);

      SWIGRegisterExceptionCallbacksArgument_rlib(
                                argumentDelegate,
                                argumentNullDelegate,
                                argumentOutOfRangeDelegate);
    }
  }

  protected static SWIGExceptionHelper swigExceptionHelper = new SWIGExceptionHelper();

  public class SWIGPendingException {
    [global::System.ThreadStatic]
    private static global::System.Exception pendingException = null;
    private static int numExceptionsPending = 0;

    public static bool Pending {
      get {
        bool pending = false;
        if (numExceptionsPending > 0)
          if (pendingException != null)
            pending = true;
        return pending;
      } 
    }

    public static void Set(global::System.Exception e) {
      if (pendingException != null)
        throw new global::System.ApplicationException("FATAL: An earlier pending exception from unmanaged code was missed and thus not thrown (" + pendingException.ToString() + ")", e);
      pendingException = e;
      lock(typeof(rlibPINVOKE)) {
        numExceptionsPending++;
      }
    }

    public static global::System.Exception Retrieve() {
      global::System.Exception e = null;
      if (numExceptionsPending > 0) {
        if (pendingException != null) {
          e = pendingException;
          pendingException = null;
          lock(typeof(rlibPINVOKE)) {
            numExceptionsPending--;
          }
        }
      }
      return e;
    }
  }


  protected class SWIGStringHelper {

    public delegate string SWIGStringDelegate(string message);
    static SWIGStringDelegate stringDelegate = new SWIGStringDelegate(CreateString);

    [global::System.Runtime.InteropServices.DllImport("rlibcsharp", EntryPoint="SWIGRegisterStringCallback_rlib")]
    public static extern void SWIGRegisterStringCallback_rlib(SWIGStringDelegate stringDelegate);

    static string CreateString(string cString) {
      return cString;
    }

    static SWIGStringHelper() {
      SWIGRegisterStringCallback_rlib(stringDelegate);
    }
  }

  static protected SWIGStringHelper swigStringHelper = new SWIGStringHelper();


  static rlibPINVOKE() {
  }


  [global::System.Runtime.InteropServices.DllImport("rlibcsharp", EntryPoint="CSharp_rlib_init")]
  public static extern global::System.IntPtr rlib_init();

  [global::System.Runtime.InteropServices.DllImport("rlibcsharp", EntryPoint="CSharp_rlib_add_datasource_mysql")]
  public static extern int rlib_add_datasource_mysql(global::System.Runtime.InteropServices.HandleRef jarg1, string jarg2, string jarg3, string jarg4, string jarg5, string jarg6);

  [global::System.Runtime.InteropServices.DllImport("rlibcsharp", EntryPoint="CSharp_rlib_add_datasource_postgres")]
  public static extern int rlib_add_datasource_postgres(global::System.Runtime.InteropServices.HandleRef jarg1, string jarg2, string jarg3);

  [global::System.Runtime.InteropServices.DllImport("rlibcsharp", EntryPoint="CSharp_rlib_add_datasource_odbc")]
  public static extern int rlib_add_datasource_odbc(global::System.Runtime.InteropServices.HandleRef jarg1, string jarg2, string jarg3, string jarg4, string jarg5);

  [global::System.Runtime.InteropServices.DllImport("rlibcsharp", EntryPoint="CSharp_rlib_add_datasource_xml")]
  public static extern int rlib_add_datasource_xml(global::System.Runtime.InteropServices.HandleRef jarg1, string jarg2);

  [global::System.Runtime.InteropServices.DllImport("rlibcsharp", EntryPoint="CSharp_rlib_add_datasource_csv")]
  public static extern int rlib_add_datasource_csv(global::System.Runtime.InteropServices.HandleRef jarg1, string jarg2);

  [global::System.Runtime.InteropServices.DllImport("rlibcsharp", EntryPoint="CSharp_rlib_add_query_as")]
  public static extern int rlib_add_query_as(global::System.Runtime.InteropServices.HandleRef jarg1, string jarg2, string jarg3, string jarg4);

  [global::System.Runtime.InteropServices.DllImport("rlibcsharp", EntryPoint="CSharp_rlib_add_search_path")]
  public static extern int rlib_add_search_path(global::System.Runtime.InteropServices.HandleRef jarg1, string jarg2);

  [global::System.Runtime.InteropServices.DllImport("rlibcsharp", EntryPoint="CSharp_rlib_add_report")]
  public static extern int rlib_add_report(global::System.Runtime.InteropServices.HandleRef jarg1, string jarg2);

  [global::System.Runtime.InteropServices.DllImport("rlibcsharp", EntryPoint="CSharp_rlib_add_report_from_buffer")]
  public static extern int rlib_add_report_from_buffer(global::System.Runtime.InteropServices.HandleRef jarg1, string jarg2);

  [global::System.Runtime.InteropServices.DllImport("rlibcsharp", EntryPoint="CSharp_rlib_execute")]
  public static extern int rlib_execute(global::System.Runtime.InteropServices.HandleRef jarg1);

  [global::System.Runtime.InteropServices.DllImport("rlibcsharp", EntryPoint="CSharp_rlib_get_content_type_as_text")]
  public static extern string rlib_get_content_type_as_text(global::System.Runtime.InteropServices.HandleRef jarg1);

  [global::System.Runtime.InteropServices.DllImport("rlibcsharp", EntryPoint="CSharp_rlib_spool")]
  public static extern int rlib_spool(global::System.Runtime.InteropServices.HandleRef jarg1);

  [global::System.Runtime.InteropServices.DllImport("rlibcsharp", EntryPoint="CSharp_rlib_set_output_format")]
  public static extern int rlib_set_output_format(global::System.Runtime.InteropServices.HandleRef jarg1, int jarg2);

  [global::System.Runtime.InteropServices.DllImport("rlibcsharp", EntryPoint="CSharp_rlib_add_resultset_follower_n_to_1")]
  public static extern int rlib_add_resultset_follower_n_to_1(global::System.Runtime.InteropServices.HandleRef jarg1, string jarg2, string jarg3, string jarg4, string jarg5);

  [global::System.Runtime.InteropServices.DllImport("rlibcsharp", EntryPoint="CSharp_rlib_add_resultset_follower")]
  public static extern int rlib_add_resultset_follower(global::System.Runtime.InteropServices.HandleRef jarg1, string jarg2, string jarg3);

  [global::System.Runtime.InteropServices.DllImport("rlibcsharp", EntryPoint="CSharp_rlib_set_output_format_from_text")]
  public static extern int rlib_set_output_format_from_text(global::System.Runtime.InteropServices.HandleRef jarg1, string jarg2);

  [global::System.Runtime.InteropServices.DllImport("rlibcsharp", EntryPoint="CSharp_rlib_get_output")]
  public static extern string rlib_get_output(global::System.Runtime.InteropServices.HandleRef jarg1);

  [global::System.Runtime.InteropServices.DllImport("rlibcsharp", EntryPoint="CSharp_rlib_get_output_length")]
  public static extern int rlib_get_output_length(global::System.Runtime.InteropServices.HandleRef jarg1);

  [global::System.Runtime.InteropServices.DllImport("rlibcsharp", EntryPoint="CSharp_rlib_signal_connect")]
  public static extern int rlib_signal_connect(global::System.Runtime.InteropServices.HandleRef jarg1, int jarg2, global::System.Runtime.InteropServices.HandleRef jarg3, global::System.Runtime.InteropServices.HandleRef jarg4);

  [global::System.Runtime.InteropServices.DllImport("rlibcsharp", EntryPoint="CSharp_rlib_signal_connect_string")]
  public static extern int rlib_signal_connect_string(global::System.Runtime.InteropServices.HandleRef jarg1, string jarg2, global::System.Runtime.InteropServices.HandleRef jarg3, global::System.Runtime.InteropServices.HandleRef jarg4);

  [global::System.Runtime.InteropServices.DllImport("rlibcsharp", EntryPoint="CSharp_rlib_query_refresh")]
  public static extern int rlib_query_refresh(global::System.Runtime.InteropServices.HandleRef jarg1);

  [global::System.Runtime.InteropServices.DllImport("rlibcsharp", EntryPoint="CSharp_rlib_add_parameter")]
  public static extern int rlib_add_parameter(global::System.Runtime.InteropServices.HandleRef jarg1, string jarg2, string jarg3);

  [global::System.Runtime.InteropServices.DllImport("rlibcsharp", EntryPoint="CSharp_rlib_set_locale")]
  public static extern int rlib_set_locale(global::System.Runtime.InteropServices.HandleRef jarg1, string jarg2);

  [global::System.Runtime.InteropServices.DllImport("rlibcsharp", EntryPoint="CSharp_rlib_bindtextdomain")]
  public static extern string rlib_bindtextdomain(global::System.Runtime.InteropServices.HandleRef jarg1, string jarg2, string jarg3);

  [global::System.Runtime.InteropServices.DllImport("rlibcsharp", EntryPoint="CSharp_rlib_set_radix_character")]
  public static extern void rlib_set_radix_character(global::System.Runtime.InteropServices.HandleRef jarg1, global::System.Runtime.InteropServices.HandleRef jarg2);

  [global::System.Runtime.InteropServices.DllImport("rlibcsharp", EntryPoint="CSharp_rlib_set_output_parameter")]
  public static extern void rlib_set_output_parameter(global::System.Runtime.InteropServices.HandleRef jarg1, string jarg2, string jarg3);

  [global::System.Runtime.InteropServices.DllImport("rlibcsharp", EntryPoint="CSharp_rlib_set_output_encoding")]
  public static extern void rlib_set_output_encoding(global::System.Runtime.InteropServices.HandleRef jarg1, string jarg2);

  [global::System.Runtime.InteropServices.DllImport("rlibcsharp", EntryPoint="CSharp_rlib_set_datasource_encoding")]
  public static extern int rlib_set_datasource_encoding(global::System.Runtime.InteropServices.HandleRef jarg1, string jarg2, string jarg3);

  [global::System.Runtime.InteropServices.DllImport("rlibcsharp", EntryPoint="CSharp_rlib_free")]
  public static extern int rlib_free(global::System.Runtime.InteropServices.HandleRef jarg1);

  [global::System.Runtime.InteropServices.DllImport("rlibcsharp", EntryPoint="CSharp_rlib_version")]
  public static extern string rlib_version();

  [global::System.Runtime.InteropServices.DllImport("rlibcsharp", EntryPoint="CSharp_rlib_graph_add_bg_region")]
  public static extern int rlib_graph_add_bg_region(global::System.Runtime.InteropServices.HandleRef jarg1, string jarg2, string jarg3, string jarg4, float jarg5, float jarg6);

  [global::System.Runtime.InteropServices.DllImport("rlibcsharp", EntryPoint="CSharp_rlib_graph_clear_bg_region")]
  public static extern int rlib_graph_clear_bg_region(global::System.Runtime.InteropServices.HandleRef jarg1, string jarg2);

  [global::System.Runtime.InteropServices.DllImport("rlibcsharp", EntryPoint="CSharp_rlib_graph_set_x_minor_tick")]
  public static extern int rlib_graph_set_x_minor_tick(global::System.Runtime.InteropServices.HandleRef jarg1, string jarg2, string jarg3);

  [global::System.Runtime.InteropServices.DllImport("rlibcsharp", EntryPoint="CSharp_rlib_graph_set_x_minor_tick_by_location")]
  public static extern int rlib_graph_set_x_minor_tick_by_location(global::System.Runtime.InteropServices.HandleRef jarg1, string jarg2, int jarg3);

  [global::System.Runtime.InteropServices.DllImport("rlibcsharp", EntryPoint="CSharp_rlib_graph")]
  public static extern float rlib_graph(global::System.Runtime.InteropServices.HandleRef jarg1, global::System.Runtime.InteropServices.HandleRef jarg2, global::System.Runtime.InteropServices.HandleRef jarg3, float jarg4, global::System.Runtime.InteropServices.HandleRef jarg5);
}
