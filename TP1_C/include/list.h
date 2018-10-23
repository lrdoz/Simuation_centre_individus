#define MAGIC_ITERATOR 40
#define MAGIC_LIST 42

#define LIST_H 1


/**
 *
 */
struct tuple_s{
	/**
	 *
	 */
	int index;
	/**
	 *
	 */
	struct element_s *pivot;
};

/**
 * struct element of list
 */
struct element_s {
	/**
	 * Next element
	 */
	struct element_s *next;
	/*
	 * Pevious element
	 */
	struct element_s *prev; 
	/**
	 * Element value
	 */
	struct container_s *container;
};

/**
 * struct container of value
 */
struct container_s{
	/**
	 * Value of container
	 */
	void *value;
	/**
	 * Memory size of value
	 */
	int size;
};

/**
 * struct of list
 */
struct list_s{
	/**
	 * First element in list
	 */
	struct element_s *elements;
	/**
	 * Size of list
	 */
	int size;
	/*
	 * Size memory of value
	 */
	int sizeValue;
	/*
	 * Check validity of type
	 */
	int magic;
};

/**
 * struct of iterator
 */
struct iterator_s {
	/*
	 * Elements repsent in iterator
	 */
	struct element_s* elements;
	/*
	 * Current value of iterator
 	 */
	int current;
	/*
	 * Size of list
	 */
	int size;
	/*
	 * Check validity of type
	 */
	int magic;
};

/**
 * Definition of compare function
 */
typedef int (*func)(void *arg1,void *arg2);

/**
 * Definition of swaping function
 */
typedef void (*swap)(void *arg1,void *arg2);

/**
 * Definition of cast value to string 
 */
typedef void (*toString)(void *arg1,char *buffer);

/**
 *
 */
typedef void (*apply)(void *arg); 

/**
 * Init struct of list
 *
 * @param list : pointer of list
 * @param sizeValue : size of Value element would contain in list
 */
void init_list(struct list_s *list,int sizeValue);

/**
 * Add element in list
 *
 * @param list : pointer of list 
 * @param element :  element want to add in list
 *
 * @return return if element is add else return 0 #Always return yes :x
 */
int add(struct list_s *list,void *element);

/**
 * Add element in list to index 
 *
 * @param list : pointer of list 
 * @param element :  element want to add in list
 * @param index : index want to add element
 *
 * @return return if element is add else return 0 #Always return yes :x
 */
int addIndex(struct list_s *list,void *element,int index);

/**
 * Add element in list to index 
 *
 * @param list : pointer of list 
 * @param element :  element want to add in list
 * @param index : index want to add element
 *
 * @return return if element is add else return 0 #Always return yes :x
 */
static int addElment(struct list_s *list,void *value,int index);

/**
 * Get element in index of list
 *
 * @param list : pointer of list
 * @param index : index of element
 * 
 * @return return element of list in index
 */
static struct element_s *getElement(struct list_s *list,int index);

/**
 * Remove element in index
 * 
 * @param list : pointer of list
 * @param index : index of element
 *
 * @return return 1 if element has remove else 0 #Always return 1 ^^
 */
int removeIndex(struct list_s *list,int index);

/**
 *  Removed elemnt in list
 *
 * @param list List we are looking for
 * @param element Element we are removed
 */
static void remove_element(struct list_s *list, struct element_s *element);

/**
 * Get Element of list in index
 *
 * @param list : pointer of list
 * @param index : index of element
 *
 * @return return element in index 
 */
void *getValue(struct list_s *list,int index);

/**
 * Return size of list
 * 
 * @param list : pointer of list
 * 
 * @return return size of list
 */
int getSize(struct list_s *list);

/**
 * Destroy list
 * 
 * @param list : pointer of list
 * 
 * @return return 1 if has remove list else 0 #Always return 1 ^^
 */
int removeList(struct list_s *list);

/**
 * Remove element in list
 *
 * @param list List we are looking for
 * @param arg arg we want remove
 * @param f function of comparaison
 */
void remove_value(struct list_s *list, void *arg, func f);

/**
 * Create copy of list
 *
 * @param list : pointer of previous list want to copy
 * @param newList : pointer of new list
 *
 * return 1 if has success copy list else return 0 #Always return 1 :x
 */
int copyList(struct list_s *prev,struct list_s *newList);

/**
 * Create a copy of element
 *
 * @param element : element want to copy
 *
 * return pointer of element copy
 */
static struct element_s *copyElement(struct element_s *element);

/**
 * Create list who concat first and second list
 *
 * @param list : pointer of list
 * @param firstList : pointer of first list
 * @param secondList : pointer of second list
 */
void concat (struct list_s *list ,struct list_s *firstList ,struct list_s *secondList);

