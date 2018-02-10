#include <stdio.h>
#include <test/fx.h>
#include <fx_error/error.h>

int main(int argc, char *argv[]) {
        fx_test_t test;
        fx_test_result_t result;

        fx_test_init(&test, fx_test_mode_force);
        if (fx_error_check())
                return EXIT_FAILURE;

        fx_test_run(&test, &test_vector_set);
        if (fx_error_check()) {
                fx_test_free(&test);
                fprintf(stderr, "ERROR %s\n", fx_error_id(fx_error_state));
                return EXIT_FAILURE;
        }

        fx_test_run(&test, &test_queue_set);
        if (fx_error_check()) {
                fx_test_free(&test);
                fprintf(stderr, "ERROR %s\n", fx_error_id(fx_error_state));
                return EXIT_FAILURE;
        }

        fx_test_join(&test, &result);
        if (fx_error_check())
                return EXIT_FAILURE;

        fx_test_free(&test);
        printf("\n");
        fx_test_result_dump(stdout, &result);
        return result.is_done ? EXIT_SUCCESS : EXIT_FAILURE;
}
