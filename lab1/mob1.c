#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Telephony(double call_in, double call_out) {
  //X = T * k
  //X - итоговая стоимость всех звонков абонента
  //T - общая длительность звонков (сумма длительностей всех записей по абоненту в файле)
  //k - множитель тарифного плана
int price_call_in = 1;
int price_call_out = 1;
float x = call_in*price_call_in + call_out*price_call_out;

printf("Итоговая стоимость всех звонков абонента с номером 911926375: %f\n", x);

}

void SMS(int sms) {
  //Y = N * k
  //Y - итоговая стоимость всех СМС абонента
  //N - общее количество СМС (сумма числа всех СМС в записях по абоненту в файле)
  //k - множитель тарифного плана
  //first 5 sms are free
int price_sms = 1;
int free_sms = 5;
int y = (sms - free_sms)*price_sms;

printf("Итоговая стоимость всех СМС абонента с номером 911926375: %d\n", y);

}



int main() {

  FILE*f1 = NULL;
  f1=fopen("./data.csv","r");
  char str[101];

  int origin_out, dest_out, sms = 0;
  int origin_in, dest_in;
  float call_out = 0, call_in = 0;

  while (fgets(str,100,f1)) {
         //puts(str);
      char m[100][100];
      int i=0;
          char *p;
          p = strtok(str,",");
          while(p!=NULL){
              strcpy(m[i],p);
              i++;
              p=strtok(NULL,",");
          }
          int j=0;
          for(int j=0; j<i; j++) {
            int value1 = atoi(m[1]);
            int value2 = atoi(m[2]);
            //printf("%s ",m[j]);
            if (value1 == 911926375) {
              origin_out = value1;
              dest_out = atoi(m[2]);
              call_out = call_out + atof(m[3])/i;
              sms = sms + atoi(m[4])/i;
              }

            if (value2 == 911926375) {
              origin_in = value2;
              dest_in = atoi(m[2]);
              call_in = call_in + atof(m[3])/i;
              }
        }
  }
  fclose(f1);
  //printf("%d %d %f %d", origin_out, dest_out, call_out, sms);
  //printf("%d %d %f", origin_in, dest_in, call_in);

  Telephony(call_in, call_out);
  SMS(sms);

    return 0;
}
