#include "os.h"

#define DELAY 4000

#define USE_LOCK
static reg_t j;

void user_task0(void)
{
	uart_puts("Task 0: Created!\n");
	while (1) {
		uart_puts("Task 0: Begin ... \n");
		j = 0;
#ifdef USE_LOCK
		spin_lock();
#endif
		for (int i = 0; i < 5; i++) {
			printf("user_task0: %d\n", j++);
			// uart_puts("Task 0: Running... \n");
			task_delay(DELAY);
		}
#ifdef USE_LOCK
		spin_unlock();
#endif
		uart_puts("Task 0: End ... \n");
	}
}

void user_task1(void)
{
	uart_puts("Task 1: Created!\n");
	while (1) {
		uart_puts("Task 1: Begin ... \n");
#ifdef USE_LOCK
		spin_lock();
#endif
		j = 0;
		for (int i = 0; i < 5; i++) {
			// uart_puts("Task 1: Running... \n");
			printf("user_task1: %d\n", j++);
			task_delay(DELAY);
		}
#ifdef USE_LOCK
		spin_unlock();
#endif
		uart_puts("Task 1: End ... \n");
	}
}

/* NOTICE: DON'T LOOP INFINITELY IN main() */
void os_main(void)
{
	task_create(user_task0);
	task_create(user_task1);
}
