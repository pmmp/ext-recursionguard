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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_recursionguard.h"

ZEND_DECLARE_MODULE_GLOBALS(recursionguard)

#define INI_ENABLED_ENTRY "recursionguard.enabled"

PHP_INI_BEGIN()
PHP_INI_ENTRY(INI_ENABLED_ENTRY, "1", PHP_INI_SYSTEM, NULL)
PHP_INI_END()

typedef void(*zend_execute_ex_function)(zend_execute_data *);

zend_execute_ex_function zend_execute_ex_hook = NULL;

void guard_execute_ex(zend_execute_data *execute_data) {
	if (RECURSIONGUARD_G(call_depth) > 256) {
		zend_throw_error(NULL, "Reached maximum call depth of 256, aborting!");
		return;
	}
	RECURSIONGUARD_G(call_depth)++;
	zend_execute_ex_hook(execute_data);
	RECURSIONGUARD_G(call_depth)--;
}

PHP_MINIT_FUNCTION(recursionguard)
{
	REGISTER_INI_ENTRIES();

	if (INI_BOOL(INI_ENABLED_ENTRY)) {
		zend_execute_ex_hook = zend_execute_ex;
		zend_execute_ex = guard_execute_ex;
	}

	return SUCCESS;
}

PHP_MSHUTDOWN_FUNCTION(recursionguard) {
	UNREGISTER_INI_ENTRIES();
	return SUCCESS;
}

PHP_RINIT_FUNCTION(recursionguard)
{
#if defined(COMPILE_DL_RECURSIONGUARD) && defined(ZTS)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif
	RECURSIONGUARD_G(call_depth) = 0;
	return SUCCESS;
}

PHP_MINFO_FUNCTION(recursionguard)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "recursionguard support", (INI_BOOL(INI_ENABLED_ENTRY) ? "enabled" : "disabled"));
	php_info_print_table_end();

}

zend_module_entry recursionguard_module_entry = {
	STANDARD_MODULE_HEADER,
	"recursionguard",
	NULL,
	PHP_MINIT(recursionguard),
	PHP_MSHUTDOWN(recursionguard),
	PHP_RINIT(recursionguard),	
	NULL,
	PHP_MINFO(recursionguard),
	PHP_RECURSIONGUARD_VERSION,
	PHP_MODULE_GLOBALS(recursionguard),
	NULL,
	NULL,
	NULL,
	STANDARD_MODULE_PROPERTIES_EX
};


#ifdef COMPILE_DL_RECURSIONGUARD
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
#endif
ZEND_GET_MODULE(recursionguard)
#endif

