#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/rhashtable.h>
#include <linux/sched.h>

MODULE_LICENSE("GPL");

struct kvpair {
	u64 key;
	u64 value;
};

struct hash_entry {
	struct rhash_head node;
	struct kvpair kv;
};

void hash_entry_free(void *ptr, void *arg)
{
	kfree(ptr);
}

u32 hashfn(const void *data, u32 len, u32 seed)
{
	return jhash(data, len, seed);
}

u32 hash_entry_hashfn(const void *data, u32 len, u32 seed)
{
	struct hash_entry *entry = (struct hash_entry *)data;
	return jhash(&entry->kv.key, sizeof(entry->kv.key), seed);
}

// Function to compare key with object
int key_entry_cmp(struct rhashtable_compare_arg *arg, const void *obj)
{
	struct hash_entry *entry = (struct hash_entry *)obj;
	return *(u64 *)arg->key - entry->kv.key;
}

static int __init start_init(void)
{
	u64 i;
	struct hash_entry *entry;
	struct rhashtable_params param = {
		.key_len = sizeof(u64),
		.head_offset = offsetof(struct hash_entry, node),
		.hashfn = hashfn,
		.obj_hashfn = hash_entry_hashfn,
		.obj_cmpfn = key_entry_cmp,
		.automatic_shrinking = true,
	};
	struct rhashtable rht;
	int ret = rhashtable_init(&rht, &param);
	printk("rhashtable_init returns %d\n", ret);
	if (ret < 0)
		return ret;
	for (i = 0; i < (1 << 20); ++i) {
		// entry = kmalloc(sizeof(struct hash_entry), GFP_KERNEL);
		entry = kzalloc(sizeof(struct hash_entry), GFP_KERNEL);
		if (entry == NULL) {
			printk("kzalloc returns NULL\n");
			goto err_exit;
		}
		entry->kv.key = i;
		entry->kv.value = i * i;
		// printk("Inserting %llu %llu\n", entry->key, entry->value);
		while (1) {
			// rhashtable_insert_fast 不检查这个元素是否已经存在，而是直接插入
			ret = rhashtable_insert_fast(&rht, &entry->node, param);
			// 如果插入太快，尤其是多线程插入的时候，可能会返回-EBUSY。好像是因为需要触发table
			// resizing，但是同一时间只能有一个table
			// resizing任务，所以就返回-EBUSY。此时需要schedule一下然后重试。
			if (ret != -EBUSY)
				break;
			schedule();
		}
		if (ret < 0) {
			kfree(entry);
			printk("rhashtable_insert_fast returns %d\n", ret);
			goto err_exit;
		}
		// hashtable_lookup_insert_key
		// 会检查元素是否已经存在，如果已经存在就返回-EEXIST，不存在则插入并返回0
		ret = rhashtable_lookup_insert_key(&rht, &i, &entry->node,
						   param);
		BUG_ON(ret != -EEXIST);
	}
	for (i = 0; i < (1 << 20); ++i) {
		// 如果可以保证entry不被删掉，那么可以用rhashtable_lookup_fast
		entry = rhashtable_lookup_fast(&rht, &i, param);
		if (entry == NULL) {
			printk("rhashtable_lookup_fast returns NULL\n");
			goto err_exit;
		}
		if (entry->kv.value != i * i) {
			printk("%llu %llu\n", i, entry->kv.value);
			goto err_exit;
		}

		// 如果另一个线程可能会删掉entry，那么需要一直拿着read
		// lock直到不再需要entry
		rcu_read_lock();
		entry = rhashtable_lookup(&rht, &i, param);
		if (entry == NULL) {
			printk("rhashtable_lookup returns NULL\n");
			goto err_exit;
		}
		if (entry->kv.value != (u64)i * i) {
			printk("%llu %llu\n", i, entry->kv.value);
			goto err_exit;
		}
		rcu_read_unlock();
	}
err_exit:
	rhashtable_free_and_destroy(&rht, hash_entry_free, NULL);
	return 0;
}

static void __exit end_exit(void)
{
}

module_init(start_init) module_exit(end_exit)
