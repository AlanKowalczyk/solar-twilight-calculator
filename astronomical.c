// program created as summer side project during university summer brake in 2009
// added to github in 2026, with some small cosmetic changes 



#define _GNU_SOURCE
#include<stdio.h>
#include<math.h>

void rot(int os, double kat, double V[3]);

double zam(double E,int a);



int main(void)

{

  char z; //z- znak

  int m,d,r,a; //m-minuty, d-stopnie(godziny), r-rok, a-dzien roku

  double s,c,H,D,B,J,G,L,k; //s-sekundy, H-rekt w rad; D-dek w rad; B-szergeog w rad; J-Julian;

//G-czas gwiazdowy, L-dlugosc geog w godz, k-rekt słońca w godz,

  double radd,radh,pos[3]; //radd- radian stopnie; radh- radian godziny; pos[3]-wsp. prostokatne

  radd=M_PI/180.0;

  radh=M_PI/12.0;



//Szerokość geograficzna - wprowadzenie

while(1)

    {

 puts("Program w tej wersji, działa poprawnie dla Polski\n");

  puts("Szerokosc N poprzedz znakiem \"+\", natomiast szerokosc S znakiem \"-\"\n");

      puts("Podaj szerokosc geograficzna ze znakiem w stopniach, minutach i sekundach uzywajac spacji pomiedzy np +52 23 53\n ");

  scanf(" %c %d %d %lf",&z,&d,&m,&s);

      if((z!='-')&&(z!='+'))

  {

 puts("Najpierw podaj znak szerokosci\n");

 continue;

  }

      if(d<(-90)||d>90||(d==(-90)&&m!=0)||(d==(-90)&&s!=0.0)||(d==90&&m!=0)||(d==90&&s!=0.0))

      {

   puts("Wartosc stopniowa szerokosci jest z przedzialu <-90,90> \n");

   continue;

  }

      if(m>=60||s>=60.0)

      {

   puts("Wartosci minut i sekund  moga byc z przedzialu <0,60) \n");

   continue;

 }

 // d=52;//Poznan, instrument przejsciowy

  //m=23;

  //s=53.0;

      B=d+(m/60.0)+(s/3600.0);//zamiana na stopnie z ulamkiem

      B*=radd; //zamiana na radiany

  if (z=='-')  //przeznakowani na ujemne if minus

  B=-B;

  break;

    }



//długosc geograficzna - wprowadzenie

while(1)

    {

  puts("Dlugosc E poprzedz znakiem \"+\", natomiast dlugosc W znakiem \"-\"\n");

      puts("Podaj dlugosc geograficzna ze znakiem w stopniach, minutach i sekundach uzywajac spacji pomiedzy np +1 7 31 \n ");

  scanf(" %c %d %d %lf",&z,&d,&m,&s);

      if((z!='-')&&(z!='+'))

 {

 puts("Najpierw podaj znak dlugosci\n");

 continue;

  }

      if(d<(-180)||d>180||(d==(-180)&&m!=0)||(d==(-180)&&s!=0.0)||(d==180&&m!=0)||(d==180&&s!=0.0))

      {

   puts("Wartosc stopniowa dlugosci jest z przedzialu <-180,180> \n");

   continue;

  }

      if(m>=60||s>=60.0)

      {

   puts("Wartosci minut i sekund  moga byc z przedzialu <0,60) \n");

   continue;

  }

//d=1;

//m=7;

//s=30.99;

      L=d+(m/60.0)+(s/3600.0);//zamiana na godziny z ulamkiem

     // L/=15.0; //zamiana na godziny

  if (z=='-')  //przeznakowanie na ujemne if minus

  L=-L;

  break;

    }



//data - wprowadzenie

while(1)

    {

      puts("Podaj date obserwacji w formacie (rrrr-mm-dd)\n ");

  scanf(" %d%c%d%c%d",&r,&z,&m,&z,&d);//r-rok,m-miesiac,d-dzien

      if(z!='-'||d<1||d>31||m>12||(d>30&&m==4)||(d>30&&m==6)||(d>30&&m==9)||(d>30&&m==11))

      {

  puts("niepoprawny format daty \n");//ilosc dni i miesiecy

  continue;

  }

  if((!(r%400)&&m==2&&d>29)||((r%400)&&!(r%100)&&m==2&&d>28))

  {

  puts("niepoprawny format daty \n");//luty co 100 nieprzestepny, a co 400 tak

  continue;

  }

  else if((!(r%4)&&m==2&&d>29)||((r%4)&&m==2&&d>28))

  {

  puts("niepoprawny format daty \n");//co 4 przestepny

  continue;

  }

  break;

    }

//dzien roku

a=floor((m-1)*(365.25/12.0)+d);

if(m==2||m>8) a++;

//zamiana na date Julianska

if(m<3)

{

  m+=12;//styczen i luty to miesiace 13 i 14

  r-=1;//roku poprzedniego

}

s=4716+r+floor((m+9)/12.0);//takie s do wzoru nizej

J=1729279.5+367*r+floor(275*m/9.0)-floor(7*s/4.0)+d;//wzory na JD

J+=(38-floor(3*(floor(s+83)/100.0+1)/4.0));//data Julianska

//czas gwiazdowy

c=2451545;//J2000UT1 - 2000.1.1 12h ut1

s=(J-c)/36525.0;//różnica naszej daty i J2000

G=24110.54841+8640184.812866*s+0.093104*s*s-6.2e-6*s*s*s;//G-czas gwiazdowy w sekundach

G/=3600.0;//w godzinach

while(G>24)

G-=24;

while(G<0)

G+=24;

printf("czas gwiazdowy green o północy. %.14f\n",G);

G+=L;//G naszego poludnika a nie green.

printf("czas gwiazdowy nasz o północy. %.14f\n",G);



//czas -wprowadzenie

while(1)

{

puts("Podaj czas w formacie (hh:mm:ss) zakładając ze 24=0\n");

scanf("%d%c%d%c%d",&d,&z,&m,&z,&r);//d-godz; m-min; r-sek

if(z!=':')

{

puts("niepoprawny format czasu \n");

continue;

}

if(d>=24||m>=60||r>=60)

{

puts("podaj czas jeszcze raz \n");

continue;

}

break;

}



s=d/24.0+m/(60*24.0)+r/(3600*24.0);//ulamek dnia



//strefa czasowa

//tu trzeba, napisać fragment kodu, który oblicza strefe czasową z daty, (czas letni, zimowy) bedzie masakra...!!!!!!!!!!!!!!

//na razie przyjmuje czas zimowy w polsce d=1

d=1;





s-=d/24.0;

J+=s;//dodanie ulamka dnia do Jd

c=24/24.0+3/(60*24.0)+56.5553678/(3600*24.0);//stala k

s*=24;//ulamek dnia w godzinach

G+=s*c;//G na chwile zadana

while(G<0)

G+=24;

while(G>=24)

G-=24;

printf("czas gwiazdowy nasz teraz %.14f\n",G);

G*=radh;//G w rad



    //wschód i zachód słońca



//D-deklinacja slonca w rad

//k-rektascencja slonca w godz

k=0.0;

c=360/365.25;//otyle sie zmienia w ciagu doby rekt sl w stopnaich

D=0.0;//dek slonca

if(a>0&&a<81)//do 21 marca rosnie sobie do 0

{

s=(23*60+26)/91.0;

D-=(81-a)*s;

}

else if(a==81) D=0.0;

else if(a>81&&a<173)

{

D=0.0;

s=(23*60+26)/92.0;

D+=(a-81)*s;

}

else if(a==173) D=23*60+26;//max deklinacja dalej juz bedzie malala

else if(a>173&&a<266)

{

D=23*60+26;

s=(23*60+26)/93.0;

D-=(a-173)*s;

}

else if(a==266) D=0.0;

else if(a>266&&a<356)

{

D=0.0;

s=(23*60+26)/90.0;

D-=(a-266)*s;

}

else if(a==356) D=-(23*60+26);//min dek dalej bedzie rosla

else if(a>356)

{

D=-(23*60+26);

s=(23*60+26)/91.0;

D+=(a-356)*s;

}

if(a>81) k+=(a-81)*c;//ilosc dni mnoze przez wspolczynnk b (linijka okolo 159)

else if(a<81) k-=(81-a)*c;

D/=60.0;

D*=radd;

G/=radh;

while(k<0)

k+=360;

while(k>360)

k-=360;

k/=15.0;//zamiana na godz

J=G-k;//kat godzinny slonca

while(J<0)

J+=24;

while(J>24)

J-=24;

J*=radh;



pos[0]=cos(J)*cos(D);//zamiana na wspolrzedne prostokatne

pos[1]=sin(J)*cos(D);//potrzebne to transformacji macierzami

pos[2]=sin(D);

rot(2,90.0*radd-B,pos);//zamiana na wspolrzedne horyzontalne

rot(3,-180.0*radd,pos);

J=asin(pos[2]);//a teraz J jest to wysokosc slonca;)

printf("wysokos slonca: ");
zam(J,1);

    //wnioski ostateczne



if(J<-(42/60.0)*radd&&J>-(6+42/60.0)*radd)

puts("panuje biała noc cywilna\n");

else if(J<-(6+42/60.0)*radd&&J>-(12+42/60.0)*radd)

puts("panuje biała noc żeglarska\n");

else if(J<-(12+42/60.0)*radd&&J>-(18+42/60.0)*radd)

puts("panuje biała noc astronomiczna\n");

else if(J<-(18+42/60.0)*radd)

puts("panuje noc astronomiczna\n");

else

puts("jest dzień\n");

return 0;

}



