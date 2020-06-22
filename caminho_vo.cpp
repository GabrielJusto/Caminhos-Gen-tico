/**************************************************
Gabriel Bonatto Justo, gabriel.justo@acad.pucrs.br

Compilar: g++ caminho_vo.cpp -o caminho_vo
rodar: ./caminhos_vo <nome do arquivo>

**************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <set>
#include <cmath>
#include <time.h>
#include <vector>

using namespace std;

struct City
{
    float x,y;
    int city_number;

    friend bool operator == (City a, City b)
    {
        if(a.city_number == b.city_number)
            return true;
        else 
            return false;
    }
    friend bool operator < (City a, City b)
    {
    if (a.city_number < b.city_number)
        return true;
    else
        return false;
    }
};


set<struct City> CITIES;
vector<struct City> CITIES_VEC;
int CITIES_NUMBER;
float min_dist;





void get_x_y(char* buff, float*x, float* y)
{
    char* aux = buff;
    char x_buff[255], y_buff[255];
    char* coord = x_buff;
    int count = 0;
    while(!isspace(*aux))
    {
        *coord = *aux;
        aux++;
        coord++;
        count ++;
    }
    coord = y_buff;
    *x = atof(x_buff);
    aux ++;
    while(!isspace(*aux))
    {
        *coord = *aux;
        aux++;
        coord++;
        count ++;
    }
    *y = atof(y_buff);

}




void readfile(char* name)
{
    FILE* data = fopen(name, "r");
   
    if(data == NULL)
   {
      printf("Error! \n");   
      exit(1);             
   }
    char aux_buff[255];
    fgets(aux_buff, 255, data);
    CITIES_NUMBER = atoi(aux_buff);


    struct City city;
    float x,y;
    for (int i = 0; i < CITIES_NUMBER; i++)
    {
        fgets(aux_buff, 255, data);
        get_x_y(aux_buff, &x, &y);

        city.city_number = i;
        city.x = x;
        city.y = y;
        CITIES.insert(city);//insere todas as cidades em um conjunto
    }

    fclose(data);
}


// gera a primeira população aleatoreamente
void first_population()
{
    srand( (unsigned)time(NULL) );
    set<struct City>::iterator it;
    struct City *aux_city = (struct City*) malloc(sizeof(struct City));
    int r;

    while (!CITIES.empty())
    {
        do
        {
            r = rand() % CITIES_NUMBER; // escolhe uma cidade aleatória
            aux_city -> city_number = r;
            it = CITIES.find(*aux_city);            
            
        } while (it == CITIES.end()); //verifica se a cidade está no conjusto de cidades não visitadas

        CITIES_VEC.push_back(*it);
        CITIES.erase(it);
    }
}   




float dist_calc(vector<struct City> vec)
{
    float dist = 0;
    for (int i = 0; i < vec.size()-1; i++) 
        dist += sqrt(pow((vec[i].x - vec[i+1].x),2) + pow((vec[i].y - vec[i+1].y),2));
    dist += sqrt(pow((vec[0].x - vec[vec.size()-1].x),2) + pow((vec[0].y - vec[vec.size()-1].y),2));

      
    return dist;
}


void next_gen(int mut)
{
    // srand( (unsigned)time(NULL));
    vector<struct City> new_vec (CITIES_VEC);
    int r;

    for (int i = 0; i < new_vec.size(); i++)
    {
        r = rand() % 101;
        if (r <= mut)   
        {
            r = rand() % new_vec.size();
            struct City aux = new_vec[r];
            new_vec[r] = new_vec[i];
            new_vec[i] = aux; 
        }        
    }




    float dist_new = dist_calc(new_vec);
    float dist_old = dist_calc(CITIES_VEC);

    if (dist_new < dist_old)
    {
        CITIES_VEC = new_vec;
        printf("Um caminho melhor foi encontrado com distância de: %f \n", dist_new);
    }
    

}

int main (int argc, char** argv)
{
    readfile(argv[1]);
    first_population();
    printf("dist: %f \n",dist_calc(CITIES_VEC));
    while (1)
    {
        next_gen(1);
    }
    
    
    // for (int i = 0; i < CITIES_VEC.size(); i++)
    // {
    //     printf("%d, ", CITIES_VEC[i].city_number);
    // }
    
    // printf("vec: %f \n",dist_calc(CITIES_VEC));
}

