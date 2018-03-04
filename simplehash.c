#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// K&R Pg. 144-145

struct nlist {              // table entry:
    char *name;             // defined name
    char *defn;             // replacement text
};

#define HASHSIZE 101
static struct nlist *hashtab[HASHSIZE]; // pointer table

// hash: form hash value for string
unsigned hash(char *s)
{
    unsigned hashval;

    for (hashval = 0; *s != '\0'; s++)
        hashval = *s + 31 * hashval;
    return hashval % HASHSIZE;
}

// lookup:look for s in hashtab
struct nlist *lookup(char *s)
{
    // return np w/ the hash
    return hashtab[hash(s)];
}

struct nlist *lookup(char *);

// install:put (name, defn) in hashtab
struct nlist *install(char *name, char *defn)
{
    struct nlist *np;
    unsigned hashval;

    if ((np = lookup(name)) == NULL) { // not found
        np = (struct nlist *) malloc(sizeof(*np));
        if (np == NULL || (np->name = strdup(name)) == NULL)
            return NULL;
        hashval = hash(name);
        hashtab[hashval] = np;
    } 
    else // already there
    {
        free((void *) np->defn); // free previous defn
    }

    if ((np->defn = strdup(defn)) == NULL)
        return NULL;

    return np;
}


int main()
{
    // Example of using a hash table
    install("A", "65");
    install("B", "66");
    install("C", "67");

    struct nlist *n = lookup("B");

    printf("%s", n->defn);

    return 0;
}
