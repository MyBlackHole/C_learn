#ifndef DEMO_H
#define DEMO_H

// the main item
#define DEMO_MAIN_ITEM(name)              \
	{                                 \
		#name, demo_##name##_main \
	}

#define DEMO_MAIN_DECL(name) int demo_##name##_main(int argc, char **argv)

#define DEMO_MAIN_ENV_ITEM(name)          \
	{                                 \
		#name, demo_##name##_main \
	}

#define DEMO_MAIN_ENV_DECL(name) \
	int demo_##name##_main(int argc, char **argv, char **env)

/* //////////////////////////////////////////////////////////////////////////////////////
 * types
 */

#define arrayn(x) ((sizeof((x)) / sizeof((x)[0])))

// the demo type
typedef struct demo {
	// the demo name
	char const *name;

	// the demo main
	int (*main)(int argc, char **argv);

} demo_t;

// the demo type
typedef struct demo_env {
	// the demo name
	char const *name;

	// the demo main
	int (*main)(int argc, char **argv, char **env);

} demo_env_t;
#endif
