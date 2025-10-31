import math

res = '''
<translate time = "10" align="true">
'''

array = '{'

alfa = 0
n = 2
r = 1
    
for i in range(n):
    res += f'                   <point x="{r*math.sin(alfa)}" y="0" z="{r*math.cos(alfa)}"/>\n'
    alfa += 2*math.pi / n
    array += f'{{{r*math.sin(alfa)},0,{r*math.cos(alfa)}}},'

res += "                </translate>"
array = array[:-1]
array += '}'

print(res)
print(array)
