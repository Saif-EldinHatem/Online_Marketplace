#include "Global.h"
#include "RatingSys.h"
#include "product.h"

void RatingSys::avg_ratings(product* p)
{
    float sum = 0.0;
    for (float rating : p->ratings) {
        sum += rating;
    }
    float average_rating = sum / p->ratings.size();

    cout << "Average rating: " << average_rating << endl;
    p->avg_rate = average_rating;
}

void RatingSys::sorAsc(int catIndex)
{
    int min;
    for (int i = 0; i < category_vector[catIndex].size() - 1; i++) {
        min = i;
        for (int j = i + 1; j < category_vector[catIndex].size(); j++) {
            if (category_vector[catIndex][j]->avg_rate < category_vector[catIndex][min]->avg_rate)
                min = j;
        }
        swapp(&category_vector[catIndex][i]->avg_rate, &category_vector[catIndex][min]->avg_rate);
    }

}

void RatingSys::sorDesc(int catIndex)
{
    int max;

    for (int i = 0; i < category_vector[catIndex].size() - 1; i++) {
        max = i;
        for (int j = i + 1; j < category_vector[catIndex].size(); j++) {
            if (category_vector[catIndex][j]->avg_rate > category_vector[catIndex][max]->avg_rate)
                max = j;
        }
        swapp(&category_vector[catIndex][i]->avg_rate, &category_vector[catIndex][max]->avg_rate);
    }
}

void RatingSys::swapp(float* first, float* second)
{
    float temp = *first;
    *first = *second;
    *second = temp;
}
