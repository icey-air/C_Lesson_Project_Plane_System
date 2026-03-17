#include"Tourist_File.h"




FILE*Tourist_File_Save(struct tourist *Tourist_head)
{

    tourist*Tourist=Tourist_head;

    char buffer[128];
    FILE*Tourist_File=NULL;
    Tourist_File=fopen(Tourist_File_Site,"w");

    while(Tourist!=NULL)
    {
    sprintf(buffer, "Account:%s Password:%s\n", Tourist->Account, Tourist->password);

    fputs(buffer,Tourist_File);
    Tourist=Tourist->next;
    }
    printf("Save");
    fclose(Tourist_File);
}