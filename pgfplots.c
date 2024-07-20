#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <string.h>
#include <stdarg.h>
#include "pgfplots.h"

//Macro to check if memory allocation failed
#define CHECK_PTR_ALLOC(ptr) if ((ptr) == NULL) { fprintf(stderr, "Memory allocation failed in %s at line %d\n", __FILE__, __LINE__); exit(EXIT_FAILURE); }

// Predefined strings for LaTex document generation
const char addplot_string[] = "\n\t\t\\addplot\n\t\t";
const char begin_axis_string[] = "\t\\begin{axis}";
const char end_axis_string[] = "\n\t\\end{axis}\n";
const char begin_tikzpicture_string[] = "\\begin{tikzpicture}\n";
const char end_tikzpicture_string[] = "\\end{tikzpicture}\n";
const char begin_document_string[] = "\\begin{document}\n";
const char end_document_string[] = "\\end{document}\n";
const char preamble_string[] = "\\documentclass{article}\n\\usepackage[margin=0.25in]{geometry}\n\\usepackage{pgfplots}\n\\usepackage{tikz}\n\\pgfplotsset{width=10cm,compat=1.9}\n\n";
const char open_attributes[] = "[\n";
const char close_attributes[] = "\n\t\t]";
const char legend[] = "\n\t\\legend";
const char open_key[] = "{";
const char default_key[] = "you need to define a key";
const char close_key[] = "}";
const char default_attribute[] = "this is a default attribute";

//Create a new Corrdinate and return its pointer
Coordinate* new_coordinate() {
    Coordinate *new_coordinate = malloc(sizeof(Coordinate));
    CHECK_PTR_ALLOC(new_coordinate);

    return new_coordinate;
}

//Create a new Legend and return its pointer
Legend* new_legend() {
    Legend *new_legend = malloc(sizeof(Legend));
    CHECK_PTR_ALLOC(new_legend);
    new_legend->open_key = malloc(sizeof(open_key));
    CHECK_PTR_ALLOC(new_legend->open_key);
    new_legend->legend = malloc(sizeof(legend));
    CHECK_PTR_ALLOC(new_legend->legend);
    new_legend-> close_key = malloc(sizeof(close_key));
    CHECK_PTR_ALLOC(new_legend->close_key);
    new_legend->key = malloc(sizeof(default_key));
    CHECK_PTR_ALLOC(new_legend->key);

    strcpy(new_legend->open_key, open_key);
    strcpy(new_legend->legend, legend);
    strcpy(new_legend->close_key, close_key);
    strcpy(new_legend->key, default_key);

    return new_legend;
}

//Create a new Addplot and return its pointer
Addplot* new_addplot() {
    Addplot *new_addplot = malloc(sizeof(Addplot));
    CHECK_PTR_ALLOC(new_addplot);
    new_addplot->addplot = malloc(sizeof(addplot_string));
    CHECK_PTR_ALLOC(new_addplot->addplot);
    strcpy(new_addplot->addplot, addplot_string);
    new_addplot->coordinates = new_coordinate();
    new_addplot->current = new_addplot->coordinates;

    return new_addplot;
}

//Create a new Attribute and return its pointer
Attribute* new_attribute() {
    Attribute *new_attribute = malloc(sizeof(Attribute));
    CHECK_PTR_ALLOC(new_attribute);

    return new_attribute;
}

//Create a new PlotAttributes and return its pointer
PlotAttributes* new_plotattributes() {
    PlotAttributes *new_plotattributes = malloc(sizeof(PlotAttributes));
    CHECK_PTR_ALLOC(new_plotattributes);
    new_plotattributes->open_attributes = malloc(sizeof(open_attributes));
    CHECK_PTR_ALLOC(new_plotattributes->open_attributes);
    new_plotattributes->attributes = new_attribute();
    new_plotattributes->current = new_plotattributes->attributes;
    new_plotattributes->close_attributes = malloc(sizeof(close_attributes));
    CHECK_PTR_ALLOC(new_plotattributes->close_attributes);

    strcpy(new_plotattributes->open_attributes, open_attributes);
    strcpy(new_plotattributes->close_attributes, close_attributes);

    return new_plotattributes;
}

