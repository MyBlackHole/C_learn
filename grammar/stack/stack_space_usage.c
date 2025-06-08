#include <limits.h>
#include <fcntl.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

/* 此空间不会影响栈空间的占用 */
char g_buffer[1 * 1024 * 1024]; // 1MB buffer
/*char g_buffer[1024 * 1024 * 1024]; // 1GB buffer*/

int demo_stack_space_usage_main()
{
	/*char buffer[1024 * 1024 * 1024]; // 1GB buffer*/
	char m_buffer[1024 * 1024]; // 1MB buffer
	memset(m_buffer, 0, sizeof(m_buffer)); // fill the buffer with zeroes
	m_buffer[0] = 'a'; // write to the first byte of the buffer
	g_buffer[0] = 'b'; // write to the first byte of the buffer
	return 0;
}

// output:
//
// ❯ ulimit -s 1024
// ❯ xmake run grammar stack_space_usage
// error: execv(/run/media/black/Data/Documents/c/build/linux/x86_64/debug/grammar stack_space_usage) failed(-1)
// ❯ ulimit -s 1026
// ❯ xmake run grammar stack_space_usage
// error: execv(/run/media/black/Data/Documents/c/build/linux/x86_64/debug/grammar stack_space_usage) failed(-1)
// ❯ ulimit -s 1512
// ❯ xmake run grammar stack_space_usage
// ❯ ulimit -s 1100
// ❯ xmake run grammar stack_space_usage
// ❯ ulimit -s 1030
// ❯ xmake run grammar stack_space_usage
// error: execv(/run/media/black/Data/Documents/c/build/linux/x86_64/debug/grammar stack_space_usage) failed(-1)
// ❯ ulimit -s 1040
// ❯ xmake run grammar stack_space_usage
