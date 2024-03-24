#include <stdio.h>
#include <stdlib.h>

int add_row(FILE *fp)
{
    char name[20];
    int id;
    int qty;
    float price;
    fp=fopen("warehouse.txt","a");
    //check the order in which input has been taken
    printf("enter name,id,quantity and price of each piece \n");
    scanf("%s %d %d %f",name,&id,&qty,&price);
    fprintf(fp,"%d \t %s \t %d \t %f \n",id,name,qty,price);
    fclose(fp);
    return 0;
}

int get_details(FILE *fp)
{
    int id,to_find;
    int qty;
    int check=0;
    float price;
    char name[20];
    fp=fopen("warehouse.txt","r");
    if(fp==NULL)
    {
        printf("Database not found\n");
        return 0;
    }
    printf("enter id to be found\n");
    scanf("%d",&to_find);
    while(fscanf(fp,"%d %s %d %f",&id,name,&qty,&price)==4)
    {
        if(id==to_find)
        {
            printf("id :%d  product name:%s  quantity:%d  price is:%f\n",id,name,qty,price);
            check++;
            break;
        }
    }
    if(check==0)
    {
        printf("product not found\n");
    }
    fclose(fp);
    return 0;
}

int display_all(FILE *fp)
{
    int id;
    int qty;
    float price;
    char name[20];
    fp=fopen("warehouse.txt","r");
    if(fp==NULL)
    {
        printf("Database not found\n");
        return 0;
    }
    while(fscanf(fp,"%d %s %d %f",&id,name,&qty,&price)==4)
    {
        printf("id :%d  product name:%s  quantity:%d  price is:%f\n",id,name,qty,price);
    }
    fclose(fp);
    return 0;
}

int remove_row(FILE *fp)
{
    FILE *fp1;
    int id,to_find;
    int qty;
    int check=0;
    float price;
    char name[20];
    fp1=fopen("duplicate.txt","w");
    fp=fopen("warehouse.txt","r");
    if(fp==NULL)
    {
        printf("Database not found\n");
        return 0;
    }
    printf("enter id to be removed\n");
    scanf("%d",&to_find);
    while(fscanf(fp,"%d %s %d %f",&id,name,&qty,&price)==4)
    {
        if(id==to_find)
        {
            continue;
        }
        fprintf(fp1,"%d \t %s \t %d \t %f \n",id,name,qty,price);
    }
    fclose(fp);
    fclose(fp1);
    remove("warehouse.txt");
    rename("duplicate.txt","warehouse.txt");
    return 0;
}

int sell_item(FILE *fp)
{
    FILE *fp1;
    int id,to_find;
    int qty,qty_sold;
    int check=0;
    float price;
    char name[20];
    fp1=fopen("duplicate.txt","w");
    fp=fopen("warehouse.txt","r");
    if(fp==NULL)
    {
        printf("Database not found\n");
        return 0;
    }
    printf("enter id of item sold\n");
    scanf("%d",&to_find);
    printf("enter quantity sold\n");
    scanf("%d",&qty_sold);
    while(fscanf(fp,"%d %s %d %f",&id,name,&qty,&price)==4)
    {
        if(id==to_find)
        {
            if(qty>=qty_sold)
            {
                fprintf(fp1,"%d \t %s \t %d \t %f \n",id,name,(qty-qty_sold),price);
                continue;
            }
            else
            {
                printf("there are not sufficient items to sell\n");
            }
        }
        fprintf(fp1,"%d \t %s \t %d \t %f \n",id,name,qty,price);
    }
    fclose(fp);
    fclose(fp1);
    remove("warehouse.txt");
    rename("duplicate.txt","warehouse.txt");
    return 0;
}

int main()
{
    FILE *fp;
    int i=1;
    int dec;
    while(i)
    {
       printf("Enter 1 to add row\nEnter 2 to display row\nEnter 3 to display complete database\nEnter 4 to remove a row\nEnter 5 to sell item\nAny other key to exit program\n");
       scanf("%d",&dec);
       switch(dec)
       {
           case 1:
               add_row(fp);
               break;
           case 2:
               get_details(fp);
               break;
           case 3:
               display_all(fp);
               break;
           case 4:
               remove_row(fp);
               break;
           case 5:
               sell_item(fp);
               break;
           default:
               printf("Thank You");
               i--;
               break;
       }
    }
    return 0;
}
