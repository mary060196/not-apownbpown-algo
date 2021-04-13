// Miriam Briskman, 04/13/2021
// The input alphabet is {a, b}.
// The stack alphabet is {$, a, #}.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stack> // stack

using namespace std;

bool are_comments_on = false;

// Function Prototypes:
void recur_func(int, int, char *);
void algo(int, char *);

int main (int argc, char * argv[])
{
    int argument_index = 1;
    if (argc == 1)
    {
       printf("No maximum test string size (integer) passed!\nUsage:\n\t./%s SIZE\nwhere SIZE is a natural number.\n", argv[0]);
       exit(EXIT_FAILURE);
    }
    // Check for "more comments" option:
    if (strcmp(argv[1], "-c") == 0 || strcmp (argv[1], "--comments") == 0)
    {
      are_comments_on = true;
      argument_index = 2;
    }
    int max_size = atoi(argv[argument_index]);
    char * ptr = (char*)malloc(max_size + 1);
    // State that the empty input string is rejected since its of the form a^nb^n:
    printf ("The empty word is rejected! (it's of the form a^0b^0)\n", ptr);
    // Call the recursive function:
    recur_func(max_size, 0, ptr);
    return EXIT_SUCCESS;
}

void recur_func(int max_size, int index, char * ptr)
{
   // Base Case (we reached the maximum string capacity).
   if (index == max_size)
     return;
   ptr[index + 1] = '\0';
   ptr[index] = 'a';
   algo(index + 1, ptr);
   recur_func(max_size, index + 1, ptr);
   ptr[index] = 'b';
   algo(index + 1, ptr);
   recur_func(max_size, index + 1, ptr);
}

void algo (int size, char * ptr)
{
    /* Variable Declaration + Initialization */
    stack<char> the_stack; // The PDA's stack
    char recent_popped; // The most recently popped character.
    char recent_read = '$'; // The most recently read character from the input string.

    ptr[size] = '\0';

    /* The algorithm: */
    the_stack.push('$'); // Begin the PDA by pushing a $ sign into the stack.
    if (are_comments_on)
       printf("[Pushed $");
    for (int i = 0; i < size; i++)
    {
       if (ptr[i] == 'a') // For each encountered 'a' in the input string,
       {
          the_stack.push('a'); // push an 'a' onto the stack.
          if (recent_read == 'b') // If we encountered the sequence "ba",
          {
              if (are_comments_on)
                  printf(", Stopped due to a \"ba\" sequence.]\n");
              printf ("The word: %s is accepted!\n", ptr); // The word is immediatelly accepted!
              return;
          }
          if (are_comments_on)                                                                                                       printf(", pushed a");
          recent_read = 'a';
       }
       else // Otherwise, for each encountered b,
       {
          recent_popped = the_stack.top(); // pop an a from the stack.
          the_stack.pop();
          if (are_comments_on)                                                                                                       printf(", popped %c", recent_popped);
          if (recent_popped == '$') // If a $ symbol is popped from the stack,
          {
             if (are_comments_on)                                                                                                       printf("]\n");
             // accept the word (the string begins with b's or there are more b's than a's.)
             printf ("The word: %s is accepted!\n", ptr);
             return;
          }
          recent_read = 'b';
       }
    }
    // When there are no more symbols to read from the input string,
    recent_popped = the_stack.top(); // pop a symbol from the stack.
    the_stack.pop();
    if (are_comments_on)                                                                                                       printf(", {Last popping} popped %c]\n", recent_popped);
    if (recent_popped == 'a') // If this symbol is an a,
      printf ("The word: %s is accepted!\n", ptr); // accept the word (there are more a's than b's.)
    else // If this is the $ symbol,
      printf ("The word: %s is rejected!\n", ptr); // reject the word (there are as many a's as b's.)
}
