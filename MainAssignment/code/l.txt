%{

# include<iostream>
# include "classes.h"
# include "main.tab.h"

using namespace std;

%}

%%

"case"			{
					return CASE;
				}

"switch"		{
					return SWITCH;
				}

":"				{
					return ':';
				}
				
"int"			{ 
					yylval.s=new char[strlen(yytext)+1];
					for(int i=0;i<strlen(yytext);i++)
					yylval.s[i]=yytext[i];

					yylval.s[strlen(yytext)]='\0'; ;cout<<"Came int\n";
					return DT;
				}

[","";""("")""{""}"]	{ 

							yylval.s=new char[strlen(yytext)+1];
							for(int i=0;i<strlen(yytext);i++)
							yylval.s[i]=yytext[i];

							yylval.s[strlen(yytext)]='\0'; ; cout<<"Came separator "<<yytext<<endl; 
							return yytext[0];
							
						}

"="						{	 
							yylval.s=new char[strlen(yytext)+1];
							for(int i=0;i<strlen(yytext);i++)
							yylval.s[i]=yytext[i];

							yylval.s[strlen(yytext)]='\0'; ; cout<<"Came assignment "<<endl;
							return yytext[0];
							
						}

"*="					{ 
							yylval.s=new char[strlen(yytext)+1];
							for(int i=0;i<strlen(yytext);i++)
							yylval.s[i]=yytext[i];

							yylval.s[strlen(yytext)]='\0'; ; cout<<"Came MULA\n";
							return MULA;
							
						}

"/="					{
							 yylval.s=new char[strlen(yytext)+1];
							for(int i=0;i<strlen(yytext);i++)
							yylval.s[i]=yytext[i];

							yylval.s[strlen(yytext)]='\0'; ; cout<<"Came DIVA\n";
							return DIVA;
							
						}

"+="					{ 

							yylval.s=new char[strlen(yytext)+1];
							for(int i=0;i<strlen(yytext);i++)
							yylval.s[i]=yytext[i];

							yylval.s[strlen(yytext)]='\0'; ; cout<<"Came ADDA\n";
							return ADDA;
							
						}

"-="					{ 

							yylval.s=new char[strlen(yytext)+1];
							for(int i=0;i<strlen(yytext);i++)
							yylval.s[i]=yytext[i];

							yylval.s[strlen(yytext)]='\0'; ; cout<<"Came SUBA\n";
							
							return SUBA;
							
						}

"input()" 				{
							yylval.s=new char[strlen(yytext)+1];
							for(int i=0;i<strlen(yytext);i++)
							yylval.s[i]=yytext[i];

							yylval.s[strlen(yytext)]='\0'; ; cout<<"Came input statement\n";
							return INPUT;
							
						}

"output"				{
							yylval.s=new char[strlen(yytext)+1];
							for(int i=0;i<strlen(yytext);i++)
							yylval.s[i]=yytext[i];

							yylval.s[strlen(yytext)]='\0'; ; cout<<"Came output statement\n";
							return OUTPUT;
							
						}

"bool"					{

							yylval.s=new char[strlen(yytext)+1];
							for(int i=0;i<strlen(yytext);i++)
							yylval.s[i]=yytext[i];

							yylval.s[strlen(yytext)]='\0'; ; cout<<"Came bool\n";
							return DT;
							
						}

"true"					{
							yylval.s=new char[strlen(yytext)+1];
							for(int i=0;i<strlen(yytext);i++)
							yylval.s[i]=yytext[i];

							yylval.s[strlen(yytext)]='\0'; ; cout<<"Came true\n";
							return TR;
							
						}

"false"					{
							yylval.s=new char[strlen(yytext)+1];
							for(int i=0;i<strlen(yytext);i++)
							yylval.s[i]=yytext[i];

							yylval.s[strlen(yytext)]='\0'; ; cout<<"Came false\n";
							return FL;
						}

"if"					{
							yylval.s=new char[strlen(yytext)+1];
							for(int i=0;i<strlen(yytext);i++)
							yylval.s[i]=yytext[i];

							yylval.s[strlen(yytext)]='\0'; ; cout<<"Came if\n";
							return IF;
							
						}

"else"					{
							yylval.s=new char[strlen(yytext)+1];
							for(int i=0;i<strlen(yytext);i++)
							yylval.s[i]=yytext[i];

							yylval.s[strlen(yytext)]='\0'; ; cout<<"Came else\n";
							return ELSE;
							
						}

"while"					{
							yylval.s=new char[strlen(yytext)+1];
							for(int i=0;i<strlen(yytext);i++)
							yylval.s[i]=yytext[i];

							yylval.s[strlen(yytext)]='\0'; ; cout<<"Came while\n";
							return WHILE;
						}

