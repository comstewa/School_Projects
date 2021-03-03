import numpy as np
from io import StringIO
def KNN(train, test, k):# 
    ItoD= []
    for i in range(len(train)):
        temp=0
        for q in range(len(train[0])):
            temp+=(((train[i][q])-test[q])**2)
        temp= (temp**(1/2))
        if len(ItoD)<k:
            addit=0
            for y in range(len(ItoD)):
                if temp <ItoD[y][1]:
                    ItoD.insert(y,[i,temp])
                    addit=1
                    break
            if addit ==0:
                ItoD.append([i,temp])
        else:
            for t in range(k):
                if temp<ItoD[t][1]:
                    ItoD.insert(t,[i,temp])
                    ItoD.pop()
                    break
    
    return ItoD
def howManyLabel(ItoD, TrainResults):
    maxI=0
    maxsum=0
    howmany = [0]*11
    for i in range(len(ItoD)):
        howmany[int(TrainResults[int(ItoD[i][0])])]+=1
    for v in range(len(howmany)):
        if howmany[v]> maxsum:
            maxsum= howmany[v]
            maxI=v
        elif (howmany[v]==maxsum and maxsum!=0):

            for i in range(len(ItoD)):
                if int(TrainResults[int(ItoD[i][0])])==v:
                    if int(TrainResults[int(ItoD[i+1][0])])==maxI:
                        break
                    maxI= v
                    maxsum= howmany[v]
                elif int(TrainResults[int(ItoD[i][0])])==maxI:
                    break
    return maxI

def run(Xtrain_file, Ytrain_file,test_data_file, pred_file):
    test_data = np.genfromtxt(test_data_file, delimiter=",")
    train_data = np.genfromtxt(Xtrain_file, delimiter=",")
    train_data_result = np.genfromtxt(Ytrain_file, delimiter=",")
    [row1, col1] = train_data.shape
    [row2, col2] = test_data.shape
    k= int(row1**(1/2))
    #labels can be 0-10
    
    prediction = np.zeros((len(test_data), 1), dtype=np.int16)
    for i in range(row2):
        indexs=KNN(train_data,test_data[i],k)
        prediction[i]= howManyLabel(indexs, train_data_result)
        

    np.savetxt(pred_file, prediction, fmt='%1d', delimiter=",")

    
if __name__ == "__main__":
    Xtrain_file = './ref/Xtrain.csv'
    Ytrain_file = './ref/Ytrain.csv'
    test_data_file = './ref/Xtest.csv'
    pred_file = './res/prediction.csv'
    run(Xtrain_file,Ytrain_file,test_data_file,pred_file)
#if __name__ == "__main__":
#    Xtrain_file = 'Xtrain.csv'
#    Ytrain_file = 'Ytrain.csv'
#    test_data_file = 'Xtest.csv'
#    pred_file = 'prediction.csv'
#    run(Xtrain_file,Ytrain_file,test_data_file,pred_file)