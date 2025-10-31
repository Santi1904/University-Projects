import os


def parse():

    d1 = {'idade':[],'sexo':[],'tensao':[],'colesterol':[],'batimento':[],'doente':[]}
    f = [l.rstrip() for l in open("myheart.csv")]
    f.remove('idade,sexo,tensão,colesterol,batimento,temDoença')
    i = 0

    for line in f:
        
        str = line.split(",")
        d1['idade'].append(str[0])
        d1['sexo'].append(str[1])
        d1['tensao'].append(str[2])
        d1['colesterol'].append(str[3])
        d1['batimento'].append(str[4])
        d1['doente'].append(str[5])

    return d1

def bySex(d1):
    
    imasc = 0
    man = 0
    wom = 0
    ifem = 0

    for i in range(len(d1['sexo'])):
        if d1['sexo'][i] == 'M':
            man += 1
            if(d1['doente'][i] == '1'):
                imasc += 1
        elif(d1['sexo'][i] == 'F'):
            wom += 1
            if(d1['doente'][i] == '1'):
                ifem += 1
    
    ret = [imasc,man,ifem,wom]

    return ret

def maxAge(d1):

    age = 0
    for i in range(len(d1['idade'])):
        
        if int(d1['idade'][i]) >= age:
            age = int(d1['idade'][i])
    
    return age

def byAge(d1):

    supAge = maxAge(d1)

    dicAge = dict()
    size = 0
    for i in range(len(d1['idade'])):
        if(d1['idade'][i] in dicAge.keys() and d1['doente'][i] == '1'):
            dicAge[d1['idade'][i]] += 1
            size += 1
        elif(d1['doente'][i] == '1'):
            dicAge[d1['idade'][i]] = 1
            size += 1

    dicAgeSorted = dict(sorted(dicAge.items()))

    dicSickAge = dict()
    dicSickAge['size'] = size
    allSick = 0

    for i in range(30,supAge+3,5):
        allSick = 0
        for j in range(i,i+5):
            if str(j) in dicAgeSorted.keys():
                allSick += int(dicAgeSorted[str(j)])
        dicSickAge[f"[{i}..{i+4}]"] = [allSick,(allSick/size)*100]
        
    return dicSickAge    

def limSup(d1,param):

    sup = 0
    for i in range(len(d1[param])):
        if(int(d1[param][i])) >= sup:
            sup = int(d1[param][i])
    return sup

def limInf(d1,param):

    inf = limSup(d1,param)

    for i in range(len(d1[param])):
        if(int(d1[param][i]) != 0 and int(d1[param][i]) <= inf):
            inf = (int(d1[param][i])) 
    return inf


def byColesterol(d1):

    max = limSup(d1,'colesterol')
    min = limInf(d1,'colesterol')
    dicColest = dict()
    size = 0
    for i in range(len(d1['colesterol'])):
        if(d1['colesterol'][i] in dicColest.keys() and d1['doente'][i] == '1'):
            dicColest[d1['colesterol'][i]] += 1
            size += 1
        elif(d1['doente'][i] == '1'):
            dicColest[d1['colesterol'][i]] = 1
            size += 1
        
    dicColestSorted = dict(sorted(dicColest.items()))
    dicSickColest = dict()
    dicSickColest['0'] = [dicColestSorted['0'],(dicColestSorted['0']/size)*100]
    dicSickColest['size'] = size
    
    allSick = 0
    for i in range(min,max,10):
        allSick = 0
        for j in range(i,i+10):
            if str(j) in dicColestSorted.keys():
                allSick += int(dicColestSorted[str(j)])
        dicSickColest[f"[{i}..{i+9}]"] = [allSick,allSick/size*100]
   
    return dicSickColest


def printDistSex(list):
    
    print("-------------------------------------------------------------")
    print("|                   Distribuição por sexo                   |")
    print("-------------------------------------------------------------")
    print("|  Género    | NºDoentes  |   Total    |   Percentagem(%)   |")
    print("-------------------------------------------------------------")
    print(f"|  Masculino |    {list[0]}     |    {list[1]}     |       {round(list[0]/list[1]*100,1)}         |")
    print("-------------------------------------------------------------")
    print(f"|  Feminino  |    {list[2]}      |    {list[3]}     |       {round(list[2]/list[3]*100,1)}         |")
    print("-------------------------------------------------------------")




