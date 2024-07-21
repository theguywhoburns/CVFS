#include "ht.h"
#include <stdio.h>
#include <string.h>

typedef const char* ccp;


#define ccp_ht_dtor(x) free(x)
#define int_ht_dtor(x) (unsigned int)x

size_t ccp_ht_hash(ccp key) {
	size_t ret = 0;
	const int len = strlen(key);
	__HASHFUNC_FNV1A(ret, key, len);
	return ret;
}

#define ccp_copy(x) strdup(x)
#define int_copy(x) x

#define ccp_ht_equal(x, y) strcmp(x, y)

define_ht_all(ccp, int);
define_ht_all_impl(ccp, int);


int main(int argc, char **argv) {
	ccp_int_ht_t ht = ccp_int_ht_create();
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
	ccp_int_ht_set(&ht, "Zero", 0);
	ccp_int_ht_set(&ht, "One", 1);
	ccp_int_ht_set(&ht, "Two", 2);
	ccp_int_ht_set(&ht, "Three", 3);
	ccp_int_ht_set(&ht, "Four", 4);
	ccp_int_ht_set(&ht, "Five", 5);
	ccp_int_ht_set(&ht, "Six", 6);
	ccp_int_ht_set(&ht, "Seven", 7);
	ccp_int_ht_set(&ht, "Eight", 8);
	ccp_int_ht_set(&ht, "Nine", 9);

	int d = ccp_int_ht_get(&ht, "Nine");
	ccp_int_ht_remove(&ht, "One");
	bool e = ccp_int_ht_exists(&ht, "One"); 
	ccp_int_ht_set(&ht, "One", 1);
	e = ccp_int_ht_exists(&ht, "One"); 

	ccp_int_ht_dump(&ht);
	e = ccp_int_ht_exists(&ht, "One"); 
	ccp_int_ht_removeAll(&ht);
	
	ccp_int_ht_destroy(&ht);
	return 0;
}