#include "btree.h"
#include <stdio.h>
#include <string.h>

struct user {
	char *first;
	char *last;
	int age;
};

int user_compare(const void *a, const void *b, void *udata)
{
	const struct user *ua = a;
	const struct user *ub = b;
	int cmp = strcmp(ua->last, ub->last);
	if (cmp == 0) {
		cmp = strcmp(ua->first, ub->first);
	}
	return cmp;
}

bool user_iter(const void *a, void *udata)
{
	const struct user *user = a;
	printf("%s %s (age=%d)\n", user->first, user->last, user->age);
	return true;
}

int main()
{
	// create a new btree where each item is a `struct user`.
	struct btree *tr =
		btree_new(sizeof(struct user), 0, user_compare, NULL);

	// load some users into the btree. Each set operation performas a copy of
	// the data that is pointed to in the second argument.
	btree_set(tr, &(struct user){
			      .first = "Dale", .last = "Murphy", .age = 44 });
	btree_set(tr, &(struct user){
			      .first = "Roger", .last = "Craig", .age = 68 });
	btree_set(tr, &(struct user){
			      .first = "Jane", .last = "Murphy", .age = 47 });

	struct user *user;

	printf("\n-- get some users --\n");
	user = btree_get(tr,
			 &(struct user){ .first = "Jane", .last = "Murphy" });
	printf("%s age=%d\n", user->first, user->age);

	user = btree_get(tr,
			 &(struct user){ .first = "Roger", .last = "Craig" });
	printf("%s age=%d\n", user->first, user->age);

	user = btree_get(tr,
			 &(struct user){ .first = "Dale", .last = "Murphy" });
	printf("%s age=%d\n", user->first, user->age);

	user = btree_get(tr,
			 &(struct user){ .first = "Tom", .last = "Buffalo" });
	printf("%s\n", user ? "exists" : "not exists");

	printf("\n-- iterate over all users --\n");
	btree_ascend(tr, NULL, user_iter, NULL);

	printf("\n-- iterate beginning with last name `Murphy` --\n");
	btree_ascend(tr, &(struct user){ .first = "", .last = "Murphy" },
		     user_iter, NULL);

	btree_free(tr);
}