//Create a new Axis and return its pointer
Axis* new_axis() {
    Axis *new_axis = malloc(sizeof(Axis));
    CHECK_PTR_ALLOC(new_axis);
    new_axis->plotattributes = new_plotattributes();
    new_axis->addplots = new_addplot();
    new_axis->current = new_axis->addplots;
    new_axis->legend = new_legend();
    new_axis->begin_axis = malloc(sizeof(begin_axis_string));
    CHECK_PTR_ALLOC(new_axis->begin_axis);
    new_axis->end_axis = malloc(sizeof(end_axis_string));
    CHECK_PTR_ALLOC(new_axis->end_axis);

    strcpy(new_axis->begin_axis, begin_axis_string);
    strcpy(new_axis->end_axis, end_axis_string);
    
    return new_axis;
}

//Create a new Tikzpicture and return its pointer
Tikzpicture* new_tikzpicture() {
    Tikzpicture *new_tikzpicture = malloc(sizeof(Tikzpicture));
    CHECK_PTR_ALLOC(new_tikzpicture);
    new_tikzpicture->axis = new_axis();
    new_tikzpicture->begin_tikzpicture = malloc(sizeof(begin_tikzpicture_string));
    CHECK_PTR_ALLOC(new_tikzpicture->begin_tikzpicture);
    new_tikzpicture->end_tikzpicture = malloc(sizeof(end_tikzpicture_string));
    CHECK_PTR_ALLOC(new_tikzpicture->end_tikzpicture);

    strcpy(new_tikzpicture->begin_tikzpicture, begin_tikzpicture_string);
    strcpy(new_tikzpicture->end_tikzpicture, end_tikzpicture_string);    

    return new_tikzpicture;
}

//Create a new Document and return its pointer
Document* new_document() {
    Document *new_document = malloc(sizeof(Document));
    CHECK_PTR_ALLOC(new_document);
    new_document->tikzpictures = new_tikzpicture();
    new_document->current = new_document->tikzpictures;
    new_document->begin_document = malloc(sizeof(begin_document_string));
    new_document->end_document = malloc(sizeof(end_document_string));

    strcpy(new_document->begin_document, begin_document_string);
    strcpy(new_document->end_document, end_document_string);    

    return new_document;
}

//Create a new Preamble and return its pointer
Preamble* new_preamble() {
    Preamble *new_preamble = malloc(sizeof(Preamble));
    CHECK_PTR_ALLOC(new_preamble);
    new_preamble->preamble = malloc(sizeof(preamble_string));
    CHECK_PTR_ALLOC(new_preamble->preamble);

    strcpy(new_preamble->preamble, preamble_string);

    return new_preamble;
}

// Create a new TexDoc and return its pointer
TexDoc* new_texdoc() {
    TexDoc *new_texdoc = malloc(sizeof(TexDoc));
    CHECK_PTR_ALLOC(new_texdoc);
    new_texdoc->preamble = new_preamble();
    new_texdoc->document = new_document();

    return new_texdoc;
}

//Function to set the Legend key to a new value
void set_legend_key(Legend* legend, char* value) {
    legend->key = realloc(legend->key, sizeof(value));
    CHECK_PTR_ALLOC(legend->key);
    strcpy(legend->key, value);
}

//Function to get the Legend from a Tikzpicture pointer 
Legend* get_legend(Tikzpicture* tikz) {
    return tikz->axis->legend;
}

// Function to a specific Addplot by its index from a Tikzpicture
Addplot* get_addplot(Tikzpicture* tikz, int addplot_index) {
    Addplot* addplot_head = tikz->axis->addplots;

    if (addplot_index == 0) {
        return addplot_head;
    } else {
        for(int i = 1 ; i <= addplot_index; i++) {
            if(addplot_head->next == NULL) {
                printf("Invalid addplot index: %d\n", addplot_index);
                exit(EXIT_FAILURE);
            }
            addplot_head = addplot_head->next;
        }
        return addplot_head;
    }  
}

//Function to get the Plotattributes from a Tikzpicture
PlotAttributes* get_plotattributes(Tikzpicture* tikz) {
    return tikz->axis->plotattributes;
}

//Function to get the Axis from a Tikzpicture
Axis* get_axis(Tikzpicture* tikz) {
    return tikz->axis;
}

