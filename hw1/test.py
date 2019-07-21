import numpy as np
import pandas as pd
import time


def insert_sort(a):
    '''
    Algoritmo insertion sort para ordenar elementos em uma lista
    '''
    for i in range(len(a)):
        cur_value = a[i]
        
        j = i-1
        while j>=0 and a[j] > cur_value:
            a[j+1] = a[j]
            j = j-1
        
        a[j+1] = cur_value
        
    return a


def merge(A,B):
    '''
    Agrupa duas listas (arrays) - Usada no algoritmo mergesort
    '''
    result = []
    
    while len(A)>0 and len(B)>0:
        if A[0] < B[0]:
            result.append(A[0])
            A.pop(0)
        else:
            result.append(B[0])
            B.pop(0)        
    result.extend(A)
    result.extend(B)
    
    return result    


def merge_sort(a):
    '''
    Algoritmo Mergesort para ordenar elementos em uma lista.
    '''
    if len(a) <= 1:
        return a
    else:
        half = int(len(a)/2)
        left = a[:half]
        right = a[half:]
        
    return merge(merge_sort(left), merge_sort(right))  


def random_partition(B,p,r):
    # elem. aleatório
    i = np.random.randint(p,r)
    
    # Troca de lugar os termos A[r] e A[i]
    temp = B[i]
    B[i] = B[r]
    B[r] = temp
    
    return partition(B,p,r)



def partition(B,p=0,r=-1):
    '''
    Particiona o vetor (obs: sempre escolhe o último elemento como pivô)
    '''
    x = B[r]
    i = p-1
    
    for j in range(p,r):
        if B[j]<=x:
            i += 1
            temp = B[i]
            B[i] = B[j]
            B[j] = temp
    
    temp2 = B[i+1]
    B[i+1] = x
    B[r] = temp2
        
    return i+1

def quicksort(A, p=0, r=-1):
    '''
    Algoritmo quicksort (usa o último elemento da lista como pivô)
    
    OBS: No python, essa função apresenta um problema de recursão
    ** RecursionError: maximum recursion depth exceeded **
    para vetores com número de elementos igual ou superior a 10 mil.
    
    Recomendo o uso dessa função apenas para vetores pequenos. 
    
    Esperançosamente, uma correção para esse problema sairá na próxima versão.
    '''
    if r == -1:
        r = len(A)-1
        
    if len(A)<=1:
        # A já está trivialmente ordenada
        return A
    if p<r:
        q = partition(A,p,r)
        quicksort(A,p,q-1)
        quicksort(A,q+1,r)
    
    return A


def randomized_quicksort(A, p=0, r=-1):
    '''
    Algoritmo quicksort com pivô aleatório.
    '''
    if r == -1:
        r = len(A)-1
    
    if p<r:
        q = random_partition(A,p,r)
        randomized_quicksort(A,p,q-1)
        randomized_quicksort(A,q+1,r)
    
    return A
    
    
    
def is_sorted(a):
    '''
    Checa se a lista (array) está ordenada.
    '''
    n = len(a)
    
    for i in range(0,n-1):
        if a[i] > a[i+1]:
            return False
        
    return True




def main():    
    
    for k in range(0,3):

        # Definindo o tipo de vetor que vai ser criado
        if k == 0:
            tipo = 'random order'
            # criando vetores aleatórios
            ns = [list(np.random.randint(1, 1000, 10000*i)) for i in range(1,11)]
            
        elif k == 1:
            tipo = 'ascending order'
            ns = [list(np.linspace(1,10000*i,10000*i, dtype=int)) for i in range(1,11)]
            
        elif k == 2:
            tipo = 'descending order'
            ns = [list(np.linspace(10000*i,1,10000*i, dtype=int)) for i in range(1,11)]
    
        # Nome do arquivo .csv
        file_name = "py_outputs_" + tipo + ".csv"
        
        # Nome das colunas
        col_names = ['size','py_insert_sort','py_merge_sort','py_quick_sort','py_random_quick_sort']
        
        # Dataframe com os tempos
        df = pd.DataFrame(index=col_names)
        
        
        # Comparando tempo de execução dos algoritmos
        print('\nTesting algorithms with vectors in {}'.format(tipo))
        print('n     |  insert  |   merge   |  quick  | rd_quick')
        
        count = 1 # contando índice para o dataframe
        for a in ns:
            # create and fill an array with random numbers
            # a = ...

            # call insert_sort and  calculate the time
            start = time.time()
            sorted_a = insert_sort(a.copy())
            end = time.time()
            t1 = end - start
            if not is_sorted(sorted_a):
                print("ERROR")

            # call merge_sort and  calculate the time
            start = time.time()
            sorted_a = merge_sort(a.copy())
            end = time.time()
            t2 = end - start
            if not is_sorted(sorted_a):
                print("ERROR")

            # call quicksort and  calculate the time
            start = time.time()
            try: 
                sorted_a = quicksort(a.copy())
                end = time.time()
                t3 = end - start
                if not is_sorted(sorted_a):
                    print("ERROR")
            
            # Recursion Error exception
            except RecursionError as re:
                #print('Sorry but quicksort with fixed pivot was unable to finish.')
                t3 = np.NAN
            
                
            # call randomized_quicksort and  calculate the time
            start = time.time()
            sorted_a = randomized_quicksort(a.copy())
            end = time.time()
            t4 = end - start
            if not is_sorted(sorted_a):
                print("ERROR")

            n = int(len(a))
            print("%d | %f | %f  | %f | %f" % (n,t1, t2, t3,t4))  # n = nº de elementos na lista
            
            # armazenando os tempos no dataframe
            df[count] = pd.Series([n,t1, t2, t3,t4], index=col_names)
            
            # avança o índice
            count += 1
        
        df.transpose().to_csv(file_name, sep=',', encoding='utf-8', index=False)
            


if __name__ == "__main__":
    main()
