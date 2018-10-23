#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <time.h>
#include "list.h"

#define UNUSED(x) (void)(x)

/**
 * {@inheritdoc}
 */
void init_list(struct list_s *list,int sizeValue){
	list->size=0;
	list->elements=NULL;
	list->magic=MAGIC_LIST;
	list->sizeValue=sizeValue;
}

/**
 * {@inheritdoc}
 */
int add(struct list_s *list,void *value){
	assertList(list,"add");

	return addElment(list,value,0);
}

/**
 * {@inheritdoc}
 */
int addIndex(struct list_s *list,void *value,int index){
	assertList(list,"addIndex");
	
	return addElment(list,value,index);
}

/**
 * {@inheritdoc}
 */
static int addElment(struct list_s *list,void *value,int index){
	struct element_s *next;
	struct element_s *element;
	struct container_s *container;

	/* Current element in index */	
	next=getElement(list,index);

	/* Create new element */
	element=malloc(sizeof(struct element_s));
	container=malloc(sizeof(struct container_s));
	assertError(element && container,"Error when try to allow memory","addElement");

	container->value=value;
	container->size=list->sizeValue;
	
	element->container=container;
	/* Update element in list */
	if(next!=NULL){
		element->next=next;
		element->prev=next->prev;
		next->prev->next=element;
		next->prev=element;
	}
	else{
		element->prev=element;
		element->next=element;
		list->elements=element;
	}
	list->size++;

	return 1;
}

/**
 * {@inheritdoc}
 */
static struct element_s *getElement(struct list_s *list,int index){
	struct element_s *it;
	int i;
	
	if(!list->size)
		return NULL;
	assertError(!(index>=list->size || index<=-list->size),"Erreur index out of range","getElement");
	
	if(index>=0)
		for(i=0,it=list->elements;i<index;i++,it=it->next);
	else
		for(i=0,it=list->elements;i>index;i--,it=it->prev);
	
	return it;
}

/**
 * {@inheritdoc}
 */
int removeIndex(struct list_s *list,int index){
	struct element_s *element;

	assertError(list->size, "Error empty list", "removeIndex");
	assertList(list, "removeIndex");

	element=getElement(list, index);	
	remove_element(list, element);

	return 1;
}

/**
 * {@inheritdoc}
 */
static void remove_element(struct list_s *list, struct element_s *element){
	
	/* Update elements and list */	
	element->next->prev=element->prev;
	element->prev->next=element->next;

	list->size--;
	if(list->elements == element)
		list->elements=element->next;
	if(list->size==0)
		list->elements=NULL;

	/* Free element */
	free(element->container);
	free(element);
}

/**
 * {@inheritdoc}
 */
void *getValue(struct list_s *list,int index){
	return getElement(list,index)->container->value;
}

/**
 * {@inheritdoc}
 */
int getSize(struct list_s *list){
	return list->size;		
}

/**
 * {@inheritdoc}
 */
int	removeList(struct list_s *list){
	struct iterator_s it;
	struct element_s *element;

	assertList(list,"removeList");
	
	/* Init iterator */
	init_Iterator(list,&it);
	
	/* free all elements */	
	while(hasNext(&it)){
		element=nextElement(&it);
		free(element->container);
		free(element);
	}	
	
	free(list);

	return 1;
}

/**
 * {@inheritdoc}
 */
void remove_value(struct list_s *list, void *arg, func f){
	struct element_s *current;
	struct container_s *container;
	int size, i;
	
	size = list->size;
	current = list->elements;

	for(i = 0; i < size; i++, current = current->next){
		container = current->container;
		if(!f(arg, container->value)){
			remove_element(list, current);
			return;
		}
	}
}

/**
 * {@inheritdoc}
 */
int copyList(struct list_s *list,struct list_s *newList){
	struct iterator_s *it;
	struct element_s *next;
	struct element_s *copy;

	assertList(list,"copyList");

	/* Init new list */
	init_list(newList,list->sizeValue);
    newList->size=list->size;
	
	/* Init iterator */
	init_Iterator(list,it);
	
	/* Initialisation of first element */
	next=nextElement(it);
	copy=newList->elements=copyElement(next);
	
	/* Copy of all elements */	
	while(hasNext(it)){
		next=nextElement(it);
		copy=copy->next=copyElement(next);
	}
	
	/* Update last element */
	newList->elements->prev=copy;
	copy->next=newList->elements;
	
	return 1;
}

/**
 * {@inheritdoc}
 */
static struct element_s *copyElement(struct element_s *element){
	struct element_s *res;
	struct container_s *container;
	
	res=malloc(sizeof(struct element_s));
	container=malloc(sizeof(struct container_s));

	assertError(element && container,"Error when try to allow memory","concat");	
	container->value=element->container->value;
	container->size=element->container->size;

	res->container=container;
	
