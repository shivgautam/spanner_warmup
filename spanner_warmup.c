#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "sapi/embed/php_embed.h"

PHP_MINIT_FUNCTION(spanner_warmup)
{
    // php_error_docref(NULL, E_NOTICE, "Module test init");
    PHP_EMBED_START_BLOCK(0, NULL)
        zend_file_handle file_handle;
        zend_stream_init_filename(&file_handle, "/var/www/html/ee-no/grpc_warmup.php");

        if (php_execute_script(&file_handle) == FAILURE) {
          php_error_docref(NULL, E_ERROR, "Failed to execute PHP script.");
          return FAILURE; // Indicate initialization failure
        } else {
          php_printf("PHP script executed successfully.\n");
        }
    PHP_EMBED_END_BLOCK()
    return SUCCESS;
}

PHP_MSHUTDOWN_FUNCTION(spanner_warmup)
{
    return SUCCESS;
}

PHP_MINFO_FUNCTION(spanner_warmup)
{
    php_info_print_table_start();
    php_info_print_table_header(2, "spanner_warmup support", "enabled");
    php_info_print_table_end();
}

const zend_function_entry spanner_warmup_functions[] = {
    // PHP_FE(confirm_spanner_warmup_compiled,  NULL)       /* For testing, remove later. */
    PHP_FE_END      /* Must be the last line in spanner_warmup_functions[] */
};

zend_module_entry spanner_warmup_module_entry = {
    STANDARD_MODULE_HEADER,
    "spanner_warmup",
    NULL,
    PHP_MINIT(spanner_warmup),
    PHP_MSHUTDOWN(spanner_warmup),
    NULL,
    NULL,
    PHP_MINFO(spanner_warmup),
    "0.1",
    STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_SPANNER_WARMUP
// #ifdef ZTS
// ZEND_TSRMLS_CACHE_DEFINE()
// #endif
ZEND_GET_MODULE(spanner_warmup)
#endif
