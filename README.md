# Plot-Generierung

PGFPLOTS C Library
===================

This library provides functionalities to generate LaTeX PGFPlots documents programmatically 
using C. It allows users to create documents, add TikZ pictures, configure plot attributes, 
add plots, and manage coordinates for creating comprehensive plots.

To use this library, you need to download the source files and inlcude them in your script. 
Here are the steps:

1. Download the source files `pgfplots.h` and `pgfplots.c`
2. Include the header file in your .c file:
	 #include "pgfplots.h"
    as long as the source files are in the same directory as your .c file, otherwise include a path
    to the source files in the #include statement.
3. Compilation:
    - if your .c file is named main.c, call "make" and then "./main" in your project's directory.
    - if your .c file is called something else:
        - either edit the makefile and change every instance of main to the name of your file.
        - or compile your .c file with the "gcc -c -g <your-file.c> -o main.o" command before calling "make"
            and runing it with "./main".

## Library Structure and Methods

### Structure Heirarchy:
    - TexDoc
      - Preamble
        - Document
          - Tikzpicture
		    - Axis
			  - Legend
			  - Addplot
			    - Coordinate
			  - PlotAttributes
			    - Attribute

### Exposed Methods:

TexDoc* new_texdoc();
- Returns TexDoc struct and calls initial constructors for all substructs. Use this method to create a new texdoc object.


int append_coordinate(double x, double y, Addplot* addplot);
- appends coordinates to the addplot structure provided. `x` and `y` are the coordinate values. Returns 0 on success. Use this method to add data points to your plot. 

Addplot* add_addplot(Tikzpicture* tikz);
- Returns an addplot pointer, appended onto the provided Tikzpicture. A TexDoc created withnew_texdoc() will already contain one addplot struct with an addplot_index == 0. Usethis function to add multiple plots to an Axis. Each new Addplot in a TexDoc will have an addplot_index of addplot_index++.

Attribute* add_attribut(PlotAttributes*, char* value);
- Returns a pointer to the attribute structure appended to the provided PlotAttributesstructure. Value is the entire attribute you want added on one line.

Tikzpicture* add_tikzpicture(TexDoc* doc);
- Returns a tikzpicture pointer appended onto the given doc. A TexDoc created with new_texdoc() will already contain one Tikzpicture struct with an tikz_index == 0. Use this function to add multiple tikzpictures to a TexDoc. Each new Tikzpicture will have a tikz_index of tikz_index++. A Tikzpicture with a tikz_index =<2 will be rendered to far to the right to be visible with a default page size and/or a default axis width.


void set_legend_key(Legend* legend, char* value);
- Sets the values that should be displayed in the legend for each axis. Value is a string containing a name for each addplot corresponding to the order in which the addplots were added. Each name in value should be seperated with a comma, for example:
	set_legend_key(legend, "Men, Women");


PlotAttributes* get_plotattributes(Tikzpicture* tikz);
- Returns a pointer to the PlotAttributes object child of the given Tikzpicture object.

Legend* get_legend(Tikzpicture* tikz);
- Returns a pointer to the Legend object child of the given Tikzpicture object;

Addplot* get_addplot(Tikzpicture* tikz, int addplot_index);
- Returns a pointer to a Addplot object child of the given Tikzpicture object. An addplot_index value is required becuase there can be multiple Addplots belonging to a tikzpicture. 

Tikzpicture* get_tikzpicture(TexDoc* doc, int tikz_index);
- Returns a pointer to a Tikzpicture object child of the given TexDoc object. An tikz_index value is required becuase a TexDoc object can have multiple Tikzpicture children.


void generate_doc(const TexDoc *doc, char* value);
- Generates a .tex file using the provided TexDoc object's values. The char string value is the name of the resulting .tex file. Calling the method generate_doc(my_texdoc, "my-file-name") will result in the generation of a .tex file called my-file-name.tex. Call this method after all values have already been generated so that all values are correctly added to the file.

void generate_doc_and_pdf(const TexDoc *doc, char* value);
- The same as generate_doc() only also calls the `pdflatex` command to automatically compile the .tex file into a PDF with the same name. 

void free_texdoc(TexDoc *texdoc);
- Recursively frees all pointers allocated in memory. Call after `void generate_doc(const TexDoc *doc)`



                    
