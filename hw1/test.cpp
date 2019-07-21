#include <iostream>
#include <vector>
#include <bits/stdc++.h> 
#include <fstream>
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

// Random Partition
int random_partition(vector <int> &A, int p, int r){
    // OBS: Chame srand(time(NULL)) antes de executar essa função

    // random seed 
    // srand(time(NULL));
    int i = rand() % (r - p + 1) + p;

    // Troca de lugar os termos A[r] com A[i]
    int temp = A[i];
    A[i] = A[r];
    A[r] = temp;

    int result = partition(A,p,r);
    return result;
}


/* QuickSort */
void quicksort(vector <int> &v, int p = 0, int r = -1){
    // OBS: usa o último elemento do vetor como pivô
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

/* Randomized QuickSort */
void randomized_quicksort(vector <int> &v, int p=0, int r = -1){

    // Ajusta r para o tamanho real do vetor
    if (r == -1){
        r = v.size()-1;
    }
    int q;
    
    if (p<r) {
        q = random_partition(v,p,r);
        randomized_quicksort(v,p,q-1);
        randomized_quicksort(v,q+1,r);
    }
}

/* Checa se o vetor está ordenado */
bool is_sorted(vector <int> &v){
    bool result = true;
    for (int i = 0; i< v.size()-1; i++){
        if (v[i] > v[i+1]){
            result = false;
            break;
        }
    }
    return result;
}




/* Cria vetor com elementos aleatórios */
std::vector<int> GenerateRandomVector(int n_elem,int min, int max, int seed= 100) {
    // n_elem = nº de elementos do vetor (size)
    // min = valor mínimo
    // max = valor máximo
    // seed = fixa uma seed para sorteio dos números
    
    std::vector<int> randVec;
    int i = 0, randValue = 0;
    srand(seed);
    while (i < n_elem) {
        randValue = rand() % (max - min + 1) + min;
        randVec.push_back(randValue);
        i++;
    }
    // retorna para seed aleatória
    srand(time(NULL));
    return randVec;
}


/* Cria vetor com elementos em ordem ascendente ou descendente */
std::vector<int> GenerateVector(int n_elem = 0, int min=-1, int max=-1, string order="ascending") {
    // Função para criar um vetor em ordem crescente ou decrescente
    // USO: especifique valor máximo e mínimo (n_elem é definido automaticamente)
    //      OU especifique n_elem e um valor de partida (max ou min) 
    // ARGUMENTOS:
    // n_elem = nº de elementos do vetor (size)
    // min = valor mínimo
    // max = valor máximo
    // order = "ascending" (crescente) ou  "descending" (decrescente)

    std::vector <int> vec; 
  
    if (n_elem == 0){ 
        n_elem = max-min+1;

        if (order == "ascending"){
            int i = 0;
            while (i < n_elem) {
                int value = min+i;
                vec.push_back(value);
                i++;
            }
        }
        if (order == "descending"){
            int i = 0;
            while (i < n_elem) {
                int value = max-i;
                vec.push_back(value);
                i++;
            }
        }
        n_elem = 0;
    }

    if (n_elem != 0 && min != -1){ 

        if (order == "ascending"){
            int i = 0;
            while (i < n_elem) {
                int value = min+i;
                vec.push_back(value);
                i++;
            }
        }
        if (order == "descending"){
            max = min + n_elem - 1;
            int i = 0;
            while (i < n_elem) {
                int value = max-i;
                vec.push_back(value);
                i++;
            }
        }
        max = -1;
    }

    if (n_elem != 0 && max != -1){ 

        if (order == "ascending"){
            min = max - n_elem + 1;
            int i = 0;
            while (i < n_elem) {
                int value = min+i;
                vec.push_back(value);
                i++;
            }
        }
        if (order == "descending"){
            int i = 0;
            while (i < n_elem) {
                int value = max-i;
                vec.push_back(value);
                i++;
            }
        }
        min = -1;
    }
    return vec;
}
/*END*/


int main(){
	// Inicializando variáveis
    vector<int> v; 
    vector<int> rdVec;
    clock_t start;  
    clock_t end;
    stringstream ss;
    string file_name;
    string tipo;
    double t1;
    double t2;
    double t3;
    double t4;

    // inicializa a seed para nºs aleatórios
    srand(time(NULL));

    for (int k=0;k<=2; k++){

        // Definindo o tipo de vetor que vai ser criado
        if (k == 0) { tipo = "random order";}
        if (k == 1) { tipo = "ascending order";}
        if (k == 2) { tipo = "descending order";}

        // Nome do arquivo .csv 
        ss.str("");
        ss.clear();
        ss << "cpp_outputs_"<< tipo << ".csv";
        file_name = ss.str();
        ofstream out (file_name);

        // Nome das colunas
        out << "size,cpp_insert_sort,cpp_merge_sort,cpp_quick_sort,cpp_random_quick_sort\n";

        /* Comparando tempo de execução dos algoritmos */
        cout << "\nTesting algorithms with vectors in " << tipo << endl;
        cout << "n     |  insert  |  merge  |  quick  | rd_quick" << endl;
        for (int i=1; i<=10; i++){
            int size = 10000*i;  // define o tamanho do vetor a cada iteração em i

            out << size << ",";
            /* InsertionSort */
            if (k == 0) {v = GenerateRandomVector(size,1,1000, 100+i);}
            if (k == 1) {v = GenerateVector(size,1,-1, "ascending");}
            if (k == 2) {v = GenerateVector(size,-1,size, "descending");}

            start = clock();
            insert_sort(v);
            end = clock();

            t1 = double(end - start)/double(CLOCKS_PER_SEC);  // tempo do insertion sort
            out << t1 << ","; // exportando para o .csv

            // checa se o vetor está ordenado
            if (is_sorted(v) == false){
                cout << "OOOPS, VECTOR IS NOT SORTED! (insert)" << endl;
            }

            /* MergeSort */
            if (k == 0) {v = GenerateRandomVector(size,1,1000, 100+i);}
            if (k == 1) {v = GenerateVector(size,1,-1, "ascending");}
            if (k == 2) {v = GenerateVector(size,-1,size, "descending");}
            
            start = clock();
            v = merge_sort(v);
            end = clock();

            t2 = double(end - start)/double(CLOCKS_PER_SEC);  // tempo do insertion sort
            out << t2 << ",";
            // checa se o vetor está ordenado
            if (is_sorted(v) == false){
                cout << "OOOPS, VECTOR IS NOT SORTED! (merge)" << endl;
            }


            /* QuickSort */
            if (k == 0) {v = GenerateRandomVector(size,1,1000, 100+i);}
            if (k == 1) {v = GenerateVector(size,1,-1, "ascending");}
            if (k == 2) {v = GenerateVector(size,-1,size, "descending");}

            start = clock();
            quicksort(v);
            end = clock();

            t3 = double(end - start)/double(CLOCKS_PER_SEC);  // tempo do insertion sort
            out << t3 << ","; // exporta pro csv

            // checa se o vetor está ordenado
            if (is_sorted(v) == false){
                cout << "OOOPS, VECTOR IS NOT SORTED! (quick)" << endl;
            }

            /* Randomized QuickSort */
            if (k == 0) {v = GenerateRandomVector(size,1,1000, 100+i);}
            if (k == 1) {v = GenerateVector(size,1,-1, "ascending");}
            if (k == 2) {v = GenerateVector(size,-1,size, "descending");}

            start = clock();
            randomized_quicksort(v);
            end = clock();

            t4 = double(end - start)/double(CLOCKS_PER_SEC);  // tempo do insertion sort
            out << t4 << endl; // exporta pro csv

            // checa se o vetor está ordenado
            if (is_sorted(v) == false){
                cout << "OOOPS, VECTOR IS NOT SORTED! (rd_quick)" << endl;
            }

            // Exibe resultados na tela a cada iteração no tamanho do vetor
            cout << size << " | ";
            cout << fixed << t1 << setprecision(5) << " | ";
            cout << fixed << t2 << setprecision(5) << " | ";  
            cout << fixed << t3 << setprecision(5) << " | ";  
            cout << fixed << t4 << setprecision(5) << endl;
        }
        out.close();
    } 
    return 0;
}
