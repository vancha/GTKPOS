#include "shop.h"
#include <string.h>
#include <stdio.h>

#define MAX_PRINT_STATEMENT_LEN 1000


////////////////////////////////////////////////////////////////////////////////
#pragma region helper functions prototypes

static char *
add_to_text(char *current_char, 
            int *buffer_left,
            const char *format,
            void* value,
            int alignment);

#pragma endregion
////////////////////////////////////////////////////////////////////////////////
// Public functions

/*
    Buys an item in the shop and increments the value bought
*/
void 
Buy_Item(Shop s, 
         int id)
{
    s->quantity_bought[id]++;
}

/*
    Creates an output of the items bought in char array that has to be freed

    Idk this got worse and worse as i wrote it.
*/
char *
Get_Print_Statement(Shop s)
{
    // kind of only used snprintf rarely no idea how safe this is.
    int buffer_left = MAX_PRINT_STATEMENT_LEN;
    int character_added = 0;
    char *print_statement = malloc(sizeof(char) * MAX_PRINT_STATEMENT_LEN);
    
    // Where it is currently up to.
    char *statement_cursor = print_statement;

    character_added = snprintf(print_statement, buffer_left, 
        "Items bought in the shop:\n");
    buffer_left -= character_added;
    statement_cursor += character_added;

    if (buffer_left < 0) {
        return "Print Statement went over buffer";
    }
    int accumalated_cost = 0;
    char currency_symbol[2] = CURRENCY_SYMBOL;
    for (int id = 0; id < NUM_ITEMS; id++) {
        int cost = (shop_items[id].price) * (s->quantity_bought[id]); 
        if ((statement_cursor = add_to_text(statement_cursor, &buffer_left,
            "\t- %s", &(shop_items[id].name), 20))) 
            return "Print Statement went over buffer";
        if ((statement_cursor = add_to_text(statement_cursor, &buffer_left,
            "%s", &(currency_symbol), 21))) 
            return "Print Statement went over buffer";
        if ((statement_cursor = add_to_text(statement_cursor, &buffer_left,
            "%d.", &(s->quantity_bought[id]), 26))) 
            return "Print Statement went over buffer";
        if ((statement_cursor = add_to_text(statement_cursor, &buffer_left,
            " x %d", &(shop_items[id].price), 32))) 
            return "Print Statement went over buffer";
        if ((statement_cursor = add_to_text(statement_cursor, &buffer_left,
            " = %d\n", &cost, 0))) 
            return "Print Statement went over buffer";
        accumalated_cost += cost;
    }
    if ((statement_cursor = add_to_text(statement_cursor, &buffer_left,
        "Total Cost: %s", &(currency_symbol), 0))) 
        return "Print Statement went over buffer";
    if ((statement_cursor = add_to_text(statement_cursor, &buffer_left,
        "%d\n", &accumalated_cost, 0))) 
        return "Print Statement went over buffer";
}

/*
    Makes a struct shop *, to store items bought
*/
Shop 
New_Shop()
{
    Shop s = malloc(sizeof(struct shop));
    s->quantity_bought = calloc(NUM_ITEMS, sizeof(int));
    return s;
}

/*
    Frees a struct shop *,
*/
void
Free_Shop(Shop s)
{
    free(s->quantity_bought);
    free(s);
}

////////////////////////////////////////////////////////////////////////////////
#pragma region helper functions

/*
    Add to text, is a helper function that uses snprinf to incrementally add text

    (NVM) variadic something chatgpt told me about,
    just used (void*)
*/
static char *
add_to_text(char *current_cursor, 
            int *buffer_left,
            const char *format,
            void *value,
            int alignment)
{
    int character_added = snprintf(current_cursor, *buffer_left, format, value);
    if (character_added >= *buffer_left)
        return NULL; // Insufficient space in the buffer

    *buffer_left -= character_added;
    current_cursor += character_added;

    if (*buffer_left - alignment + character_added < 0)
        return NULL; // Not enough space for alignment

    // Adding Spaces After for the alignment
    for (int i = 0; i < (alignment - character_added > 0 ? alignment - character_added : 0); i++) {
        if (*buffer_left <= 0)
            return NULL; // Insufficient space in the buffer
        snprintf(current_cursor, *buffer_left, " ");
        (*buffer_left)--;
        current_cursor++;
    }

    return current_cursor;
}

#pragma endregion helper functions