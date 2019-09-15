%{
# include<iostream>
# include<fstream>
# include<cstring>
# include "classes.h"
# include "header.h"
using namespace std;

int yylex();
void yyerror(const char*);

string finalcode="";
string expressioncode="";
string statementcode="";


%}


%union
{
	char* s;
	int a;
	value* v;
	expression* e;
	functioncall* fc;
	multiargument* m;
	statement* st;
	output* o;
	declaration* d;
	multistatement* ms;
	block* b;
	boolvalue* bv;
	conditionalt* c;
	loop * l;
	parameter* p;
	function* f;
	component* cp;
	switches* sw;
	multicases* cs;
	barefunctioncall* bf;
}


%token  EF DT TR FL IF ELSE WHILE RELOP LOGOP ID NUMBER NOT INPUT OUTPUT MOD STRING BREAK RETURN
%token  MULA ADDA DIVA SUBA SWITCH CASE

%left  '|' '^' '&' '~'
%left  '+' '-'
%left  '*' '/' 
%left '%'
%right  '@'

%type <s>  EF DT TR FL IF ELSE WHILE  NOT INPUT OUTPUT MOD  BREAK RETURN
%type <s> MULA ADDA DIVA SUBA 

%type <s> '|' '^' '&' '~'
%type <s> '+' '-'
%type <s> '*' '/' 
%type <s>'%'
%type <s> '@'
%type <s> '=' ';' "(" ")" ","

%type <cp> program component
%type <f> function
%type <fc> functioncall
%type <p> parameter multiparameter
%type <e> expression ID NUMBER STRING LOGOP RELOP
%type <st> statement
%type <d> declaration init_decl un_init_decl
%type <c> conditional
%type <l> loop
%type <o> output
%type <m> multiargument printable argument
%type <ms> multistatement
%type <b> block
%type <v> value getvalue
%type <bv> boolexpression boolstmt boolean
%type <sw> switch
%type <cs> cases

%%

program:component EF	{
							cout<<"Program detected successfully\n";
							
							cout<<"*************************************************************\n";
							cout<<"SECTION-II\n-------------------------------------------->\n";
							$1->generatecode();
							
						}

//--------------------------------------------------------------------------------------------------

component:		{
					$$=new component();
					
				}
|function component 	{	
							cout<<"Function detected1 successfully\n";
							$$=new component();
							
							$$->parts.push_back($1);
							
							for(int i=0;i<$2->parts.size();i++)
							$$->parts.push_back($2->parts[i]);
							
							cout<<"Function componenet generated successfully\n";							
						}
|declaration component 	{
							cout<<"Declaration detected successfully\n";
							$$=new component();
							
							$$->parts.push_back($1);
							
							$1->evaluatestatement();
							
							for(int i=0;i<$2->parts.size();i++)
							$$->parts.push_back($2->parts[i]);
							
							cout<<"Declaration code generated successfully\n";
							
						}
;

//--------------------------------------------------------------------------------------------------


parameter:						{
									cout<<"No parameter detected successfully\n";
									
									$$=new parameter;
								}
								
|multiparameter					{
									cout<<"Function parameter detected succesfully\n";
									
								}
;

//--------------------------------------------------------------------------------------------------


multiparameter:multiparameter ',' DT ID	{

											cout<<"Multiparameter detected successfully\n";
											
											$$=new parameter;
											
											for(int i=0;i<$1->parameters.size();i++)
											$$->parameters.push_back($1->parameters[i]);
											
											$$->parameters.push_back($4->evaluatedto);
									
										}
|DT ID		{	
				cout<<"One parameter detected successfully\n";
				
				$$=new parameter;
				
				$$->parameters.push_back($2->evaluatedto);
				
			}
;

//--------------------------------------------------------------------------------------------------


function:DT ID '(' parameter ')' block	{
							
							cout<<"function detected successfully\n";
							
							$$=new function();
							
							$$->name=$2->evaluatedto;
							$$->p=$4;
							$$->b=$6;
							
							if($6!=NULL)
							$$->end=$6->end;
							
							cout<<"Function code generated successfully\n";
							}
;

//--------------------------------------------------------------------------------------------------

expression:expression '+' expression{
										cout<<"ADD parameter detected successfully\n";
										
										$$=createexpression('+',$1,$3);
									}
|expression '-' expression	{
								cout<<"SUB parameter detected successfully\n";
								$$=createexpression('-',$1,$3);
							}
							
