/////////////////////////////////////////////////////////////////
//This code is logically correct.
/////////////////////////////////////////////////////////////////
int[]sens = new int[8];
int cte =0;
int lastcte =0;
int totcte=0;
int power =0;
double kp=14.2857, ki=0,kd=0;
void setup()  
{
}
void loop()
{
    readSens();
    calcCte();
    lcd("%d",cte);
    power = (int)(kp*(double)cte + ki*(double)(totcte) + kd*(double)(cte - lastcte));
    if(power>0)
    {
        motor(1,100+power);
        motor(2,-power);
    }  
    else if(power<0)
    {
        motor(1,power);
        motor(2,100-power);
    }
    else
    {
        motor(1,100);
        motor(2,100);
    }
    lastcte = cte;
    totcte +=cte;
    lcd(" ");
}

void calcCte()
{
    int lcte =0, rcte=0;
    int i=0;
    while(sens[i] != 0)
    {
        lcte = lcte+sens[i];
        i++;
        if(i==8)
        {
            break;
        }
    }
    i=7;
    while(sens[i] != 0)
    {
        rcte = rcte+sens[i];
        i--;
        if(i==-1)
        {
            break;
        }
        
    }
    cte =(int)((lcte-rcte));
}

void readSens()
{
    for(int i=0; i<8;i++)
    {
        int res = analog(i);
        if(res>=512 && res<=1024)
        {
            sens[i] = 1;
        }
        else
        {
            sens[i] = 0;
        }
    }
}