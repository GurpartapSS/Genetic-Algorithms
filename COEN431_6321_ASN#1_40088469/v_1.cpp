#include<iostream>
#include<stdlib.h>
#include<math.h>
#include<algorithm>
#include<time.h>
#define PI 3.14159265
#define populationsize 1000
#define Xhigh 12.0
#define Yhigh 6.0
#define Mutationrate 0.2

struct pop
{
    float popX;
    float popY;
    float popValue;
};

class InitPopulation
{
    public:
    pop* getPopulation()
    {
        //pop * popI = (pop*)(malloc(sizeof(struct pop)));
        pop *popI = new pop[populationsize];
        for (int i = 0; i < populationsize; i++)
        {
            popI[i].popX = -Xhigh + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(Xhigh)));
            popI[i].popY = -Yhigh+ static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(Yhigh)));
            popI[i].popValue = 0;
        }
        return popI;
    }
//private:
  //  int populationSize = populationsize;
};

class claCfunction
{
public:
    pop *popV = new pop[populationsize];
    void setPopulation(pop * v)
    {
        popV = v;
    }
    pop * returnFuntion()
    {
        for(int i=0;i<populationsize;i++)
        {
            x = popV[i].popX;
            y = popV[i].popY;
            popV[i].popValue= 21.5 + (x*sin(4*PI*x))+(y*sin(20*PI*y));
        }
        bubbleSort(popV);
        return popV;
       // return sortVal(popV);
    }

    void bubbleSort(pop* arr)
{
    int i, j;
    for (i = 0; i < populationsize-1; i++)

    // Last i elements are already in place
    for (j = 0; j < populationsize-i-1; j++)
        if (arr[j].popValue > arr[j+1].popValue)
            swap(&arr[j], &arr[j+1]);
}

    void swap(pop *xp, pop *yp)
    {
    pop temp = *xp;
    *xp = *yp;
    *yp = temp;
    }
private:
    pop* Population();
    float x;
    float y;
    bool myfunction (pop d,pop e) { return (d.popValue < e.popValue); }
};

class reproduce
{
public:
    pop crossover(pop parent1,pop parent2)
    {
        pop child;
        child.popX = parent1.popX;
        child.popY = parent2.popY;
        child.popValue = 0.0;
        return child;
    }
    pop * mutation(int mutationNumber)
    {
        pop* popMut= new pop[mutationNumber];
        for (int i = 0; i < mutationNumber; i++)
        {
            popMut[i].popX = -Xhigh + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(Xhigh)));
            popMut[i].popY = -Yhigh+ static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(Yhigh)));
            popMut[i].popValue = 0;
        }
        return popMut;
    }
private:
    pop* parent1;
    pop* parent2;
    int mutationNumber;
};
int main()
{
    srand (time(NULL));
    //Initialise Population
    InitPopulation popul;
    //pop * noam = (pop*)(malloc(sizeof(struct pop)));
    pop * noam = new pop[populationsize];
    //test allocation
    noam = popul.getPopulation();
    //calculating function values
    claCfunction cal;
    cal.setPopulation(noam);
    pop * populationVal = cal.returnFuntion();
    //get highest ranked value and save for comparision

    //delete [] populationVal;
    //pop min1 = populationVal[0];
    //pop min2;
    //min2.popValue=0.0;
    int GenerationLimit = 20;
    //float delta = min1.popValue - min2.popValue;
    int MutationNum = Mutationrate * populationsize;
    int CrossOverNum = populationsize - MutationNum;GenerationLimit;
    pop temp;
    //pop *chr = new pop[populationsize];
    reproduce rep;
    while(GenerationLimit>0)
    {

        for(int i =0;i<CrossOverNum;i++)
        {
            int p1 = rand()%90;
            int p2 = rand()%90;
            noam[i] = rep.crossover(populationVal[p1],populationVal[p2]);
        }
        pop* mutPop = rep.mutation(MutationNum);
        for(int i=0;i<MutationNum;i++)
        {
            noam[CrossOverNum+i]=mutPop[i];
        }
        delete [] mutPop;
        cal.setPopulation(noam);
        populationVal = cal.returnFuntion();
        temp = populationVal[populationsize-1];
        int genNumber = 20-GenerationLimit;
        std::cout << "Generation#: " << genNumber <<std::endl;
        std::cout << "\tMax value: " << temp.popValue<<std::endl;
        GenerationLimit--;
    }
    delete [] noam;
    delete [] populationVal;
    return 0;
}

