
#ifndef SIMPLEMAP_H
#define SIMPLEMAP_H

#include <string.h>

template<typename K>
struct defcmp
{
  bool operator()(const K& k1, const K& k2) {
    return k1 == k2;
  }
};

template<typename K, typename V, int capacity, typename comparator = defcmp<K> >
class SimpleMap
{
  public:
    /**
     * Initialize map
     */
    SimpleMap() {
      currentIndex = 0;
    }

    /**
     * Get the size of this map
     */
    unsigned int size() const {
      return currentIndex;
    }

    /**
     * Get a key at a specified index
     */
    K keyAt(unsigned int idx) {
      return keys[idx];
    }

    /**
     * Get a value at a specified index
     */
    V valueAt(unsigned int idx) {
      return values[idx];
    }

    /**
     * Check if a new assignment will overflow this map
     */
    bool willOverflow() {
      return (currentIndex + 1 > capacity);
    }

    /**
     * An indexer for accessing and assigning a value to a key
     * If a key is used that exists, it returns the value for that key
     * If there exists no value for that key, the key is added
     */
    V& operator[](const K& key) {
      if ( contains(key) ) {
        return values[indexOf(key)];
      }
      else if (currentIndex < capacity) {
        keys[currentIndex] = key;
        values[currentIndex] = nil;
        currentIndex++;
        return values[currentIndex - 1];
      }
      return nil;
    }

    /**
     * Get the index of a key
     */
    unsigned int indexOf(K key) {
      for (int i = 0; i < currentIndex; i++) {
        if ( cmp(key, keys[i]) ) {
          return i;
        }
      }
      return -1;
    }

    /**
     * Check if a key is contained within this map
     */
    bool contains(K key) {
      for (int i = 0; i < currentIndex; i++) {
        if ( cmp(key, keys[i]) ) {
          return true;
        }
      }
      return false;
    }

    /**
     * Check if a key is contained within this map
     */
    void remove(K key) {
      int index = indexOf(key);
      if ( contains(key) ) {
        for (int i = index; i < capacity - 1; i++) {
          keys[i] = keys[i + 1];
          values[i] = values[i + 1];
        }
        currentIndex--;
      }
    }

    void setNullValue(V nullv) {
      nil = nullv;
    }

    const char* toString() const {
      static char buffer[128];
      strcpy(buffer, "{");
      for(int i=0; i<currentIndex; i++) {
        if (i > 0) {
          strcat(buffer, ", ");
        }
        sprintf(buffer,"%s?=%d", buffer, values[i]); 
      }
      strcat(buffer, "}");
      return buffer; 
    }

  private:
    K keys[capacity];
    V values[capacity];
    V nil;
    int currentIndex;
    comparator cmp;
};

#endif
// SIMPLEMAP_H
