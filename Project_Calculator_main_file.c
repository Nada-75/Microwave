#include "TM4C123.h" // Device header
#include "stopwatch.h"
#include "Stack.h"
void SystemInit()
{}
void Init_GPIO_C()
{
	SYSCTL->RCGCGPIO |= 0x24; //PORTC & F clock
	GPIOC->DIR |=0x00; //PORTC rows 
	GPIOC->DEN |=0xFF;
	
	GPIOF->DIR |=0xFF; //PORTF colummns
	GPIOF->DEN |=0xFF;
}
int c=0;
unsigned int col;
unsigned const char key[4][4] ={		//KEYPAD INTERFACE
									{'1','2','3','+'},
									{'4','5','6','-'},
									{'7','8','9','*'},
									{'.','0','=','/'}
								};

unsigned char scan_keypad(void)
{
	int i=0;
	while(1) {		
	for(i=0;i<4;i++)	//COLUMN TRAVERSAL
	{
		GPIOF->DATA = 0x01 <<(i+1);
		if(GPIOC->DATA & 0x10)
		{
			while(GPIOC->DATA & 0x10){}
			return key[0][i];	
		}
		if(GPIOC->DATA & 0x20)
		{
			while(GPIOC->DATA & 0x20){}
			return key[1][i];
		}
		if(GPIOC->DATA & 0x40)
		{
			while(GPIOC->DATA & 0x40){}
			return key[2][i];
		}
		if(GPIOC->DATA & 0x80)
		{
			while(GPIOC->DATA & 0x80){}
			return key[3][i];
		}
	}
}
}

void LCD_STR_DATA(char *p)
{
	int index = 0;
	while(*p)
	{
    LCD_Data(*p);  
			delay_milli(1);
    p++;		
	 }
	delay_milli(1);
  LCD_Data(' ');
	delay_milli(1);
	LCD_Cmd(0x10);
}

void displaynum(int n)
{
  unsigned char num[30]; 
	short int count = 0;
  num[0] = '0'; 
	if(n == 0)  {LCD_Data('0');return;} 
	while(n>0)
	 {
       num[count++] = (unsigned char) ( n %10 + 48 );
       n /=10; 
   }
   for(n=count-1;n>=0;n--) 
   {
       LCD_Data(num[n]);  
  		  delay_milli(2);
    }			
}
	
void calculatorbasic(){
	int ans = 0;
	int div;
	int a=0,b=0,i=0;
	unsigned char tmp = ' ';	
  unsigned	char op;	
	int count;
	unsigned char p[10];
	LCD_Cmd(0x01);
  while(1)
   {
     tmp = scan_keypad(); 
		 delay_milli(10);
      if (tmp == '=') break;
      if (tmp == '.') 
			{
				i--;
				LCD_Cmd(0x10);
				LCD_Data(' ');
				LCD_Cmd(0x10);
				LCD_Cmd(0x10);
				continue;
			}
			LCD_Data(tmp);
			p[i++] = tmp;
      if (tmp == '+' || tmp == '-' || tmp == '*'||tmp =='/')  
			{
				op = tmp; 
			}     
		}
	 for(count =0;count<i;count++)
	 {
		 if ( p[count] =='+' || p[count] == '-' || p[count] == '*' || p[count] == '/') 
		 {
			ans = b;
			b=0;
			continue;
			}
      b = b *10 + ( (int) p[count] -48);  
  }
 switch(op)
    {
            case '+':
                      a = ans + b;
                      break;
            case '-' :
                      a = ans - b;
                      break;
            case '*' :
                      a = ans * b;
                      break; 
						case '/' :				
                      div = ans;
						          a = ans / b;
                      if (b ==0)  { LCD_STR_DATA("MATH_ERROR");return;}                 
											break; 
   }	 
	 LCD_Cmd(0xC0);
	for(i=0;i<=25;i++)
		LCD_Cmd(0x14);
  if (a < 0)  {
		LCD_Data('-');
		delay_milli(1); 
		a= -a;
		}	 
	displaynum(a);
	if (op == '/' && a == 0 ) { 
		LCD_Data('.');
		delay_milli(1);
		}
	if ( op == '/') { 
		div = (div - a * b) * 10000 / b;
    LCD_Data('.');
		delay_milli(1); 
	  a = div;
		if (a==0) return;
		LCD_Data('.');
		delay_milli(1); 
	  
    while(a < 1000) {	
			LCD_Data('0');
			delay_milli(2);
			a=a*10;}
		displaynum(div);  
	 }
 }
