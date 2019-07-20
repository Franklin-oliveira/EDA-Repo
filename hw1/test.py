import numpy as np
import time

def insert_sort(a):
    '''
    Algoritmo insertion sort para ordenar elementos em uma lista
    '''
    for i in range(len(A)):
        cur_value = A[i]
        
        j = i-1
        while j>=0 and A[j] > cur_value:
            A[j+1] = A[j]
            j = j-1
        
        A[j+1] = cur_value
        
    return A


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


def partition(B,p=0,r=-1):
    '''
    Particiona uma lista a partir de um elemento na r-ésima posição da lista B. 
    '''
    if r == -1:
        r = len(A)-1
     
    x = B[r]
    i = p-1
    
    if len(B) <= 1:
        return B
    
    for j in range(p,r):
        if B[j]<=x:
            i = i+1
            y = B[i]
            B[i] = B[j]
            B[j] = y
    
    B[r] = B[i+1]
    B[i+1] = x
    
    return i+1


def quicksort(A, p=0, r=-1):
    '''
    Algoritmo quicksort para ordenar elementos em uma lista (necessita da função partition)
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


def is_sorted(a):
    '''
    Checa se uma lista está ordenada.
    '''
    
    n = len(a)
    
    for i in range(0,n):
        if a[i] > a[i+1]:
            return False
               
    return True



def main():
    ns = [list(np.random.randint(10000, 100000, 1000**i)) for i in range(1,15)] # list of lists to sort
    
    print('n | t1 | t2 | t3')
    
    # iterates over every element (list) of the list ns 
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
        sorted_a = quicksort(a.copy())
        end = time.time()
        t3 = end - start
        if not is_sorted(sorted_a):
            print("ERROR")

        n = len(a)
        print("%d | %f | %f  | %f" % (n,t1, t2, t3))


if __name__ == "__main__":
    main()
