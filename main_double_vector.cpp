#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <cmath>
#include "double_vector.h"
#include "distance.h"

using namespace std;

int main() {
    vector<double_vector> my_double_vectors;
    vector<my_distance> all_pairs_distances;

    ifstream in_file("vectors_2D.txt");
    double from, to;

    while (in_file >> from >> to) {
        my_double_vectors.push_back(double_vector(from, to));
    }
    in_file.close();

    int size = my_double_vectors.size();

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (i != j) {
                my_distance dist(i, j, cosine_distance(my_double_vectors[i], my_double_vectors[j]));
                all_pairs_distances.push_back(dist);
            }
        }
    }

    sort(all_pairs_distances.begin(), all_pairs_distances.end(),
         [](const my_distance & left, const my_distance & right) {
            return left.cos_distance < right.cos_distance;
         });

    for (auto & dist : all_pairs_distances) {
        cout << dist.id_1 << " " << dist.id_2 << " cos dist = " << dist.cos_distance << endl;
    }

    return 0;
}