	return res;
}

/**
 * {@inheritdoc}
 */
void concat (struct list_s *list ,struct list_s *firstList ,struct list_s *secondList){
	struct list_s *copy;
	
	assertList(firstList,"concat");
	assertList(secondList,"concat");
	assertError(firstList->sizeValue==secondList->sizeValue,"Doesn't have same type","concat");
	
	/* Init new list */
	init_list(list,firstList->sizeValue);
	list->size=firstList->size+secondList->size;
	
	/* Copy first list */
	copyList(firstList,copy);
	list->elements=copy->elements;
	
	/* Copy second list and merge */
	copyList(secondList,copy);
	list->elements->prev=copy->elements;
	copy->elements->next=list->elements;
}

/**
 * {@inheritdoc}
 */
void merge (struct list_s *list,struct list_s *secondList,func f){
	struct iterator_s *itFirst;
	struct iterator_s *itSecond;
	struct iterator_s *itLast;
	struct element_s *current;
	struct element_s *previous;
	struct element_s *firstElement;
	struct element_s *secondElement;
	
	assertList(list, "merge");
	assertList(secondList, "merge");

	/* Initialization */
	init_Iterator(list,itFirst);
	init_Iterator(secondList,itSecond);
	
	/* First check */
	firstElement = nextElement(itFirst);
	secondElement = nextElement(itSecond);
	previous = current = check(firstElement,secondElement,f);
	
	/* Update list */
	list->elements = current;
	list->size += secondList->size;
	
	if(current==firstElement)
		firstElement = nextElement(itFirst);
	else
		secondElement = nextElement(itSecond);
	
	/* check first element */
	while(hasNext(itFirst) && hasNext(itSecond)){
		/* Update element */
		current=check(firstElement,secondElement,f);
		current->prev = previous;
		previous->next = current;
	
		if(current == firstElement)
			firstElement = nextElement(itFirst);
		else
			secondElement = nextElement(itSecond);

		previous = current;
	}
	
	/* merge last list into list*/
	if(hasNext(itFirst))
		itLast = itFirst;
	else
		itLast = itSecond;

	current = nextElement(itLast);	
	current->prev = previous;
	previous->next = current;

	/* Go to last element */ 	
	while(hasNext(itLast))
		current = nextElement(itLast);
	
	
	/* Update last element */
	current->next = list->elements;
	list->elements = current;	
}


/**
 * {@inheritdoc}
 */
static struct element_s *check(struct element_s *first,struct element_s *second,func f){
		void *firstValue;
		void *secondValue;
		
		firstValue=first->container->value;
		secondValue=second->container->value;

		/* first element big than second*/
		if(f(firstValue,second)>=0)
			return second;			
		else
			return firstValue;
}

/**
 * {@inheritdoc}
 */
void sortList(struct list_s *list, func f){
	sort_list_with_swap(list, f, basic_swap);
}

/**
 * {@inheritdoc}
 */
void sort_list_with_swap(struct list_s *list, func f, swap fswap){
	struct element_s *first;
	first = list->elements;

	speedSort(0, list->size-1, first, first->prev, f, fswap);
}

/**
 * {@inheritdoc}
 */
void sort_lineaire(struct list_s *list, func f, apply fapply){
	struct element_s *current;
	int i;

	current = list->elements;

	for(i = 0; i < list->size; i++){
		local_search(current, f, list->size-i);
		fapply(current->container->value);
		current = current->next;
	}
}

/**
 * {@inheritdoc}
 */
static void local_search(struct element_s* first, func f, int size){
	int i;
	struct element_s *cu, *ch;
	
	for(i = 1, cu = ch = first; i < size; i++){
		cu = cu->next;
		
		//Permut pour laissé le plus petit en premier
		if(f(ch->container->value, cu->container->value) > 0)
			swap_value(ch, cu, basic_swap);
	}
}

/**
 * {@inheritdoc}
 */
static void speedSort(int first,int last,struct element_s *firstElement, struct element_s *lastElement,func f, swap fswap){
	struct tuple_s pivotIndex;

	if(last > first){
		partition(first, last, firstElement, lastElement, &pivotIndex, f, fswap);
		speedSort(first, pivotIndex.index-1, firstElement, pivotIndex.pivot->prev, f, fswap);
		speedSort(pivotIndex.index+1, last, pivotIndex.pivot->next, lastElement, f, fswap);
	}
}

/**
 * {@inheritdoc}
 */
static void partition(int first, int last, struct element_s *firstElement, struct element_s *lastElement, struct tuple_s *res, func f, swap fswap){
	void *pivotValue;
	struct element_s *pivotElement;

	/* Get first element for start pivot */
	pivotElement = firstElement;
	pivotValue = pivotElement->container->value;

	firstElement = firstElement->next;
	first++;

	while(first <= last){
		/* Pivot smaller than first element*/
		if(f(pivotValue, firstElement->container->value) <= 0){
			swap_value(firstElement, lastElement, fswap);
			lastElement = lastElement->prev;
			last--;
		}
		else{
			swap_value(pivotElement, firstElement, fswap);
			pivotElement = firstElement;
			firstElement = firstElement->next;
			first++;
		}
	}
	res->pivot = pivotElement;
	res->index = --first;
}

