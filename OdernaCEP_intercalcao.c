 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma pack(1)

typedef struct _Endereco Endereco;

struct _Endereco
{
    char logradouro[72];
    char bairro[72];
    char cidade[72];
    char uf[72];
    char sigla[2];
    char cep[8];
    char lixo[2];
};

int compara(const void *endereco1, const void *endereco2)
{
    return strncmp(((Endereco*)endereco1)->cep,((Endereco*)endereco2)->cep,8);
}

int main(int argc, char**argv)
{
    FILE *f,*g, *saida;
    Endereco *e;
    Endereco x,y;
    long tamanho_arquivo, qtd, partedocep;
   int i=1;
    f = fopen("cep.dat","r");
    fseek(f,0,SEEK_END);
    tamanho_arquivo = ftell(f);
    qtd = tamanho_arquivo/sizeof(Endereco);
    partedocep = qtd/8;
    char file[20],file2[20],file3[20];
    fseek(f,0,SEEK_SET);


  while(i<=16){


	e = (Endereco*) malloc(partedocep*sizeof(Endereco));
    if(fread(e,sizeof(Endereco),partedocep,f) == partedocep)
    {
        printf("O arquivo foi %d Lido\n", i);

    }

	qsort(e,partedocep,sizeof(Endereco),compara);

	printf("O arquivo %d foi ordenado\n", i);
    sprintf(file,"Cep%d.dat",i);
    saida = fopen(file,"w");
    fwrite(e,sizeof(Endereco),partedocep,saida);
    fclose(saida);
    printf("Foi escrito no arquivo %d\n", i);
    i++;

}
fclose(f);

int j=2,k=17;

i=1;

    while(k<=31){
        sprintf(file,"Cep%d.dat",i);
        sprintf(file2,"Cep%d.dat",j);
        sprintf(file3,"Cep%d.dat",k); 
        f = fopen(file,"r");//
        g = fopen(file2,"r");//
        saida = fopen(file3,"w");//

        fread(&x,sizeof(Endereco),1,f);
        fread(&y,sizeof(Endereco),1,g);

        while(!feof(f) && !feof(g))
        {
            if(compara(&x,&y)<0)
            {
                fwrite(&x,sizeof(Endereco),1,saida);
                fread(&x,sizeof(Endereco),1,f);
            }
            else
            {
                fwrite(&y,sizeof(Endereco),1,saida);
                fread(&y,sizeof(Endereco),1,g);
            }
        }

        while(!feof(f))
        {
            fwrite(&x,sizeof(Endereco),1,saida);
            fread(&x,sizeof(Endereco),1,f);
        }
        while(!feof(g))
        {
            fwrite(&y,sizeof(Endereco),1,saida);
            fread(&y,sizeof(Endereco),1,g);

        } 

        i+=2;
        j+=2;
        k++;
        if(k==24){
            i=16;
            j=17;

        }

    fclose(f);
    fclose(g);
    fclose(saida);

}
i=1;
sprintf(file,"Cep%d.dat",i);
while(i<=31)
{
remove(file);
i++;
sprintf(file,"Cep%d.dat",i);
}

}
