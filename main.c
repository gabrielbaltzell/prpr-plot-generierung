#include "pgfplots.h"

int main () {



   TexDoc *my_doc = new_texdoc();

   Tikzpicture *first_tikz = get_tikzpicture(my_doc, 0);

   char myxlabel[] = "Year";
   char myylabel[] = "Amount";

   PlotAttributes* pa = get_plotattributes(first_tikz);
   Legend* legend = get_legend(first_tikz);

   add_attribute(pa, "xlabel=Year");
   add_attribute(pa, "ylabel=Amount");
   add_attribute(pa, "x tick label style={/pgf/number format/1000 sep=}");
   add_attribute(pa, "legend style={at={(0.5,-0.15)},anchor=north,legend columns=-1}");

   set_legend_key(legend, "Men, Women");
   double xarray0[] = {1, 2, 3, 4, 5};
   double yarray0[] = {1, 2, 3, 4, 5};

   Addplot *addplot0 = get_addplot(first_tikz, 0);

   for(int i = 0; i < 5; i++){
      append_coordinate(xarray0[i], yarray0[i], addplot0);
   }

   add_addplot(first_tikz);

   Addplot *addplot1 = get_addplot(first_tikz, 1);

   double xarray1[] = {5, 4, 3, 2, 1};
   double yarray1[] = {1, 2, 3, 4, 5};

   for(int i = 0; i < 5; i++){
      append_coordinate(xarray1[i], yarray1[i], addplot1);
   }

   Tikzpicture* tik1 = add_tikzpicture(my_doc);

   

   set_legend_key(get_legend(tik1), "Men, Women");

   add_attribute(get_plotattributes(tik1), "xlabel=Year");
   add_attribute(get_plotattributes(tik1), "ylabel=Amount");
   add_attribute(get_plotattributes(tik1), "x tick label style={/pgf/number format/1000 sep=}");
   add_attribute(get_plotattributes(tik1), "legend style={at={(0.5,-0.15)},anchor=north,legend columns=-1}");

   double xarray2[] = {2, 2, 2, 2, 2};
   double yarray2[] = {1, 2, 3, 4, 5};

   for(int i = 0; i < 5; i++) {
      append_coordinate(xarray2[i], yarray2[i], get_addplot(tik1, 0));
   }

   double xarray3[] = {1, 2, 3, 4, 5};
   double yarray3[] = {2, 2, 2, 2, 2};

   Addplot *addplot3 = add_addplot(tik1);

   for(int i = 0; i < 5; i++) {
      append_coordinate(xarray3[i], yarray3[i], addplot3);
   }

   generate_doc(my_doc, "generated");

   generate_doc_and_pdf(my_doc, "generatedpdf");

   free_texdoc(my_doc);

}