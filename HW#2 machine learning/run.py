# -*- coding: utf-8 -*-
import numpy as np


# This will be the code you will start with, note that the formate of the function 
# run (train_dir,test_dir,pred_file) and saving method can not be changed
# Feel free to change anything in the code

def run (train_input_dir,train_label_dir,test_input_dir,pred_file):
    # Reading data
    test_data = np.loadtxt(test_input_dir,skiprows=0)
    train_data = np.loadtxt(train_input_dir,skiprows=0)
    train_labes = np.loadtxt(train_label_dir,skiprows=0)
    [num, num2] = test_data.shape
    [var, var2] = train_data.shape

    prediction = np.zeros((num, 1), dtype=np.int16)

    #where my code starts
    averages = np.zeros((var2, 3), dtype=np.float32)   
    #Var = number of lines (x, y, z) in the data
    #Var2 = number of features (x1, y2, z3) 3 or 4 lol
    a = 0
    b = 0
    c = 0
   
    for x in range(var):
        for i in range(var2):
            #print(train_labes[x])
            averages[i, int(train_labes[x])] += train_data[x, i]
            
        if int(train_labes[x]) == 0:
            a += 1
        elif int(train_labes[x]) == 1:
            b += 1
        elif int(train_labes[x]) == 2:
            c += 1
    for r in range(var2):
        
        averages[r][0] = (averages[r][0])/a
        averages[r][1] = (averages[r][1])/b
        averages[r][2] = (averages[r][2])/c
    for q in range(num):
        temp1 = 0
        temp2 = 0
        temp3 = 0
        for L in range(num2):
            
            temp1 += ((averages[L][0] - test_data[q][L]) ** 2)
            temp2 += ((averages[L][1] - test_data[q][L]) ** 2)
            temp3 += ((averages[L][2] - test_data[q][L]) ** 2)
        temp1 = temp1 ** (1/2)
        
        temp2 = temp2 ** (1/2)
        temp3 = temp3 ** (1/2)
        
       
        if temp1 <= temp2:
            if temp1 <= temp3:
                prediction[q] = int(0)
            else:
                prediction[q] = int(2)
        elif temp2 < temp1:
            if temp2 <= temp3:
                prediction[q] = int(1)
            else:
                prediction[q] = int(2)
        

    # Creates a list containing 5 lists, each of 8 items, all set to 0
    
    

    # Saving you prediction to pred_file directory (Saving can't be changed)
    np.savetxt(pred_file, prediction, fmt='%1d', delimiter=",")
    
    
if __name__ == "__main__":
    train_input_dir = 'training2.txt'
    train_label_dir = 'training2_label.txt'
    test_input_dir = 'testing2.txt'
    pred_file = 'result2'
    run(train_input_dir,train_label_dir,test_input_dir,pred_file)