|expression '/' expression	{

								cout<<"DIV parameter detected successfully\n";
								$$=createexpression('/',$1,$3);
								
							}
							
|expression '*' expression	{	
								cout<<"MUL parameter detected successfully\n";
								$$=createexpression('*',$1,$3);
							}
							
|expression '|' expression	{

								cout<<"OR parameter detected successfully\n";
								$$=createexpression('|',$1,$3);
								
							}
							
|expression '&' expression	{

								cout<<"AND parameter detected successfully\n";
								$$=createexpression('&',$1,$3);
								
							}
							
|expression '^' expression	{

								cout<<"XOR parameter detected successfully\n";
								$$=createexpression('^',$1,$3);
								
							}
							
|expression '@' expression	{

								cout<<"EXP detected successfully\n";
								$$=createexpression('@',$1,$3);
								
							}
							
|expression '~' expression	{
								cout<<"Not detected successfully\n";

								$$=createexpression('~',$1,$3);
							}
							
|expression '%' expression	{	

								cout<<"MOD detecte	d successfully\n";
								
								$$=createexpression('%',$1,$3);
								
							}
								
|NUMBER						{
								cout<<"Number detected successfully "<<$$<<endl;
							}
							
|ID							{
								$$->getcode();
								cout<<"ID detected successfully "<<$$<<endl;
							}
;

//--------------------------------------------------------------------------------------------------

statement:declaration 		{
								cout<<"Declaration detected successfully\n";
								$$=$1;
								
								
							}
							
|conditional				{
								cout<<"Conditional detected successfully\n";
								$$->start=getchararray(getnextlabel());
								$$->end=getchararray(getnextlabel());
							}
							
|loop						{
								cout<<"Loop detected succesfully\n";
								$$->start=getchararray(getnextlabel());
								$$->end=getchararray(getnextlabel());
							}
							
|RETURN ';'					{
								creturn *r=new creturn(); 
								r->returnvalue=NULL; $$=r;
								$$->start=getchararray(getnextlabel());
								$$->end=getchararray(getnextlabel());
							}
							
|RETURN expression ';'				{

										creturn *r=new creturn();
										r->returnvalue=$2->evaluatedto;
										$$=r;
										$$->start=getchararray(getnextlabel());
										$$->end=getchararray(getnextlabel());
									}
									
|output						{
								cout<<"Output statement detected\n";
								$$->start=getchararray(getnextlabel());
								$$->end=getchararray(getnextlabel());
							}

|init_decl				{
							cout<<"Assignment statement encountered\n";
							$$->start=getchararray(getnextlabel());
							$$->end=getchararray(getnextlabel());
						}
						
						
|switch					{

							cout<<"Switch statement encountered\n";
							$$->start=getchararray(getnextlabel());
			
						}
						
|functioncall ';'		{
							barefunctioncall* b=new barefunctioncall();
							b->v=$1;
							$$=b;
							$$->start=getchararray(getnextlabel());
							$$->end=getchararray(getnextlabel());
						}
						
;

//--------------------------------------------------------------------------------------------------

switch:SWITCH '(' value ')' '{' cases '}'	{		
												cout<<"switch identified\n";
												
												$$=new switches();
												$$->v=$3;
												$$->c=$6;
												
												$$->end=$6->m[$6->m.size()-1]->end;
												
												cout<<"SWITCH statement code generated\n";
											}

cases:		{
				$$=new multicases;
				$$->start=getchararray(getnextlabel());
				$$->end=getchararray(getnextlabel());
				cout<<"Empty case identified\n";

				cout<<$$->start<<" "<<$$->end<<endl;
			}
			
|CASE NUMBER ':' multistatement BREAK ';' cases	{
													cout<<"Case with break identified\n";
													
													$$=new multicases;
													cases *i=new cases();
													i->v=$2;
													i->m=$4;
													i->hasbreak=1;
													i->start=getchararray(getnextlabel());
													i->end=getchararray(getnextlabel());
													int k=0;
													
													$$->m.push_back(i);
												
													for(int i=0;i<$7->m.size();i++)
													$$->m.push_back($7->m[i]);
													
													cout<<"case with break code generated\n";
												}
												
