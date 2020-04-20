#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Internet(int bytes) {
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

  int bytes = 0;
  int num = 0; //Number of words in a string

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

          for (int j=0; j<i; j++) {

            char * value1 = m[5];
            char * value2 = m[7];

            char * str = "17.248.150.51";

            istr1 = strstr(value1,str);
            istr2 = strstr(value2,str);

            if (istr1 != NULL || istr2 != NULL) {
              bytes = bytes + atoi(m[11]);
              num = i;
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

          fprintf(f2,"%d%d %d\n", chisla[0], chisla[1], atoi(m[11]));
        }
  }
    fclose(f1);
    fprintf(f2,"e\n");
    fclose(f2);
    bytes = bytes/num;
    printf("Всего байтов: %d", bytes);
    printf("\n");

    Internet(bytes);

  return 0;
}
