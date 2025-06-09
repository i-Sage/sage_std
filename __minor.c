#include <sage_log/sage_log.h>

int main() {
    Logger logger;
    init_logger(&logger, "log.log");
    LOG(&logger, "hello world");
    destroy_logger(&logger);
}
