#ifndef _PGFPLOTS_
#define _PGFPLOTS_

void make_file(char data[], int size, int length);

void generate_tex(char width[]);

void make_doc(char *axislabel);

void variadic_test(int count, ...);

typedef struct Coordinate {
    double x;
    double y;
    struct Coordinate * next;

}Coordinate;

typedef struct Legend {
    char* legend;
    char* open_key;
    char* key;
    char* close_key;
}Legend;

typedef struct Addplot {
    char* addplot;
    struct Addplot * next;
    Coordinate* coordinates;
    Coordinate* current;

}Addplot;

typedef struct Attribute {
    char* attribute;
    struct Attribute* next;
}Attribute;

typedef struct PlotAttributes {
    char* open_attributes;
    Attribute* attributes;
    Attribute* current;
    char* close_attributes;
}PlotAttributes;

typedef struct Axis {
    char* begin_axis;
    PlotAttributes* plotattributes;
    Addplot* addplots;
    Addplot* current;
    Legend* legend;
    char* end_axis;
}Axis;

typedef struct Tikzpicture {
    char* begin_tikzpicture;
    Axis* axis;
    struct Tikzpicture* next;
    char* end_tikzpicture;

}Tikzpicture;

typedef struct Document {
    char* begin_document;
    Tikzpicture* tikzpictures;
    Tikzpicture* current;
    char* end_document;

}Document;

typedef struct Preamble {
    char* preamble;

}Preamble;

typedef struct TexDoc {
    Preamble* preamble;
    Document* document;

}TexDoc;

TexDoc* new_texdoc();

int append_coordinate(double x, double y, Addplot* addplot);

Addplot* add_addplot(Tikzpicture* tikz);

Attribute* add_attribute(PlotAttributes* pa, char* value);

Tikzpicture* add_tikzpicture(TexDoc* doc);

void set_legend_key(Legend* legend, char* value);

PlotAttributes* get_plotattributes(Tikzpicture* tikz);

Legend* get_legend(Tikzpicture* tikz);

Addplot* get_addplot(Tikzpicture* tikz, int addplot_index);

Tikzpicture* get_tikzpicture(TexDoc* doc, int tikz_index);

void generate_doc(const TexDoc *my_doc, char* value);

void generate_doc_and_pdf(const TexDoc *my_doc, char* value);

void write_doc(TexDoc *my_doc);

void free_texdoc(TexDoc *texdoc);

#endif