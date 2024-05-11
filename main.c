#include <gtk/gtk.h>
#include <string.h>

#include "shop.h"


///////////////////////////////////////////////////////////////////////////////
#pragma region Static Function Prototypes

// vsc allows folds with the #pragma region, in it settings

static void
activate(GtkApplication *app,
         gpointer user_data);

static GtkWidget *
make_grid(GtkWidget *window);

static GtkWidget *
make_shop_item(int item_id);

#pragma endregion
////////////////////////////////////////////////////////////////////////////////
#pragma region Static Const Data / Structs


#define MAX_ITEM_LEN 100

#pragma endregion
////////////////////////////////////////////////////////////////////////////////
// Main

int main(int argc,
         char **argv) {
  // eferences
  GtkApplication *app;
  int status;

  // calling application constructor
  app = gtk_application_new("org.gtk.example", G_APPLICATION_DEFAULT_FLAGS);

  // Making Shop from shop.h
  Shop s = New_Shop();


  // attaching static function to activate signal
  g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);

  // Status returns at termination?
  status = g_application_run(G_APPLICATION(app), argc, argv);


  // Free?
  g_object_unref(app);

  return status;
}

////////////////////////////////////////////////////////////////////////////////
// Helper functions

static void
activate(GtkApplication *app,
         gpointer user_data) {
  GtkWidget *window;
  GtkWidget *grid;

  window = gtk_application_window_new(app);
  gtk_window_set_title(GTK_WINDOW(window), "Window");
  gtk_window_set_default_size(GTK_WINDOW(window), 200, 200);
  gtk_window_present(GTK_WINDOW(window));

  // making grid and its children
  grid = make_grid(window);  // static
  gtk_window_set_child(GTK_WINDOW(window), grid);
}

/*
  Make grid, makes a grid and populates it with widget of text, image, button

  Grids are first shown in example-2.c, Using `Gtk.Grid` with its methods
   - GtkWidget *gtk_grid_new(void) creates a new grid
   - void *gtk_grid_attach(...),
     - adds a widget, takes in grid poisiton, dimensions, and child as arguments
     - 1st parameter uses function GTK_GRID() to change type or somthing?
  
*/
static GtkWidget *
make_grid(GtkWidget *window) {
  GtkWidget *grid;

  grid = gtk_grid_new();

  // row/column indexed by 0
  for (int row = 0; row < 4; row++) {
    for (int col = 0; col < 4; col++) {
      GtkWidget *shop_item = make_shop_item(row * 4 + col % NUM_ITEMS);
      // width/height is number of span in columns and width
      gtk_grid_attach(GTK_GRID(grid), shop_item, row, col,/* width: */1,/* height: */1);
    }
  }

  return grid;
}



/*
 Make shop item uses a Box Layout (Gtk.Box)
  - grabs an image a from img/ and puts in a widget
  - Displays a label with name,
  - Buy Button is price

  Gtk.Box displays widgets in a single row or column
   - gtk_box_new() constructor
   - gtk_box_append() adds a child
   - gtk_orientable_set_orientation() sets orientation
   - gtk_widget_set_halign() sets horizontal align for childern
   - gtk_widget_set_valign() sets vertical align for childern

  Gtk.Button is a button idk
   - gtk_button_new_with_label() constructs button with label
   - gtk_b
  Uses singals copied from example-2.c are in GObject.signal_connect
   - g_signal_connect() documentation was brief confused?

  Gtk.Picture displays a GdkPaintable (idk what that is)
   - gtk_picture_new_for_filename() gets a 
   - gtk_picture_set_content_fit()  
    size is changed through content fit (enum Gtk.ContentFit)

*/
static GtkWidget *
make_shop_item(int item_id) 
{
  GtkWidget *item_box;
  GtkWidget *button;
  GtkWidget *image;

  // values from shop_items
  int   price =     shop_items[item_id].price;
  char *img_path =  shop_items[item_id].path;
  char *name =      shop_items[item_id].name;

  
  // Making item_box
  // enum Gtk.Orientation has 2 values horizontal and vertical
  item_box = gtk_box_new(GTK_ORIENTATION_VERTICAL,/* spacing */5);
  // enum Gtk.Align controls stretch boolean, 
  // values fill, start, end, center, baseline/baseline fill & baseline center
  gtk_widget_set_valign(GTK_WIDGET(item_box), GTK_ALIGN_START);
  gtk_widget_set_halign(GTK_WIDGET(item_box), GTK_ALIGN_FILL);


  // Making Gtk.Button for title and price
  char item_title[MAX_ITEM_LEN];
  snprintf(item_title, MAX_ITEM_LEN, "%s: %d. %s", "$", price, name);
  button = gtk_button_new_with_label(item_title);

  // Adding a Signal to the button, that buys item 
  g_signal_connect(button, "clicked", G_CALLBACK(Buy_Item), item_id);
  
  
  // Making Gtk.Picture from file,
  image = gtk_picture_new_for_filename (img_path);
  
  // Set Content Fit, picture does fit,
  // enum Gtk.ContentFit has 4 values: fill, contain, cover, scale down 
  gtk_picture_set_content_fit(GTK_PICTURE(image), GTK_CONTENT_FIT_CONTAIN);

  // Setting the Widget to be able to expand vertically & horizontally
  gtk_widget_set_hexpand(GTK_WIDGET(image), true);
  gtk_widget_set_vexpand(GTK_WIDGET(image), true);

  return image;
}

/*
  TODO
*/
static 


////////////////////////////////////////////////////////////////////////////////
#pragma region functions that are dud

// /*
//  Make shop item grabs an image a from img/ and puts in a widget
 
//   Gtk.Image is a class that does image widgets, but they are more Icons
//      - gtk_image_new_from_file() makes a new image widget from a file
//      - gtk_image_set_icon_size() changes the size of the icon

  
//   Bad Gtk.Image is an icon which has fixed size and is too small.

// */
// static GtkWidget *
// make_shop_item(int item_id) 
// {
//   GtkWidget *image;

//   // Makes Image from file,
//   image = gtk_image_new_from_file (img_path);
  
//   // Makes the Image Icon thing bigger uses GtkIconSize as 2nd Argument is 
//   // enum GTK_ICON_SIZE has three values inherit, normal and large
//   gtk_image_set_icon_size(GTK_IMAGE(image), GTK_ICON_SIZE_LARGE);


//   return image;
// }

#pragma endregion
