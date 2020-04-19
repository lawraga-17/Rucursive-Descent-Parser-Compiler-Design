#include <stdio.h>
#include<string.h>
#include<ctype.h>

/*

Roll No: IIT2017110
Syntax Analyser Assignment 
Compiler Design

The given code does Recursive Descent Parsing for examining strings(max lenth 100) of the grammar of arithmetic expressions involving + and *. That is, it will accept arithmetic expressions of the form  a+(b*c+d), v+b*(e+f), c+d*e while a+*b, (((a+b*c, +a*b are rejected...

The Grammar is:

S->TS'		First(S)= {( , id }
S'->+TS'/e		First(S'= { + , e }
T->FT'		First(T)= { ( , id }
T'->*FT'/e      First(S)= { * , e } (e==epsilon)
F->(S)/id       First(F)= { ( , id }

(isalnum() function used to check id) 

*5 production rules( Non Terminals)

*We have ensured this grammar is Left Factored and free from Left recursion.

*The algorithm used to construct this is:

->For each Non-Terminal node N, create a procedure parse_N(). Start off by calling the start symbol S's parse function parse_S()in main. 

-> The function parse_N will return 1 if it matches with the corresponding input stream of characters and 0 if it doesn't.

-> Here we have used Predictive Recursion Descent Parsing wherein a lookahead pointer of input string is maintained which is used to decide which production rule is to be applied whenever a Non-Terminal has more than one productions.

->The firsts of each Non-Terminal is pre-evaluated and is compared with the lookahead in the if else statements inside parse_N() to select which production rule is appllied.

->Each token of the rule(from RHS) is parsed one buy one by calling respective parse_N functions in case of Non terminals and by incrementing lookahead after comparing with terminal symbol in case of terminals.

->If no firsts are matched with the lookahead, then 0 is returned.

-> If Parse_S() returns 1 with lookahead=(length of input), then string is matched otherwise not.

*/



char input[100];		//input string


int parse_F();		//Non terminal functions
int parse_E();
int parse_Eprime();
int parse_T();
int parse_Tprime();

int l;			//lookahead variable

int parse_F()
{
	if(input[l]=='(')
	{
		int b,c;
				
		l++;
		
		b=parse_E();
		if(!b)return 0;
		
		if(input[l]==')')
		l++;
		else return 0;
		
		return 1;
	}
	else if(isalnum(input[l]))  //alphanmeric 
	{
			
		l++;
		
		return 1;
	}

	else return 0;
}

int parse_Eprime()
{
	if(input[l]=='+')
	{
		int b,c;
		
		l++;                // + parsed
				
		b=parse_T();
		if(!b)return 0;
		
		c=parse_Eprime();
		if(!c)return 0;
		
		return 1;
	}

	else return 1;

}

int parse_Tprime()
{
	if(input[l]=='*')
	{
		int b,c;
		
		l++; 				//parsed *
				
		b=parse_F();
		if(!b)return 0;
		
		c=parse_Tprime();
		if(!c)return 0;
		
		return 1;
	}

	else return 1;  			//Epsilon production
}

int parse_T()
{
	if(input[l]=='('||isalnum(input[l]))
	{
		int a,b;
		
		a=parse_F();
		if(!a)return 0;
		
		b=parse_Tprime();
		if(!b)return 0;
		
		return 1;
	}
	else return 0;
}

int parse_E()
{
	if(input[l]=='('||isalnum(input[l]))
	{
		int a,b;
		
		a=parse_T();
		if(!a)return 0;
		
		b=parse_Eprime();
		if(!b)return 0;
		
		return 1;
	}
	else return 0;
}

int main(void) {
	
    l=0;
    gets(input);
    if(parse_E()&& strlen(input)==l)
    {
    	printf("The entered input string is Accepted!\n");
    }
    else printf("The entered input string is Rejected!\n");
 
    return 0;
	
}
