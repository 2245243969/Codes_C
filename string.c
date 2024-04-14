//串的相关操作
//串和线性表的区别：线性表上的操作是针对其某个元素进行的，而串上的操作主要是针对串的整体或串的一部分子串进行的。
//串也有顺序存储和链式存储，大多数用顺序存储，以下也为顺序存储的实现,存储从数组下标的1开始

#include<stdio.h>
#include<stdlib.h>
#define MAX_SIZE 100

#define OK 1;
#define ERROR 0;


//定长顺序存储
typedef struct {
char data[MAX_SIZE];
int length;
}SString;

//串的初始化
void InitString(SString *string){
    string->length=0;
}

//判断串是否为空
int EmptyString(SString *string){
    if(string->length==0){
        return OK;
    }
    else{return ERROR;}
}

//判断串是否为满
int FullString(SString *string){
    if (string->length==MAX_SIZE-1){
        return OK;
    }else{
        return ERROR;
    }
}

//串的建立
int CreateString(SString *string){
    printf("Please enter a string:\n");
    scanf("%s",string->data);
    int i=0;
    while(string->data[i]!='\0'){
        string->length++;
        i++;
    }
    return OK;
}

//串的遍历输出
int PrintString(SString *string){
    if(EmptyString(string)){
        printf("The string is empty!!!");
        return ERROR;
    }
    else{
    for(int i=0;i<string->length;i++){
    printf("%c",string->data[i]);
    }
    return OK;}
}

//求串的字串
//求串S的第pos位置开始，长度为length的子串，并将其存入到串Sub中
int SubString(SString *string,SString *sub,int pos,int length){
    if(pos<1||pos>string->length||length<1||length>string->length-pos+1){
        return ERROR;
    }
    else{
        for(int i=0;i<length;i++){
            sub->data[i]=string->data[pos];
            pos++;
        }
        sub->length=length;
        return OK;
    }
}

//插入子串
//串S的第pos个位置进行插入，插入子串S1
int InsertString(SString *string1,SString *string2,int pos){
    if(pos>string1->length+1||string1->length+string2->length>MAX_SIZE){
        return ERROR;
    }
    //先将string1第pos后的元素都往后移，空出位置
    for(int i=0;i<string2->length;i++){
        string1->data[string1->length+string2->length-1-i]=string1->data[pos-1+i];
    }
    for(int n=0;n<string2->length;n++){
        string1->data[pos-1+n]=string2->data[n];
    }
    string1->length=string1->length+string2->length;
    string1->data[string1->length]='\0';
    return OK;
}

//删除字串
//串S的第pos个位置进行删除length长度的字串
int DeleteString(SString *string,int pos,int length){
    if(pos<1||pos>string->length-1||length<1){
        return ERROR;
    }
    //先删除
    for(int i=0;i<length;i++){
        string->data[pos-1+i]='\0';
    }
    //再将后面的字符往前填入
    for(int n=0;n<length;n++){
        string->data[pos-1+n]=string->data[pos+length-1+n];
        string->data[pos+length-1+n]='\0';
    }
    return OK;
}

int main(){
    SString S,S1;
    InitString(&S);
    InitString(&S1);
    CreateString(&S);
    CreateString(&S1);
    int pos;
    scanf("%d",&pos);
    InsertString(&S,&S1,pos);
    PrintString(&S);
    return 0;


}