/**
 * {@inheritdoc}
 */
static void swap_value(struct element_s *firstElement, struct element_s *secondElement, swap fswap){
	struct container_s *container;
	
	//Apply swap element function
	fswap(firstElement->container->value, secondElement->container->value);
	
	//Swap container
	container = firstElement->container;
	firstElement->container = secondElement->container;
	secondElement->container = container;
}

/**
 * {@inheritdoc}
 */
static void swap_element(struct element_s *first_element, struct element_s *second_element){
	struct element_s *tmp;

	first_element->prev->next = second_element;
	first_element->next->prev = second_element;

	second_element->prev->next = first_element;
	second_element->next->prev = second_element;

	tmp = first_element->prev;
	first_element->prev = second_element->prev;
	second_element->prev = tmp;

	tmp = first_element->prev;
	first_element->prev = second_element->prev;
	second_element->next = tmp;
	
	return;
}

/**
 * {@inheritdoc}
 */
void basic_swap (void * arg, void *arg2){
	UNUSED(arg);
	UNUSED(arg2);
	return;
}

/**
 * {@inheritdoc}
 */
void displayList(struct list_s *list,char * buffer,toString f){
	struct iterator_s *it;
	struct element_s *element;
	it=malloc(sizeof(struct iterator_s));
	
	init_Iterator(list,it);
	while(hasNext(it)){
		element=nextElement(it);
		f(element->container->value,buffer);
		printf("%s, ",buffer);
	}
	printf("\n");
}

/**
 * {@inheritdoc}
 */
void *findValue(struct list_s *list,void *value,func f){
	void *res;
	struct iterator_s *iterrator;
	
	assertList(list,"findValue");
	init_Iterator(list,iterrator);

	while(hasNext(iterrator))
		if(!f(value,(res=next(iterrator))))
			return res;
	return 0;

}

/**
 * {@inheritdoc}
 */
int contain(struct list_s *list,void *value,func f){
	struct iterator_s *iterrator;
	
	assertList(list,"contain");
	init_Iterator(list,iterrator);

	while(hasNext(iterrator))
		if(!f(value,next(iterrator)))
			return 1;
	return 0;
}

/**
 * {@inheritdoc}
 */
void init_Iterator(struct list_s *list,struct iterator_s *iterator){
	assertList(list,"init_Iterator");

	iterator->magic=MAGIC_ITERATOR;
	iterator->size=list->size;
	iterator->current=0;
	iterator->elements=list->elements;
}

/**
 * {@inheritdoc}
 */
int hasNext(struct iterator_s *iterator){
	assertIterator(iterator,"hasNext");

	return iterator->current<iterator->size;	
}

/**
 * {@inheritdoc}
 */
void *next(struct iterator_s *iterator){
	return nextElement(iterator)->container->value;
}

/**
 * {@inheritdoc}
 */
void shuffle(struct list_s *list){
	int rand, i, j, size;
	struct element_s *current_element, *first_element, *second_element;
	

	current_element = getElement(list,0);
	size = list->size;
	srandom(time(NULL));

	for(i = 0; i < size; i++){
		//Get first element
		rand = random()%size;
		for(j = 0; j < rand; j++)
			current_element = current_element->next;
		
		first_element = current_element;

		//Get second element
		rand = random()%size;
		for(j = 0; j < rand; j++)
			current_element = current_element->prev;

		second_element = current_element;

		swap_value(first_element, second_element, basic_swap);
	}
}

/**
 * {@inheritdoc}
 */
static struct element_s *nextElement(struct iterator_s *iterator){
	struct element_s *res;

	assertIterator(iterator,"nextElement");
	assertError(hasNext(iterator),"Error doesn't have next value","next_element");

	res=iterator->elements;
	iterator->elements=res->next;
	iterator->current++;
	
	return res;
}

/**
 * {@inheritdoc}
 */
static void assertList(struct list_s *list,char *back){
	assertError(list->magic==MAGIC_LIST,"Error corupted list",back);
}

/**
 * {@inheritdoc}
 */ 
static void assertIterator(struct iterator_s *iterator,char *back){
	assertError(iterator->magic==MAGIC_ITERATOR,"Error corupted iterator",back);
}

/**
 * {@inheritdoc}
 */
void assertError(int check,char *buffer,char *back){
	if(!check){
		printf("[ERROR]: %s\n", buffer);
		printf("Function : %s\n", back);
		assert(0);
	}
}
