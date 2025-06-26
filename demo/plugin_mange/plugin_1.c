// 示例插件实现
#include <stdio.h>
#include <stdlib.h>

typedef struct {
	const char *name;
	const char *version;
	int (*init)(void);
	int (*process)(const char *input, char **output);
	void (*cleanup)(void);
} PluginInterface;

int my_plugin_init(void)
{
	printf("My Plugin Initialized\n");
	return 0;
}

int my_plugin_process(const char *input, char **output)
{
	char *result = malloc(256);
	snprintf(result, 256, "Processed: %s", input);
	*output = result;
	return 0;
}

void my_plugin_cleanup(void)
{
	printf("My Plugin Cleaned Up\n");
}

PluginInterface my_plugin_api = { .name = "MyPlugin",
				  .version = "1.0",
				  .init = my_plugin_init,
				  .process = my_plugin_process,
				  .cleanup = my_plugin_cleanup };

// 导出插件接口
// __attribute__((visibility("default"))) PluginInterface *get_plugin_api(void)
PluginInterface *get_plugin_api(void)
{
	return &my_plugin_api;
}
