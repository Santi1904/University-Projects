import os
import re

def concatHeader(l):
    for i in range(len(l)):
        if '}' in l[i] and l[i-1][-1].isdigit():
            l[i-1] += ','+l[i]
            l.pop(-1)
    return l

def stripList(l):
    newList = []
    for i in l:
        if i != '':
            newList.append(i)
    return newList

def sumList(l):
    ret = 0
    for i in l:
        ret += int(i)
    return ret

def meanList(l):
    return(sumList(l)/len(l))

def parse_csv(file):

    f = [x.strip() for x in open(file)]
    header = f.pop(0).split(",")
    headerStrip = concatHeader(stripList(header))
    l = []
    l2 = []
    for line in f:
        newLine = line.split(",")
        dic = {}
        size = len(headerStrip)
        for pos in range(size):
            num = re.search(r'{(\d+),?(\d*)}',headerStrip[pos])
            if num != None:
                if(num.group(2)).isdigit():
                    max = int(num.group(2))
                else:  
                    max = int(num.group(1)) 
                nStrip = re.sub(r'{(\d+),?(\d*)}','',headerStrip[pos])
                op = re.search(r'::([a-z]+)',nStrip)
                key = re.sub(r'::','_',nStrip)
                if op != None:   
                    for i in range(pos,max+pos):
                        l2.append(newLine[i])
                    if op.group(1) == 'sum':
                        dic[key] = sumList(stripList(l2))
                        l2 = []
                    else:
                        dic[key] = meanList(stripList(l2))
                        l2 = []
                else:
                    for i in range(pos,max+pos):
                        l2.append(newLine[i])
                    dic[nStrip] = stripList(l2)
                    l2 = []    
            else:
                dic[headerStrip[pos]] = newLine[pos]
        l.append(dic)
    return l


def outJson(data,path):
    
    file = open(path,"w")
    json = '[\n'
    for dic in data:
        json += '   {\n'
        for key in dic.keys():
            if key != list(dic.keys())[-1]:
                json += f'      "{key}": "{dic[key]}",\n'
            elif type(dic[key]) == list:
                json += f'      "{key}": {[int(i) for i in dic[key]]}\n'
            else:
                json += f'      "{key}": "{dic[key]}"\n'
        if dic != data[-1]:
            json += "   },\n"
        else:
            json += "   }\n"
    json += ']'
    file.write(json)
    file.close()


def main():
   
    csv_dir = 'csv'
    json_dir = 'json/'
    for file in os.listdir(csv_dir):
        f = os.path.join(csv_dir, file)
        data = parse_csv(f)
        name = re.search(r'(\w+)',file)
        outputFileName = json_dir+name.group(0)+'.json'
        outJson(data,outputFileName)

if __name__ == "__main__":
   main()


