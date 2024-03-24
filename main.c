#include <stdio.h>
#include <stdlib.h>

int add_row(FILE *fp)
{
    char name[20],name1[20];
    int check=0;
    int id,id1;
    int qty,qty1;
    float price,price1;
    printf("Enter Name, ID, Quantity and Price of each piece: \n");
    scanf("%s %d %d %f",name,&id,&qty,&price);
    fp=fopen("warehouse.txt","r");
    while(fscanf(fp,"%d %s %d %f",&id1,name1,&qty1,&price1)==4)
    {
        if(id1==id)
        {
            printf("Unable to add item(ID already exists)\n");
            check=1;
            break;
        }
    }
    fclose(fp);
    if(check==0)
    {
        fp=fopen("warehouse.txt","a");
        fprintf(fp,"%d \t %s \t %d \t %f \n",id,name,qty,price);
        fclose(fp);
        printf("Row added\n");
    }
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
    printf("Enter ID to be found\n");
    scanf("%d",&to_find);
    while(fscanf(fp,"%d %s %d %f",&id,name,&qty,&price)==4)
    {
        if(id==to_find)
        {
            printf("ID :%d  Product Name:%s  Quantity:%d  Price is:%f\n",id,name,qty,price);
            check++;
            break;
        }
    }
    if(check==0)
    {
        printf("Product not found\n");
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
    printf("%-5s%-20s%-10s%-10s\n", "ID", "Product Name", "Quantity", "Price");
    while (fscanf(fp, "%d %s %d %f", &id, name, &qty, &price) == 4)
    {
        printf("%-5d%-20s%-10d%-10.2f\n", id, name, qty, price);
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
    printf("Enter ID to be removed\n");
    scanf("%d",&to_find);
    while(fscanf(fp,"%d %s %d %f",&id,name,&qty,&price)==4)
    {
        if(id==to_find)
        {
            printf("Product removed\n");
            check=1;
            continue;
        }
        fprintf(fp1,"%d \t %s \t %d \t %f \n",id,name,qty,price);
    }
    fclose(fp);
    fclose(fp1);
    remove("warehouse.txt");
    rename("duplicate.txt","warehouse.txt");
    if(check==0)
    {
        printf("Product not in warehouse(was not removed)\n");
    }
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
    printf("Enter ID of item to be sold:\n");
    scanf("%d",&to_find);
    printf("Enter Quantity to be sold:\n");
    scanf("%d",&qty_sold);
    while(fscanf(fp,"%d %s %d %f",&id,name,&qty,&price)==4)
    {
        if(id==to_find)
        {
            if(qty>=qty_sold && qty_sold>=0)
            {
                fprintf(fp1,"%d \t %s \t %d \t %f \n",id,name,(qty-qty_sold),price);
                printf("Sale Processed\n");
                continue;
            }
            else
            {
                printf("Sale not processed(insufficient items to sell)\n");
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

int restock_item(FILE *fp)
{
    FILE *fp1;
    int id,to_find;
    int qty,qty_add;
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
    printf("Enter ID of item restocked\n");
    scanf("%d",&to_find);
    printf("Enter quantity to be added\n");
    scanf("%d",&qty_add);
    while(fscanf(fp,"%d %s %d %f",&id,name,&qty,&price)==4)
    {
        if(id==to_find)
        {
            if(qty_add>0)
            {
                fprintf(fp1,"%d \t %s \t %d \t %f \n",id,name,(qty+qty_add),price);
                printf("Restocking successful\n");
                continue;
            }
            else
            {
                printf("Unable to Restock(Invalid Input)\n");
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
       printf("Enter 1 to add an item\nEnter 2 to display item\nEnter 3 to display warehouse stock\nEnter 4 to remove an item\nEnter 5 to sell an item\nEnter 6 to restock\nAny other key to exit program\n");
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
           case 6:
               restock_item(fp);
               break;
           default:
               printf("Thank You");
               i--;
               break;
       }
    }
    return 0;
}