void evaluateexp()
 {
   char postfix[10];
	 char inf[10] ;
	 char tmp = ' ';
	 int a[15] = {0};
	 char exp[50];
	 int count = 0;int c,i;
	 int x =0;
	 int size = 0;
	 int tmp1;
	 start();
	 LCD_Cmd(0x01);
	 while(1)
	 {
		 tmp = scan_keypad();
		 LCD_Data(tmp);
		 delay_milli(1);
		 if(tmp == '=') break;
		 exp[count++] = tmp;
		 if(count+1==21)
			 LCD_Cmd(0xC0);
	 }
	 for(c=0;c<count;c++)
	 { 
		 if(exp[c] == '+' || exp[c] == '/' || exp[c] == '-' || exp[c] == '*' )
		 {
			 tmp1 = 0;
			 inf[size++] = exp[c];
			 x++;
			 continue;
		 }
		 a[x] = a[x] * 10 +(int)exp[c] - 48;
		 if (tmp1 == 0) inf[size++] = 48 + x; 
	   tmp1++;	 
	 }
	 
	/* for(c=0;c<=x;c++)
	   {
			 			 displaynum(a[c]);
			 delay_milli(1);
			 LCD_Data(',');
			 delay_milli(1);
		 }*/
	 
	 /*LCD_STR_DATA("  ");
		 for(c=0;c<size;c++)
		  { LCD_Data(inf[c]);delay_milli(2);}
	
  */
		  count = 0;
			
			for(c=0;c<size;c++)
      {
				delay_milli(2);
         switch(inf[c])
				{
                 case '+':
                 case '*':
                 case '/':
                 case '-':
                     count = addoperator(inf[c],count,postfix);      
                     break;
                      
                  default:
                          postfix[count++] = inf[c];
				delay_milli(2);
        }
      }			
			for(c=top-1;c>=0;c--)
			 postfix[count++] = pop();
			delay_milli(2);
			
			
           /*for(c=0;c<count;c++)
				    {  delay_milli(2);
        
					
              LCD_Data(postfix[c]);}*/
			delay_milli(2);				
	for(c=0;c<count;c++)
   {
      switch(postfix[c])
      {
                 case '+':
                 case '*':
                 case '/':
                 case '-':
                    if ( solve(postfix[c]) == 1) return; 
								    break;
                  default:
                         push1( a[(int)postfix[c]  - 48]  );
      }
    }							
		LCD_Cmd(0xC0);
		while(i++<20)
			LCD_Cmd(0x14);
			c = pop1();				
		  if (c<0) { LCD_Data('-');delay_milli(1);c=-c;}
	    delay_milli(2);	
     displaynum(c);							
 }
void pow(int i,int j)
 {
	 int k,temp=1,l=0;
		for(k=0;k<j;k++)
			temp *= i;
	 LCD_Cmd(0x80);
	 while(l++ <20)
		 LCD_Cmd(0x14);
	 LCD_STR_DATA("Pow(");
	 delay_milli(1);
	 displaynum(i);
	 delay_milli(1);
	 LCD_Data(',');
	 delay_milli(1);
	 displaynum(j);
	 LCD_STR_DATA(")= ");
	 displaynum(temp);
	 scan_keypad();
 }
 
 void fact(int i)
 {
	 int ans=1,j=i;
	 while(i>0)
	 {
			ans*=i;
			i--;
	 }
	 LCD_Cmd(0xC0);
	 displaynum(j);
	 delay_milli(1);
	 LCD_STR_DATA("! = ");
	 delay_milli(1);
	 displaynum(ans);
	 scan_keypad();
 }
 
 void dec_bin(int input)
 {
	 int disp[20],i=0,j=0;
	while(input>0)
	 {
		disp[i]=input%2;
		input/=2;
		i++;
	 }
	i--;
	LCD_Cmd(0xC0);
	while(j++<20)
		LCD_Cmd(0x14);
	while(i>=0)
	{
		displaynum(disp[i]);
		delay_milli(1);
		i--;
	}
	 scan_keypad();
	}
	
	void dec_oct(int input)
 {
	 int disp[30];
	 int i=0,j=0;
	while(input>0)
	 {
		disp[i]=input%8;
		input/=8;
		i++;
	 }
	i--;
	LCD_Cmd(0xC0);
	while(j++<20)
		LCD_Cmd(0x14);
	while(i>=0)
	{
		displaynum(disp[i]);
		delay_milli(1);
		i--;
	}
}

