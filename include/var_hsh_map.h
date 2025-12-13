#include <stdio.h>
#include <stdbool.h>

/**
 * @brief Hash table entry slot.
 * Can be filled or empty.
 */
typedef struct {
	const char* key;	// NULL if slot is empty
	void* value;
} ht_entry;

/**
 * @brief Hash table struct for storing and retrieving data quickly.
 * Create with ht_create
 * Free with ht_destroy
 */
typedef struct {
	ht_entry* entries; 	// slots
	size_t capacity;	// size of entries array
	size_t length;		// items in hash table
} ht;

/**
 * @brief Create hash table and return its pointer or NULL.
 */
ht* ht_create(void);

/**
 * @brief Free memory associated with a hash table and its keys.
 */
void ht_destroy(ht* table);

/**
 * @brief Get item from hash table via its key.
 * Return value or NULL if not found.
 */
void* ht_get(ht* table, const char* key);

/**
 * @brief Update value of item in the hash table and return its address.
 * Return address of updated key or NULL.
 */
const char* ht_set(ht* table, const char* key, void* value);

/**
 * @brief Hash table iterator.
 * Create with ht_iterator
 * Iterate with ht_next
 */
typedef struct {
	const char* key; 	// current key
	void* value;		// current value
	
	// private, don't use externally
	ht* _table;			// reference to hash table
	size_t _index;		// current index
} hti;

/**
 * @brief Create a new hash table iterator.
 */
hti ht_iterator(ht* table);

/**
 * @brief Move iterator forward in hash table, update its fields.
 * Returns false if there are no more items.
 */
bool ht_next(hti* it);
