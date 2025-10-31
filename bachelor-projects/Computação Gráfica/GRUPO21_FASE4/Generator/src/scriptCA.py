import math
import random

res =""
array = '{'
lista = [0.01,0.015,0.017,0.012]
alfa = 0
n = 1000

    
for i in range(n):
    r = random.uniform(39,42.5)
    res += '        <group>\n'
    height = random.uniform(-0.5, 0.5)
    res += f'            <transform>\n'
    res += f'                <translate x="{r*math.sin(alfa)}" y="{height}" z="{r*math.cos(alfa)}"/>\n'
    size = random.choice(lista)
    res += f'                <scale x="{size}" y="{size}" z="{size}"/>\n'
    res += f'            </transform>\n'
    res += f'            <models>\n'
    res += f'                <model file="sphere_10_20_20.3d">\n'
    res += f'                    <color>\n' 
    res += f'                        <rgb R="0.3" G="0.3" B="0.2"/>\n' 
    res += f'                    </color>\n'
    res += f'                </model>\n'
    res += f'            </models>\n'
    alfa += 2*math.pi / n
    array += f'{{{r*math.sin(alfa)},0,{r*math.cos(alfa)}}},'
    res += "            </group>\n"

array = array[:-1]
array += '}'


print(res)
#print(array)
