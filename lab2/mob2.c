#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Internet(float bytes) {
  //X = Q * k
  //Q - общий объем трафика NetFlow за отчетный период
  //k - множитель тарифного плана, k = 0,5руб/Мб
float k = 0.5;
float x = bytes * k / 1048576;

printf("Итоговая стоимость трафика для IP 17.248.150.51: %f\n", x);

}

int main() {

  FILE*f1 = NULL;
  f1=fopen("./text.txt","r");

  FILE*f2 = NULL;
  f2=fopen("./graph.plt","w");

  fprintf(f2,"set terminal jpeg\nset output \"res.jpeg\"\nplot '-' using 1:2 w points ps 3 pt 4\n");

  char str[300];

  float bytes = 0;
  char * hi;

  while (fgets(str,300,f1)) {
         //puts(str);
      char m[100][100];
      int i=0;
          char *p;
          p = strtok(str," ");
          while(p!=NULL){
              strcpy(m[i],p);
              i++;
              p=strtok(NULL," ");
          }
          int j=0;
          char *istr1;
          char *istr2;
          char *istr3;

          for (int j=0; j<i; j++) {

            char * value1 = m[5];
            char * value2 = m[7];
            char * value3 = m[12];

            char * str = "17.248.150.51";
            char * str1 = "M";

            istr1 = strstr(value1,str);
            istr2 = strstr(value2,str);
            istr3 = strstr(value3,str1);

            if (istr1 != NULL || istr2 != NULL) {
              if (istr3 != NULL) {
                bytes = bytes + atof(m[11])/i*1048576;
              }
              else {
                bytes = bytes + atoi(m[11])/i;
              }
            }
        }

        if (istr1 != NULL || istr2 != NULL) {
          char * time = m[1];
          int k=0;
          char *t;
          int chisla[4] = {0};
          t = strtok(time,":.");
          while(t!=NULL){
            chisla[k] = atoi(t);
            k++;
            t=strtok(NULL,":.");
          }

          if (istr3 != NULL)
            fprintf(f2,"%d%d %f\n", chisla[0], chisla[1], atof(m[11])*1048576);
          else
            fprintf(f2,"%d%d %d\n", chisla[0], chisla[1], atoi(m[11]));
        }
  }
    fclose(f1);
    fprintf(f2,"e\n");
    fclose(f2);
    printf("Всего байтов: %.0f\n", bytes);
    printf("\n");

    Internet(bytes);

  return 0;
}