int bin_to_dec()
{
 	int decimal_value=0;
	int base=1,rem=0;
	 int bin_value=0,j=0;
	 unsigned char in;
	LCD_Cmd(0x01);
	 LCD_STR_DATA("Enter Number ");
	 while(1)
	{
	    in =  scan_keypad();
      if (in == '=') break;             
									 bin_value = bin_value * 10 + (int)in - 48; 
									LCD_Data(in);
									delay_milli(1);
	}
	while(bin_value>0)
	{
		rem=bin_value%10;
		decimal_value=decimal_value+rem*base;
		bin_value/=10;
		base*=2;
	}
	LCD_Cmd(0xC0);
	while(j++<20)
		LCD_Cmd(0x14);
	displaynum(decimal_value);
	return decimal_value;
}

int oct_to_dec()
{
	int decimal_value=0;
	int base=1,rem=0;
	 int oct_value=0,j=0;
	 unsigned char in;
	LCD_Cmd(0x01);
	delay_milli(5);
	LCD_STR_DATA("Enter Number ");	
	while(1)
	{
	    in =  scan_keypad();
      if (in == '=') break;             
				oct_value = oct_value * 10 + (int)in - 48; 
	     	LCD_Data(in);
				delay_milli(1);
	}
	while(oct_value>0)
	{
		rem= oct_value % 10;
		decimal_value=decimal_value+rem*base;
		oct_value/=10;
		base*=8;
	}
	LCD_Cmd(0xC0);
	while(j++<20)
		LCD_Cmd(0x14);
	displaynum(decimal_value);
	return decimal_value;
}

void decimal_to_hex(int decimalnum)
{
	int quotient=0,remainder=0;
	int i,j=0,k=0;
	char hexadecimal[20];
  LCD_Cmd(0xC0);
	quotient=decimalnum;
	while(quotient!=0)
	{
		remainder=quotient%16;
		if(remainder<10)
		{
			hexadecimal[j++]=48+remainder;
		}
		else
			hexadecimal[j++]=55+remainder;
		quotient/=16;
	}

	for(i=j-1;i>=0;i--)
	{
		LCD_Data(hexadecimal[i]);
		delay_milli(1);
	}
	LCD_Data(' ');
	LCD_Cmd(0x10);
	scan_keypad();
}

void oct_to_hex(){
	int num,i=0,j=0;
	num = oct_to_dec();
	LCD_Cmd(0xC0);
	while(i++ <20)
		LCD_Data(' ');
	LCD_Cmd(0xC0);
	decimal_to_hex(num);	
	LCD_Data(' ');
	LCD_Cmd(0x10);
	while(j++<20)
		LCD_Cmd(0x14);
	scan_keypad();
}

void bin_to_hex(){	
	int num,i=0,j=0;
	num = bin_to_dec();
	LCD_Cmd(0xC0);
	while(i++ <20)
		LCD_Data(' ');
	LCD_Cmd(0xC0);
	while(j++<20)
		LCD_Cmd(0x14);
	decimal_to_hex(num);	
	LCD_Data(' ');
	LCD_Cmd(0x10);
} 

void bin_to_oct(){
	int num,i=0,j=0;
	num = bin_to_dec();
	LCD_Cmd(0xC0);
	while(i++ <20)
		LCD_Data(' ');
	LCD_Cmd(0xC0);
	while(j++<20)
		LCD_Cmd(0x14);
	dec_oct(num);
	scan_keypad();
}

void oct_to_bin()
{
	int num,i=0,j=0;
	num = oct_to_dec();
	LCD_Cmd(0xC0);
	while(i++ <20)
		LCD_Data(' ');
	LCD_Cmd(0xC0);
	while(j++<20)
		LCD_Cmd(0x14);
	dec_bin(num);
	scan_keypad();	
}

