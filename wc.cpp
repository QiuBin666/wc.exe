#include <stdio.h>
#include <string.h> 
#include <stdlib.h>
#include <ctype.h> 
#include <io.h>
int a=0;
int b=0;
int c=0;
int main() { //������
    void CharCount(char filename[]);//�ַ���ͳ�ƺ��� 
	void WordCount(char filename[]);//������ͳ�ƺ���
	void LineCount(char filename[]);//����ͳ�ƺ���  
	int Extend(char filename[]);//��չ����ͳ�ƺ��� 
    char input[10], filename[32];
    while (1) {
        //����ָ��
        printf("wc.exe - c file.c      �����ļ����ַ���\nwc.exe - w file.c      �����ļ��Ĵʵ���Ŀ\nwc.exe - l file.c      �����ļ�������\nwc.exe - a file.c      ���ظ����ӵ����ݣ������� / ���� / ע���У�\nwc.exe - o file.c      �˳�\n������ָ�- ");
        scanf("%s",&input);
        
        switch(input[0]){
            case 'c':  //�ַ���
                printf("�������ļ�����");//�����ļ���
                scanf("%s", &filename);
				CharCount(filename);
                printf("�ļ����ַ���Ϊ��%d\n",a);
                break;
        
            case 'w':  //����                
                printf("�������ļ�����");//�����ļ���
                scanf("%s", &filename);
                WordCount(filename);
                printf("�ļ��Ĵ���Ϊ��%d\n", b);
                break;

            case 'l':  //����
                printf("�������ļ�����");//�����ļ���
                scanf("%s", &filename);           
                LineCount(filename);
                printf("�ļ�������Ϊ��%d\n", c);
                break;

            case 'a':    //���ظ����ӵ����ݣ������� / ���� / ע���У���
                printf("�������ļ�����");//�����ļ���
                scanf("%s", &filename);
                Extend(filename);
                break;
        
            case 'o':  //�˳�
                return 0;

            default:
                printf("�������ָ����������������");
                break;
        }

    }
    system("pause");
    return 0;
}
void CharCount(char filename[]){//�ַ���ͳ�ƺ��� 
    FILE *fp=NULL;
    fp=fopen(filename,"r");
    if(fp==NULL){
        printf("Ѱ���ļ�ʧ��\n");
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
void WordCount(char filename[]){//������ͳ�ƺ��� 
    FILE *fp = NULL;
    fp=fopen(filename,"r");
    if(fp==NULL){
        printf("Ѱ���ļ�ʧ��\n");
        exit(-1);
    }
    char fchar = 0;
    fchar = fgetc(fp);
    while (fchar != EOF)
    {
        if ((fchar >= 'a' && fchar <= 'z') || (fchar >= 'A' && fchar <= 'Z') )//������ĸ
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
void LineCount(char filename[]){//����ͳ�ƺ��� 
    FILE *fp = NULL;
    fp=fopen(filename,"r");
    if(fp==NULL){
        printf("Ѱ���ļ�ʧ��\n");
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
int Extend(char filename[]) {  //��չ���� 
    FILE *fp = NULL;
    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Ѱ���ļ�ʧ��\n");
        exit(-1);
    }

    char fchar = 0;
    int emptyline = 0, code = 0, note = 0;
    int l = 0, n = 0, c = 0;//lΪ�������ͣ�0�����ַ����У�1��1�ַ����У�nΪע�����ͣ�0Ϊ��ע���У�1Ϊ��ע���У�2Ϊ��ע����,cΪ��������

    while (fchar != EOF) {
        fchar = fgetc(fp);
            if (l == 0 || l == 1) {//�����ʼ�ǿո���Ʊ���ʼ�ж��ǲ��ǿ��л���ע���л��ߴ�����
                if (fchar == '\n') {//�س�֮ǰû���ַ�������;1�ַ������Ҳ��û�������ַ�
                    emptyline++;
                    l = 0;
                    continue;
                }
                else if (fchar == '/') {//ע���ж�
                    fchar = fgetc(fp);
                    if (fchar == '/') {//����ע��
                        n = 1;
                        while (fchar != EOF && fchar != '\n') {
                            fchar = fgetc(fp);
                        }
                        n = 0;
                        note++;
                        continue;
                    }
                    else if (fchar == '*') {//����ע��
                        n = 2;
                        continue;
                    }
                }
                else if( fchar == '}' && l == 0){
                    l = 1;        //һ�ַ�����
                    continue;
                }
                else if(fchar == ' ' || fchar == '\t'){
                    continue;
                }
                else {
                    c = 1;
                }
            }
            if (c == 1) {//������
                while (fchar != EOF && fchar != '\n') {
                    fchar = fgetc(fp);
                }
                l = 0;//״̬��ؿ���
                code++;
                continue;
            }
            if (n == 2) {//����ע��
                while (fchar != EOF && fchar != '*') {
                    while (fchar != EOF && fchar != '\n') {
                        fchar = fgetc(fp);
                    }
                    note++;
                    fchar = fgetc(fp);
                }
                fchar = fgetc(fp);
                if (fchar == '/') {//���н���
                    n = 0;
                }
                continue;
            }
    }
    printf("\n���п�����: %d  \n��������: %d  \nע������: %d\n", emptyline, code, note);
    fclose(fp);
}
































