/*
  +----------------------------------------------------------------------+
  | PHP Version 7                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2018 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:                                                              |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifndef PHP_RECURSIONGUARD_H
#define PHP_RECURSIONGUARD_H

extern zend_module_entry recursionguard_module_entry;
#define phpext_recursionguard_ptr &recursionguard_module_entry

#define PHP_RECURSIONGUARD_VERSION "0.1.0"

#ifdef ZTS
#include "TSRM.h"
#endif

ZEND_BEGIN_MODULE_GLOBALS(recursionguard)
	zend_long call_depth;
ZEND_END_MODULE_GLOBALS(recursionguard)

#define RECURSIONGUARD_G(v) ZEND_MODULE_GLOBALS_ACCESSOR(recursionguard, v)

#if defined(ZTS) && defined(COMPILE_DL_RECURSIONGUARD)
ZEND_TSRMLS_CACHE_EXTERN()
#endif

#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