int sine(int num){
	 int result = 0;
  const unsigned char sinelookup[90][4] = {
                                             {'0','0','0','0'},   
																						 {'0','1','7','5'},   
																						 {'0','3','4','9'},   
																						 {'0','5','2','3'},   
																						 {'0','6','9','8'},   
																						 {'0','8','7','2'},   
																						 {'1','0','4','5'},   
																						 {'1','2','1','9'},   
																						 {'1','3','9','1'},   
																						 {'1','5','6','4'},   
																						 {'1','7','3','6'},   
																						 {'1','9','0','8'},   
																						 {'2','0','7','9'},   
																						 {'2','2','5','0'},   
																						 {'2','4','1','9'},   
																						 {'2','5','8','8'},   
																						 {'2','7','5','6'},   
																						 {'2','9','2','4'},   
																						 {'3','0','9','0'},   
																						 {'3','2','5','6'},
																						 {'3','4','2','0'},
																						 {'3','5','8','4'},
																						 {'3','7','4','6'},
																						 {'3','9','0','7'},
																						 {'4','0','6','7'},
																						 {'4','2','2','6'},
																						 {'4','3','8','4'},
																						 {'4','5','4','0'},
																						 {'4','6','9','5'},
																						 {'4','8','4','8'},
																						 {'5','0','0','0'},
																						 {'5','1','5','0'},
																						 {'5','2','9','9'},
																						 {'5','4','4','6'},
																						 {'5','5','9','2'},
																						 {'5','7','3','6'},
																						 {'5','8','7','8'},
																						 {'6','0','1','8'},
																						 {'6','1','5','7'},
																						 {'6','2','9','3'},
																						 {'6','4','2','8'},
																						 {'6','5','6','1'},
																						 {'6','6','9','1'},
																						 {'6','8','2','0'},
																						 {'6','9','4','7'},
																						 {'7','0','7','1'},
																						 {'7','1','9','3'},
																						 {'7','3','1','4'},
																						 {'7','4','3','1'},
																						 {'7','5','4','7'},
																						 {'7','6','6','0'},
																						 {'7','7','7','1'},
																						 {'7','8','8','0'},
																						 {'7','9','8','6'},
																						 {'8','0','9','0'},
																						 {'8','1','9','2'},
																						 {'8','2','9','0'},
																						 {'8','3','8','7'},
																						 {'8','4','8','0'},
																						 {'8','5','7','2'},
																						 {'8','6','6','0'},
																						 {'8','7','4','6'},
																						 {'8','8','2','9'},
																						 {'8','9','1','0'},
																						 {'8','9','8','8'},
																						 {'9','0','6','3'},
																						 {'9','1','3','5'},
																						 {'9','2','0','5'},
																						 {'9','2','7','2'},
																						 {'9','3','3','6'},
																						 {'9','3','9','7'},
																						 {'9','4','5','5'},
																						 {'9','5','1','1'},
																						 {'9','5','6','3'},
																						 {'9','6','1','3'},
																						 {'9','6','5','9'},
																						 {'9','7','0','3'},
																						 {'9','7','4','4'},
																						 {'9','7','8','1'},
																						 {'9','8','1','6'},
																						 {'9','8','4','8'},
																						 {'9','8','7','7'},
																						 {'9','9','0','3'},
																						 {'9','9','2','5'},
																						 {'9','9','4','5'},
																						 {'9','9','6','2'},
																						 {'9','9','7','6'},
																						 {'9','9','8','6'},
																						 {'9','9','9','4'},
																						 {'9','9','9','8'},
																						 };
				
  if(num >360)
	{
		num = num %360;
	}
	if(num == 270) LCD_Data('-');
	if (num % 90 == 0 && (num/90) % 2 != 0 ){
		LCD_STR_DATA("1.000");
		return 1; 
		}
	if (num % 90 == 0 && (num/90) % 2 == 0 ){ 
		LCD_STR_DATA("0.000");
		return 0;
		}																			 
  if (num >= 91 && num < 180 ) 
		num = 180 - num;
	if (num >=181 && num < 270) {
		LCD_Data('-');
		num = num-180;
		}
	if(num>=271 && num <360)
		{
			 LCD_Data('-');
			num = 360-num;
		}
		delay_milli(2);
	if(num<90)		 
		{ 
		 LCD_STR_DATA("0.");
     delay_milli(1);		
		 result = result * 10 + (int)sinelookup[num][0] - 48; 
		 LCD_Data(sinelookup[num][0]);                                       
     delay_milli(1);
		 result = result * 10 + (int)sinelookup[num][1] - 48;
		 LCD_Data(sinelookup[num][1]);
		 delay_milli(1);
		 result = result * 10 + (int)sinelookup[num][2] - 48;
		 LCD_Data(sinelookup[num][2]);
		 delay_milli(1);
		 result = result * 10 + (int)sinelookup[num][3] - 48;
		 LCD_Data(sinelookup[num][3]);			
		 return result; 
		}
}

int cose(int angle){
	angle = angle % 360;
	if (angle <= 90) sine(90 - angle); 
	if (angle >90 && angle <=180) { 
		LCD_Data('-');
		return sine(angle - 90);
	}
	if (angle >180 && angle <=270) {
		LCD_Data('-');
		return sine(270 - angle);
	}
	if (angle >270 && angle <=360) { 
		return sine(angle - 270); 
	}
}

