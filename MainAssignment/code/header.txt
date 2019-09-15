# include<vector>
# include<map>
# include<stack>
int temp_count=1;
int label_count=1;
using namespace std;

string getnextlabel()
{
	string s="";
	int i=label_count;
	label_count++;
	
	while(i>0)
	{
		s=(char)(i%10+48)+s;
		i/=10;
	}
	
	s="label"+s;
	
	cout<<s<<endl;
	return s;
}


string getnexttemp()
{
	string s="";
	int i=temp_count;
	temp_count++;
	
	while(i>0)
	{
		s=(char)(i%10+48)+s;
		i/=10;
	}
	return "t"+s;
}

char* getchararray(string s)
{
	char *a=new char[s.length()+1];
	for(int i=0;i<s.length();i++)
	a[i]=s[i];
	
	a[s.length()]='\0';
	
	return a;
}

expression* createexpression(char c,expression* e1,expression* e2)
{
	expression* e=new expression();
	e->cexpression1=e1;
	e->cexpression2=e2;
		
	e->evaluatedto=getchararray(getnexttemp());
	
	string s1(e1->evaluatedto);
	string s2(e2->evaluatedto);
	
	string s="="+s1;
	s.push_back(c);
	s+=s2;
	
	e->code=getchararray(s);
	
	return e;
}

string getexpressioncode(expression* e)
{
	if(e->cexpression1==NULL)
	return "";
	
	cout<<"Entered getexpressioncode\n";
	string s1(e->evaluatedto);
	string s2(e->code);
	
	cout<<s1<<" "<<s2<<endl;
	
	string s=getexpressioncode(e->cexpression1)+"\n"+getexpressioncode(e->cexpression2)+"\n"+s1+s2;
	
	cout<<s<<endl;
	
	return s;
	
}