"break"					{
							yylval.s=new char[strlen(yytext)+1];
							for(int i=0;i<strlen(yytext);i++)
							yylval.s[i]=yytext[i];

							yylval.s[strlen(yytext)]='\0'; ; cout<<"Came break\n";
							return BREAK;
							
						}

"return"				{
							yylval.s=new char[strlen(yytext)+1];
							for(int i=0;i<strlen(yytext);i++)
							yylval.s[i]=yytext[i];

							yylval.s[strlen(yytext)]='\0'; ; cout<<"Came return\n";
							return RETURN;
						}

[0-9]+					{ 

							yylval.e=new expression();

							yylval.e->isterminal=1;
							yylval.e->cexpression1=NULL;
							yylval.e->cexpression2=NULL;

							yylval.e->evaluatedto=new char[strlen(yytext)+1];
							for(int i=0;i<strlen(yytext);i++)
							yylval.e->evaluatedto[i]=yytext[i];

							yylval.e->evaluatedto[strlen(yytext)]='\0'; 

							cout<<"Came number\n";return NUMBER;
							
						}

"<"						{ 
							yylval.e=new expression();

							yylval.e->isterminal=1;
							yylval.e->cexpression1=NULL;
							yylval.e->cexpression2=NULL;

							yylval.e->evaluatedto=new char[strlen(yytext)+1];
							for(int i=0;i<strlen(yytext);i++)
							yylval.e->evaluatedto[i]=yytext[i];

							yylval.e->evaluatedto[strlen(yytext)]='\0'; 
							return RELOP;
						}

"<="					{

							yylval.e=new expression();

							yylval.e->isterminal=1;
							yylval.e->cexpression1=NULL;
							yylval.e->cexpression2=NULL;

							yylval.e->evaluatedto=new char[strlen(yytext)+1];
							for(int i=0;i<strlen(yytext);i++)
							yylval.e->evaluatedto[i]=yytext[i];

							yylval.e->evaluatedto[strlen(yytext)]='\0'; 
							return RELOP;
							
						}

">"						{
							yylval.e=new expression();

							yylval.e->isterminal=1;
							yylval.e->cexpression1=NULL;
							yylval.e->cexpression2=NULL;

							yylval.e->evaluatedto=new char[strlen(yytext)+1];
							for(int i=0;i<strlen(yytext);i++)
							yylval.e->evaluatedto[i]=yytext[i];

							yylval.e->evaluatedto[strlen(yytext)]='\0'; 
							return RELOP;
							
						}

">="					{

							yylval.e=new expression();

							yylval.e->isterminal=1;
							yylval.e->cexpression1=NULL;
							yylval.e->cexpression2=NULL;

							yylval.e->evaluatedto=new char[strlen(yytext)+1];
							for(int i=0;i<strlen(yytext);i++)
							yylval.e->evaluatedto[i]=yytext[i];

							yylval.e->evaluatedto[strlen(yytext)]='\0';
							return RELOP;
							
						}

"=="					{
							yylval.e=new expression();

							yylval.e->isterminal=1;
							yylval.e->cexpression1=NULL;
							yylval.e->cexpression2=NULL;

							yylval.e->evaluatedto=new char[strlen(yytext)+1];
							for(int i=0;i<strlen(yytext);i++)
							yylval.e->evaluatedto[i]=yytext[i];

							yylval.e->evaluatedto[strlen(yytext)]='\0';
							return RELOP;
						}

"!="					{ 
							yylval.e=new expression();

							yylval.e->isterminal=1;
							yylval.e->cexpression1=NULL;
							yylval.e->cexpression2=NULL;

							yylval.e->evaluatedto=new char[strlen(yytext)+1];
							for(int i=0;i<strlen(yytext);i++)
							yylval.e->evaluatedto[i]=yytext[i];

							yylval.e->evaluatedto[strlen(yytext)]='\0';
							return RELOP;
						}

"&&"					{ 
							yylval.e=new expression();

							yylval.e->isterminal=1;
							yylval.e->cexpression1=NULL;
							yylval.e->cexpression2=NULL;

							yylval.e->evaluatedto=new char[strlen(yytext)+1];
							for(int i=0;i<strlen(yytext);i++)
							yylval.e->evaluatedto[i]=yytext[i];

							yylval.e->evaluatedto[strlen(yytext)]='\0'; 

							
							return LOGOP;
							
						}

"||"					{ 
							yylval.e=new expression();

							yylval.e->isterminal=1;
							yylval.e->cexpression1=NULL;
							yylval.e->cexpression2=NULL;

							yylval.e->evaluatedto=new char[strlen(yytext)+1];
							for(int i=0;i<strlen(yytext);i++)
							yylval.e->evaluatedto[i]=yytext[i];

							yylval.e->evaluatedto[strlen(yytext)]='\0'; 

							cout<<"Came ||\n";
							return LOGOP;
						}