void secant(int angle)
{
	  int result = angle;
	  int tmp = 0;
	  angle  =  angle % 360;
	  if (angle % 180 == 0 && (angle/180) % 2 == 0 ) { 
			LCD_STR_DATA("1.0000");
			return;
			}
    if (angle % 180 == 0 && (angle/180) % 2 == 1 ) { 
			LCD_STR_DATA("-1.0000");
			return;
			}
    if (angle % 90 == 0)  { 
			LCD_STR_DATA("INF");
			return;
			}
   tmp = cose(angle);
   delay_milli(2);
  LCD_Cmd(0x01);
  LCD_STR_DATA("sec(");
  delay_milli(2);
  displaynum(result);
  LCD_STR_DATA(")");
  delay_milli(2);
  LCD_Data('='); 
  delay_milli(2);
   if ( (angle > 90 && angle < 180) || ( angle > 180 && angle < 270 ) ) LCD_Data('-');
    delay_milli(2);
    result = 10000 / tmp;
    displaynum(result);
  if (result == 0) LCD_Data('0');
  delay_milli(2) ;
  LCD_Data('.');
  delay_milli(2) ;
  result =  ( 10000 - result *  tmp ) * 10000  / tmp;
  angle = result;
	while(angle  < 1000) {
		LCD_Data('0');
		delay_milli(2);
		angle=angle*10;
	}
	displaynum(result);
}

void cosecant(int angle)
{
	  int result = angle;
	  int tmp = 0;
	  angle  =  angle % 360;
	  if (angle % 180 == 0)  {
			LCD_STR_DATA("INF");
			return;
		}
    if (angle % 90 == 0 ) {
			LCD_STR_DATA("1.0000");
			return;
		}		
    if (angle == 270 ) { 
			LCD_STR_DATA("-1.0000");
			return;
		}
    tmp = sine(angle);
   delay_milli(2);
  LCD_Cmd(0x01);
  LCD_STR_DATA("cosec(");
  delay_milli(2);
  displaynum(result);
  LCD_STR_DATA(")");
  delay_milli(2);
  LCD_Data('='); 
  delay_milli(2);
   if (angle > 180 )  {
		LCD_Data('-');
		delay_milli(2);
		}
    delay_milli(2);
    result = 10000 / tmp;
    displaynum(result);
  if (result == 0)
			LCD_Data('0');
  delay_milli(2) ;
  LCD_Data('.');
  delay_milli(2) ;
  result =  ( 10000 - result *  tmp ) * 10000  / tmp;
  angle = result;
	while(angle  < 1000) {	
		LCD_Data('0');
		delay_milli(2);
		angle=angle*10;
	}	
	displaynum(result);
}

void cot(int angle)
{
  int result = angle;
	int c = 0;
	int s = 0;
	angle = angle % 360;  
	if (angle % 180  == 0) {
		LCD_STR_DATA("MATH ERROR"); 
		return;
	}
  if (angle % 90 == 0) {
		LCD_STR_DATA("0.0000");
		return; 
	}
  s = sine(angle);
  c = cose(angle);
  
  delay_milli(2);
  LCD_Cmd(0x01);
  
  LCD_STR_DATA("cot(");
  delay_milli(2);
  displaynum(result);
  LCD_STR_DATA(")");
  delay_milli(2);
  LCD_Data('='); 
  delay_milli(2);
  if ( (angle > 90 && angle < 180) || ( angle > 270 && angle < 360 ) ) 
		LCD_Data('-');
    delay_milli(2);
  result = c/s;    
	displaynum(result);
  if (result == 0) 
			LCD_Data('0');
  delay_milli(2) ;
  delay_milli(2) ;
  result =  ( c - result *  s ) * 10000  / s;
  angle = result;
	if (angle ==0) return;
  LCD_Data('.');
	delay_milli(2);
	while(angle  < 1000) {	
		LCD_Data('0');
		delay_milli(2);
		angle=angle*10;
	}
			
	displaynum(result);
}


void tane(int angle)
{
  int result = angle;
	int c = 0;
	int s = 0;
	angle = angle % 360;  
	
  if (angle % 180 == 0) {  
		LCD_STR_DATA("0.0000");
		return;
	}
  if (angle % 90 == 0) { 
		LCD_STR_DATA("MATH ERROR"); 
		return; 
	}
  s = sine(angle);
  c = cose(angle);
  
  delay_milli(2);
  LCD_Cmd(0x01);
  
  LCD_STR_DATA("tan(");
  delay_milli(2);
  displaynum(result);
  LCD_STR_DATA(")");
  delay_milli(2);
  LCD_Data('='); 
  delay_milli(2);
   if ( (angle > 90 && angle < 180) || ( angle > 270 && angle < 360 ) ) 
		LCD_Data('-');
    delay_milli(2);
  result = s/c;    
	displaynum(result);
  if (result == 0) LCD_Data('0');
  result =  ( s - result *  c ) * 10000  / c;
  	angle = result;
	if(result==0)return;
  delay_milli(2) ;
  LCD_Data('.');
  delay_milli(2) ;
	while(angle  < 1000) {
		LCD_Data('0');
		delay_milli(2);
		angle=angle*10;
	}	
	displaynum(result);
}