// Function to get a Tikzpicture by its index from a TexDoc
Tikzpicture* get_tikzpicture(TexDoc* doc, int tikz_index) {
    Tikzpicture* tikz_head = doc->document->tikzpictures;

    if (tikz_index == 0) {
        return tikz_head;
    } else {
        for(int i = 1; i <= tikz_index; i++) {
            tikz_head = tikz_head->next;
        }
        return tikz_head;
    }
}

//Function to append a Coordinate to a the end of a linked list of Coordinates by its Addplot parent
int append_coordinate(double x, double y, Addplot* addplot) {
    addplot->current->x = x;
    addplot->current->y = y;
    addplot->current->next = new_coordinate();

    Coordinate *old_coordinate = addplot->current;
    addplot->current = old_coordinate->next;

    return 0;
}

// Function to add a new Addplot to a Tikzpicture
Addplot* add_addplot(Tikzpicture* tikz){
    tikz->axis->current->next = new_addplot();

    Addplot* old_addplot = tikz->axis->current;
    tikz->axis->current = old_addplot->next;
    return tikz->axis->current;
}

// Function to add an attribute to a PlotAttributes object
Attribute* add_attribute(PlotAttributes* pa, char* value) {
    pa->current->next = new_attribute();
    pa->current->attribute = value;

    Attribute* old_attribute = pa->current;
    pa->current = old_attribute->next;
    
    return pa->current;
}

// Function to add a new Tikzpicture to a TexDoc
Tikzpicture* add_tikzpicture(TexDoc* doc) {
    Document* document = doc->document;
    document->current->next = new_tikzpicture();

    Tikzpicture* old_tikz = document->current;
    document->current = old_tikz->next;

    return document->current;
}

// Generates and Formats the Coordinates in a .tex file given the head of the Coordinate linked list
void generate_coordinates(FILE* fp, Coordinate* coordinate){
    fprintf(fp, "\tcoordinates {");
    int i = 0;
    while(coordinate->next != NULL) {
        fprintf(fp, "(%f,%f) ", coordinate->x, coordinate->y);
        coordinate = coordinate->next;
        i++;
        if(i > 3){
            fprintf(fp, "\n\t\t\t\t");
            i = 0;
        }
    }
    fprintf(fp, "};");
}

// Generates the Legend in the .tex file
void generate_legend(FILE *fp, Legend* legend) {
    fprintf(fp, "%s%s%s%s", legend->legend, legend->open_key, legend->key, legend->close_key);
}

// Function to generate the Addplots in the .texfile
void generate_addplot(FILE *fp, Addplot* addplot){
    while(addplot->next != NULL) {
        fprintf(fp, "%s", addplot->addplot);
        generate_coordinates(fp, addplot->coordinates);
        addplot = addplot->next;
    }
    fprintf(fp, "%s", addplot->addplot);
    generate_coordinates(fp, addplot->coordinates);
}

// Function to generate the Attributes in the .texfile
void generate_attribute(FILE *fp, Attribute* attribute) {
    while(attribute->next != NULL) {
        fprintf(fp, "\t\t%s,", attribute->attribute);
        attribute = attribute->next;
        if(attribute->next != NULL) {
            fprintf(fp, "\n");
        }
    }
}

// Function to generate the Plotattribute in the .texfile
void generate_plotattributes(FILE *fp, PlotAttributes* pa){
    fprintf(fp, "%s", pa->open_attributes);
    generate_attribute(fp, pa->attributes);
    fprintf(fp, "%s", pa->close_attributes);
}

// Function to generate the Axis in the .texfile
void generate_axis(FILE *fp, Axis* axis){
    fprintf(fp, "%s", axis->begin_axis);
    generate_plotattributes(fp, axis->plotattributes);
    generate_addplot(fp, axis->addplots);
    generate_legend(fp, axis->legend);
    fprintf(fp, "%s", axis->end_axis);
}

// Function to generate the Tikzpictures in the .texfile
void generate_tikzpicture(FILE *fp, Tikzpicture* tikzpicture){
    fprintf(fp, "%s", tikzpicture->begin_tikzpicture);
    generate_axis(fp, tikzpicture->axis);
    fprintf(fp, "%s", tikzpicture->end_tikzpicture);

    while(tikzpicture->next != NULL) {
        generate_tikzpicture(fp, tikzpicture->next);
        tikzpicture = tikzpicture->next;
    }
}

