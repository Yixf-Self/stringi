/* This file is part of the 'stringi' library.
 * 
 * Copyright 2013 Marek Gagolewski, Bartek Tartanus, Marcin Bujarski
 * 
 * 'stringi' is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * 'stringi' is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with 'stringi'. If not, see <http://www.gnu.org/licenses/>.
 */
 
#include "stringi.h"



#define STRI__MAKE_CALL_METHOD(name, args) \
   {#name, (DL_FUNC)&name, args}

/**
 * List of functions available in R via .Call()
 * 
 * Form:
 * \code{\{"method_name", (DL_FUNC)pointer, number_of_args\}} - 
 * this is generated by the STRI__MAKE_CALL_METHOD macro.
 */
static const R_CallMethodDef cCallMethods[] = {
   
   STRI__MAKE_CALL_METHOD(stri_casefold,                   3),
//   STRI__MAKE_CALL_METHOD(stri_charcategories,             0),  // TO BE v>=0.2
//   STRI__MAKE_CALL_METHOD(stri_chartype,                   1),  // TO BE v>=0.2
   STRI__MAKE_CALL_METHOD(stri_compare,                    3),
   STRI__MAKE_CALL_METHOD(stri_compare_codepoints,         2),
   STRI__MAKE_CALL_METHOD(stri_count_charclass,            2),
   STRI__MAKE_CALL_METHOD(stri_count_fixed,                3),
   STRI__MAKE_CALL_METHOD(stri_count_regex,                3),
   STRI__MAKE_CALL_METHOD(stri_detect_charclass,           2),
   STRI__MAKE_CALL_METHOD(stri_detect_fixed,               3),
   STRI__MAKE_CALL_METHOD(stri_detect_regex,               3),
   STRI__MAKE_CALL_METHOD(stri_dup,                        2),
   STRI__MAKE_CALL_METHOD(stri_enc_info,                   1),
   STRI__MAKE_CALL_METHOD(stri_enc_isascii,                1),
   STRI__MAKE_CALL_METHOD(stri_enc_isutf8,                 1),
   STRI__MAKE_CALL_METHOD(stri_enc_list,                   0),
   STRI__MAKE_CALL_METHOD(stri_enc_isnf,                   2),
   STRI__MAKE_CALL_METHOD(stri_enc_nf,                     2),
   STRI__MAKE_CALL_METHOD(stri_enc_set,                    1),
   STRI__MAKE_CALL_METHOD(stri_enc_fromutf32,              1),
   STRI__MAKE_CALL_METHOD(stri_enc_toascii,                1),
   STRI__MAKE_CALL_METHOD(stri_enc_toutf8,                 2),
   STRI__MAKE_CALL_METHOD(stri_enc_toutf32,                1),
   STRI__MAKE_CALL_METHOD(stri_encode,                     4),
   STRI__MAKE_CALL_METHOD(stri_extract_first_charclass,    2),
   STRI__MAKE_CALL_METHOD(stri_extract_last_charclass,     2),
   STRI__MAKE_CALL_METHOD(stri_extract_all_charclass,      3),
   STRI__MAKE_CALL_METHOD(stri_extract_first_fixed,        3),
   STRI__MAKE_CALL_METHOD(stri_extract_last_fixed,         3),
   STRI__MAKE_CALL_METHOD(stri_extract_all_fixed,          3),
   STRI__MAKE_CALL_METHOD(stri_extract_first_regex,        3),
   STRI__MAKE_CALL_METHOD(stri_extract_last_regex,         3),
   STRI__MAKE_CALL_METHOD(stri_extract_all_regex,          3),
   STRI__MAKE_CALL_METHOD(stri_flatten,                    2),
   STRI__MAKE_CALL_METHOD(stri_flatten_nosep,              1),
   STRI__MAKE_CALL_METHOD(stri_info,                       0),
   STRI__MAKE_CALL_METHOD(stri_isempty,                    1),
   STRI__MAKE_CALL_METHOD(stri_join,                       3),
   STRI__MAKE_CALL_METHOD(stri_join2,                      2),
//   STRI__MAKE_CALL_METHOD(stri_justify,                    2),  // TODO: version >= 0.2
   STRI__MAKE_CALL_METHOD(stri_length,                     1),
   STRI__MAKE_CALL_METHOD(stri_locale_info,                1),
   STRI__MAKE_CALL_METHOD(stri_locale_list,                0),
   STRI__MAKE_CALL_METHOD(stri_locale_set,                 1),
   STRI__MAKE_CALL_METHOD(stri_locate_first_charclass,     2),
   STRI__MAKE_CALL_METHOD(stri_locate_last_charclass,      2),
   STRI__MAKE_CALL_METHOD(stri_locate_all_charclass,       3),
   STRI__MAKE_CALL_METHOD(stri_locate_last_fixed,          3), 
   STRI__MAKE_CALL_METHOD(stri_locate_first_fixed,         3), 
   STRI__MAKE_CALL_METHOD(stri_locate_all_fixed,           3), 
   STRI__MAKE_CALL_METHOD(stri_locate_all_regex,           3), 
   STRI__MAKE_CALL_METHOD(stri_locate_first_regex,         3), 
   STRI__MAKE_CALL_METHOD(stri_locate_last_regex,          3), 
   STRI__MAKE_CALL_METHOD(stri_match_first_regex,          3),
   STRI__MAKE_CALL_METHOD(stri_match_last_regex,           3),
   STRI__MAKE_CALL_METHOD(stri_match_all_regex,            3),
   STRI__MAKE_CALL_METHOD(stri_numbytes,                   1),
   STRI__MAKE_CALL_METHOD(stri_order,                      3),
//   STRI__MAKE_CALL_METHOD(stri_pad,                        3), // TODO: version >= 0.2
   STRI__MAKE_CALL_METHOD(stri_prepare_arg_string,         2),
   STRI__MAKE_CALL_METHOD(stri_prepare_arg_double,         2),
   STRI__MAKE_CALL_METHOD(stri_prepare_arg_integer,        2),
   STRI__MAKE_CALL_METHOD(stri_prepare_arg_logical,        2),
   STRI__MAKE_CALL_METHOD(stri_prepare_arg_raw,            2),
   STRI__MAKE_CALL_METHOD(stri_prepare_arg_string_1,       2),
   STRI__MAKE_CALL_METHOD(stri_prepare_arg_double_1,       2),
   STRI__MAKE_CALL_METHOD(stri_prepare_arg_integer_1,      2),
   STRI__MAKE_CALL_METHOD(stri_prepare_arg_logical_1,      2),
   STRI__MAKE_CALL_METHOD(stri_replace_all_fixed,          4),
   STRI__MAKE_CALL_METHOD(stri_replace_first_fixed,        4),
   STRI__MAKE_CALL_METHOD(stri_replace_last_fixed,         4),
   STRI__MAKE_CALL_METHOD(stri_replace_all_regex,          4),
   STRI__MAKE_CALL_METHOD(stri_replace_first_regex,        4),
   STRI__MAKE_CALL_METHOD(stri_replace_last_regex,         4),
   STRI__MAKE_CALL_METHOD(stri_replace_all_charclass,      3),
   STRI__MAKE_CALL_METHOD(stri_replace_first_charclass,    3),
   STRI__MAKE_CALL_METHOD(stri_replace_last_charclass,     3),
   STRI__MAKE_CALL_METHOD(stri_reverse,                    1),
   STRI__MAKE_CALL_METHOD(stri_split_charclass,            4),
   STRI__MAKE_CALL_METHOD(stri_split_regex,                5),
   STRI__MAKE_CALL_METHOD(stri_split_fixed,                5),
//   STRI__MAKE_CALL_METHOD(stri_split_pos,              3), // TODO: version >= 0.2
   STRI__MAKE_CALL_METHOD(stri_stats_general,              1),
   STRI__MAKE_CALL_METHOD(stri_stats_latex,                1),
   STRI__MAKE_CALL_METHOD(stri_sub,                        4),
   STRI__MAKE_CALL_METHOD(stri_sub_replacement,            5),
   STRI__MAKE_CALL_METHOD(stri_test_Rmark,                 1),
   STRI__MAKE_CALL_METHOD(stri_test_returnasis,            1),
   STRI__MAKE_CALL_METHOD(stri_test_UnicodeContainer16,    1),
   STRI__MAKE_CALL_METHOD(stri_test_UnicodeContainer8,     1),
   STRI__MAKE_CALL_METHOD(stri_trim_both,                  2),
   STRI__MAKE_CALL_METHOD(stri_trim_left,                  2),
   STRI__MAKE_CALL_METHOD(stri_trim_right,                 2),
//   STRI__MAKE_CALL_METHOD(stri_trim_double,                3), // TODO: version >= 0.2
//   STRI__MAKE_CALL_METHOD(stri_width,                      1), // TODO: version >= 0.2
//   STRI__MAKE_CALL_METHOD(stri_wrap,                       4), // TODO: version >= 0.2
//   STRI__MAKE_CALL_METHOD(stri_wrap_greedy,                3), // TODO: version >= 0.2
//   STRI__MAKE_CALL_METHOD(stri_wrap_dynamic,               3), // TODO: version >= 0.2
   
   // the list must be NULL-terminated:
   {NULL,                           NULL,                  0}

};



/**
 * Library initialization.
 * 
 * R calls this automatically on lib load/attach.
 */
extern "C" void R_init_stringi(DllInfo *dll)
{
   R_registerRoutines(dll, NULL, cCallMethods, NULL, NULL);
   R_useDynamicSymbols(dll, Rboolean(FALSE));
   
   if (!SUPPORT_UTF8) {
      /* Rconfig.h states that all R platforms supports that */
      error("Your R version does not support UTF-8 encoding.");  
   }
   
#ifndef NDEBUG
    cerr << "DEBUG: Dynamic library 'stringi' loaded." << endl;
//    UErrorCode status;
//    u_init(&status);
//    if (U_FAILURE(status))
//      error("ICU init failed: %s", u_errorName(status));
#endif
}




///**
// * ... not needed ...
// */
//extern "C" void  R_unload_stringi(DllInfo *info)
//{
//#ifndef NDEBUG
//   cerr << "DEBUG: Dynamic library 'stringi' unloaded." << endl;
////   u_cleanup(); // this is just for DEBUG- memtrace
//#endif
//}

