#include "perf_index.h"
#include "fail.h"
#include "test_file_helper.h"
#include <sys/param.h>
#include <stdio.h>

char tempdir[MAXPATHLEN];

DECL_SETUP {
    char* retval;

    retval = setup_tempdir(tempdir);

    VERIFY(retval, "tempdir setup failed");

    printf("tempdir: %s\n", tempdir);

    return test_file_read_setup(tempdir, num_threads, length, 0L);
}

DECL_TEST {
    return test_file_read(tempdir, thread_id, num_threads, length, 0L);
}

DECL_CLEANUP {
    int retval;

    retval = test_file_read_cleanup(tempdir, num_threads, length);
    VERIFY(retval == PERFINDEX_SUCCESS, "test_file_read_cleanup failed");

    retval = cleanup_tempdir(tempdir);
    VERIFY(retval == 0, "cleanup_tempdir failed");

    return PERFINDEX_SUCCESS;

}
