import json
import os
import re


def parse():

    f = open("processos.txt")
    l = []

    for line in f:
        sr = re.search(r'(?P<id>\d+)::(?P<data>\d{4}-\d{2}-\d{2})::(?P<line>.*)[::::|.::]',line)
        if(sr != None):
            dic = sr.groupdict()
            l.append(dic)
    return l         
    

def processPerYear(l):

    numProc = dict()

    for dic in l:
        sr = re.findall(r'Proc',dic.get('line'))
        year = dic.get('data')[:4]
        
        if(sr != []):
            if year not in numProc.keys():
                numProc[year] = 0
            numProc[year] += len(sr)
    
    sortedNumProc = dict(sorted(numProc.items()))
    return sortedNumProc

    
def freqNames(l):

    freqLastName = dict()
    freqFstName = dict()

    for dic in l:
        year = dic.get('data')[:4]
        if year[2:4] == '00':
            yearSec = int(year[:2])
        else:
            yearSec = int(year[:2])+1
        
        if yearSec not in freqLastName:
            freqLastName[yearSec] = {}
        if yearSec not in freqFstName:
            freqFstName[yearSec] = {}
        fstNames = re.findall(r'::([A-Z][a-z]+)\s+',dic.get('line'))
        lstNames = re.findall(r'\s([A-Z][a-z]+)(?<!Anexo)[::|\,]',dic.get('line'))

        for name in lstNames:
            if name not in freqLastName[yearSec]:
                freqLastName[yearSec][name] = 0
            freqLastName[yearSec][name] += 1 
        for name2 in fstNames:
            if name2 not in freqFstName[yearSec]:
                freqFstName[yearSec][name2] = 0
            freqFstName[yearSec][name2] += 1
    freqFstName = {year: dict(sorted(names.items(), key=lambda x: x[1], reverse=True)[:5]) for year, names in freqFstName.items()}    
    freqLastName = {year: dict(sorted(names.items(), key=lambda x: x[1], reverse=True)[:5]) for year, names in freqLastName.items()}

    return freqFstName,freqLastName


    
def freqRelation(l):

    freqRel = dict()
    for dic in l:
        sr = re.findall(r',([A-Z][a-z]+\s*)[a-zA-Z]*?\. Proc',dic.get('line'))
        if sr != []:
            for r in sr:
                aux = r.strip()
                if aux not in freqRel.keys():
                    freqRel[aux] = 0
                freqRel[aux] += 1
    return freqRel


def outJson(dic,outputFile):
     
    data = dic[:20]
    with open(outputFile,'w') as f:
        json.dump(data,f,indent=4)
     
    

def printProcPerYear(l):

    print("_________________________________________")
    print("|                                       |")
    print("|   Frequência de Processos por Ano     |")
    print("|                                       |")
    print("|_______________________________________|")
    print("|                 |                     |")
    print("|      Ano        |     Nº Processos    |")
    print("|_________________|_____________________|")
    for i in l:
        print("| {:>9}       |  {:>9}          |".format(i,l[i]))
        print("|_________________|_____________________|")
    
    

def printNames(l):

    print(" _________________________________________________")
    print("|                                                |")
    print("|        Frequência de Nomes por Século          |")
    print("|________________________________________________|")
    print("|                 |              |               |")
    print("|      Século     |     Nome     |   Frequência  |")
    print("|_________________|______________|_______________|")

    fstN = l[0]
    keys = list(fstN.keys())
    keys.sort()
    for key in keys:
        for name in fstN[key]:
            print("|   {:^9}     |   {:^9}  |    {:^9}  |".format(key,name,fstN[key][name]))
        print("|_________________|______________|_______________|")



def printSurnames(l):

    print(" _________________________________________________")
    print("|                                                |")
    print("|        Frequência de Apelidos por Século       |")
    print("|________________________________________________|")
    print("|                 |              |               |")
    print("|      Século     |     Nome     |   Frequência  |")
    print("|_________________|______________|_______________|")

    sur = l[1]
    keys = list(sur.keys())
    keys.sort()
    for key in keys:
        for name in sur[key]:
            print("|   {:^9}     |   {:^9}  |    {:^9}  |".format(key,name,sur[key][name]))
        print("|_________________|______________|_______________|")


