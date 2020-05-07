#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
/*
 * Item: An item that is being pushed to or popped from the stack
 *       It may be float (to be used while evaluating the postfix)
 *       It may be char* (to be used while converting infix to postfix)
 */
typedef union
{
    float fData;
    char* cpData;
} Item;
/*
 *
 */
typedef struct
{
    Item stksize[100];
    int top;
} Stack;
/*
 *
 */
void init(Stack *s)
{
    s->top=-1;
}
/*
 *
 */
int isEmpty(Stack *s)
{
    if(s->top==-1)
        return 1;
    return 0;
}
/*
 *
 */
Item top(Stack *s)
{
    return s->stksize[s->top];
}
/*
 *
 */
Item pop(Stack *s)
{
    Item x;
    if(s->top==-1)
        printf("Stack is empty\n");
    else
    {
        x=s->stksize[s->top];
        s->top--;
       // printf("popped %c\n",x);
        return x;
    }
}
/*
 *
 */
void push(Stack *s, Item val)
{
    int count;
    if(s->top==99)
        printf("Stack is full");
    s->stksize[++s->top]=val;
    //printf("pushed %f\n",s->stksize[s->top].fData);
    count++;
}
/*
 *
 */
void destroy(Stack *s)
{
    while(s->top--!=-1)
        pop(&s);
}
/*
 * infixToPostfix: converts an expression in infix notation to
 *					to a postfix notation (Reverse-Polish Notation)
 *					ASSUME single-digit operands
 *					ASSUME ^*+-/ operators
 *					e.g., 2+3 --> 23+
 *					e.g., (2+3)*4 --> 23+4*
 */
void infixToPostfix(char* infix, char* postfix)
{

    Stack s;
    int i=0;
    int k=0;
    int z;
    Item x;
    Item val;
    init(&s);
    while(infix[i]!=NULL)
    {
        if(infix[i]!='^' && infix[i]!='+' && infix[i]!='-' && infix[i]!='/' && infix[i]!='*' && infix[i]!='(' && infix[i]!=')')
        {
            postfix[k]=infix[i];
            k++;
        }
        if(infix[i]=='^' || infix[i]=='+' || infix[i]=='-' || infix[i]=='/' || infix[i]=='*' || infix[i]=='(')
        {
            x=top(&s);
            if(infix[i]=='^')
            {
                if(infix[i]=='^' && x.cpData!='^')
                {
                    val.cpData=infix[i];
                    push(&s,val);
                    x=top(&s);
                }
                else if(infix[i]=='^' && x.cpData=='^')
                {
                    while(x.cpData=='^' && !isEmpty(&s))
                    {
                        val=pop(&s);
                        postfix[k]=val.cpData;
                         k++;
                        postfix[k]='   ';
                        k++;
                        x=top(&s);
                    }
                    postfix[k]='   ';
                    k++;
                    val.cpData=infix[i];
                    push(&s,val);
                }
            }
            if(infix[i]=='*' || infix[i]=='/')
            {
                if((infix[i]=='*' || infix[i]=='/') && (x.cpData!='*' && x.cpData!='/' && x.cpData!='^'))
                {
                    val.cpData=infix[i];
                    push(&s,val);
                    x=top(&s);
                }
                else if((infix[i]=='*' || infix[i]=='/') && (x.cpData=='*' || x.cpData=='/' || x.cpData=='^'))
                {
                    while((x.cpData=='*' || x.cpData=='^' || x.cpData=='/' )&& !isEmpty(&s))
                    {
                        val=pop(&s);
                        postfix[k]=val.cpData;
                        k++;
                        postfix[k]='   ';
                        k++;
                        x=top(&s);
                    }
                    postfix[k]='  ';
                    k++;
                    val.cpData=infix[i];
                    push(&s,val);
                }
            }
                if(infix[i]=='+' || infix[i]=='-')
                {
                    if((infix[i]=='+' || infix[i]=='-') && (x.cpData!='*' && x.cpData!='/' && x.cpData!='+' && x.cpData!='-' && x.cpData!='^'))
                    {
                        val.cpData=infix[i];
                        push(&s,val);
                        x=top(&s);
                    }
                    else if((infix[i]=='+' || infix[i]=='-')&&(x.cpData=='*' || x.cpData=='/' || x.cpData=='^' || x.cpData=='+' || x.cpData=='-'))
                    {
                        while((x.cpData=='*' || x.cpData=='^' || x.cpData=='/' || x.cpData=='-' || x.cpData=='+')&& !isEmpty(&s))
                        {
                            val=pop(&s);
                            postfix[k]=val.cpData;
                             k++;
                            postfix[k]='   ';
                            k++;
                            x=top(&s);
                        }
                        postfix[k]='   ';
                        k++;
                        val.cpData=infix[i];
                        push(&s,val);
                        postfix[k]='   ';
                        k++;
                    }
                }
                if(infix[i]=='(')
                {
                    val.cpData=infix[i];
                        push(&s,val);
                        x=top(&s);
                }
        }
        if(infix[i]==')')
        {
            while(!isEmpty(&s) && x.cpData!='(')
            {
                val=pop(&s);
                postfix[k]=val.cpData;
               k++;
               postfix[k]='   ';
                    k++;
                x=top(&s);
            }
            pop(&s);
        }
        i++;
    }
    while(!isEmpty(&s))
    {
        val=pop(&s);
        postfix[k]=val.cpData;
        k++;
        postfix[k]='   ';
        k++;
    }
destroy(&s);
}
/*
 * evaluatePostfix: Evaluates an expression in postfix notation
 *					 (Reverse-Polish Notation)
 *					ASSUME single-digit operands
 */
float evaluatePostfix(char* postfix)
{
Stack q;
init(&q);
Item c,c1,c2,f1;
int i=0;
float r,f,b;
float c11,c22;
char p;
char *token=strtok(postfix," ");
while(token!=NULL)
    {
if(strcmp(token,"+")!=0 && strcmp(token,"*")!=0 && strcmp(token,"-")!=0 && strcmp(token,"/")!=0 && strcmp(token,"^")!=0 )
{
    f=atof(token);
    c.fData=f;
    push(&q,c);
}
else
{
c1= pop(&q);
c11=c1.fData;
c2=pop(&q);
c22=c2.fData;
if(strcmp(token,"+")==0)
{
    r=c22+c11;
}
if(strcmp(token,"-")==0)
{
    r=c22-c11;
}
if(strcmp(token,"*")==0)
{
    r=c22*c11;
}
if(strcmp(token,"/")==0)
{
    r=c22/c11;
}
if(strcmp(token,"^")==0)
{
    r=pow(c22,c11);
}
f1.fData=r;
push(&q,f1);
}
token=strtok(NULL," ");
}

    return r;
}

/*
 *
 */
void replaceNewLineBySpace(char *s)
{
    char *s1 = s;
    while((s1 = strstr(s1, "\n")) != NULL)
        *s1 = ' ';
}
/*
 *
 */
int main(int argc, char**argv)
{
    char infixExpr[256] = "";
    char postfixExpr[256] = "";

    printf("Enter an expression you want to evaluate or Ctrl+Z to exit: ");
    while(fgets(infixExpr, 255, stdin) != NULL)
    {
        replaceNewLineBySpace(infixExpr);

        infixToPostfix(infixExpr, postfixExpr);
        printf("Postfix : %s\n", postfixExpr);
        float result = evaluatePostfix(postfixExpr);
        printf("Result: %f\n\n", result);
        printf("Enter an expression you want to evaluate or Ctrl+Z to exit: ");
    }
    return 0;
}
