#include "main.h"

/**
 * SIGINT_handler - Signal handler for SIGINT.
 * @signum: The signal number.
 * Description: A handler function for the SIGINT signal that does nothing.
 * Used to catch and ignore SIGINT signals.
 */
void SIGINT_handler(int signum)
{
	(void)signum;
}
