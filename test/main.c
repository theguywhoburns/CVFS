#include "ht.h"
#include <stdio.h>
#include <string.h>

typedef const char* ccp;
__define_ht_main(ccp, int);

size_t ccp_ht_hash(const char* key) {
	size_t ret = 0;
	const size_t _keysize = strlen(key);
	__HASHFUNC_FNV1A(ret, key, _keysize);
	return ret;
}

void int_ht_dtor(int key) {
	//DO NOTHING
}

void ccp_ht_dtor(ccp key) {
	//DO NOTHING
}

bool ccp_ht_equal(const char* key1, const char* key2) {
	return strcmp(key1, key2) == 0;
}

void ccp_int_ht_dump(ccp_int_ht* ht) {
	for (int i = 0; i < ht->size; i++) {
		___ht_entry_ccp_int *cur = ht->entries[i];
		if(cur != NULL) printf("\n[%d]: ", i);
		while (cur != NULL) {
			printf("%s:%d;", cur->key, cur->val);
			cur = cur->next;
		}
	}
}

__define_ht_main_impl(ccp, int);

int main(int argc, char **argv) {
	ccp_int_ht* ht = ccp_int_ht_init();

	/*
	[163]: waldo:fred;
	[644]: plugh:xyzzy;
	[656]: hello:world;
	[2553]: thud:thud;
	[3856]: foo:bar;
	[6509]: fred:plugh;
	[7873]: baz:qux;
	[8411]: quux:corge;
	[9551]: grault:garply;
	[9986]: xyzzy:thud;
	*/
	ccp_int_ht_set(ht, "Zero", 0);
	ccp_int_ht_set(ht, "One", 1);
	ccp_int_ht_set(ht, "Two", 2);
	ccp_int_ht_set(ht, "Three", 3);
	ccp_int_ht_set(ht, "Four", 4);
	ccp_int_ht_set(ht, "Five", 5);
	ccp_int_ht_set(ht, "Six", 6);
	ccp_int_ht_set(ht, "Seven", 7);
	ccp_int_ht_set(ht, "Eight", 8);
	ccp_int_ht_set(ht, "Nine", 9);	

	ccp_int_ht_dump(ht);
	ccp_int_ht_destroy(ht);
	return 0;
}