def printFreqRelation(l):

    print("_________________________________________")
    print("|                                       |")
    print("|      Frequência dos vários tipos      |")
    print("|              de Relações              |")
    print("|_______________________________________|")
    print("|                 |                     |")
    print("|     Relação     |     Frequência      |")
    print("|_________________|_____________________|")
    for i in l:
        print("| {:>10}      |  {:>9}          |".format(i,l[i]))
        print("|_________________|_____________________|")


def printMenu():

    print("")
    print(" ____________________________________________")
    print("|                                            |")
    print("|                 [MENU]                     |")
    print("|____________________________________________|")
    print("|                                            |")
    print("|  [1] Frequência de processos por ano       |")
    print("|____________________________________________|")
    print("|                                            |")
    print("|  [2] Nomes por século                      |")
    print("|____________________________________________|")
    print("|                                            |")
    print("|  [3] Apelidos por século                   |")
    print("|____________________________________________|")
    print("|                                            |")
    print("|  [4] Frequência dos tipos de relação       |")
    print("|____________________________________________|")
    print("|                                            |")
    print("|  [5] Exportar para JSON                    |")
    print("|____________________________________________|")
    print("|                                            |")
    print("|  [6] Sair                                  |")
    print("|____________________________________________|")
    print("")

def printSubMenu():

    print(" _______________")
    print("|               |")
    print("|  [5] Voltar   |")
    print("|_______________|")
    print("|               |")
    print("|  [6] Sair     |")
    print("|_______________|")

def end():
    print(" ____________")
    print("|            |")
    print("|  Goodbye!  |")
    print("|____________|")
    print("")
    
    
def startMenu():

    dic = parse()
    printMenu()
    inp = int(input("Digite uma opção: "))
    
    while(inp != 6):
        if(inp == 1):
            print(" ")
            os.system("clear")
            printProcPerYear(processPerYear(dic))
            print(" ")
            printSubMenu()
            print(" ")
            subInp = int(input("Digite uma opção: "))
            if(subInp == 5):
                os.system('clear')
                printMenu()
                inp = int(input("Digite uma opção: "))
            elif(subInp == 6):
                end()
                break
        elif(inp == 2):
            print(" ")
            os.system("clear")
            printNames(freqNames(dic))
            print(" ")
            printSubMenu()
            print(" ")
            subInp = int(input("Digite uma opção: "))
            if(subInp == 5):
                os.system('clear')
                printMenu()
                inp = int(input("Digite uma opção: "))
            elif(subInp == 6):
                end()
                break
        elif(inp == 3):
            print(" ")
            os.system("clear")
            printSurnames(freqNames(dic))
            print(" ")
            printSubMenu()
            print(" ")
            subInp = int(input("Digite uma opção: "))
            if(subInp == 5):
                os.system('clear')
                printMenu()
                inp = int(input("Digite uma opção: "))
            elif(subInp == 6):
                end()
                break
        elif(inp == 4):
            print(" ")
            os.system("clear")
            printFreqRelation(freqRelation(dic))
            print(" ")
            printSubMenu()
            print(" ")
            subInp = int(input("Digite uma opção: "))
            if(subInp == 5):
                os.system('clear')
                printMenu()
                inp = int(input("Digite uma opção: "))
            elif(subInp == 6):
                end()
                break
        elif(inp == 5):
            print(" ")
            os.system("clear")
            file = input("Digite o nome do ficheiro de output: ")
            file += '.json'
            os.system("clear")
            print(" ")
            outJson(dic,file)
            print("Ficheiro criado com sucesso!")
            print(" ")
            printSubMenu()
            print(" ")
            subInp = int(input("Digite uma opção: "))
            if(subInp == 5):
                os.system('clear')
                printMenu()
                inp = int(input("Digite uma opção: "))
            elif(subInp == 6):
                end()
                break
        else:
            print(" ")
            print("Opção inválida! ")
            printMenu()
            inp = int(input("Digite uma opção: "))
    os.system('clear')
    end()

def main():
    startMenu()

if __name__ == "__main__":
    main()