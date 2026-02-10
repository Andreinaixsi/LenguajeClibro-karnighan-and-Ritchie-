/* Combined extended RPN calculator for exercises 4-3..4-11 */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

#define MAXVAL 100
#define MAXOP 100
#define NUMBER '0'

static int sp=0;
static double val[MAXVAL];

void push(double f){ if(sp<MAXVAL) val[sp++]=f; else fprintf(stderr,"full\n"); }
double pop(){ return (sp>0)? val[--sp]: (fprintf(stderr,"empty\n"),0); }

int getop(char s[]){
    int c; while((s[0]=c=getchar())==' '||c=='\t');
    s[1]=0;
    if(!isdigit(c) && c!='.' && !isalpha(c)) return c;
    int i=0;
    if(isalpha(c)){
        while(isalpha(c)){ s[i++]=c; c=getchar(); }
        s[i]=0;
        if(c!=EOF) ungetc(c,stdin);
        return 'A';
    }
    if(isdigit(c)) while(isdigit(s[++i]=c=getchar()));
    if(c=='.') while(isdigit(s[++i]=c=getchar()));
    s[i]=0;
    if(c!=EOF) ungetc(c,stdin);
    return NUMBER;
}

int main(){
    char s[MAXOP];
    double vars[26]={0}, last=0, op2;
    int type;
    while((type=getop(s))!=EOF){
        if(type==NUMBER) push(atof(s));
        else if(type=='A'){
            if(!strcmp(s,"sin")) push(sin(pop()));
            else if(!strcmp(s,"exp")) push(exp(pop()));
            else if(!strcmp(s,"pow")){ op2=pop(); push(pow(pop(),op2));}
            else if(strlen(s)==1 && s[0]>='a'&&s[0]<='z') push(vars[s[0]-'a']);
            else fprintf(stderr,"unk %s\n",s);
        } else switch(type){
            case '+': push(pop()+pop()); break;
            case '*': push(pop()*pop()); break;
            case '-': op2=pop(); push(pop()-op2); break;
            case '/': op2=pop(); if(op2) push(pop()/op2); else fprintf(stderr,"div0\n"); break;
            case '\n': last=pop(); printf("%g\n",last); break;
        }
    }
}