void trig()
{
	unsigned char function_sel;
	unsigned char value;
	int angle =  0,l=0;
	int neg_indicator=0;
	LCD_Cmd(0x01);
	LCD_STR_DATA("1.Sin");
	while(l++ <15)
		LCD_Cmd(0x14);
	LCD_STR_DATA("3.Tan");
	LCD_Cmd(0xC0);
	LCD_STR_DATA("2.Cos");
	LCD_Cmd(0x80);
	l=0;
	while(l++ <10)
		LCD_Cmd(0x14);
	LCD_STR_DATA("4.Cosec");
	LCD_Cmd(0xC0);
	l=0;
	while(l++ <10)
		LCD_Cmd(0x14);
	LCD_STR_DATA("5.sec");
	LCD_Cmd(0x80);
	l=0;
	while(l++ <30)
		LCD_Cmd(0x14);
	LCD_STR_DATA("6.Cot");
	
	function_sel=scan_keypad();
   switch(function_sel)
    {  case '1':	
				        LCD_Cmd(0x01);
                LCD_STR_DATA("sin(");
                while(1)
								{
									 function_sel =  scan_keypad();
                   if (function_sel == '=') break;
                   if(function_sel == '-') {
										 neg_indicator= 1;
										 LCD_Data('-');
										 continue;
									 }
								 angle = angle * 10 + (int)function_sel - 48; 
									LCD_Data(function_sel);
									delay_milli(1);
									
                }
                 LCD_STR_DATA(")= ");
								if(neg_indicator==1)
									sine(360-angle);
								else
								sine(angle);
								scan_keypad();	
								neg_indicator = 0;
								break;
								
			case '2':	
				        LCD_Cmd(0x01);
                LCD_STR_DATA("cos(");
                while(1)
								{
									 function_sel =  scan_keypad();
                   if (function_sel == '=') break;
                   if(function_sel == '-') {
										 neg_indicator= 1;
										 LCD_Data('-');
										 continue;
									 }
									 angle = angle * 10 + (int)function_sel - 48; 
									LCD_Data(function_sel);
									delay_milli(1);
									
                }
                 LCD_STR_DATA(")= ");
								if(neg_indicator==1)
									cose(360-angle);
								else
								 cose(angle);
								scan_keypad();	
								neg_indicator=0;
								break;
			case '3':	
				        LCD_Cmd(0x01);
                LCD_STR_DATA("tan(");
                while(1)
								{
									 function_sel =  scan_keypad();
                   if (function_sel == '=') break;
                   if(function_sel == '-') {
										 neg_indicator= 1;
										 LCD_Data('-');
										 continue;
									 }
									 angle = angle * 10 + (int)function_sel - 48; 
									LCD_Data(function_sel);
									delay_milli(1);
                }
                 LCD_STR_DATA(")= ");
								if(neg_indicator==1)
									tane(360-angle);
								else
								 tane(angle);
								scan_keypad();	
								neg_indicator=0;
								break;
         case '5':	
				        LCD_Cmd(0x01);
                LCD_STR_DATA("sec(");
                while(1)
								{
									 function_sel =  scan_keypad();
                   if (function_sel == '=') break;
                   if(function_sel == '-'){
										 neg_indicator= 1;
										 LCD_Data('-');
										 continue;
									 }
									 angle = angle * 10 + (int)function_sel - 48; 
									LCD_Data(function_sel);
									delay_milli(1);
                }
                 LCD_STR_DATA(")= ");
								if(neg_indicator==1)
									secant(360-angle);
								else
								 secant(angle);
								scan_keypad();	
								neg_indicator=0;
								break;
											
         case '4':	
				        LCD_Cmd(0x01);
                LCD_STR_DATA("cosec(");
                while(1)
								{
									 function_sel =  scan_keypad();
                   if (function_sel == '=') break;
                   if(function_sel == '-') {
										 neg_indicator= 1;
										 LCD_Data('-');
										 continue;
									 }
									 angle = angle * 10 + (int)function_sel - 48; 
									LCD_Data(function_sel);
									delay_milli(1);
                }
                 LCD_STR_DATA(")= ");
								if(neg_indicator==1)
									cosecant(360-angle);
								else
								 cosecant(angle);
								scan_keypad();	
								neg_indicator = 0;
								break;
					
          case '6':	
				        LCD_Cmd(0x01);
                LCD_STR_DATA("cot(");
                while(1)
								{
									 function_sel =  scan_keypad();
                   if (function_sel == '=') break;
                   if(function_sel == '-') {
										 neg_indicator= 1;
										 LCD_Data('-');
										 continue;
									 }
									 angle = angle * 10 + (int)function_sel - 48; 
									LCD_Data(function_sel);
									delay_milli(1);
                }
                 LCD_STR_DATA(")= ");
								if(neg_indicator==1)
									cot(360-angle);
								else
								 cot(angle);
								scan_keypad();	
								neg_indicator=0;
								break;
      				}							
}
void baseN(){
	int i=0;
	unsigned char choice1,choice2;
	LCD_Cmd(0x01);
	LCD_STR_DATA("From");
  LCD_Cmd(0xC0);
	LCD_STR_DATA("1.Decimal");
	LCD_Cmd(0x80);
	i=0;
	while(i++ <20)
		LCD_Cmd(0x14);
	LCD_STR_DATA("2.Binary");
	LCD_Cmd(0xC0);
	i=0;
	while(i++ <20)
		LCD_Cmd(0x14);
	LCD_STR_DATA("3.Octal");
	
	choice1 = scan_keypad();
	if(choice1 == '1'){
	LCD_Cmd(0x01);
	LCD_STR_DATA("To");
  LCD_Cmd(0xC0);
	LCD_STR_DATA("1.Binary");
	LCD_Cmd(0x80);
	i=0;
	while(i++ <20)
		LCD_Cmd(0x14);
	LCD_STR_DATA("2.HexaDecimal");
	LCD_Cmd(0xC0);
	i=0;
	while(i++ <20)
		LCD_Cmd(0x14);
	LCD_STR_DATA("3.Octal");
  }
	if(choice1 == '2'){
	LCD_Cmd(0x01);
	LCD_STR_DATA("To");
  LCD_Cmd(0xC0);
	LCD_STR_DATA("1.Decimal");
	LCD_Cmd(0x80);
	i=0;
	while(i++ <20)
		LCD_Cmd(0x14);
	LCD_STR_DATA("2.HexaDecimal");
	LCD_Cmd(0xC0);
	i=0;
	while(i++ <20)
		LCD_Cmd(0x14);
	LCD_STR_DATA("3.Octal");
  }
	if(choice1 == '3'){
	LCD_Cmd(0x01);
	LCD_STR_DATA("To");
  LCD_Cmd(0xC0);
	LCD_STR_DATA("1.Decimal");
	LCD_Cmd(0x80);
	i=0;
	while(i++ <20)
		LCD_Cmd(0x14);
	LCD_STR_DATA("2.HexaDecimal");
	LCD_Cmd(0xC0);
	i=0;
	while(i++ <20)
		LCD_Cmd(0x14);
	LCD_STR_DATA("3.Binary");
  }
	
	choice2 = scan_keypad();
	if(choice1 == '1')
	{
		if(choice2 == '1')
		{
			 unsigned char in;
	int i=0;
	int answer;
	 LCD_Cmd(0x01);
	 LCD_STR_DATA("Enter Number ");
	 while(1)
	{
	    in =  scan_keypad();
      if (in == '=') break;             
			answer = answer * 10 + (int)in - 48; 
	   	LCD_Data(in);
			delay_milli(1);
	}
			dec_bin(answer);
		}
		if(choice2 == '2')
		{
			int decimalnum;
	    unsigned char in;
			LCD_Cmd(0x01);
			LCD_STR_DATA("Enter Number ");
	    while(1)
	{
	    in =  scan_keypad();
          if (in == '=') break;             
									 decimalnum = decimalnum * 10 + (int)in - 48; 
									LCD_Data(in);
									delay_milli(1);
	}
			decimal_to_hex(decimalnum);
	
		}
		if(choice2 == '3')
		{
			unsigned char in;
	int i=0;
	int answer;
	 LCD_Cmd(0x01);
	 LCD_STR_DATA("Enter Number ");
	 while(1)
	{
	    in =  scan_keypad();
      if (in == '=') break;             
			answer = answer * 10 + (int)in - 48; 
	   	LCD_Data(in);
			delay_milli(1);
	}
			dec_oct(answer);
			scan_keypad();
		}
	}
	if(choice1 == '2')
	{
		if(choice2 == '1')
		{
			bin_to_dec();
			scan_keypad();
		}
		if(choice2 == '2')
		{
			bin_to_hex();
		}
		if(choice2 == '3')
		{
			bin_to_oct();
		}
	}
	if(choice1 == '3')
	{
		if(choice2 == '1')
		{
			oct_to_dec();
			scan_keypad();
		}
		if(choice2 == '2')
		{
			oct_to_hex();
		}
		if(choice2 == '3')
		{
			oct_to_bin();
		}
	}
	
}

