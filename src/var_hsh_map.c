#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "../include/var_hsh_map.h"
#include "../include/utils.h"

// Set initial capacity to 16
const size_t init_capacity = 16;

// Hashing constants
const uint32_t fnv_prime = 16777619;
const uint32_t fnv_offset = 2166136261;

// Return 32-bit FNV-1a hash for key
static uint64_t hash_key(const char* key) {
	uint32_t hash = fnv_offset;

	for (const char* p = key; *p; p++) {
		hash ^= (uint32_t)(unsigned char)(*p);
		hash *= fnv_prime;
	}
	return hash;
}

ht* ht_create(void) {
	// Alloc space for struct
	ht* table = safe_malloc(sizeof(ht));
	if (table == NULL) {
		return NULL;
	}
	table->length = 0;
	table->capacity = init_capacity;

	// Allocate zero'd space for entry slots
	table->entries = safe_calloc(table->capacity, sizeof(ht_entry));
	if (table->entries == NULL) {
		free(table);
		return NULL;
	}
	return table;
}

void ht_destroy(ht* table) {
	// Free allocated keys
	for (size_t i = 0; i < table->capacity; i++) {
		free((void*)table->entries[i].key);
	}

	// Free entries array and table
	free(table->entries);
	free(table);
}

void* ht_get(ht* table, const char* key) {
	// Hash key using hashing algorithm
	uint32_t hash = hash_key(key);
	size_t i = (size_t)(hash & (uint32_t)(table->capacity - 1)); // prevent overflow

	// Loop until empty entry is found
	while (table->entries[i].key != NULL) {
		// If match found, return it
		if (strcmp(key, table->entries[i].key) == 0) {
			return table->entries[i].value;
		}

		// Key not found, iterate
		i++;

		// If at end of table, wrap around
		if (i >= table->capacity) {
			i = 0;
		}
	}
	return NULL;
}

// Replace or insert an entry
static const char* ht_set_entry(ht_entry* entries, size_t capacity,
		const char* key, void* value, size_t* out_length) {
	// Hash key using hashing algorithm
	uint32_t hash = hash_key(key);
	size_t i = (size_t)(hash & (uint32_t)(capacity - 1));

	// Loop until empty entry is found
	while (entries[i].key != NULL) {
		// Check for duplicate and update value
		if (strcmp(key, entries[i].key) == 0) {
			entries[i].value = value;
			return entries[i].value;
		}

		// Key not found, iterate
		i++;

		// If at end of table, wrap around
		if (i >= capacity) {
			i = 0;
		}
	}
	
	// Didn't find duplicate key, reallocate and insert
	if (out_length != NULL) {
		key = safe_strdup(key);
		if (key == NULL) {
			return NULL;
		}
		(*out_length)++; // increment length
	}

	// Insert new entry
	entries[i].key = (char*)key;
	entries[i].value = value;
	return key;
}

// Expand table capacity
static bool ht_expand(ht* table) {
	// Double capacity
	size_t new_capacity = table->capacity * 2;
	if (new_capacity < table->capacity) {
		return false; // expansion failed
	}

	// Allocate memory
	ht_entry* new_entries = safe_calloc(new_capacity, sizeof(ht_entry));
	if (new_entries == NULL) {
		return false; // allocation failed
	}

	// Iterate and copy valuable entries to new table
	for (size_t i = 0; i < table->capacity; i++) {
		ht_entry entry = table->entries[i];
		if (entry.key != NULL) {
			ht_set_entry(new_entries, new_capacity,
					entry.key, entry.value, NULL);
		}
	}

	// Free old data and update table's fields
	free(table->entries);
	table->entries = new_entries;
	table->capacity = new_capacity;
	return true;
}

// Replace or insert a key
const char* ht_set(ht* table, const char* key, void* value) {
	// Ensure operation is safe
	if (value == NULL) {
		return NULL;
	}

	// If table is half full expand it
	if (table->length >= table->capacity / 2) {
		if (!ht_expand(table)) { // check if expand succeeded
			return NULL;
		}
	}

	return ht_set_entry(table->entries, table->capacity, key, value, &table->length);
}

// Retrieve length of table
size_t ht_length(ht* table) {
	return table->length;
}

// Create iterator
hti ht_iterator(ht* table) {
	hti it;
	it._table = table;
	it._index = 0;
	return it;
}

bool ht_next(hti* it) {
	ht* table = it->_table;
	while (it->_index < table->capacity) {
		size_t i = it->_index;
		it->_index++;
		if (table->entries[i].key != NULL) {
			ht_entry entry = table->entries[i];
			it->key = entry.key;
			it->value = entry.key;
			it->value = entry.value;
			return true;
		}
	}
	return false;
}