/**
 * Merge second list in list
 *
 * @param list : pointer of list
 * @param secondList : pointer of second list
 */
void merge (struct list_s *list,struct list_s *secondList,func f);

/**
 * Get lower element bewteen first and second element
 *
 * @param first : pointer of first element
 * @param second : pointer of second element
 * @param f : function of comparaison
 * @return return pointer of lower element
 */
static struct element_s *check(struct element_s *first, struct element_s *second, func f);

/**
 * Sort list, with function of compare value
 *
 * @param list pointer of list
 * @param func function of comparaison
 */
void sortList(struct list_s *list, func f);

/**
 * Sort list, with function of compare value and swap call back for element
 *
 * @param list pointer of list
 * @param func function of comparaison
 * @param fswap function of swaping
 */
void sort_list_with_swap(struct list_s *list, func f, swap fswap);

/**
 * Sort list with lineary recherche
 *
 * @param list List we are looking for
 * @param f comparaison function
 * @param fapply Function of set element
 */
void sort_lineaire(struct list_s *list, func f, apply fapply);

/**
 * Search local optimal
 *
 * @param list List we are looking for
 * @param f comparaison function
 * @param size Size of interval
 */
static void local_search(struct element_s* first, func f, int size);

/**
 * Implementation of speed sort
 *
 * @param left Left born
 * @param right Right born
 * @param firstElement First element
 * @param lastElement Last element
 * @param func function of comparaison
 * @param fswap function of swaping
 */
static void speedSort(int first, int last, struct element_s *firstElement, struct element_s *lastElement, func f, swap fswap);


/**
 * Partition of  list into first and last 
 *
 * @param first : index of first element
 * @param last : index of last element
 * @param firstElement First element
 * @param lastElement Last element
 * @param func : function of comparaison
 * @param fswap : function of swaping
 * @return index of new pivot
 */
static void partition(int first, int last, struct element_s *firstElement, struct element_s *lastElement, struct tuple_s *res, func f, swap fswap);

/**
 * Switch two element 
 *
 * @param firstElement : first element
 * @param secondElement : second element
 * @param fswap : function of swaping
 */
static void swap_value(struct element_s *firstElement,struct element_s *secondElement, swap fswap);

/**
 * Switch two element
 *
 * @param firstElement : first element
 * @param secondElement : second element
 */
static void swap_element(struct element_s *first_element, struct element_s *second_element);

/**
 * Defined basic swap
 *
 * @param arg First element
 * @param arg2 Second element
 */
void basic_swap (void * arg, void *arg2);

/**
* String display of list
*
* @param list
* @param buffer 
* @param f
*/
void displayList(struct list_s *list, char * buffer, toString f);

/**
 * Find value in list, return 0 if element not find
 *
 * @param list : pointer of list
 * @param value : value want to check in list
 * @param f : function of comparaison 
 *
 * @return Pointer of value, if not find return 0
 */
void *findValue(struct list_s *list,void *value,func f);

/**
 * Check if value is in list
 *
 * @param list : pointer of list
 * @param value : value want to check in list
 * @param f : function of comparaison 
 *
 * @return 1 if contains, else return 0
 */
int contain(struct list_s *list,void *value,func f);

/**
 * Initialize Iterrator of list
 *
 * @param list : pointer of list
 * @param iterator : pointer of list
 */
void init_Iterator(struct list_s *list,struct iterator_s *iterator);

/**
 * Know if has next element
 *
 * @param iterator : pointer of iterator
 * 
 * @return 1 if hasNext else return 0 
 */
int hasNext(struct iterator_s *iterator);

/**
 * Get next value of iterator
 *
 * @param iterator : pointer of iterator 
 * 
 * @return next value of iterator
 */
void *next(struct iterator_s *iterator);

/**
 * Shuffle list
 *
 * @param list List we are looking for
 */
void shuffle(struct list_s *list);

/**
 * Get next element of iterator
 * 
 * @param iterator : pointer of iterator
 *
 * @return next element of iterator
 */
static struct element_s *nextElement(struct iterator_s *iterator);

/**
 * Check validity of list
 * Create exception if list invalid
 *
 * @param list : pointer of list
 * @param back : name of funcion call
 */
static void assertList(struct list_s *list,char *back);

/**
 * Check validiy of iterator
 * Create exception if iterator is invalid
 *
 * @param iterator : pointer of iterator
 * @param back : name of funcion call
 */ 
static void assertIterator(struct iterator_s *iterator,char *back);

/**
 * Check code value, 
 * if code value is false, create exception and display string and stop process
 *
 * @param check : check value
 * @param string : display message of error
 * @param back : name of funcion call
 */
void assertError(int check,char *string,char *back);
