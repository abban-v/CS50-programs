#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc!=2)
    {
        printf("Usage: ./recover [filename].\n");
        return 1;
    }
    FILE *input_im=fopen(argv[1],"rb");
    if (input_im==NULL)
    {
        printf("File could not be opened.\n");
        return 1;
    }

    BYTE b[512];
    int indexo=0;
    int indext=0;
    int indexh=0;
    char *filename=malloc(10);
    if (filename==NULL)
    {
        printf("No memory.\n");
    }
    sprintf(filename,"%i%i%i.jpg",indexh,indext,indexo);
    FILE *file_op=fopen(filename,"wb");
    while (fread(&b,sizeof(b),1,input_im)!=0)
    {
        if (b[0]==0xff && b[1]==0xd8 && b[2]==0xff)
        {
            int three=b[3];
            if (three>=224 && three<=239)
            {
                sprintf(filename,"%i%i%i.jpg",indexh,indext,indexo);
                fclose(file_op);
                file_op=fopen(filename,"wb");
                if (file_op==NULL)
                {
                    printf("Unable to create file.\n");
                    return 1;
                }
                fwrite(&b,sizeof(b),1,file_op);
                indexo+=1;
                if (indexo>9)
                {
                    indexo=0;
                    indext+=1;
                }
                if (indext>9)
                {
                    indext=0;
                    indexh+=1;
                }
            }
        }
        else
        {
            fwrite(&b,sizeof(BYTE),512,file_op);
        }
    }
    fclose(input_im);
    fclose(file_op);
    free(filename);

}