void rot(int os, double kat, double V[3])//kawalek programu z 2 roku, dziala i to

{//sie liczy, transformacja macierzowa mozna zamieniac wszytsko na wszytsko

int i,j;

double m,c,s,b[3][3],q[3];

c=cos(kat);

s=sin(kat);

if(os==1)//p

{

b[0][0]=1;

b[0][1]=0;

b[0][2]=0;

b[1][0]=0;

b[1][1]=c;

b[1][2]=s;

b[2][0]=0;

b[2][1]=-s;

b[2][2]=c;

}

else if(os==2)//q

{

b[0][0]=c;

b[0][1]=0;

b[0][2]=-s;

b[1][0]=0;

b[1][1]=1;

b[1][2]=0;

b[2][0]=s;

b[2][1]=0;

b[2][2]=c;

}

else if(os==3)//r

{

b[0][0]=c;

b[0][1]=s;

b[0][2]=0;

b[1][0]=-s;

b[1][1]=c;

b[1][2]=0;

b[2][0]=0;

b[2][1]=0;

b[2][2]=1;

}

else if(os==4)//My

{

b[0][0]=1;

b[0][1]=0;

b[0][2]=0;

b[1][0]=0;

b[1][1]=-1;

b[1][2]=0;

b[2][0]=0;

b[2][1]=0;

b[2][2]=1;

}

else if(os==5)//Mx

{

b[0][0]=-1;

b[0][1]=0;

b[0][2]=0;

b[1][0]=0;

b[1][1]=1;

b[1][2]=0;

b[2][0]=0;

b[2][1]=0;

b[2][2]=1;

}



for(i=0;i<3;++i)

{

m=0;

for(j=0;j<3;++j)//po wybraniu osi mnozymy ja w petli przez nasze wspolrzedne

m=V[j]*b[i][j]+m;//mnozenie maciezy wiec trzeba dodac poprzedni wynik

q[i]=m;//a tu zapisuje gotowy wynik po dodaniu

  }

  for(i=0;i<3;++i)

  V[i]=q[i];//przepisanie otrzymanych wynikow do wyjsciowego V

return;

}

double zam(double E,int a) //zamiana z radianow na stopnie (godziny), minuty i sekundy z ulamkiem

{

int d,m; //d-stopnie (godziny), m-minuty

double s,n,radd,radh; //s-sekundy, n-minuty z ulamkiem, rad-radiany

radd=M_PI/180.0;

radh=M_PI/12;

if (a==1) E/=radd;//tu zamiana na stopnie

else if (a==2) E/=radh;//tu na godziny

else;

if (E>=0.0)//zamiana dodatnich wartości

{

d=floor(E);

    n=(E-d)*60.0;

   m=floor(n);

    s=((n-m)*60.0);

}

else//a tu zamiana niedodatmich wartości

{

d=ceil(E);

    n=(-(E-d)*60.0);

    m=floor(n);

    s=(n-m)*60.0;

}

printf("%+d %d %.14f\n",d,m,s);

return 0.0;

}
