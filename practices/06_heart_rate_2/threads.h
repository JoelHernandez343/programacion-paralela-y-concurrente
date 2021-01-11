/**
 * Joel Hernández @ 2020
 * Github JoelHernandez343
 */

void thread_parent_process();
void execute_threads(void *(child_function)(void *args));
void *thread_calculate_windowed_data(void *args);
void *thread_calculate_rxx(void *args);