def printDistAge(d1):
    
    k = list(d1.keys())
    l = list(d1.values())
    
    print("--------------------------------------------------")
    print("|      Distribuição por intervalos etários       |")
    print(f"|           (Num total de {l[0]} doentes )          |")
    print("--------------------------------------------------")
    print("| Intervalo   | Percentagem(%) |   Nº Doentes    |")
    print("--------------------------------------------------")
    for i in range(1,len(k)):
          #print(f"| {k[i]} | {round(l[i][1],1)}% | {l[i][0]} |")
        print ("| {:^11} | {:>9}      | {:>7}         |".format(k[i],round(l[i][1],1),l[i][0]))
    print("--------------------------------------------------")


def printDistColest(d1):

    k = list(d1.keys())
    l = list(d1.values())

    print("--------------------------------------------------")
    print("|   Distribuição por intervalos de colesterol    |")
    print(f"|           (Num total de {l[1]} doentes )          |")
    print("--------------------------------------------------")
    print("| Intervalo   | Percentagem(%) |  Nº Doentes     |")
    print("--------------------------------------------------")
    #print ("| {:^9}   | {:<6} | {:<3} |".format(k[0],(round(l[0][1],1)),l[0][0]))
    print ("| {:^11} | {:>9}      | {:>7}         |".format(k[0],round(l[0][1],1),l[0][0]))
    for i in range(2,len(k)):
          #print(f"| {k[i]} | {round(l[i][1],1)}% | {l[i][0]} |")
          #print ("| {:^9} | {:<6} | {:<3} |".format(k[i],round(l[i][1],1),l[i][0]))
         print ("| {:^11} | {:>9}      | {:>7}         |".format(k[i],round(l[i][1],1),l[i][0]))
    print("--------------------------------------------------")

def printMenu():

    print("")
    print("------------------[MENU]----------------------")
    print("|  [1] Distribuição por sexo                 |")
    print("----------------------------------------------")
    print("|  [2] Distribuição por escalões etários     |")
    print("----------------------------------------------")
    print("|  [3] Distribuição por níveis de colesterol |")
    print("----------------------------------------------")
    print("|  [4] Sair                                  |")
    print("----------------------------------------------")
    print("")

def printSubMenu():

    print("-----------------")
    print("| [5] Voltar    |")
    print("----------------|")
    print("| [6] Sair      |")
    print("-----------------")


def startDist():

    dic = parse()
    printMenu()
    inp = int(input("Digite uma opção: "))
    
    while(inp != 4):
        if(inp == 1):
            print(" ")
            os.system("clear")
            printDistSex(bySex(dic))
            print(" ")
            printSubMenu()
            print(" ")
            subInp = int(input("Digite uma opção: "))
            if(subInp == 5):
                os.system('clear')
                printMenu()
                inp = int(input("Digite uma opção: "))
            elif(subInp == 6):
                break
        elif(inp == 2):
            print(" ")
            os.system("clear")
            printDistAge(byAge(dic))
            print(" ")
            printSubMenu()
            print(" ")
            subInp = int(input("Digite uma opção: "))
            if(subInp == 5):
                os.system('clear')
                printMenu()
                inp = int(input("Digite uma opção: "))
            elif(subInp == 6):
                break
        elif(inp == 3):
            print(" ")
            os.system("clear")
            printDistColest(byColesterol(dic))
            print(" ")
            printSubMenu()
            print(" ")
            subInp = int(input("Digite uma opção: "))
            if(subInp == 5):
                os.system('clear')
                printMenu()
                inp = int(input("Digite uma opção: "))
            elif(subInp == 6):
                break
        else:
            print(" ")
            print("Opção inválida! ")
            printMenu()
            inp = int(input("Digite uma opção: "))


def main():

    startDist()

if __name__ == "__main__":
    main()
