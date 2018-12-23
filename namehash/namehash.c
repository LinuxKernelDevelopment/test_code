#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct namehash {
	char *name;
	u_int32_t hash;
} namehash_t;

typedef struct namehashLink {
	namehash_t *element;
	struct namehashLink *next;
} namehashLink_t;

static inline u_int32_t rol32(u_int32_t word, unsigned int shift)
{
	return (word << shift) | (word >> ((-shift) & 31));
}

u_int32_t
hashname(const u_int8_t *name, int namelen)
{
	u_int32_t hash;

	for (hash = 0; namelen >= 4; namelen -= 4, name += 4)
		hash = (name[0] << 21) ^ (name[1] << 14) ^ (name[2] << 7) ^
			(name[3] << 0) ^ rol32(hash, 7 * 4);

	switch (namelen) {
	case 3:
		return (name[0] << 14) ^ (name[1] << 7) ^ (name[2] << 0) ^
			rol32(hash, 7 * 3);
	case 2:
		return (name[0] << 7) ^ (name[1] << 0) ^ rol32(hash, 7 * 2);
	default:
		return hash;
	}
}

namehashLink_t* insert_namehashList(namehashLink_t *head, namehash_t *tmp)
{
	namehashLink_t *it = NULL, *prev = NULL;
	namehashLink_t *list_tmp = (namehashLink_t *) malloc(sizeof(namehashLink_t));
	list_tmp->element = tmp;
	list_tmp->next = NULL;
	if (head == NULL) {
		head = list_tmp;
	}
	else {
		prev = head;
		while (prev->next != NULL) {
			if (tmp->hash < prev->next->element->hash)
				break;
			if (prev->next != NULL)
				prev = prev->next;
		}
		if (tmp->hash >= prev->element->hash) {
			list_tmp->next = prev->next;
			prev->next = list_tmp;
		} else {
			list_tmp->next = prev;
			if (prev == head)
				head = list_tmp;
		}
	}
	return head;
}

void output_namehashList(namehashLink_t *head)
{
	namehashLink_t *it = head;
	while (it != NULL) {
		printf("name:%s, hash:0x%x\n", it->element->name, it->element->hash);
		if (it->next != NULL)
			it = it->next;
		else
			break;
	}
}

int main()
{
	namehashLink_t *head = NULL;
	char str[256] = {0 };
	u_int32_t hashval = 0;

	while (strcmp(str, "stop") != 0) {
		scanf("%s", str);
		hashval = hashname(str, strlen(str));
		namehash_t *tmp = (namehash_t *) malloc(sizeof(namehash_t));
		tmp->name = (char *) malloc(strlen(str) + 1);
		strcpy(tmp->name, str);
		tmp->hash = hashval;
		head = insert_namehashList(head, tmp);
	}
	output_namehashList(head);
	return 0;
}