void misc()
{
	unsigned char temp,x,y,i=0;
	int base,exp;
	LCD_Cmd(0x01);
	LCD_STR_DATA("1.Pow(x,y)");	
	LCD_Cmd(0xC0);
	LCD_STR_DATA("2.Factorial");	
	LCD_Cmd(0x80);
	while(i++ <20)
		LCD_Cmd(0x14);
	LCD_STR_DATA("3.Base-N");	
	temp=scan_keypad();
	switch(temp)
	{
		case '1':
			LCD_Cmd(0x01);
                LCD_STR_DATA("x = ");
                while(1)
								{
									 x =  scan_keypad();
                   if (x == '=') break;
                   
									 base = base * 10 + (int)x - 48; 
									LCD_Data(x);
									delay_milli(1);
                }
								LCD_Cmd(0xC0);
								LCD_STR_DATA("y = ");
                while(1)
								{
									 y =  scan_keypad();
                   if (y == '=') break;
                   
									 exp = exp * 10 + (int)y - 48; 
									LCD_Data(y);
									delay_milli(1);
                }
								pow(base,exp);
								break;
		 case '2':
			 LCD_Cmd(0x01);
                LCD_STR_DATA("num = ");
                while(1)
								{
									 x =  scan_keypad();
                   if (x == '=') break;
                   
									 base = base * 10 + (int)x - 48; 
									LCD_Data(x);
									delay_milli(1);
                }
								fact(base);
								break;
			case '3':
			 LCD_Cmd(0x01);
					baseN();
			break;	
	}	
}


