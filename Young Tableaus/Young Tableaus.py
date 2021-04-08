import math
import numpy as np

fin =  'D:\input.txt'
fout = 'D:\output.txt'


num_tables = 0
with open(fin) as f:
    num_tables = int(f.readline())   
    raw_data = f.read().split('\n')
    for i in range(num_tables):
        data = []
        while True:
            try:
                e = raw_data.pop(0)
                if e == '':
                    break
                else:
                    data.append(e)
            except:
                break
        
        if(data[0] == '1'):
            print("insert")
            insertValues = [int(ele) for ele in data[1].split(' ')]
            #build table
            table = [[int(ele) if ele != 'x' else math.inf for ele in row.split(' ')] 
                    for row in data[2:]]
            table = np.array(table)
           
            #insert value
            row = len(table)
            col = len(table[0])
            for val in insertValues:
                test_insert = False
                for i in range(row):
                    if test_insert == True:
                        break
                    for j in range(col):
                        if table[i][j] == np.inf:
                            table[i][j] =val
                            test_insert = True                            
                            break
            #sort
            for a in range(row-1,-1,-1):
                for b in range(col-1,-1,-1):
                    #row = 0 go left
                    if a == 0:
                        if b==0:
                            break
                        elif table[a][b-1] > table[a][b]:
                            temp = table[a][b]
                            table[a][b] = table[a][b-1]
                            table[a][b-1] = temp
                    #col = 0 go up
                    elif b == 0:
                        if table[a-1][b]> table[a][b]:
                            temp = table[a][b]
                            table[a][b] = table[a-1][b]
                            table[a-1][b] = temp
                    else:
                        #go up 
                        if table[a - 1][b] > table[a][b]:
                            if table[a - 1][b] > table[a][b - 1]:
                                temp = table[a][b]
                                table[a][b] = table[a - 1][b]
                                table[a - 1][b] = temp
        
                        #go left
                        if table[a][b - 1] > table[a][b]:
                            if table[a][b - 1] > table[a - 1][b]:
                                temp = table[a][b]
                                table[a][b] = table[a][b - 1]
                                table[a][b - 1] = temp  
            #write
            ref = ['Insert']
            for val in insertValues:
                ref.append(str(val))
            ref = ' '.join(ref)
            with open(fout, 'a') as f:
                f.write(ref)
                f.write('\n')
                for row in table:
                    for ele in row:
                        if not np.isinf(ele):
                            f.write(str(int(ele)))
                            f.write(' ')
                        else:
                            f.write('x')
                            f.write(' ')
                    f.write('\n')
                f.write(' ')
                f.write('\n')
                    
            
            
        elif(data[0] == '2'):
            print("extract")
            table = [[int(ele) if ele != 'x' else math.inf for ele in row.split(' ')]
                    for row in data[1:]]
            table = np.array(table)
            
            row = len(table)
            col = len(table[0])
            
            extract_min = table[0][0]
            down = False
            for i in range(row-1,-1,-1):
                if down == True:
                    break
                for j in range(col-1,-1,-1):
                    if table[i][j] != np.inf:
                        table[0][0] = table[i][j]
                        table[i][j] = np.inf
                        down = True
                        break      
            #sort
            for a in range(0,row):
                for b in range(0,col):
                    #row 
                    if a == row-1:
                        if b==col-1:
                            break
                        elif table[a][b+1] < table[a][b]:
                            temp = table[a][b]
                            table[a][b] = table[a][b+1]
                            table[a][b+1] = temp
                    #col 
                    elif b == col-1:
                        if table[a+1][b] < table[a][b]:
                            temp = table[a][b]
                            table[a][b] = table[a+1][b]
                            table[a+1][b] = temp
                    #go down 
                    else:
                        if table[a + 1][b] < table[a][b]:
                            if table[a + 1][b] < table[a][b + 1]:
                                temp = table[a][b]
                                table[a][b] = table[a + 1][b]
                                table[a + 1][b] = temp
        
                        #go right
                        if table[a][b + 1] < table[a][b]:
                            if table[a][b + 1] < table[a + 1][b]:
                                temp = table[a][b]
                                table[a][b] = table[a][b + 1]
                                table[a][b + 1] = temp  
            #write
            extract_min = int(extract_min)
            ref = 'Extract-min '+str(extract_min)
            with open(fout, 'a') as f:
                f.write(ref)
                f.write('\n')
                for row in table:
                    for ele in row:
                        if not np.isinf(ele):
                            f.write(str(int(ele)))
                            f.write(' ')
                        else:
                            f.write('x')
                            f.write(' ')
                    f.write('\n')
                f.write(' ')
                f.write('\n')
                      




                
        

  


          

            
            
            
            
            
            
            
            
            
            
            