#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "stdafx.h"
#include "sapi/embed/php_embed.h"
#include "gcp_spanner_warmup.h"

PHP_FUNCTION(confirm_gcp_spanner_warmup_compiled)
{
    char *arg = NULL;
    size_t arg_len, len;
    zend_string *strg;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &arg, &arg_len) == FAILURE) {
        return;
    }

    strg = strpprintf(0, "Extension %.78s loaded into PHP.", "gcp_spanner_warmup", arg);

    RETURN_STR(strg);
}

PHP_MINIT_FUNCTION(gcp_spanner_warmup)
{
    php_error_docref(NULL, E_NOTICE, "Module test init[%d]", getpid());
    zval retval;
    PHP_EMBED_START_BLOCK(0, NULL)
        zend_file_handle file_handle;
        zend_stream_init_filename(&file_handle, "/var/www/html/ee-no/grpc_warmup.php");

        if (php_execute_script(&file_handle) == FAILURE) {
          php_printf("Failed to execute PHP script.\n");
        } else {
          php_printf("PHP script executed successfully.\n");
        }
    PHP_EMBED_END_BLOCK()
    php_error_docref(NULL, E_NOTICE, "Output:[%s]", Z_STRVAL(retval));
    return SUCCESS;
}

PHP_MSHUTDOWN_FUNCTION(gcp_spanner_warmup)
{
    return SUCCESS;
}

PHP_MINFO_FUNCTION(gcp_spanner_warmup)
{
    php_info_print_table_start();
    php_info_print_table_header(2, "gcp_spanner_warmup support", "enabled");
    php_info_print_table_end();
}

const zend_function_entry gcp_spanner_warmup_functions[] = {
    PHP_FE(confirm_gcp_spanner_warmup_compiled,  NULL)       /* For testing, remove later. */
    PHP_FE_END      /* Must be the last line in gcp_spanner_warmup_functions[] */
};

zend_module_entry gcp_spanner_warmup_module_entry = {
    STANDARD_MODULE_HEADER,
    "gcp_spanner_warmup",
    gcp_spanner_warmup_functions,
    PHP_MINIT(gcp_spanner_warmup),
    PHP_MSHUTDOWN(gcp_spanner_warmup),
    NULL,
    NULL,
    PHP_MINFO(gcp_spanner_warmup),
    PHP_GCP_SPANNER_WARMUP_VERSION,
    STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_GCP_SPANNER_WARMUP
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
#endif
ZEND_GET_MODULE(gcp_spanner_warmup)
#endif