"+"						{ 
							yylval.s=new char[strlen(yytext)+1];
							for(int i=0;i<strlen(yytext);i++)
							yylval.s[i]=yytext[i];

							yylval.s[strlen(yytext)]='\0'; ; cout<<"Came +\n";
							return '+';
							
						}

"-"						{	
							yylval.s=new char[strlen(yytext)+1];
							for(int i=0;i<strlen(yytext);i++)
							yylval.s[i]=yytext[i];

							yylval.s[strlen(yytext)]='\0'; ; cout<<"Came -\n";
							return '-';
						}

"/"					{
							yylval.s=new char[strlen(yytext)+1];
							for(int i=0;i<strlen(yytext);i++)
							yylval.s[i]=yytext[i];

							yylval.s[strlen(yytext)]='\0'; ; cout<<"Came /\n";
							return '/';
						}

"*"						{
							yylval.s=new char[strlen(yytext)+1];
							for(int i=0;i<strlen(yytext);i++)
							yylval.s[i]=yytext[i];

							yylval.s[strlen(yytext)]='\0'; ; cout<<"Came *\n";
							return '*';
							
						}

"&"						{
							yylval.s=new char[strlen(yytext)+1];
							for(int i=0;i<strlen(yytext);i++)
							yylval.s[i]=yytext[i];

							yylval.s[strlen(yytext)]='\0'; ; cout<<"Came &\n";
							return '&';
						}

"|"					{ 
							yylval.s=new char[strlen(yytext)+1];
							for(int i=0;i<strlen(yytext);i++)
							yylval.s[i]=yytext[i];

							yylval.s[strlen(yytext)]='\0'; ; cout<<"Came |\n";
							return '|';
						}

"^"						{ 

							yylval.s=new char[strlen(yytext)+1];
							for(int i=0;i<strlen(yytext);i++)
							yylval.s[i]=yytext[i];

							yylval.s[strlen(yytext)]='\0'; ; cout<<"Came ^\n";
							return '^';
							
						}

"@"						{
							yylval.s=new char[strlen(yytext)+1];
							for(int i=0;i<strlen(yytext);i++)
							yylval.s[i]=yytext[i];

							yylval.s[strlen(yytext)]='\0'; ; cout<<"Came @\n";
							return '@';
						}

"~"						{

							yylval.s=new char[strlen(yytext)+1];
							for(int i=0;i<strlen(yytext);i++)
							yylval.s[i]=yytext[i];

							yylval.s[strlen(yytext)]='\0'; ; cout<<"Came ~\n";
							return '~';
						}

"\!"					{
							yylval.s=new char[strlen(yytext)+1];
							for(int i=0;i<strlen(yytext);i++)
							yylval.s[i]=yytext[i];

							yylval.s[strlen(yytext)]='\0'; ; cout<<"Came !\n";
							return NOT;
							
						}

"%"						{

							yylval.s=new char[strlen(yytext)+1];
							for(int i=0;i<strlen(yytext);i++)
							yylval.s[i]=yytext[i];

							yylval.s[strlen(yytext)]='\0'; ; cout<<"Came %\n";
							return '%';
						}

"\""[A-Za-z0-9\\ =\*^&%$#@!,.;:]*"\""	{ 

											yylval.e=new expression();

											yylval.e->isterminal=1;
											yylval.e->cexpression1=NULL;
											yylval.e->cexpression2=NULL;

											yylval.e->evaluatedto=new char[strlen(yytext)+1];
											for(int i=0;i<strlen(yytext);i++)
											yylval.e->evaluatedto[i]=yytext[i];

											yylval.e->evaluatedto[strlen(yytext)]='\0'; 

											cout<<"Came STRING"<<yytext<<endl;
											
											return STRING;

										}

[A-Za-z_][A-Za-z_0-9]*					{	
											yylval.e=new expression();

											yylval.e->isterminal=1;
											yylval.e->cexpression1=NULL;
											yylval.e->cexpression2=NULL;

											yylval.e->evaluatedto=new char[strlen(yytext)+1];
											for(int i=0;i<strlen(yytext);i++)
											yylval.e->evaluatedto[i]=yytext[i];

											yylval.e->evaluatedto[strlen(yytext)]='\0'; 

											cout<<"Came ID "<<yytext<<endl;
											
											return ID;
											
										}

"%%"		cout<<"Came EOF\n";return EF;

[ \t\n]+	{}

.		{ cout<<yytext<<" &&\n";;}

%%

