#include <iostream>
#include <vector>
#include <bits/stdc++.h> 
using namespace std;

// // Função para printar na tela 
// criando template para o print
template<class T>
void print(vector<T> &v){
//	for (int i=0; i<v.size();i++){
//		cout <<v[i] << " ";
//	}
//	cout << endl;

	int i=0;
	while (i < v.size()){
		cout << v[i] << " ";
		i++;
	}
	cout << endl;
}


/* Insertion Sort */
void insert_sort(vector <int> &v){
    int cur_value;
    int j;

    for (int i=0; i<v.size(); i++){
        cur_value = v[i];
        j = i-1;

        while (j>=0 and v[j]>cur_value){
            v[j+1] = v[j];
            j = j-1;
        }
        v[j+1] = cur_value;
    }
};


/* Funções Auxiliares para o MergeSort */
// Merge (une dois vetores)
vector <int> merge(vector <int> &A, vector <int> &B){
    vector <int> result;

    while (A.size()>0 and B.size()>0){

        if (A[0] < B[0]){
            result.insert(result.end(),A[0]);
            A.erase(A.begin());
        }

        else {
            result.insert(result.end(),B[0]);
            B.erase(B.begin());
        }
    }

    result.insert(result.end(),A.begin(),A.end());
    result.insert(result.end(),B.begin(),B.end());

    return result;
};


// Função para fatiar vetores (slicing vectors)
vector<int> slice_vec(const vector<int>& v, int start=0, int end=-1) {
    int oldlen = v.size();
    int newlen;

    if (end == -1 or end >= oldlen){
        newlen = oldlen-start;
    } else {
        newlen = end-start;
    }

    vector<int> nv(newlen);

    for (int i=0; i<newlen; i++) {
        nv[i] = v[start+i];
    }
    return nv;
}


/* MergeSort */ 
vector  <int> merge_sort(vector <int> &a){
    int half;
    vector <int> left;
    vector <int> right;
    vector <int> left_sorted;
    vector <int> right_sorted;
    vector <int> result;

    if (a.size()<=1){
        return a;
    }
    else{
        half = a.size()/2;
        left = slice_vec(a,0, half);
        right = slice_vec(a,half,a.size());
    }
    
    left_sorted = merge_sort(left);
    right_sorted = merge_sort(right);
    result = merge(left_sorted, right_sorted);

    return result;
};


/* Função auxiliar para o QuickSort */
// Partition
int partition(vector <int> &B, int p, int r){
    int x;
    int y;
    int i;

    if (B.size()<=1){
        return B[0];
    }
    x = B[r];
    i = p-1;

    for (int j=p; j<r; j++){
        if (B[j]<=x){
            i = i+1;
            y = B[i];
            B[i] = B[j];
            B[j] = y;
        }
    }
    B[r] = B[i+1];
    B[i+1] = x;

    return i+1;
}

/* QuickSort */
void quicksort(vector <int> &v, int p = 0, int r = -1){
    
    // p = start
    // r = separator (default)
    // q = new separator (result from partition func.)
        
    // Ajusta r para o tamanho real do vetor
    if (r == -1){
        r = v.size()-1;
    }
    int q;
    
    if (p<r) {
        q = partition(v,p,r);
        quicksort(v,p,q-1);
        quicksort(v,q+1,r);
    }
};


/* Checa se o vetor está ordenado */
bool is_sorted(vector <int> &v){
    bool result = true;
    for (int i = 0; i< v.size(); i++){
        if (v[i] > v[i+1]){
            result = false;
            break;
        }
    }
    return result;
}


/* Cria vetor com elementos aleatórios */
std::vector<int> GenerateRandomVector(int n_elem,int min, int max, int seed = 101) {
    // n_elem = nº de elementos do vetor (size)
    // min = valor mínimo
    // max = valor máximo
    // seed = fixa uma seed para sorteio dos números
    
    std::vector<int> randVec;
    int i = 0, randValue = 0;
    //srand(time(NULL));
    srand(seed);
    while (i < n_elem) {
        randValue = rand() % (max - min + 1) + min;
        randVec.push_back(randValue);
        i++;
    }
    return randVec;
}


int main(){
	// Inicializando variáveis
    vector<int> v; 
    clock_t start;  
    clock_t end;
    float t1;
    double t2;
    double t3;


    cout << "n | t1 | t2 | t3" << endl;
    for (int i=1; i<=15; i++){
        int size = 1000*i;  // define o tamanho do vetor em cada loop

        /* InsertionSort */
        v = GenerateRandomVector(size,10000,100000, 100+i);
        start = clock();
        insert_sort(v);
        end = clock();

        t1 = double(end - start)/double(CLOCKS_PER_SEC);  // tempo do insertion sort

        // checa se o vetor está ordenado
        if (is_sorted(v) != false){
            cout << "OOOPS, VECTOR IS NOT SORTED! (insert)" << endl;
        }

        /* MergeSort */
        v = GenerateRandomVector(size,10000,100000, 100+i);
        start = clock();
        v = merge_sort(v);
        end = clock();

        t2 = double(end - start)/double(CLOCKS_PER_SEC);  // tempo do insertion sort

        // checa se o vetor está ordenado
        if (is_sorted(v) != false){
            cout << "OOOPS, VECTOR IS NOT SORTED! (merge)" << endl;
        }


        /* QuickSort */
        v = GenerateRandomVector(size,10000,100000, 100+i);
        start = clock();
        quicksort(v);
        end = clock();

        t3 = double(end - start)/double(CLOCKS_PER_SEC);  // tempo do insertion sort

        // checa se o vetor está ordenado
        if (is_sorted(v) != false){
            cout << "OOOPS, VECTOR IS NOT SORTED! (quick)" << endl;
        }


        cout << size << " | ";
        cout << fixed << t1 << setprecision(7) << " | ";
        cout << fixed << t2 << setprecision(7) << " | ";  
        cout << fixed << t3 << setprecision(7) << endl;
    }
    
    return 0;
}
