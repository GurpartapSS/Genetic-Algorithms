#include<iostream>
#include<stdlib.h>
#include<math.h>
#include<algorithm>
#include<time.h>
#include<numeric>
#define PI 3.14159265
#define populationsize 1000
#define GenerationNum 100
#define Xhigh 12.0
#define Yhigh 6.0
#define Mutationrate 0.3
#include <cmath>
#define dynamicWindow 1.0

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
    pop * selectionCri(pop*np,int n,int limit)
    {
        pop* tempp = np;
        for(int i =0;i<n;i++)
        {
            np[i] = tempp[limit-i];
        }
        return tempp;
    }

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

float Popaverage(pop* arr)
{
    float total = 0.0;
    for(int i =0;i<populationsize;i++)
    {
        total = total+arr[i].popValue;
    }
    float avg = total/populationsize;
    return avg;
}

std::pair<float, float> calculateMean(float data[2][GenerationNum],int n)
{
    float meanav=0.0;
    float meanmax = 0.0;
    float totalav=0.0;
    float totalmax = 0.0;
    for(int i =0;i<n;i++)
    {
        totalav = totalav+data[0][i];
        totalmax = totalmax + data[1][i];
    }
    meanav = totalav/n;
    meanmax = totalmax/n;
    return std::make_pair(meanav,meanmax);
}

std::pair<float, float> calculateSD(float data[2][GenerationNum],int n)
{
    float sumav = 0.0,summax=0.0, meanav,meanmax, standardDeviation[2] = {0.0,0.0};
    int i;
    for(i = 0; i < n; ++i)
    {
        sumav += data[0][i];
        summax += data[1][i];
    }
    meanav = sumav/n;
    meanmax = summax/n;
    for(i = 0; i < n; ++i)
    {
     standardDeviation[0] += pow(data[0][i] - meanav, 2);
        standardDeviation[1] += pow(data[1][i]- meanmax,2);
    }
    return std::make_pair(sqrt(standardDeviation[0] / n),sqrt(standardDeviation[1] / n));
}

int main()
{
    srand (time(NULL));
    //Initialise Population
    InitPopulation popul;

    pop * noam = new pop[populationsize];
    //test allocation
    noam = popul.getPopulation();
    //calculating function values
    claCfunction cal;
    cal.setPopulation(noam);
    pop * populationVal = cal.returnFuntion();
    int genNumber =0;
    float AverageFitness = 0.0;
    //float dw = dynamicWindow;  //Dynamic window
    int GenerationLimit = GenerationNum;
   // int MutationNum = std::ceil(dw*Mutationrate * populationsize); //Dynamic window
    int MutationNum = Mutationrate * populationsize;
    int CrossOverNum = populationsize - MutationNum;
    float analysis[2][GenerationNum] = {};
    pop temp;
    reproduce rep;

    while(GenerationLimit>0)
    {
        //Dynamic Window
        /*if(GenerationLimit%10==0&&dw!=1.0)
        {
                MutationNum = std::ceil(dw*Mutationrate * populationsize);
                CrossOverNum = populationsize - MutationNum;
                dw=dw-0.03;
                if(dw<=0.0)
                {
                    dw=0.0;
                }
        }*/
        for(int i =0;i<1000;i++)
        {
            int p1 = (populationsize-MutationNum-1)+(rand()%MutationNum);
            int p2 = (populationsize-MutationNum-1)+(rand()%MutationNum);
            noam[i] = rep.crossover(populationVal[p1],populationVal[p2]);
        }

        //to enable selection criterea change CrossOverNum in line 181 to a larger number, lesser than populationsize and set same values at
        //code line 191 in limit for the "for loop"
        //code line 203 in (noam,CrossOverNum,**here**);
        cal.setPopulation(noam);
        noam = cal.returnFuntion();
        noam = rep.selectionCri(noam,CrossOverNum,1000);
        // ends here

        pop* mutPop = rep.mutation(MutationNum);
        for(int i=0;i<MutationNum;i++)
        {
            noam[CrossOverNum+i]=mutPop[i];
        }
        delete [] mutPop;
        cal.setPopulation(noam);
        populationVal = cal.returnFuntion();
        temp = populationVal[populationsize-1];

        AverageFitness = Popaverage(populationVal);
        genNumber = GenerationNum-GenerationLimit;
        analysis[0][genNumber]=AverageFitness;
        analysis[1][genNumber]=temp.popValue;
        std::cout << "Generation#: " << genNumber <<std::endl;
        std::cout << "\tMax value: " << temp.popValue<<std::endl;
        std::cout << "\tMeanvalue: " << AverageFitness<<std::endl;
        GenerationLimit--;
    }

    std::pair<float,float> sd_d= calculateSD(analysis,GenerationNum);
    std::pair<float,float> mean_m = calculateMean(analysis,GenerationNum);


    std::cout<<"Points for max value: " << "\nx1: " << temp.popX << "\nx2: " << temp.popY << "\nValue: "<<temp.popValue<< std::endl;
    std::cout<<"Standard Deviation for Average Fitness: " << sd_d.first << std::endl;
    std::cout<<"Mean for Average Fitness: " << mean_m.first<< std::endl;
    std::cout<<"Standard Deviation for Highest Fitness: " << sd_d.second<< std::endl;
    std::cout<<"Mean for Highest Fitness: " << mean_m.second << std::endl;


    delete [] noam;
    delete [] populationVal;
    char t;
    std::cout << "Enter a CHAR and hit enter to exit ";
    std::cin >> t;
    return 0;
}