|CASE NUMBER ':' multistatement cases	{
											cout<<"Case without break identified\n";
											
											$$=new multicases;
											
											cases *i=new cases();
											i->v=$2;
											i->m=$4;
											i->start=getchararray(getnextlabel());
											i->end=getchararray(getnextlabel());
											
											
											$$->start=i->start;
											$$->end=i->end;
											
											cout<<$$->start<<" "<<$$->end<<endl;
											
											$$->m.push_back(i);
											
											for(int i=0;i<$5->m.size();i++)
											$$->m.push_back($5->m[i]);
										}
;

//--------------------------------------------------------------------------------------------------

output:OUTPUT'('printable')'';'	{	
									cout<<"Output to be printed\n";
									$$=new output();
									$$->m=$3;
											
								}

;

//--------------------------------------------------------------------------------------------------

printable:multiargument	{
							cout<<"Multiple arguments to be printed\n";	
						}
						
|STRING					{
							$$=new multiargument;
							$$->subargument.push_back($1);
								
						}
;

//--------------------------------------------------------------------------------------------------

multistatement:		{	
						$$=new multistatement;

						cout<<"No statement detected successfully\n";
					}
|statement multistatement	{
								cout<<"Multistatement detected successfully\n";
	
								
								$$=new multistatement;
								
								if($1!=NULL);
								$$->constituents.push_back($1);
								
								if($2!=NULL && $2->constituents.size()!=0)
								{
									
									int flag=0;
									
									for(int i=0;i<$2->constituents.size();i++)
									{
										if($1!=NULL && $2->constituents[i]!=NULL && !flag)
										{
											$2->constituents[i]->start=$1->end;
											flag=1;
										}
										
										$$->constituents.push_back($2->constituents[i]);
									}
								}
								
								
							}
;

//--------------------------------------------------------------------------------------------------

block:'{' multistatement '}'	{

									$$=new block();
									$$->start=getchararray(getnextlabel());
									$$->end=getchararray(getnextlabel());

									$$->m=$2;

									cout<<"Block detected successfully\n";


								}
;

//--------------------------------------------------------------------------------------------------

declaration:un_init_decl	{
								cout<<"Uninitialized detected successfully\n";
							}
							
|DT init_decl				{
								cout<<"Initialized detected successfully\n";$$=$2;
								$$->start=getchararray(getnextlabel());
								$$->end=getchararray(getnextlabel());
							}
;

//--------------------------------------------------------------------------------------------------

un_init_decl:DT ID ';'		{	$$=new declaration();
								$$->start=getchararray(getnextlabel());
								$$->end=getchararray(getnextlabel());
								cout<<"Uninitialized detected successfully\n";
								
							}
;

//--------------------------------------------------------------------------------------------------

init_decl:  ID '=' getvalue ';'	{cout<<"Normal initialized detected successfully\n";
								
								$$=new declaration();
								$$->id=$1->evaluatedto;
								$$->rhs=$3;
								
								}
								
| ID MULA getvalue ';'		{

								cout<<"MUL initialized detected successfully\n";

								$$=new declaration;
								$$->id=$1->evaluatedto;

								$$->rhs=createexpression('*',(expression*)$1,(expression*)$3);

							}
							
| ID DIVA getvalue ';'		{
								cout<<"DIV initialized detected successfully\n";

								$$=new declaration;
								$$->id=$1->evaluatedto;

								$$->rhs=createexpression('/',(expression*)$1,(expression*)$3);

							}
							
| ID ADDA getvalue ';'		{
								cout<<"ADD initialized detected successfully\n";

								$$=new declaration;
								$$->id=$1->evaluatedto;

								$$->rhs=createexpression('+',(expression*)$1,(expression*)$3);

							}
							
| ID SUBA getvalue ';'		{
								cout<<"SUB initialized detected successfully\n";

								$$=new declaration;
								$$->id=$1->evaluatedto;

								$$->rhs=createexpression('-',(expression*)$1,(expression*)$3);

	
							}
;

//--------------------------------------------------------------------------------------------------

getvalue:INPUT					{
									cout<<"Input detected successfully\n";
									$$=new value();
									$$->evaluatedto="input\0";
									
								}
								
|value							{
									cout<<"Other value has been requested\n";
								}
;

//--------------------------------------------------------------------------------------------------

value:boolean					{
									cout<<"Boolean detected successfully\n";
									$$=new value();
									$$->evaluatedto=$1->evaluatedto;
								}

|functioncall					{
									$$=$1;
									$$->evaluatedto="Return Value\n";
									cout<<"Function call detected successfully\n";
								}
								
|expression						{	
									$$=$1;
									$1->getcode();
									cout<<"Expression detected successfully\n";
									
								}
;


