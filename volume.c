#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef uint8_t BYTE;
typedef int16_t byte;

int main(int argc, char *argv[])
{
    if (argc!=4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }
    FILE *file_inp=fopen(argv[1],"rb");
    if (file_inp==NULL)
    {
        printf("File not opened.\n");
        return 1;
    }

    FILE *file_out=fopen(argv[2],"wb");
    if (file_out==NULL)
    {
        printf("File not opened.\n");
        return 1;
    }

    float factor=atof(argv[3]);
    for(int i=0;i<44;i++)
    {
        BYTE b;
        fread(&b,sizeof(b),1,file_inp);
        fwrite(&b,sizeof(b),1,file_out);
    }
    byte b;
    while (fread(&b,sizeof(b),1,file_inp)!=0)
    {
        byte new_byte=factor*b;
        fwrite(&new_byte,sizeof(b),1,file_out);
    }
    fclose(file_inp);
    fclose(file_out);
}
