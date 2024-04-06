#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STACK_SIZE 100

typedef int element;
typedef struct{
element data[MAX_STACK_SIZE];
int top;
}StackType;

void init_stack(StackType *s)
{
    s->top=-1;
}

int is_empty(StackType *s)
{
    return (s->top==-1);
}

int is_full(StackType *s)
{
    return (s->top==(MAX_STACK_SIZE - 1));
}

void push(StackType *s,element item)
{
    if(is_full(s)){
        fprintf(stderr,"스택 포화 에러\n");
        return;
    }
    else s->data[++(s->top)]=item;
}

element pop(StackType *s)
{
   if(is_empty(s)){
        fprintf(stderr,"스택 공백 에러\n");
        exit(1);
    }
    else return s->data[(s->top)--];
}

element peek(StackType *s)
{
   if(is_empty(s)){
        fprintf(stderr,"스택 공백 에러\n");
        exit(1);
    }
    else return s->data[(s->top)];
}

int eval(char exp[])    //(스택에는 숫자를 저장 )
{
    int op1,op2,value,i=0;
    int len=strlen(exp);
    char ch;
    StackType s;

    init_stack(&s);   //스택 초기화
    for(i=0;i<len;i++){
        ch=exp[i];           //입력한 수식
        if(isdigit(ch)){   //입력한 수식이 숫자일경우
            value=ch-'0';  //아스키코드 0을 빼 문자형을 숫자형으로 바꿈
            push(&s,value);//스택에 숫자를 저장
        }
        else{
            op2=pop(&s);  //연산자일 경우
            op1=pop(&s);   //op2,1에 스택 상위의 숫자 2개를 저장
            switch(ch){
            case '+':push(&s,op1+op2);break;  //덧셈
            case '-':push(&s,op1-op2);break;
            case '*':push(&s,op1*op2);break;
            case '/':push(&s,op1/op2);break;
            }
        }
    }
    return pop(&s); //마지막남은 스택==결과
}
int main()
{
    int result;
    char s[MAX_STACK_SIZE];
    printf("수식입력 :");
    scanf("%[^\n]s",s); //공백포함하여 문자열 저장방법
    result=eval(s);
    printf("연산결과==> %d\n",result);
    return 0;
}