// Function to generate the Document in the .texfile
void generate_document(FILE *fp, Document* document){
    fprintf(fp, "%s", document->begin_document);
    generate_tikzpicture(fp, document->tikzpictures);
    fprintf(fp, "%s", document->end_document);
}

// Function to generate the Preamble in the .texfile
void generate_preamble(FILE *fp, Preamble* preamble){
    fprintf(fp, "%s", preamble->preamble);
}

//Callable function that starts the generation of the different parts of the .tex file with the pointer
//TexDoc and an argument
void generate_doc(const TexDoc *my_doc, char* value) {
    int i = sizeof(value) + 10;
    char file_name[i];
    strcpy(file_name, value);
    strcat(file_name, ".tex");
    FILE *fp = fopen(file_name, "w");
    generate_preamble(fp, my_doc->preamble);
    generate_document(fp, my_doc->document); 
    fclose(fp);   
}

//Callable function that starts the generation of the different parts of the .tex file with the pointer
//TexDoc and an argument and calls the `pdflatex` command to compile a PDF with the generated .tex file
void generate_doc_and_pdf(const TexDoc *my_doc, char* value){
    int i = sizeof(value) + 10;
    char file_name[i];
    strcpy(file_name, value);
    strcat(file_name, ".tex");
    FILE *fp = fopen(file_name, "w");
    generate_preamble(fp, my_doc->preamble);
    generate_document(fp, my_doc->document); 
    fclose(fp);   

    int j = sizeof(file_name) + 20;
    char system_command[j];
    strcpy(system_command, "pdflatex ");
    strcat(system_command, file_name);

    int ret = system(system_command);
    if(ret != 0) {
        printf("Error: pdflatex command failed on %s. \n", file_name);
    }
}

//Recursively frees memory allocated for Coordinates
void free_coordinate(Coordinate* coordinate) {
    if(coordinate) {
        if (coordinate->next) {
            free_coordinate(coordinate->next);
        }
        free(coordinate);
    }
}

//Recursively frees memory allocated for Addplots
void free_addplot(Addplot* addplot) {
    if (addplot) {
        free_coordinate(addplot->coordinates);
        free(addplot->addplot);
        if (addplot->next) {
            free_addplot(addplot->next);
        }
        free(addplot);
    }
}

//Recursively frees memory allocated for Attributes
void free_attribute(Attribute* attribute) {
    if (attribute) {
        if (attribute->next) {
            free_attribute(attribute->next);
        }
        free(attribute);
    }
}

//Frees memory allocated for the Plotattribute object
void free_plotattributes(PlotAttributes* plotattributes) {
    if (plotattributes) {
        free(plotattributes->close_attributes);
        free(plotattributes->open_attributes);
        free_attribute(plotattributes->attributes);
        free(plotattributes);
    }
}

//Frees memory allocated for the Axis object
void free_axis(Axis* axis) {
    if (axis) {
        free_plotattributes(axis->plotattributes);
        free_addplot(axis->addplots);
        free(axis->begin_axis);
        free(axis->end_axis);
        free(axis);
    }
}

//Recursively frees memory allocated for Tikzpictures
void free_tikzpicture(Tikzpicture* tikzpicture) {
    if(tikzpicture) {
        free_axis(tikzpicture->axis);
        free(tikzpicture->begin_tikzpicture);
        free(tikzpicture->end_tikzpicture);
        if(tikzpicture->next){
            free_tikzpicture(tikzpicture->next);
        }
        free(tikzpicture);
    }
}

//Frees memory allocated for the Document object
void free_document(Document* document) {
    if (document) {
        free_tikzpicture(document->tikzpictures);
        free(document->begin_document);
        free(document->end_document);
        free(document);
    }
}

//Frees memory allocated for the Preamble object
void free_preamble(Preamble* preamble) {
    if (preamble) {
        free(preamble->preamble);
        free(preamble);
    }
}

//Callable function free memory allocated for the TexDoc object and starts the freeing the tree of Objects
//parented to the TexDoc
void free_texdoc(TexDoc* texdoc) {
    if (texdoc) {
        free_preamble(texdoc->preamble);
        free_document(texdoc->document);
        free(texdoc);
    }
}