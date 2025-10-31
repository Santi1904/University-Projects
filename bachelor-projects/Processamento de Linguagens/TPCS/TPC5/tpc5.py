import re

def returnChange(bal):

    coins = [2,1,0.5,0.2,0.1,0.05,0.02,0.01]
    r = 'maq: troco='
    for c in coins:
        if bal >= c:
           x = bal // c
           bal %= c
           if x > 0:
               if c < 1:
                    c *= 100
                    r += f'{int(x)}x{int(c)}c,'
               else:
                   r += f'{int(x)}x{int(c)}e,'
    r += ' Volte Sempre!'
    r = re.sub(r', V','; V',r)
    
    return r



def convertBalance(b):
    k = "{:.2f}".format(b)
    newSum = re.sub(r'\.','e',k)
    formatSum = re.sub(r'\Z','c',newSum)
    return formatSum

def balance(coins,bal):
    sum = 0
    for c in coins:
        if re.match(r'[125]0?c|[12]e',c):
            if c[-1] == 'c':
                num = c[0:-1]
                k = float(num)/100
                sum += k
            else:
                k = c[0:-1]
                sum += float(k)
        else:
            print(f'maq: "{c} - Moeda Inválida "')
    tot = convertBalance(sum+bal)
    print(f'maq: Saldo = {tot}')
    return sum+bal

def call(phone_num,bal):
    if re.match(r'^601|641',phone_num):
        print('Chamada bloqueada!')
    elif re.match(r'00',phone_num):
        if bal >= 1.50:
            bal -= 1.50
        else:
            print('Saldo Insuficiente!')
    elif re.match(r'^2',phone_num):
        if bal >= 0.25:
            bal -= 0.25
        else:
            print('Saldo Insuficiente!')
    elif re.match(r'^808',phone_num):
        if bal >= 0.10:
            bal -= 0.10
    elif re.match(r'^800',phone_num):
        bal += 0
    else:
        print('maq: "Número inválido"')
        return bal
    tot = convertBalance(bal)
    print(f'maq: Saldo = {tot}')        
    return bal


def phone_booth(input,bal):
    if re.match(r'LEVANTAR',input):
        print('maq: "Introduza moedas."')
        return bal
    elif re.match(r'MOEDA',input):
        coins = re.findall(r'[0-9]*0?c|[0-9]*e',input)
        if coins != None:
            return(balance(coins,bal))
    elif re.match(r'^T\=',input):
        phone_num = re.sub(r'T=','',input)
        if re.match(r'(00)?[0-9]{9}',phone_num):
            return(call(phone_num,bal))
        else:
            print('Número Inválido')
    elif re.match(r'ABORTAR',input) or re.match(r'POUSAR',input):
        return bal
    else:
        print("Opção Inválida")
        
                    
def main():
    bal = 0
    state = ""
    while(state != 'POUSAR'):
        state = input()
        bal = phone_booth(state,bal)
    print(returnChange(bal))
   
if __name__ == "__main__":
    main()