int main()
{
	int i=0;
	unsigned char input;
	LCD_init();
	Init_GPIO_C();
	LCD_STR_DATA("      WELCOME");
	delay_milli(2500);
	LCD_Cmd(0x01);
	LCD_STR_DATA(" Asad Ali   2015EE77");
	delay_milli(1);
	LCD_STR_DATA("Ansar Rasool2015EE80");
	delay_milli(1);
	LCD_STR_DATA("Qasim Elahi 2015EE66");
	delay_milli(1);
	LCD_STR_DATA("Abdullah    2015EE82");
	delay_milli(3500);
	
	while(1) {
     i=0;
		LCD_Cmd(0x01);		
	LCD_STR_DATA("1.Basic  2.Stopwatch"); //print on LCD
		while(i++<20)
			LCD_Cmd(0x14);
		LCD_STR_DATA("3.Trignometric"); //print on LCD
		LCD_Cmd(0x80);
		i=0;
		while(i++ <20)
			LCD_Cmd(0x14);
		LCD_STR_DATA("4.Misc");
		LCD_Cmd(0xC0);
		i=0;
		while(i++ <20)
			LCD_Cmd(0x14);
		LCD_STR_DATA("5.EvaluateExpresion");
		
     input = scan_keypad();
	
	switch(input)
	{	
		case '1':
					calculatorbasic();
					 delay_milli(1);
	            scan_keypad();
	            break;
		case '2':
					Stopwatch();
					break;           
		case '3':
					trig();
					break;
		case '4':
			    misc();
		      break;
		case '5':
			    evaluateexp();
	         scan_keypad();
         		break;
  }
  }
}


void LCD_init(void){
	SYSCTL->RCGCGPIO |= 0x01; //PORTA clock  For RS,RW,E
	SYSCTL->RCGCGPIO |= 0x02; //PORTB clock  For Data lines
	GPIOA->DIR |=0xE0; //PORTA controls RS,E and R/W
	GPIOA->DEN |=0xE0;
	GPIOB->DIR |=0xFF; //PORTB D0-D7
	GPIOB->DEN |=0xFF; //PORTB D0-D7
	LCD_Cmd(0x38); //8-bits,2 display lines, 5x7 font
	LCD_Cmd(0x06); //increments automatically
	LCD_Cmd(0x0F); //Turn on display
	LCD_Cmd(0x01); //clear display
}
 
void LCD_Cmd(unsigned char command)
{
	GPIOA->DATA = 0x00; //RS =0, E=0, RW=0
	GPIOB->DATA =command;
	GPIOA->DATA =0x80; //E=1 to secure command
	delay_micro(0);
	GPIOA ->DATA =0x00;
	if(command <4) 
		delay_milli(2);
	else
		delay_micro(37); 
} 

void LCD_Data(unsigned char data) {
	GPIOA ->DATA =0x20; //RS=1, E=0,RW=0
	GPIOB->DATA =data;
	GPIOA->DATA |= 0x80; 
	GPIOA->DATA =0x00;
	delay_micro(0);
}

void delay_milli(int n){
	int i,j;
	for(i=0;i<n;i++)
	for(j=0;j<3180;j++)
	{}
}
 
void delay_micro(int n){
	int i,j;
	for(i=0;i<n;i++)
	for(j=0;j<3;j++)
	{}
}