boolean:TR						{	
									$$=new boolvalue();
									$$->evaluatedto="true\0";
									cout<<"True detected successfully\n";
								}
|FL								{	
									$$=new boolvalue();
									$$->evaluatedto="false\0";
									cout<<"False detected successfully\n";
								}
;

//--------------------------------------------------------------------------------------------------

functioncall: ID '(' argument ')'	{	
										cout<<"Function call 2 detected successfully\n";
										
										$$=new functioncall();
										$$->functionname=$1->evaluatedto;
										$$->arguments=$3->subargument;
										
										cout<<"Function call code generated\n";
									}
;

argument:			{	
						$$=new multiargument;
						statementcode+="result=returnvalue\n";
						cout<<"No argument detected successfully\n";
					}
					
|multiargument		{	
						cout<<"Multiargument detected successfully\n";
					}
;

//--------------------------------------------------------------------------------------------------

multiargument:value			{	
								cout<<"ID detected successfully\n";
								
								$$=new multiargument;
								
								$$->subargument.push_back($1);
								
								cout<<"Only value for multiargument detected\n";
							}
							
|value ',' multiargument	{		
									
								cout<<"Multiargument detected successfully\n";
								
								$$=new multiargument;
								$$->subargument.push_back($1);
								
								for(int i=0;i<$3->subargument.size();i++)
								$$->subargument.push_back($3->subargument[i]);
								
								cout<<"Multiargument for function found\n";
							}
;

//--------------------------------------------------------------------------------------------------

conditional:IF '(' boolexpression ')' block ELSE block	{
											cout<<"If else detected successfully\n";
											
											$$=new conditionalt();
											$$->elsethere=1;
											$$->condition=$3;
											$$->ifblock=$5;
											$$->elseblock=$7;
											
											cout<<"If else code generated successfully\n";
											}
|IF '(' boolexpression ')' block		{	
											
											$$=new conditionalt();
											$$->elsethere=0;
											$$->condition=$3;
											$$->ifblock=$5;
											
											
										}
;

//--------------------------------------------------------------------------------------------------

loop: WHILE'('boolexpression')'block	{
											cout<<"Loop detected successfully\n";
											
											$$=new loop();
											$$->condition=$3;
											$$->body=$5;
											
											cout<<"Loop code generated \n";
											
										}
;

//--------------------------------------------------------------------------------------------------

boolexpression:boolstmt LOGOP boolexpression	{
													cout<<"Bool expression detected successfully\n";
												
												$$=new boolvalue();
												$$->evaluatedto=getchararray(getnexttemp());
												$$->op=$2->evaluatedto;
												$$->v1=$1;
												$$->v2=$3;
												
													cout<<"Bool expression code generated\n";
												}
|NOT '(' boolexpression ')' 	{	
									cout<<"Not detected successfully\n";
									$$=new boolvalue();
									$$->evaluatedto=getchararray(getnexttemp());
									char a[]="NOT\0";
									$$->op=a;
									
									$$->v1=NULL;
									$$->v2=$3;
									
									cout<<"Not code generated\n";
								}

|boolstmt						{
									cout<<"Bool stmt detected successfully\n";
								}

;

//--------------------------------------------------------------------------------------------------

boolstmt: value RELOP value		{
									cout<<"Bool stmt detected successfully\n";
									
									$$=new boolvalue();
									$$->evaluatedto=getchararray(getnexttemp());
									$$->op=$2->evaluatedto;
									$$->v1=$1;
									$$->v2=$3;
									$1->getcode();
									$$->getcode();
									
									cout<<"Bool statement code generated\n";
								}
								
|boolean						{	
									cout<<"Came for only one plain boolean statement\n";
									$$=$1;
									cout<<"Created code for plain boolean statement\n";
								}
;
//--------------------------------------------------------------------------------------------------
%%

void yyerror(const char * s)
{
	cout<<s<<endl;
}

int main()
{
	cout<<"Parsing of sub c language will begin.\n";
	cout<<"This has two sections\nThe first section elaborates how each construct is identified as a bottom up traversal of the inbulit yacc parse tree\nThe second section will thereafter provide the three address intermediate code\n";
	
	cout<<"*********************************************************************************\n";
	cout<<"SECTION-I\n-------------------------------------------->\n";
	yyparse();
	
	cout<<"************************************************************************************\n";
	cout<<"This concludes the semester assignment of generating three address intermediate code for a custom sub c language having selected features\n";
	
}
