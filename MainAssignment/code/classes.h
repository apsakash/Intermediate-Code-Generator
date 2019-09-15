# include<vector>

using namespace std;


class value
{
	public:
		char* evaluatedto;
		virtual void getcode(){}
};

class expression: public value
{
	public:
		int isterminal;
		char* code;
		expression* cexpression1;
		expression* cexpression2;
		
		void getcode()
		{
			
			if(cexpression1==NULL)
			return;
	
			cexpression1->getcode();
			cexpression2->getcode();
			
			cout<<"\t"<<evaluatedto<<" "<<code<<endl;
		}
};

class functioncall:public value
{
	public:
		char* functionname;
		vector<value*> arguments;
		
		void getcode()
		{
		
			for(int i=0;i<arguments.size();i++)
			{
				if(arguments[i]!=NULL)
				arguments[i]->getcode();
				
			}
			
			for(int i=0;i<arguments.size();i++)
			{
				if(arguments[i]!=NULL)
				cout<<"\tParam "<<arguments[i]->evaluatedto<<endl;
			}
			
			cout<<"\tcall "<<functionname<<endl;
		}
};

struct multiargument
{
	vector<value*> subargument;
};

class statement
{
	public:
		char* start;
		char* end;
		virtual void evaluatestatement(){}
};

class creturn:public statement
{
	public:
		char* returnvalue;
		void evaluatestatement()
		{
			cout<<endl<<start<<":"<<endl;
			cout<<"\tReturn ";
			if(returnvalue!=NULL)
			cout<<returnvalue;
			
			cout<<endl;
		}
};

class output:public statement
{
	public:
		multiargument* m;
		void evaluatestatement()
		{
			if(m->subargument.size()>0)
			{
				cout<<endl<<start<<":"<<endl;
				for(int i=0;i<m->subargument.size();i++)
				{
					m->subargument[i]->getcode();
					cout<<"\tWrite "<<m->subargument[i]->evaluatedto<<endl;
				}
			}
		}
};


class declaration:public statement
{
	public:
		char* id;
		value* rhs;
		void evaluatestatement()
		{
			if(rhs!=NULL)
			{
				//cout<<"Entered\n";
				cout<<endl<<start<<":"<<endl;
				rhs->getcode();
				cout<<"\t"<<id<<"="<<rhs->evaluatedto<<endl;
			}
		}
};

struct multistatement
{
	vector<statement*> constituents;
};

class block:public statement
{
	public:
		multistatement *m;
		void evaluatestatement()
		{
			cout<<endl<<start<<":"<<endl;
			if(m->constituents.size())
			{
			
				
				if(m==NULL)
				{
			
					return;
				}
			
				for(int i=0;i<m->constituents.size();i++)
				{
					if(m->constituents[i]!=NULL)
					{
						m->constituents[i]->evaluatestatement();
					}
				}
			}
		}
};

class boolvalue:public value
{
	public:
		char* op;
		value* v1;
		value* v2;
		
		void getcode()
		{
			
			if(v1!=NULL)
			v1->getcode();
			else
			{
				v1=new value();
				v1->evaluatedto=new char[1];
				v1->evaluatedto[0]='\0';
			}
			
			v2->getcode();
			
			cout<<"\t"<<this->evaluatedto<<"="<<v1->evaluatedto<<op<<v2->evaluatedto<<endl;
		}
};


class conditionalt:public statement
{
	public:
		int elsethere;
		boolvalue* condition;
		block* ifblock;
		block* elseblock;
		
		void evaluatestatement()
		{
			cout<<endl<<start<<":"<<endl;
			condition->getcode();
			
			if(elsethere)
			{
				cout<<"\tIf "<<condition->evaluatedto<<" is false go to "" "<<elseblock->start<<endl;
				ifblock->evaluatestatement();
				cout<<"\tGoto "" "<<end<<endl;
				
				elseblock->evaluatestatement();
				cout<<"\tGoto "" "<<end<<endl;
				
			}
			
			else
			{
				cout<<"\tIf "<<condition->evaluatedto<<" is false go to "" "<<end<<endl;
				ifblock->evaluatestatement();
			}
			
			cout<<end<<":"<<endl;
		}
};

class loop:public statement
{
	public:
		boolvalue* condition;
		block* body;
		
		void evaluatestatement()
		{
			cout<<endl<<start<<":"<<endl;
			condition->getcode();
			
			cout<<"\tIf "<<condition->evaluatedto<<" is false go to "" " <<end<<endl;
			
			body->evaluatestatement();
			
			cout<<"\tReturn to "" "<<start<<endl;
			
			cout<<end<<":"<<endl;
		}
			
};

struct parameter
{
	vector<char*> parameters;
};

class function:public statement
{
	public:
		
		char* name;
		parameter* p;
		block* b;
		function()
		{
			b=NULL;
		}
		void evaluatestatement()
		{
			cout<<endl<<"\tDefine function "<<name<<endl;
			for(int i=0;i<p->parameters.size();i++)
			if(p->parameters[i]!=NULL)
			cout<<"\tParam "<<p->parameters[i]<<endl;
			
			if(b!=NULL)
			{
				
				b->evaluatestatement();
				cout<<end<<":\n Function Completed\n";
			}
			else
			cout<<"\tblock is null\n";
		}
};

class component
{
	public:
		vector<statement*> parts;
		
		void generatecode()
		{
			for(int i=0;i<parts.size();i++)
			{
				if(parts[i]!=NULL)
				parts[i]->evaluatestatement();
			}
		}
};

class cases:public statement
{
	public:
		value* v;
		multistatement* m;
		int hasbreak;
		
		void evaluatestatement()
		{
			//cout<<endl<<start<<endl;	
				
			for(int i=0;i<m->constituents.size();i++)
			m->constituents[i]->evaluatestatement();
			
			cout<<end<<":"<<endl;
		}
};

struct multicases
{
	char* start;
	char* end;
	vector<cases*> m;
};

class switches:public statement
{
	public:
		value* v;
		multicases* c;
		
		void evaluatestatement()
		{
			cout<<endl<<start<<":"<<endl;
			v->getcode();
			int i;
			for(i=0;i<c->m.size()-1;i++)
			{
				cout<<endl<<c->m[i]->start<<":"<<endl;
				cout<<"\tIf "<<v->evaluatedto<<"!="<<c->m[i]->v->evaluatedto<<"goto "<<c->m[i+1]->start<<endl;
				c->m[i]->evaluatestatement();
				if(c->m[i]->hasbreak)
				cout<<"\tGoto "<<end<<endl;
			}
			
			cout<<endl<<c->m[i]->start<<":"<<endl;
			
			cout<<"\tIf "<<v->evaluatedto<<"!="<<c->m[i]->v->evaluatedto<<"goto "<<end<<endl;
			c->m[i]->evaluatestatement();
			
			
			
		}
};


class barefunctioncall:public statement
{
	public:
		value* v;
		void evaluatestatement()
		{
			//cout<<endl<<start<<endl;
			v->getcode();
		}
};


