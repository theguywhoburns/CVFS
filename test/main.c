#include "jht.h"
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
ccp_int_ht_t ccp_int_ht_create() {
    return ccp_int_ht_create_ex(10000, 0.75);
} ccp_int_ht_t ccp_int_ht_create_ex(size_t ht_arr_capacity, double max_load_factor) {
    ccp_int_ht_t ht = { 0 }; ht.entries = (___ht_entry_ccp_int*)malloc(sizeof(___ht_entry_ccp_int) * ht_arr_capacity); memset(ht.entries, 0, sizeof(___ht_entry_ccp_int) * ht_arr_capacity); ht.size = ht_arr_capacity; ht.max_load_factor = max_load_factor; return ht;
} void ccp_int_ht_set(ccp_int_ht_t* ht, ccp key, int val) {
    const uint64_t powers_of_2[] = { 1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536, 131072, 262144, 524288, 1048576, 2097152, 4194304, 8388608, 16777216, 33554432, 67108864, 134217728, 268435456, 536870912, 1073741824, 2147483648, 4294967296 }; size_t index = ccp_ht_hash(key) % ht->size; ___ht_entry_ccp_int* current_entry = &ht->entries[index]; uint32_t power_of_two = 0; while (current_entry->is_set) {
        int comparison = strcmp(current_entry->key, key); if (comparison == 0) {
            (unsigned int)current_entry->val; current_entry->val = val; break;
        }
        else {
            if (power_of_two == 33) {
                power_of_two = 0;
            } index = (index + powers_of_2[power_of_two++]) % ht->size; current_entry = &ht->entries[index];
        }
    } if (!current_entry->is_set) {
        ht->length++; current_entry->is_set = 1; current_entry->key = strdup(key); current_entry->val = val;
    } if ((double)ht->length / ht->size > ht->max_load_factor) {
        ccp_int_ht_resize(ht);
    }
} int ccp_int_ht_get(ccp_int_ht_t* ht, ccp key) {
    const uint64_t powers_of_2[] = { 1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536, 131072, 262144, 524288, 1048576, 2097152, 4194304, 8388608, 16777216, 33554432, 67108864, 134217728, 268435456, 536870912, 1073741824, 2147483648, 4294967296 }; size_t index = ccp_ht_hash(key) % ht->size; ___ht_entry_ccp_int* current_entry = &ht->entries[index]; uint32_t power_of_two = 0; while (current_entry->is_set) {
        int comparison = strcmp(current_entry->key, key); if (comparison == 0) {
            return current_entry->val;
        }
        else {
            if (power_of_two == 33) {
                power_of_two = 0;
            } index = (index + powers_of_2[power_of_two++]) % ht->size; current_entry = &ht->entries[index];
        }
    } (void)((!!(0 && "key not found")) || (_wassert(L"false && \"key not found\"", L"C:\\Users\\josdd\\repos\\p\\CVFS\\test\\main.c", (unsigned)(24)), 0));
} _Bool ccp_int_ht_exists(ccp_int_ht_t* ht, ccp key) {
    const uint64_t powers_of_2[] = { 1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536, 131072, 262144, 524288, 1048576, 2097152, 4194304, 8388608, 16777216, 33554432, 67108864, 134217728, 268435456, 536870912, 1073741824, 2147483648, 4294967296 }; size_t index = ccp_ht_hash(key) % ht->size; ___ht_entry_ccp_int* current_entry = &ht->entries[index]; uint32_t power_of_two = 0; while (current_entry->is_set) {
        int comparison = strcmp(current_entry->key, key); if (comparison == 0) {
            return 1;
        }
        else {
            if (power_of_two == 33) {
                power_of_two = 0;
            } index = (index + powers_of_2[power_of_two++]) % ht->size; current_entry = &ht->entries[index];
        }
    } return 0;
} void ccp_int_ht_remove(ccp_int_ht_t* ht, ccp key) {
    const uint64_t powers_of_2[] = { 1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536, 131072, 262144, 524288, 1048576, 2097152, 4194304, 8388608, 16777216, 33554432, 67108864, 134217728, 268435456, 536870912, 1073741824, 2147483648, 4294967296 }; size_t index = ccp_ht_hash(key) % ht->size; ___ht_entry_ccp_int* current_entry = &ht->entries[index]; uint32_t power_of_two = 0; while (current_entry->is_set) {
        int comparison = strcmp(current_entry->key, key); if (comparison == 0) {
            (unsigned int)current_entry->val; current_entry->is_set = 0; ht->length--; break;
        }
        else {
            if (power_of_two == 33) {
                power_of_two = 0;
            } index = (index + powers_of_2[power_of_two++]) % ht->size; current_entry = &ht->entries[index];
        }
    } if ((double)ht->length / ht->size > ht->max_load_factor) {
        ccp_int_ht_resize(ht);
    }
} void ccp_int_ht_resize(ccp_int_ht_t* ht) {
    const uint64_t powers_of_2[] = { 1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536, 131072, 262144, 524288, 1048576, 2097152, 4194304, 8388608, 16777216, 33554432, 67108864, 134217728, 268435456, 536870912, 1073741824, 2147483648, 4294967296 }; uint32_t power_of_two = 0; ccp_int_ht_t new_ht = ccp_int_ht_create_ex(ht->size * 2, ht->max_load_factor); for (size_t i = 0; i < ht->size; i++) {
        if (!ht->entries[i].is_set) {
            continue;
        } ___ht_entry_ccp_int cur = ht->entries[i]; size_t index = ccp_ht_hash(cur.key) % new_ht.size; ___ht_entry_ccp_int* current_entry = &new_ht.entries[index]; uint32_t power_of_two = 0; while (current_entry->is_set) {
            if (power_of_two == 33) {
                power_of_two = 0;
            } index = (index + powers_of_2[power_of_two++]) % new_ht.size; current_entry = &new_ht.entries[index];
        } current_entry->is_set = 1; current_entry->key = cur.key; current_entry->val = cur.val; new_ht.length++;
    } free(ht->entries); *ht = new_ht;
} void ccp_int_ht_dump(ccp_int_ht_t* ht) {
    for (int i = 0; i < ht->size; i++) {
        ___ht_entry_ccp_int* cur = &ht->entries[i]; if (!cur->is_set) continue; free(cur->key); (unsigned int)cur->val; ht->entries[i] = (___ht_entry_ccp_int){ 0 };
    }
} void ccp_int_ht_removeAll(ccp_int_ht_t* ht) {
    if (!ht && ht->length != 0) return; ccp_int_ht_destroy(ht); *ht = ccp_int_ht_create();
} void ccp_int_ht_merge(ccp_int_ht_t* ht0, ccp_int_ht_t* ht1) {
    if (!ht0 || !ht1) return;
    ccp_int_ht_t* left = NULL;
    ccp_int_ht_t* right = NULL;
    if (ht0->size > ht1->size) {
        left = ht0;
        right = ht1;
    }
    else if (ht0->size < ht1->size) {
        left = ht1;
        right = ht0;
    }
    else {
        left = ht0;
        right = ht1;
    }
    for (size_t i = 0; i < right->size; i++) {
        ___ht_entry_ccp_int* pair = &right->entries[i];
        if (!pair->is_set) continue; 
        ccp_int_ht_set(left, pair->key, pair->val);
    }
    ccp_int_ht_destroy(ht1);
} void ccp_int_ht_destroy(ccp_int_ht_t* ht) {
        for (int i = 0; i < ht->size; i++) {
            ___ht_entry_ccp_int* cur = &ht->entries[i]; 
            free(cur->key); 
            (unsigned int)cur->val;
            ht->entries[i] = (___ht_entry_ccp_int){ 0 };
        } 
        free(ht->entries); 
        ht->entries = ((void*)0); 
        ht->size = 0; 
        ht->length = 0; 
        ht->max_load_factor = 0;
    };


int main(int argc, char** argv) {
	ccp_int_ht_t ht0 = ccp_int_ht_create();
    ccp_int_ht_t ht1 = ccp_int_ht_create();
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
	ccp_int_ht_set(&ht0, "Zero", 0);
	ccp_int_ht_set(&ht0, "One", 1);

	ccp_int_ht_set(&ht1, "Two", 2);
	ccp_int_ht_set(&ht1, "Three", 3);

    ccp_int_ht_merge(&ht0, &ht1);
    
	ccp_int_ht_destroy(&ht0);
	return 0;
}