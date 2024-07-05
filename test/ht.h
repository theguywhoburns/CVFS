#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#define __HASHFUNC_FNV1A(ret, key, keysize) \
  ret = 0x811c9dc5; \
  for (size_t ___hash_i = 0; ___hash_i < keysize; ___hash_i++) { \
    ret ^= ((uint8_t *)key)[___hash_i]; \
    ret *= 0x01000193; \
  } \

#define __define_ht_entry(key_t, val_t) \
	typedef struct ___ht_entry_##key_t##_##val_t { \
		key_t key; \
		val_t val; \
		struct ___ht_entry_##key_t##_##val_t *next; \
	} ___ht_entry_##key_t##_##val_t

#define __define_ht(key_t, val_t) \
	typedef struct __ht_##key_t##_##val_t { \
		___ht_entry_##key_t##_##val_t **entries; \
		size_t size; \
	} key_t##_##val_t##_ht

#define __define_ht_init(key_t, val_t) \
	key_t##_##val_t##_ht *key_t##_##val_t##_ht_init_ex(size_t ht_arr_capacity);\
	key_t##_##val_t##_ht *key_t##_##val_t##_ht_init(void);

#define __define_ht_destroy(key_t, val_t) \
	void key_t##_##val_t##_ht_destroy(key_t##_##val_t##_ht *ht);
#define __define_ht_set(key_t, val_t) \
	void key_t##_##val_t##_ht_set(key_t##_##val_t##_ht *ht, key_t key, val_t val);
#define __define_ht_get(key_t, val_t) \
	val_t key_t##_##val_t##_ht_get(key_t##_##val_t##_ht *ht, key_t key);


#define __define_ht_init_impl(key_t, val_t) \
	key_t##_##val_t##_ht *key_t##_##val_t##_ht_init_ex(size_t ht_arr_capacity) {\
		key_t##_##val_t##_ht *ht = (key_t##_##val_t##_ht *)malloc(sizeof(key_t##_##val_t##_ht));\
		ht->entries = (___ht_entry_##key_t##_##val_t **)malloc(sizeof(___ht_entry_##key_t##_##val_t *) * ht_arr_capacity);\
		memset(ht->entries, 0, sizeof(___ht_entry_##key_t##_##val_t *) * ht_arr_capacity);\
		ht->size = ht_arr_capacity;\
		return ht;\
	}	\
	key_t##_##val_t##_ht *key_t##_##val_t##_ht_init(void) {\
		return key_t##_##val_t##_ht_init_ex(10000);\
	}

#define __define_ht_destroy_impl(key_t, val_t) \
	void key_t##_##val_t##_ht_destroy(key_t##_##val_t##_ht *ht) {\
		for (int i = 0; i < ht->size; i++) {\
			___ht_entry_##key_t##_##val_t *cur = ht->entries[i];\
			while(cur != NULL) {\
				key_t##_ht_dtor(cur->key);\
				val_t##_ht_dtor(cur->val);\
				___ht_entry_##key_t##_##val_t *next = cur->next;\
				free(cur);\
				cur = next;\
			}	\
		}\
		free(ht->entries);\
		free(ht);\
	}

#define __define_ht_set_impl(key_t, val_t) \
	void key_t##_##val_t##_ht_set(key_t##_##val_t##_ht *ht, key_t key, val_t val) {\
		size_t index = key_t##_ht_hash(key) % ht->size;\
		___ht_entry_##key_t##_##val_t *old_entry = ht->entries[index];\
		if(old_entry == NULL) {\
			ht->entries[index] = (___ht_entry_##key_t##_##val_t *)malloc(sizeof(___ht_entry_##key_t##_##val_t));\
			ht->entries[index]->key = key;\
			ht->entries[index]->val = val;\
			ht->entries[index]->next = NULL;\
			return;\
		}	\
		___ht_entry_##key_t##_##val_t *prev = NULL;\
		while (old_entry != NULL) { \
			if (key_t##_ht_equal(old_entry->key, key)) {	\
				val_t##_ht_dtor(old_entry->val);\
				old_entry->val = val;\
				return;	\
			}	\
			prev = old_entry;\
			old_entry = old_entry->next;\
		}	\
		prev->next = (___ht_entry_##key_t##_##val_t *)malloc(sizeof(___ht_entry_##key_t##_##val_t));\
		prev->next->key = key;\
		prev->next->val = val;\
		prev->next->next = NULL;\
	}

#define __define_ht_get_impl(key_t, val_t) \
	val_t key_t##_##val_t##_ht_get(key_t##_##val_t##_ht *ht, key_t key) {\
		size_t index = key_t##_ht_hash(key) % ht->size;\
		___ht_entry_##key_t##_##val_t *old_entry = ht->entries[index];\
		while (old_entry != NULL) { \
			if (key_t##_ht_equal(old_entry->key, key)) {	\
				if(old_entry->val == (val_t){0}) return (val_t){0};\
				return old_entry->val;	\
			}	\
			old_entry = old_entry->next;\
		}	\
		return (val_t){0};\
	}

#define __define_ht_main(key_t, val_t) \
	__define_ht_entry(key_t, val_t); \
	__define_ht(key_t, val_t); \
	__define_ht_init(key_t, val_t); \
	__define_ht_destroy(key_t, val_t); \
	__define_ht_set(key_t, val_t); \
	__define_ht_get(key_t, val_t);

#define __define_ht_main_impl(key_t, val_t) \
	__define_ht_init_impl(key_t, val_t); \
	__define_ht_destroy_impl(key_t, val_t); \
	__define_ht_set_impl(key_t, val_t); \
	__define_ht_get_impl(key_t, val_t);
	