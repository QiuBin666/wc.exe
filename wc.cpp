#include <stdio.h>
#include <string.h> 
#include <stdlib.h>
#include <ctype.h> 
#include <io.h>
int a=0;
int b=0;
int c=0;
int main() { //主函数
    void CharCount(char filename[]);//字符数统计函数 
	void WordCount(char filename[]);//单词数统计函数
	void LineCount(char filename[]);//行数统计函数  
	int Extend(char filename[]);//扩展功能统计函数 
    char input[10], filename[32];
    while (1) {
        //输入指令
        printf("wc.exe - c file.c      返回文件的字符数\nwc.exe - w file.c      返回文件的词的数目\nwc.exe - l file.c      返回文件的行数\nwc.exe - a file.c      返回更复杂的数据（代码行 / 空行 / 注释行）\nwc.exe - o file.c      退出\n请输入指令：- ");
        scanf("%s",&input);
        
        switch(input[0]){
            case 'c':  //字符数
                printf("请输入文件名：");//输入文件名
                scanf("%s", &filename);
				CharCount(filename);
                printf("文件的字符数为：%d\n",a);
                break;
        
            case 'w':  //词数                
                printf("请输入文件名：");//输入文件名
                scanf("%s", &filename);
                WordCount(filename);
                printf("文件的词数为：%d\n", b);
                break;

            case 'l':  //行数
                printf("请输入文件名：");//输入文件名
                scanf("%s", &filename);           
                LineCount(filename);
                printf("文件的行数为：%d\n", c);
                break;

            case 'a':    //返回更复杂的数据（代码行 / 空行 / 注释行）。
                printf("请输入文件名：");//输入文件名
                scanf("%s", &filename);
                Extend(filename);
                break;
        
            case 'o':  //退出
                return 0;

            default:
                printf("你输入的指令有误！请重新输入");
                break;
        }

    }
    system("pause");
    return 0;
}
void CharCount(char filename[]){//字符数统计函数 
    FILE *fp=NULL;
    fp=fopen(filename,"r");
    if(fp==NULL){
        printf("寻找文件失败\n");
        exit(-1);
    }
    char ch;
    ch = fgetc(fp);
    while(ch!=EOF){
        if (ch != ' '&&ch != '\n'&&ch != '\t'&&ch != ','&&ch != '.'&&ch != '!'&&ch != ';'&&ch != '=');
		a++; 
	    ch = fgetc(fp);  
    }
    a--;
    fclose(fp);
}
void WordCount(char filename[]){//单词数统计函数 
    FILE *fp = NULL;
    fp=fopen(filename,"r");
    if(fp==NULL){
        printf("寻找文件失败\n");
        exit(-1);
    }
    char fchar = 0;
    fchar = fgetc(fp);
    while (fchar != EOF)
    {
        if ((fchar >= 'a' && fchar <= 'z') || (fchar >= 'A' && fchar <= 'Z') )//遇到字母
        {
            while ((fchar >= 'a' && fchar <= 'z') || (fchar >= 'A' && fchar <= 'Z'))
                fchar = fgetc(fp);
                b++;
                fchar = fgetc(fp);
        }
        else {
            fchar = fgetc(fp);
        }
    }
    fclose(fp);
  
}
void LineCount(char filename[]){//行数统计函数 
    FILE *fp = NULL;
    fp=fopen(filename,"r");
    if(fp==NULL){
        printf("寻找文件失败\n");
        exit(-1);
    }
    char ch;
    ch = fgetc(fp);
    while (ch != EOF)
    {
        if (ch == '\n' || ch == '\t')
            c++;
        ch = fgetc(fp);
    }
    fclose(fp);
}
int Extend(char filename[]) {  //扩展功能 
    FILE *fp = NULL;
    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("寻找文件失败\n");
        exit(-1);
    }

    char fchar = 0;
    int emptyline = 0, code = 0, note = 0;
    int l = 0, n = 0, c = 0;//l为空行类型，0是无字符空行，1是1字符空行；n为注释类型，0为非注释行，1为单注释行，2为多注释行,c为代码类型

    while (fchar != EOF) {
        fchar = fgetc(fp);
            if (l == 0 || l == 1) {//如果开始是空格或制表，开始判断是不是空行或者注释行或者代码行
                if (fchar == '\n') {//回车之前没有字符，空行;1字符进入后也是没有其他字符
                    emptyline++;
                    l = 0;
                    continue;
                }
                else if (fchar == '/') {//注释判断
                    fchar = fgetc(fp);
                    if (fchar == '/') {//单行注释
                        n = 1;
                        while (fchar != EOF && fchar != '\n') {
                            fchar = fgetc(fp);
                        }
                        n = 0;
                        note++;
                        continue;
                    }
                    else if (fchar == '*') {//多行注释
                        n = 2;
                        continue;
                    }
                }
                else if( fchar == '}' && l == 0){
                    l = 1;        //一字符空行
                    continue;
                }
                else if(fchar == ' ' || fchar == '\t'){
                    continue;
                }
                else {
                    c = 1;
                }
            }
            if (c == 1) {//代码行
                while (fchar != EOF && fchar != '\n') {
                    fchar = fgetc(fp);
                }
                l = 0;//状态变回空行
                code++;
                continue;
            }
            if (n == 2) {//多行注释
                while (fchar != EOF && fchar != '*') {
                    while (fchar != EOF && fchar != '\n') {
                        fchar = fgetc(fp);
                    }
                    note++;
                    fchar = fgetc(fp);
                }
                fchar = fgetc(fp);
                if (fchar == '/') {//多行结束
                    n = 0;
                }
                continue;
            }
    }
    printf("\n共有空行数: %d  \n代码行数: %d  \n注释行数: %d\n", emptyline, code, note);
    fclose(fp);
}
































