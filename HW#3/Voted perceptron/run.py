import numpy as np
from io import StringIO
def prediction1(vectors, weight, testnum, k):
    s=0
    
    for i in range(k):
        if (np.sum(vectors[i]*testnum))<0:
            s-= weight[i]
        else:
            s+= weight[i]
    if s>0:
        return 1
    else:
        return 0

def run(Xtrain_file, Ytrain_file, pred_file):
    #test_data = np.genfromtxt(test_data_file, delimiter=",")
    train_data = np.genfromtxt(Xtrain_file, delimiter=",")
    train_data_result = np.genfromtxt(Ytrain_file, delimiter=",")
    #y is either -1 or 1; x is a long as vector so 
    #first num row second cols
    [num1, num2] = train_data.shape
    test_data = []
    
    for  i in range(((num1)-(int(num1*.1))),num1):
        test_data.append(train_data[i])
    y= train_data_result
    w= [0]*num2
    #w = np.array([0]*num2)
    c = [0]
    t=0
    T=10
    k=0
    while(t<T):
        
        for i in range(int(len(train_data)*.18)) :
            if((np.sum(w[k]*train_data[i]))>=0):
                q=1
            else:
                q=0
            if q==y[i]:
                c[k]+=1
            else:
                #for L in range(num2):
                if y[i]==0:
                    newarray= ((w[k]) + (-1*train_data[i]))
                else:
                    newarray= ((w[k]) + (y[i]*train_data[i]))
                
                w=np.vstack((w,newarray))
                #w[k+1]= (w[k]) + (y[i]*train_data[i])
                c.append(1)
                
                k +=1
        t+=1
        
    
    prediction = np.zeros((len(test_data), 1), dtype=np.int16)
    for j in range(len(test_data)):
        prediction[j] = prediction1(w,c,test_data[j],k)
        
    np.savetxt(pred_file, prediction, fmt='%1d', delimiter=",")
# uncomment for coda lab
#if __name__ == "__main__":
#    Xtrain_file = './ref/Xtrain.csv'
#    Ytrain_file = './ref/Ytrain.csv'
#    test_data_file = './ref/Xtest.csv'
#    pred_file = './res/prediction.csv'
#    run(Xtrain_file,Ytrain_file,test_data_file,pred_file)
if __name__ == "__main__":
    Xtrain_file = 'Xtrain.csv'
    Ytrain_file = 'Ytrain.csv'
    #bullshit = np.genfromtxt(Xtrain_file, delimiter=",")
    #[fuck, this] = bullshit.shape
    #for  i in range((fuck*.1),fuck):
     #   np.savetext('./ref/Xtest.csv', bullshit[i], fmt='%1d', delimiter=",")
    #test_data_file = './ref/Xtest.csv'
    pred_file = 'prediction5.csv'
    run(Xtrain_file,Ytrain_file,pred_file)





