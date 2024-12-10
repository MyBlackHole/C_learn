#if defined(__x86_64__)
static void *hook_vmalloc_map(void *addr)
{
	unsigned int level = 0;
	pte_t *pte = lookup_address((unsigned long)addr, &level);
	if (!pte) {
		return NULL;
	}

	if (pte->pte & ~_PAGE_RW) {
		pte->pte |= _PAGE_RW;
	}
	return addr;
}

static int hook_vmalloc_unmap(void *addr)
{
	unsigned int level = 0;
	pte_t *pte = lookup_address((unsigned long)addr, &level);
	if (!pte) {
		return -1;
	}

	pte->pte = pte->pte & ~_PAGE_RW;
	return 0;
}
#endif
