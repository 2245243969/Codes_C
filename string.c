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
} SString;

//串的初始化
void InitString(SString *string) {
    string->length = 0;
}

//判断串是否为空
int EmptyString(SString *string) {
    if (string->length == 0) {
        return OK;
    } else { return ERROR; }
}

//判断串是否为满
int FullString(SString *string) {
    if (string->length == MAX_SIZE - 1) {
        return OK;
    } else {
        return ERROR;
    }
}

//串的建立
int CreateString(SString *string) {
    printf("Please enter a string:\n");
    scanf("%s", &string->data[1]);
    int i = 1;
    while (string->data[i] != '\0') {
        string->length++;
        i++;
    }
    return OK;
}

//串的遍历输出
int PrintString(SString *string) {
    if (EmptyString(string)) {
        printf("The string is empty!!!");
        return ERROR;
    } else {
        for (int i = 1; i <= string->length; i++) {
            printf("%c", string->data[i]);
        }
        return OK;
    }
}

//求串的字串
//求串S的第pos位置开始，长度为length的子串，并将其存入到串Sub中
int SubString(SString *string, SString *sub, int pos, int length) {
    if (pos < 1 || pos > string->length || length < 1 || length > string->length - pos + 1) {
        return ERROR;
    } else {
        for (int i = 1; i <= length; i++) {
            sub->data[i] = string->data[pos];
            pos++;
        }
        sub->length = length;
        return OK;
    }
}

//插入子串
//串S的第pos个位置进行插入，插入子串S1
int InsertString(SString *string1, SString *string2, int pos) {
    if (pos > string1->length + 1 || string1->length + string2->length > MAX_SIZE) {
        return ERROR;
    }
    //先将string1第pos后的元素都往后移，空出位置
    for (int i = 1; i <= string2->length; i++) {
        string1->data[pos + string2->length + i - 1] = string1->data[pos + i - 1];
    }
    for (int n = 1; n <= string2->length; n++) {
        string1->data[pos + n - 1] = string2->data[n];
    }
    string1->length = string1->length + string2->length;
    string1->data[string1->length + 1] = '\0';
    return OK;
}

//删除字串
//串S的第pos个位置进行删除length长度的字串
int DeleteString(SString *string, int pos, int length) {
    if (pos < 1 || pos > string->length || length < 1) {
        return ERROR;
    }
    //先删除
    for (int i = 0; i < length; i++) {
        string->data[pos + i] = '\0';
    }
    //再将后面的字符往前填入
    for (int n = 0; n < string->length - pos - length + 1; n++) {
        string->data[pos + n] = string->data[pos + length + n];
        string->data[pos + length + n] = '\0';
    }
    return OK;
}

//KMP算法
//即从一个字符串中找出所给的特定字串
//规律：1.next[j]的值每次最多增加1  2.模式串的最后一位字符不影响next数组的结果
//next[j]里面所装的值为第j-1位字符组成的字串的前后缀重复字符数加一
int Get_next(SString *string2, int *next) {
    if (EmptyString(string2)) {
        return ERROR;
    }
    int i = 1;
    int j = 0;
    next[1] = 0;//第一个字符的next值0
    while (i <= string2->length) {
        if (j == 0 || string2->data[i] == string2->data[j]) {
            i++;
            j++;
            next[i] = j;
        } else {
            j = next[j];//当ch[i]==ch[j]条件不成立时，ch[i接着会跟ch[next[j]]进行比较，以此类推
        }
    }
}

//KMP搜索算法
int KMPSearch(SString *string1, SString *string2) {
    if (EmptyString(string1) || EmptyString(string2) || string2->length > string1->length) {
        return ERROR;
    }
    int next[string2->length + 1];
    Get_next(&string2, next);
    int i = 1;//索引用于string1,即文本串
    int j = 1;//索引用于string2，即模式串
    int found = 0;//用found来标记是否能找到对应的子串
    while (i <= string1->length) {
        if (string2->data[j] == string1->data[i] || j == 0) {
            i++;
            j++;
        } else {
            j = next[j];//如果s2[j]不等于s1[i],j回溯
        }
        if (j > string2->length) {
            printf("Pattern found at index %d\n", i - j);
            j = next[j - 1]+1;//所有的形式的模式串都可以用这个推出来！！！可以自己再试试abcaabc,aaab,aaaa重新再推一遍
        }
    }
}

int main() {
    SString S, S1;
    InitString(&S1);
    InitString(&S);
    CreateString(&S);
    CreateString(&S1);
    KMPSearch(&S, &S1);
    return 0;
}
