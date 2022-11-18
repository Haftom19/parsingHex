#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main(int argc, char **argv)
{
   
    char str[150];
    char rec_length[10];
    char load_offset[10];
    char record_type[10];
    char data_type[20];
    char startup[100];
    char startup2[100];
    int count = 0;
    int char_to_int(char c);
    FILE *fp; // filepointer to the file
    fp = fopen(argv[1], "r");
    if (argc != 2)
    {
        printf("Error,please enter the hex file name\n");
        return 0;
    }
    while ((fgets(str, 150, fp) != NULL))
    {
        if (feof(fp)) // end of file endicator
            break;
        printf("%s", str);
        printf("RecordMark=%c\n", str[0]);
        count++;
        for (count = 1; count <= 2; count++)
        {
            rec_length[count - 1] = str[count];
           // printf("RecordLength[%d]:0x%d \n", (count - 1), 30 + char_to_int(rec_length[count - 1]));
        }
        printf("RecordLength=%lx\n", strtoul(rec_length, NULL, 16));
        for (count = 3; count <= 6; count++)
        { 
            load_offset[count - 3] = str[count];
           // printf("LoadOffset[%d]:0x%d \n", (count - 3), 30 + char_to_int(load_offset[count - 3]));
        }
        printf("LoadOffset:%lx\n", strtoul(load_offset, NULL, 16));
        for (count = 7; count <= 8; count++)
        {
            record_type[count - 7] = str[count];
           // printf("RecordType[%d]:0x%d \n", (count - 7), 30 + char_to_int(record_type[count - 7]));
        }
        printf("RecordType:%lx\n", strtoul(record_type, NULL, 16));
        for (int j = 0; j <= 31; j++)
        {
            for (int count = 9 + (2 * j); count <= (9 + (2 * j) + 1); count++)
            {
                data_type[count - (9 + (2 * j))] = str[count];
            }
            printf("Byte [%d]:%lx\n", j, strtoul(data_type, NULL, 16));
        }
        for (int j = 0; j <= 3; j++)
        {
            if ((strtoul(load_offset, NULL, 16)) == (16448 + (160 * j)))
            {
                for (count = 9; count <= 16; count++)
                {
                    startup[count - 9] = str[count];
                    startup2[count - 9] = str[count + 40];
                }
            }
            else if ((strtoul(load_offset, NULL, 16)) == (16480 + (160 * j)))
            {
                for (count = 25; count <= 32; count++)
                {
                    startup[count - 25] = str[count];
                    startup2[count - 25] = str[count + 40];
                }
            }
            else if ((strtoul(load_offset, NULL, 16)) == (16512 + (160 * j)))
            {
                for (count = 41; count <= 48; count++)
                {
                    startup[count - 41] = str[count];
                    startup2[count - 41] = 0;
                }
            }
            else if ((strtoul(load_offset, NULL, 16)) == (16544 + (160 * j)))
            {
                for (count = 17; count <= 24; count++)
                {
                    startup[count - 17] = str[count];
                    startup2[count - 17] = str[count + 40];
                }
            }
            else if ((strtoul(load_offset, NULL, 16)) == (16576 + (160 * j)))
            {
                for (count = 33; count <= 40; count++)
                {
                    startup[count - 33] = str[count];
                    startup2[count - 33] = 0;
                }
            }
        }
        printf("startup:%lx\n", strtoul(startup, NULL, 16));
        printf("startup2:%lx\n", strtoul(startup2, NULL, 16));
    }
    count++;
    fclose(fp); // closing the file pointer
    return 0;
}
int char_to_int(char ch)
{
    if ((ch >= '0') && (ch <= '9'))
    {
        return ch - '0';
    }
    if ((ch >= 'A') && (ch <= 'F'))
    {
        return 10 + (ch - 'A');
    }
    if ((ch >= 'a') && (ch <= 'f'))
    {
        return 10 + (ch - 'a');
    }
    return 0;
}
