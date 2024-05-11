// macros ifndef define, allow mulitple include's of the file, stopping multiple
// stuff

// The Purpose of this file is an interface of giving access to structs and 
// to be used outside of shop implementation functions

#ifndef SHOP_H
#define SHOP_H

#define NUM_ITEMS 16
#define CURRENCY_SYMBOL "$"

typedef struct shop *Shop; 

struct shop {
    int *quantity_bought;
};

struct shop_item {
  int   price;
  char* name;
  char* path;
};

/*
  List of paths to images in /img probably a better way to do this,
  All images are 50x50px png, that i did in paint
*/
const struct shop_item shop_items[] = {
  {1,  "Avocado",    "img//Avocado.png",},
  {2,  "Bean",       "img//Bean-Can.png",},
  {3,  "Blue",       "img//Blue-Can.png",},
  {4,  "Bread",      "img//Bread.png",},
  {5,  "Broccoli",   "img//Broccoli.png",},
  {6,  "Coin",       "img//Coin.png",},
  {7,  "Cookie",     "img//Cookie.png",},
  {8,  "Gold",       "img//Gold.png",},
  {9,  "Green",      "img//Green-Can.png",},
  {10, "Grey",       "img//Grey-Can.png",},
  {11, "Milk",       "img//Milk.png",},
  {12, "Orange",     "img//Orange.png",},
  {13, "Strawberry", "img//Strawberry.png",},
  {14, "Tomato",     "img//Tomato.png",},
  {15, "Ugly",       "img//Ugly-Can.png",},
  {16, "Yellow",     "img//Yellow-Can.png"}
};

////////////////////////////////////////////////////////////////////////////////
// Functions that are public

/*
    Buys an item in the shop and increments the value bought
*/
void 
Buy_Item(Shop s, 
         int id);

/*
    Creates an output of the items bought in char array that has to be freed
*/
char *
Get_Print_Statement(Shop s);

/*
    Makes a struct shop *, to store items bought
*/
Shop 
New_Shop();

/*
    Frees a struct shop *,
*/
void
Free_Shop(Shop s);
#endif