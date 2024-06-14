#include <gtk/gtk.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "hash.h"

long long hashValues[HASH_SIZE];

void on_button_clicked(GtkWidget *widget, gpointer data) {
    // Get the input entry and output text view from data
    GtkWidget **widgets = (GtkWidget **)data;
    GtkWidget *input_entry = widgets[0];
    GtkWidget *output_label = widgets[1];

    // Get the text from the input entry
    const char *input_text = gtk_entry_get_text(GTK_ENTRY(input_entry));

    // Calculate the hash value for the input string
    long long hash = hashString(input_text, hashValues);

    // Convert the hash value to a string
    char output_text[100];
    if (hash != -1) {
        sprintf(output_text, "%lld", hash);
    } else {
        strcpy(output_text, "Invalid input. Only A-Z and 0-9 are allowed.");
    }

    // Set the text in the output label
    gtk_label_set_text(GTK_LABEL(output_label), output_text);
}

int main(int argc, char *argv[]) {
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *input_label;
    GtkWidget *input_entry;
    GtkWidget *button;
    GtkWidget *output_label;

    // Initialize the hash values for A-Z and 0-9
    initializeHashValues(hashValues);

    gtk_init(&argc, &argv);

    // Create the main window
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "UFO Hash Generator");
    gtk_window_set_default_size(GTK_WINDOW(window), 360, 480);
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);

    // Create a grid
    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

      // Set the window icon
    if (!gtk_window_set_icon_from_file(GTK_WINDOW(window), "icon.png", NULL)) {
        g_warning("Could not load window icon from file 'icon.png'");
    }

    // Create input label and entry
    input_label = gtk_label_new("Enter word or number:");
    gtk_grid_attach(GTK_GRID(grid), input_label, 0, 0, 1, 1);

    input_entry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), input_entry, 1, 0, 2, 1);

    // Create button
    button = gtk_button_new_with_label("Generate Hash");
    gtk_grid_attach(GTK_GRID(grid), button, 0, 1, 3, 1);

    // Create output label
    output_label = gtk_label_new("");
    gtk_grid_attach(GTK_GRID(grid), output_label, 0, 2, 3, 1);

    // Load CSS
    GtkCssProvider *css_provider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(css_provider, "styles.css", NULL);
    GtkStyleContext *context = gtk_widget_get_style_context(grid);
    gtk_style_context_add_provider(context, GTK_STYLE_PROVIDER(css_provider), GTK_STYLE_PROVIDER_PRIORITY_USER);

    // Create array of widgets to pass to callback
    GtkWidget *widgets[2] = {input_entry, output_label};
    g_signal_connect(button, "clicked", G_CALLBACK(on_button_clicked), widgets);

    // Connect the destroy signal to quit the GTK main loop
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Show all widgets
    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}

