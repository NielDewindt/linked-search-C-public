
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

/*
Opgave: Link'ed Search
HINT: Implementeer onderstaande functies in volgorde. Het uitvoeren van het gecompileerde
programma zal automatisch een aantal testen runnen. Je kunt daardoor makkelijk nagaan of
je functies correct zijn. Wanneer je meer debug-informatie nodig hebt, kun je steeds
gebruik maken van gdb.
*/

struct Node
{
	char c;
	struct Node *next;
};

/*
Hulpfunctie -- DO NOT TOUCH!
*/
void check( int v, char const *filename, int line )
{
	static int no = 0;

	printf( "check %-2i at %s:%-3i: %s\n", ++no, filename, line, v ? "OK!" : "FAILED" );
}

/*
Gegeven een pointer naar een string, geef de lengte van deze string terug.
OPGELET: Uiteraard dien je hier zelf een functie te implementeren,
het aanroepen van een standaard-functie is niet toegelaten!
*/

int string_length( char const *string )
{
    int counter = 0;
    while(*string != '\0')
    {
        counter++;
        *string++;
    }
    return counter;
}

/*
Gegeven een string en een geheel getal, zoek in de string hoe vaak dit getal voorkomt.
Je mag er vanuit gaan dat dit getal tussen 0 t.e.m. 9 ligt.
*/

unsigned int search_int( char *string, unsigned int number )
{
	char numberChar[2]; 
	sprintf(numberChar, "%d", number); 
/*Error by compiler gaf aan output tussen 2-12 bytes, 
bij testen van grootte gaf 2 geen output error meer */
/*sprintf zal typecasten van int naar string om vergelijking mogelijk te maken*/
	int counter = 0;
	int i;
    for(i = 0; string[i]; i++)  
	{
		if(string[i] == *numberChar)
		{
          		counter++;
		}
 	}
 	
    return counter;
}

/*
Gegeven twee strings, plak deze aan elkaar als een nieuwe string.
OPGELET: Uiteraard dien je hier zelf een functie te implementeren,
het aanroepen van een standaard-functie is niet toegelaten!
*/

char *string_cat( char const *string1, char const *string2 )
{
	int len = string_length(string1);
	char *result = malloc(len + string_length(string2) + 1);
	
	int i;
	for(i = 0; string1[i]; i++)
	{
	 result[i] = string1[i];
	}
	for(i = 0; string2[i]; i++)
	{
	 result[len + i] = string2[i];
	}
	result[len + i] = '\0';
	
	return result;
}

/*
Gegeven een pointer naar een node van een enkelvoudige gelinkte lijst.
Geef de lengte van de lijst terug.
*/

unsigned int list_length( struct Node *node )
{
    int counter = 0;  // Initialize count
    struct Node* current = node;  // Initialize current
    while (current != NULL)
    {
        counter++;
        current = current->next;
    }
    return counter;
}

/*
Gegeven een pointer naar een node van een enkelvoudige gelinkte lijst.
Elke node van de lijst heeft een character. Transformeer de gelinkte lijst
in een string. Hierbij moeten volgende kenmerken gelden:
list_to_node( NULL ) -> ""
list_to_node( {'c', NULL} ) -> "c"
list_to_node( {'c', {'a', NULL}} ) -> "ca"
...
*/

char* list_to_string( struct Node *node )
{
	if(node != NULL)
	{
	    int i;
        char str[list_length(node)];
		struct Node* current = node;
		for(i = 0; i < list_length(node); i++)
		{
			str[i] = current->c;
			current = current->next;
 		}
 		str[i] = '\0';
 		//printf(str);
		return str;
	}
	else
	{
		return "";
	}
}

/*
Gegeven een pointer naar een node van een enkelvoudige gelinkte lijst.
Geef de gehele lijst terug vrij.
*/

void free_list( struct Node *node )
{
  	while (node != NULL)
    {
    	struct Node* tmp = node;
       	node = node->next;
       	free(tmp);
	}
}

/*
Maakt een nieuwe node aan met het gegeven karakter.
*/

struct Node* create_node( char c )
{
	struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
	//typecast naar node struct
	newNode->c = c;
	return newNode;
}

/*
Voeg een nieuwe node achteraan een gelinkte lijst toe.
De return-value is de eerste node van de lijst.
*/

struct Node* append_list( struct Node *list, struct Node *node )
{
    if(list != NULL)
    {
    	struct Node* current = list;
    	while (1) {
    	    //1 & 0 gebruikt voor true false --> while(true) 
            if(current->next == NULL)
            {
                current->next = node;
                break;
            }
            else
            {
                current = current->next;
            }
        }
    	return list;
    }
    else
    {
       return node; 
    }
}

/*
Voeg een node toe op de i-de plaats in de gelinkte lijst (gebruik zero-based indexing; het eerste element in de lijst bevindt zich dus op positie 0).
Laat de lijst ongewijzigd als i geen geldige positie is (bv. als positie i buiten de lijst valt).
De return-value is de eerste node van de lijst.
*/

