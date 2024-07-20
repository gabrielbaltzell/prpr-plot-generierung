#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>

#include "pgfplots.h"

// #include für plot library


/* Algorithmen, die gemessen werden
 * Messung siehe main() weiter unten
 */
void swap(int *lhs, int *rhs) {
    int tmp = *lhs;
    *lhs = *rhs;
    *rhs = tmp; 
}

void bubble_sort(int *values, int num_values) {
    for (int i = num_values; i > 1; --i) { 
        for (int j = 0; j < i - 1; ++j) {
            if (values[j] > values[j + 1]) {
                swap(&values[j], &values[j + 1]);
            }
        }
    }
}

int partition(int *values, int low, int high) {
    int pivot = values[low]; 
    int i = low; 
    int j = high; 
  
    while (i < j) { 
        while (values[i] <= pivot && i <= high - 1) { 
            i++; 
        } 

        while (values[j] > pivot && j >= low + 1) { 
            j--; 
        } 
        if (i < j) { 
            swap(&values[i], &values[j]); 
        } 
    } 
    swap(&values[low], &values[j]); 
    return j;
} 


void quick_sort_impl(int *values, int low, int high) {
    if (low < high) { 
        const int partition_index = partition(values, low, high); 

        quick_sort_impl(values, low, partition_index - 1); 
        quick_sort_impl(values, partition_index + 1, high); 
    } 
}

void quick_sort(int *values, int num_values) {
    quick_sort_impl(values, 0, num_values - 1);
}

typedef struct {
    char *label;
    int *values;
    int num_values;
} data_set;

data_set data_set_create(const char* label, int num_values) {
    data_set data;
    data.label = strdup(label);
    data.values = malloc(sizeof(int) * num_values);
    data.num_values = num_values;
    
    for (int i = 0; i < num_values; ++i)
        data.values[i] = rand() % 50;
    
    return data;
}

void data_set_display(const data_set *data) {
    printf("Dataset: %s\n", data->label);
    for (int i = 0; i < data->num_values; ++i)
        printf(i != data->num_values - 1 ? "%d, " : "%d\n", data->values[i]);
}

data_set data_set_destroy(data_set *data) {
    free(data->label);
    free(data->values);
}

data_set data_set_dup(const data_set *data, const char *as) {
    data_set new_data;
    new_data.label = strdup((as == NULL) ? data->label : as);
    new_data.values = malloc(sizeof(int) * data->num_values);
    new_data.num_values = data->num_values;
    memcpy(new_data.values, data->values, sizeof(int) * new_data.num_values);
    return new_data;
}

double time_in_ms() {
    struct timeval tv;
    gettimeofday(&tv, 0);
    double ret = (double) tv.tv_sec * 1000.0 + (double) tv.tv_usec / 1000.0;
    return ret;
}


int main() {
    srand(time(NULL));

    const unsigned int num_input_values = 100;

    data_set data = data_set_create("data", num_input_values);

    TexDoc *my_doc = new_texdoc();

    Tikzpicture *tikz = get_tikzpicture(my_doc, 0);

    PlotAttributes* pa = get_plotattributes(tikz);
    Legend* legend = get_legend(tikz);
    add_attribute(pa, "xlabel=Year");
    add_attribute(pa, "ylabel=Amount");
    add_attribute(pa, "x tick label style={/pgf/number format/1000 sep=}");
    add_attribute(pa, "legend style={at={(0.5,-0.15)},anchor=north,legend columns=-1}");

    set_legend_key(legend, "bubble sort, quick sort");

    // Lege Datenstruktur für TeX-Dokument an
    // Lege darin zwei Plots an (je eine Instanz einer separaten Datenstruktur)

    Addplot *addplot0 = get_addplot(tikz, 0);

    // or Addplot *addplot1 = add_addplot(axis);
    
    add_addplot(tikz);

    Addplot *addplot1 = get_addplot(tikz, 1);

    const int num_iterations = 2000;

    // In jedem Plot, benenne die X-Achse mit "iteration"

    // In jedem Plot, benenne die Y-Achse mit "time in ms"
    ////
    for (int i = 0; i < num_iterations; ++i) {
        double start_ms = time_in_ms();
        bubble_sort(data.values, data.num_values);
        double end_ms = time_in_ms();

        double time = end_ms - start_ms;
        // Füge dem ersten Plot die Koordinate (i, time) hinzu
        append_coordinate(i, time, addplot0);

        start_ms = time_in_ms();
        quick_sort(data.values, data.num_values);
        end_ms = time_in_ms();

        time = end_ms - start_ms;
        // Füge dem zweiten Plot die Koordinate (i, time) hinzu
        append_coordinate(i, time, addplot1);
    }

    // Rufe Funktion auf um TeX-Datei mit beiden Plots zu erzeugen und daraus ein PDF zu erstellen.
    // Siehe Aufruf system() für den letzten Schritt.

    generate_doc_and_pdf(my_doc, "plot-use-case");

    // Sauberes Aufräumen des TeX-Dokuments, was sauberes Aufräumen der darin enthaltenen Plot-Strukturen auslösen soll.

    free_texdoc(my_doc);

    data_set_destroy(&data);
    return 0;
}
