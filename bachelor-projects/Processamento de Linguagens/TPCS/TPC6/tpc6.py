import ply.lex as lex

tokens = (
    'MULTI_COMMENT_STRING',
    'SINGLE_COMMENT_STRING',
    'OP_BRAC',
    'CL_BRAC',
    'OP_PAREN',
    'CL_PAREN',
    'COLON',
    'SEMICOLON',
    'INT',
    'IDENTIFIER',
    'FUNCTION',
    'PROGRAM',
    'NUMBER',
    'ATRIB',
    'MULT',
    'SUB',
    'WHILE',
    'FOR',
    'GREATER',
    'LESS',
    'IN',
    'DOUBLE_DOT',
    'OP_SQRBRAC',
    'CL_SQRBRAC'
)

t_OP_BRAC = r'\{'
t_CL_BRAC = r'\}'
t_OP_PAREN = r'\('
t_CL_PAREN = r'\)'
t_COLON = r'\,'
t_SEMICOLON = r'\;'
t_ATRIB = r'\='
t_MULT = r'\*'
t_SUB = r'\-'
t_GREATER = r'\>'
t_LESS = r'\<'
t_DOUBLE_DOT = r'\.\.'
t_OP_SQRBRAC = r'\['
t_CL_SQRBRAC = r'\]'
 

def t_MULTI_COMMENT_STRING(t):
  r'\/\*[\w\W]*\*\/'
  return t

def t_SINGLE_COMMENT_STRING(t):
   r'\/\/.*'
   return t

def t_PROGRAM(t):
  r'program'
  return t

def t_FUNCTION(t):
   r'function'
   return t

def t_INT(t):
   r'int'
   return t
   
def t_NUMBER(t):
  r'\d+'
  t.value = int(t.value)
  return t

def t_WHILE(t):
   r'while'
   return t

def t_FOR(t):
   r'for'
   return t

def t_IN(t):
   r'in'
   return t
 
def t_IDENTIFIER(t):
  r'\w+'
  return t

t_ignore = ' \t\n'

def t_error(t):
    print(f'Caracter ilegal {t.value}')
    t.lexer.skip(1)


lexer = lex.lex()

data1 = '''
/* factorial.p
-- 2023-03-20 
-- by jcr
*/

int i;

// Função que calcula o factorial dum número n
function fact(n){
  int res = 1;
  while res > 1 {
    res = res * n;
    res = res - 1;
  }
}

// Programa principal
program myFact{
  for i in [1..10]{
    print(i, fact(i));
  }
}
'''

data2 = '''
/* max.p: calcula o maior inteiro duma lista desordenada
-- 2023-03-20 
-- by jcr
*/

int i = 10, a[10] = {1,2,3,4,5,6,7,8,9,10};

// Programa principal
program myMax{
  int max = a[0];
  for i in [1..9]{
    if max < a[i] {
      max = a[i];
    }
  }
  print(max);
}
'''

lexer.input(data1)

while tok := lexer.token():
    print(tok)