struct Node *insert_list( struct Node *list, struct Node *node, int i )
{
	if(list != NULL)
	{
    	if(i > -1 && i <= list_length(list))
    	{
    		struct Node* current = &list[i-1];
    		struct Node* tmp = current->next;
    		current->next = node;
    		node->next = tmp;
    		return list;
    	}
    	else
    	{
    		return list;
    	}
	}
    else
    {
        return node;
    }
}

/*
Verwissel twee nodes (op positie i en j) in de gelinkte lijst (gebruik opnieuw zero-based indexing).
Laat de lijst ongewijzigd als i of j geen geldige positie is (bv. als positie i of j buiten de lijst valt).
De return-value is de eerste node van de lijst.
*/

struct Node *swap_list( struct Node *list, int i, int j )
{
    if(list != NULL)
    {
    	if(i > -1 && i <= list_length(list) - 1 || j > -1 && j <= list_length(list) - 1)
    	{
    		struct Node* prev1 = NULL;
            struct Node* node1 = list;
            for(int k = 0; k < i; k++)
            {
              prev1 = node1;
              node1 = node1->next;
            }
            struct Node* prev2 = NULL;
            struct Node* node2 = list;
            for(int k = 0; k < j; k++)
            {
              prev2 = node2;
              node2 = node2->next;
            }
            struct Node* tmp = node2;
            prev1->next = node2;
            node2->next = node1->next;
            prev2->next = node1;
            node1->next = tmp->next;
            return list;
    	}
    	else
    	{
    		return list;
    	}
    }
    /*else
    {
        
    }*/
}


/*
Gegeven een pointer naar een enkelvoudig gelinkte lijst, keer deze om.
*/

struct Node *reverse_list( struct Node *node )
{
	    struct Node* prev = NULL;
	    struct Node* current = node;
	    struct Node* next = NULL;
	    while (current != NULL) 
	    {
		// Store next
		    next = current->next;

		// Reverse current node's pointer
		    current->next = prev;

		// Move pointers one position ahead.
		    prev = current;
		    current = next;
	    }
	    node = prev;
	    return node;
}

