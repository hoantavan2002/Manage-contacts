#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAX 100 // so Contact toi da trong DanhBa , tang len de them du lieu
typedef struct date // struct of birthday
{
    int day;
    int month;
    int year;
}date;

typedef struct danhba // struct one Contact
{
    char FirstName[20];
    char LastName[20];
    char Company[30];
    char Phone[11];
    char Working_Addr[30];
    char Home_Addr[30];
    date Birthday;
}DanhBa;
int kiemtra(char phone[]){
    int F=1,i;
    if(strlen(phone)>10||strlen(phone)<9) F=-1;
    for(i=0;i<strlen(phone);i++){
        if(phone[i]>'9'||phone[i]<'0') F=-1;
    }
    return F;
}
DanhBa makeContactNode(){  // Ham Nhap contact moi tu ban phim
    DanhBa NewContact;
    int r;
    printf("Enter FirstName: ");
    gets(NewContact.FirstName);
    printf("Enter LastName: ");
    gets(NewContact.LastName);
    printf("Enter Company: ");
    gets(NewContact.Company);
    do
    {
    printf("Enter phone number: ");
    scanf("%s",NewContact.Phone);
    getc(stdin);        
    } while (kiemtra(NewContact.Phone)!=1);
    printf("Enter Working Address: ");
    gets(NewContact.Working_Addr);
    printf("Enter Home Address: ");
    gets(NewContact.Home_Addr);
    do{
        printf("Enter birthday (XX/YY/ZZZZ): ");
        scanf("%d/%d/%d",&NewContact.Birthday.day,&NewContact.Birthday.month,&NewContact.Birthday.year);
    }while(NewContact.Birthday.day<0||NewContact.Birthday.day>31||NewContact.Birthday.month<0||NewContact.Birthday.month>12||NewContact.Birthday.year>2022||NewContact.Birthday.year<1900);
    return NewContact;
}
int NapDuLieu(DanhBa List[]){       //Nap du lieu tu file DanhBa.txt
    char FirstName[20];
    char LastName[20];
    char Company[30];
    char Phone[11];
    char Working_Addr[30];
    char Home_Addr[30];
    int day,month,year,i=0;
    FILE* file;
    if((file=fopen("DanhBa.txt","r"))==NULL){
        file=fopen("DanhBa.txt","w+");
        return 0;
        
    }
    while (!feof(file))
    {   
        fgets(FirstName,20,file);
        FirstName[strlen(FirstName)-1]='\0'; // Loai bo \n o cuoi string de khi printf ko bi xuong dong 
        strcpy(List[i].FirstName,FirstName); // gan List[],firstname = FirstName

        fgets(LastName,20,file);
        LastName[strlen(LastName)-1]='\0';
        strcpy(List[i].LastName,LastName);

        fgets(Company,30,file);
        Company[strlen(Company)-1]='\0';
        strcpy(List[i].Company,Company);

        fgets(Phone,13,file);
        Phone[strlen(Phone)-1]='\0';
        strcpy(List[i].Phone,Phone);

        fgets(Working_Addr,30,file);
        Working_Addr[strlen(Working_Addr)-1]='\0';
        strcpy(List[i].Working_Addr,Working_Addr);

        fgets(Home_Addr,30,file);
        Home_Addr[strlen(Home_Addr)-1]='\0';
        strcpy(List[i].Home_Addr,Home_Addr);

        fscanf(file,"%d/%d/%d",&day,&month,&year);
        fgetc(file);
        List[i].Birthday.day=day;
        List[i].Birthday.month=month;
        List[i].Birthday.year=year;
        i++;
    }
    fclose(file);
    return i;
}
void PrintNode(DanhBa List){     // print 1 contact
        printf("%20s",List.FirstName);
        printf("%20s",List.LastName);
        printf("%30s",List.Company);
        printf("%12s",List.Phone);
        printf("%30s",List.Working_Addr);
        printf("%30s",List.Home_Addr);
        printf("\t%2d/%2d/%d\n",List.Birthday.day,List.Birthday.month,List.Birthday.year);
}
void CapNhapDanhBa(DanhBa List[],int N){    // Cap Nhap lai file DanhBa.txt khi Add Delete Edit Contact
    int i;
    FILE * fout;
    fout=fopen("DanhBa.txt","w+");
    for(i=0;i<N;i++){
        fprintf(fout,"%s\n",List[i].FirstName);
        fprintf(fout,"%s\n",List[i].LastName);
        fprintf(fout,"%s\n",List[i].Company);
        fprintf(fout,"%s\n",List[i].Phone);
        fprintf(fout,"%s\n",List[i].Working_Addr);
        fprintf(fout,"%s\n",List[i].Home_Addr);
        if(i==N-1) fprintf(fout,"%2d/%2d/%d",List[i].Birthday.day,List[i].Birthday.month,List[i].Birthday.year);
        else{fprintf(fout,"%2d/%2d/%d\n",List[i].Birthday.day,List[i].Birthday.month,List[i].Birthday.year);}
    }    
    fclose(fout);
}
int AddNewContact(DanhBa List[], DanhBa NewContact, int N){ // Them Contact moi vao cuoi Mang (N<MAX)
    if(N==0) printf("\nDanh Ba hien chua co du lieu !\n");
    if(N==MAX-1){
        printf("Out off memory!!! Can't Add the contact \n"); // Neu N>MAX thi ko cho Add 
        return N;
    }
    List[N]=NewContact; 
    N++;
    CapNhapDanhBa(List,N);  //Cap Nhap lai file
    return N;
};
int findPhoneNumber(DanhBa List[],int N, char phone[]){     // tim ConTact theo PhoneNumber
    int i;
    for(i=0;i<N;i++){
        if(strcmp(List[i].Phone,phone)==0){
            return i;
        }
    }
    return -1;
}
void EditContact(DanhBa List[],int N){      
    char phone[11];
    int i;
    do{
        printf("Enter phone number needs edit : ");
        scanf("%s",phone);
        i=findPhoneNumber(List,N,phone);
        if(i==-1) printf("Can't find contact !\n");
    }while(i==-1);
    getc(stdin);
    DanhBa Contact=makeContactNode();
    List[i]=Contact;
    CapNhapDanhBa(List,N);
}
DanhBa Delete(DanhBa List[],int N, int i){  // Xoa Contact bang cach do'n ma?ng len tren 1 don vi ; N-=1; 
    DanhBa Contact=List[i];
    int y;
    for(y=i;y<N-1;y++){
        List[y]=List[y+1];
    }
    return Contact;
}
int DeleteContact(DanhBa List[],int N){
    int i;
    char phone[11];
    DanhBa contact;
    do{
        printf("Enter phone number needs delete : ");
        scanf("%s",phone);
        i=findPhoneNumber(List,N,phone);
        if(i==-1) printf("Can't find contact !\n");
    }while(i==-1);
    contact=Delete(List,N,i);
    N--;
    printf("you just delete contact:\n");
    printf("%20s%20s%30s%12s%30s%30s %9s\n","FirstName","LastName","Company","PhoneNumber","Working Address","Home Address","Birthday");
    PrintNode(contact);
    CapNhapDanhBa(List,N);
    return N;
}
void SearchContact(DanhBa List[],int N){
    char phone[11];
    int i;
    do{
        printf("Enter phone number needs Search : ");
        scanf("%s",phone);
        i=findPhoneNumber(List,N,phone);
        if(i==-1) printf("Can't find contact !\n");
    }while(i==-1);
    printf("%20s%20s%30s%12s%30s%30s %9s\n","FirstName","LastName","Company","PhoneNumber","Working Address","Home Address","Birthday");
    PrintNode(List[i]);
}
void ChucNang5(DanhBa List[],int N){
    int Array[N];
    int n=0,month,i,j;
    printf("Enter month want search: ");
    scanf("%d",&month);
    for(i=0;i<N;i++){                   // tao Mang cac Contact co cung month can tim 
        if(List[i].Birthday.month==month){
            Array[n]=i;
            n++;
        }
    }
    for(i=0;i<n-1;i++){                 // Sort mang month theo day tang dan (bubble Sort)
        for(j=n-1;j>i;j--){
            if(List[Array[j]].Birthday.day<List[Array[j-1]].Birthday.day){
                int tmp=Array[j];
                Array[j]=Array[j-1];
                Array[j-1]=tmp;
            }
        }
    }
    printf("%20s%20s%30s%12s%30s%30s %9s\n","FirstName","LastName","Company","PhoneNumber","Working Address","Home Address","Birthday");
    for(i=0;i<n;i++){
        PrintNode(List[Array[i]]);
    }
}
void ChucNang6(DanhBa List[],int N){
    int i,j;
    int Array[N];
    for(i=0;i<N;i++) Array[i]=i;    // khoi tao mang ben ngaoi chua stt cua ConTact trong List
    for(i=0;i<N-1;i++){             // Bubble Sort
        for(j=N-1;j>i;j--){
            char FullName2[50]="",FullName1[50]="";
            strcat(FullName2,List[Array[j]].FirstName);
            strcat(FullName2," ");
            strcat(FullName2,List[Array[j]].LastName);
            strcat(FullName1,List[Array[j-1]].FirstName);
            strcat(FullName1," ");
            strcat(FullName1,List[Array[j-1]].LastName);
            if(strcmp(FullName2,FullName1)<0){
                int tmp=Array[j];
                Array[j]=Array[j-1];
                Array[j-1]=tmp;
            }
        }
    }
    printf("%20s%20s%30s%12s%30s%30s %9s\n","FirstName","LastName","Company","PhoneNumber","Working Address","Home Address","Birthday");
    for(i=0;i<N;i++){
        PrintNode(List[Array[i]]);
    }
}
int main(){
    DanhBa List[MAX];
    int N;
    N=NapDuLieu(List);
    DanhBa NewContact;
    char choice;
    do{
        printf("\n\n*****************************\n");
        printf(    "      Quan Ly Danh Ba \n");
        printf(    "*****************************\n\n");
        printf(" 1. Add new contact\n");
        printf(" 2. Edit contact\n");
        printf(" 3. Delete contact \n");
        printf(" 4. Search contact \n");
        printf(" 5. List all contacts with birthdays in a given month \n");
        printf(" 6. List all contacts in the table format \n");
        printf(" 7. Thoat chuong trinh\n");
        fflush(stdin);
        choice= getchar();
        fflush(stdin);
        switch (choice)
        {           
        case '1':
            NewContact=makeContactNode();
            N=AddNewContact(List,NewContact,N);
            printf("You just add the contact: \n");
            printf("%20s%20s%30s%12s%30s%30s %9s\n","FirstName","LastName","Company","PhoneNumber","Working Address","Home Address","Birthday");
            PrintNode(NewContact);
            break;
        case '2':
            EditContact(List,N);
            break;
        case '3':
            N=DeleteContact(List,N);
            break;
        case '4':
            SearchContact(List,N);
            break;
        case '5':
            ChucNang5(List,N);
            break;
        case '6':
            ChucNang6(List,N);
            break;
        case '7':
            break;      
        default:
            break;
        }

    } while(choice != '7');
    return 0;
}
