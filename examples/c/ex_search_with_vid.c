/*-
 * Public Domain 2014-present MongoDB, Inc.
 * Public Domain 2008-2014 WiredTiger, Inc.
 *
 * This is free and unencumbered software released into the public domain.
 *
 * Anyone is free to copy, modify, publish, use, compile, sell, or
 * distribute this software, either in source code form or as a compiled
 * binary, for any purpose, commercial or non-commercial, and by any
 * means.
 *
 * In jurisdictions that recognize copyright laws, the author or authors
 * of this software dedicate any and all copyright interest in the
 * software to the public domain. We make this dedication for the benefit
 * of the public at large and to the detriment of our heirs and
 * successors. We intend this dedication to be an overt act of
 * relinquishment in perpetuity of all present and future rights to this
 * software under copyright law.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * ex_with_vid.c
 * 	demonstrates how to use a transaction.
 */
#include <test_util.h>

static const char *home;

static void
search_with_vid_example(void) {
    WT_CONNECTION *conn;
    WT_CURSOR *cursor;
    WT_SESSION *session;
    // const char *key, *value;
    WT_ITEM key, value;
    int ret;

    /* Open a connection to the database, creating it if necessary. */
    error_check(wiredtiger_open(home, NULL, NULL, &conn));

    /* Open a session handle for the database. */
    error_check(conn->open_session(conn, NULL, NULL, &session));
    /*! [transaction example connection] */

    /*! [transaction example cursor open] */
    error_check(session->open_cursor(session, "blue:with_vid", NULL, NULL, &cursor));
    /*! [transaction example cursor open] */

    while ((ret = cursor->next(cursor)) == 0) {
        error_check(cursor->get_key(cursor, &key));
        error_check(cursor->get_value(cursor, &value));

        printf("Got record: %s : %s\n", (const char*)key.data, (const char*)value.data);
    }
    scan_end_check(ret == WT_NOTFOUND); /* Check for end-of-table. */
    /*! [transaction example cursor list] */

    /*! [transaction example close] */
    error_check(conn->close(conn, NULL)); /* Close all handles. */
                                          /*! [transaction example close] */
}

int
main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;

    home = "WT_HOME";

    search_with_vid_example();

    return (EXIT_SUCCESS);
}