int main( int argc, char **argv )
{
	char *str;
	struct Node nodeA = {.c = 'a', .next = NULL };
	struct Node nodeB = {.c = 'b', .next = &nodeA };
	struct Node nodeC = {.c = 'c', .next = &nodeB };
	struct Node nodeD = {.c = 'd', .next = &nodeC };
	struct Node *node;

	printf( "== string_length ==\n" );
	check( string_length( "hello" ) == 5, __FILE__, __LINE__ );
	check( string_length( "x" ) == 1, __FILE__, __LINE__ );
	check( string_length( "" ) == 0, __FILE__, __LINE__ );

	printf( "== search_int ==\n" );
	check( search_int( "There are 100 bottle of beer on the wall", 0 ) == 2, __FILE__, __LINE__ );
	check( search_int( "There are 100 bottle of beer on the wall", 1 ) == 1, __FILE__, __LINE__ );
	check( search_int( "There are 100 bottle of beer on the wall", 3 ) == 0, __FILE__, __LINE__ );
	check( search_int( "1", 1 ) == 1, __FILE__, __LINE__ );
	check( search_int( "0", 1 ) == 0, __FILE__, __LINE__ );

	printf( "== string_cat ==\n" );
	check( strcmp( ( str = string_cat( "", ""       ) ) == NULL ? "" : str, ""      ) == 0, __FILE__, __LINE__ ); free( str );
	check( strcmp( ( str = string_cat( "", "abcdef" ) ) == NULL ? "" : str, "abcdef" ) == 0, __FILE__, __LINE__ ); free( str );
	check( strcmp( ( str = string_cat( "a", "bcdef" ) ) == NULL ? "" : str, "abcdef" ) == 0, __FILE__, __LINE__ ); free( str );
	check( strcmp( ( str = string_cat( "ab", "cdef" ) ) == NULL ? "" : str, "abcdef" ) == 0, __FILE__, __LINE__ ); free( str );
	check( strcmp( ( str = string_cat( "abc", "def" ) ) == NULL ? "" : str, "abcdef" ) == 0, __FILE__, __LINE__ ); free( str );
	check( strcmp( ( str = string_cat( "abcd", "ef" ) ) == NULL ? "" : str, "abcdef" ) == 0, __FILE__, __LINE__ ); free( str );
	check( strcmp( ( str = string_cat( "abcde", "f" ) ) == NULL ? "" : str, "abcdef" ) == 0, __FILE__, __LINE__ ); free( str );
	check( strcmp( ( str = string_cat( "abcdef", "" ) ) == NULL ? "" : str, "abcdef" ) == 0, __FILE__, __LINE__ ); free( str );

	printf( "== list_length ==\n" );
	check( list_length( NULL ) == 0, __FILE__, __LINE__ );
	check( list_length( &nodeA ) == 1, __FILE__, __LINE__ );
	check( list_length( &nodeB ) == 2, __FILE__, __LINE__ );
	check( list_length( &nodeC ) == 3, __FILE__, __LINE__ );
	check( list_length( &nodeD ) == 4, __FILE__, __LINE__ );

	printf( "== list_to_string ==\n" );
	check( strcmp( ( str = list_to_string( NULL ) ) == NULL ? "wrong" : str, "" ) == 0, __FILE__, __LINE__ );
	check( strcmp( ( str = list_to_string( &nodeA ) ) == NULL ? "" : str, "a" ) == 0, __FILE__, __LINE__ ); free( str );
	check( strcmp( ( str = list_to_string( &nodeB ) ) == NULL ? "" : str, "ba" ) == 0, __FILE__, __LINE__ ); free( str );
	check( strcmp( ( str = list_to_string( &nodeC ) ) == NULL ? "" : str, "cba" ) == 0, __FILE__, __LINE__ ); free( str );
	check( strcmp( ( str = list_to_string( &nodeD ) ) == NULL ? "" : str, "dcba" ) == 0, __FILE__, __LINE__ ); free( str );

	printf( "== create node ==\n" );
	node = create_node( 'q' );
	check( node != NULL, __FILE__, __LINE__ );
	check( node != NULL && node->c == 'q', __FILE__, __LINE__ );
	check( node != NULL && node->next == NULL, __FILE__, __LINE__ );
	free_list( node );

	printf( "== append_list ==\n" );
	node = append_list( NULL, create_node( 'y' ) );
	check( node != NULL, __FILE__, __LINE__ );
	check( node != NULL && node->c == 'y', __FILE__, __LINE__ );
	check( node != NULL && node->next == NULL, __FILE__, __LINE__ );
	node = append_list( node, create_node( 'z' ) );
	check( node != NULL, __FILE__, __LINE__ );
	check( node != NULL && node->c == 'y', __FILE__, __LINE__ );
	check( node != NULL && node->next != NULL && node->next->c == 'z', __FILE__, __LINE__ );
	check( node != NULL && node->next != NULL && node->next->next == NULL, __FILE__, __LINE__ );
	check( node != NULL && node->next->next == NULL, __FILE__, __LINE__ );
	free_list( node );

	printf( "== insert_list ==\n" );
	node = insert_list( NULL, create_node( 'h' ), 0 );
	check( node != NULL, __FILE__, __LINE__ );
	check( node != NULL && node->c == 'h', __FILE__, __LINE__ );
	check( node != NULL && node->next == NULL, __FILE__, __LINE__ );
	node = insert_list( node, create_node( 'i' ), 1);
	check( node != NULL, __FILE__, __LINE__ );
	check( node != NULL && node->c == 'h', __FILE__, __LINE__ );
	check( node != NULL && node->next->c == 'i', __FILE__, __LINE__ );
	check( node != NULL && node->next->next == NULL, __FILE__, __LINE__ );
	node = insert_list( node, create_node( 'o' ), 1);
	check( node != NULL, __FILE__, __LINE__ );
	check( node != NULL && node->c == 'h', __FILE__, __LINE__ );
	check( node != NULL && node->next != NULL && node->next->c == 'o', __FILE__, __LINE__ );
	check( node != NULL && node->next->next != NULL && node->next->next->c == 'i', __FILE__, __LINE__ );
	node = insert_list( node, create_node( 'n' ), 11);
	check( node != NULL && node->c == 'h', __FILE__, __LINE__ );
	check( node != NULL && node->next != NULL && node->next->c == 'o', __FILE__, __LINE__ );
	check( node != NULL && node->next->next != NULL && node->next->next->c == 'i', __FILE__, __LINE__ );
	node = insert_list( node, create_node( 'n' ), -1);
	check( node != NULL && node->c == 'h', __FILE__, __LINE__ );
	check( node != NULL && node->next != NULL && node->next->c == 'o', __FILE__, __LINE__ );
	check( node != NULL && node->next->next != NULL && node->next->next->c == 'i', __FILE__, __LINE__ );

	printf( "== swap_list ==\n" );
	printf("check0");
	node = swap_list( node, 1, 2);
	printf("check1");
	check( strcmp( ( str = list_to_string( node ) ) == NULL ? "" : str, "hio" ) == 0, __FILE__, __LINE__ );
	node = swap_list( node, 0, 2);
	printf("check2");
	check( strcmp( ( str = list_to_string( node ) ) == NULL ? "" : str, "oih" ) == 0, __FILE__, __LINE__ );
	node = swap_list( node, 0, 3);
	printf("check3");
	check( strcmp( ( str = list_to_string( node ) ) == NULL ? "" : str, "oih" ) == 0, __FILE__, __LINE__ );

	printf( "== reverse_list ==\n" );
	node = reverse_list( create_node( 'a' ) );
	check( node != NULL, __FILE__, __LINE__ );
	check( node != NULL && node->c == 'a', __FILE__, __LINE__ );
	check( node != NULL && node->next == NULL, __FILE__, __LINE__ );
	free_list( node );
	node = reverse_list( &nodeD );
	check( strcmp( ( str = list_to_string( node ) ) == NULL ? "" : str, "abcd" ) == 0, __FILE__, __LINE__ ); free( str );

	return 0;
}
