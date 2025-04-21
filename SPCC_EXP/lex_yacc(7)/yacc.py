# parser.py

import ply.yacc as yacc
from lexer import tokens, lexer

# --- Operator Precedence ---
precedence = (
    ('left', 'PLUS', 'MINUS'),
    ('left', 'TIMES', 'DIVIDE'),
    ('right', 'UMINUS'),
)

# --- Grammar Rules ---

def p_expression_plus(p):
    'expression : expression PLUS term'
    p[0] = p[1] + p[3]

def p_expression_minus(p):
    'expression : expression MINUS term'
    p[0] = p[1] - p[3]

def p_expression_term(p):
    'expression : term'
    p[0] = p[1]

def p_term_times(p):
    'term : term TIMES factor'
    p[0] = p[1] * p[3]

def p_term_divide(p):
    'term : term DIVIDE factor'
    p[0] = p[1] / p[3]  # float division

def p_term_factor(p):
    'term : factor'
    p[0] = p[1]

def p_factor_number(p):
    'factor : NUMBER'
    p[0] = p[1]

def p_factor_group(p):
    'factor : LPAREN expression RPAREN'
    p[0] = p[2]

def p_factor_uminus(p):
    'factor : MINUS factor %prec UMINUS'
    p[0] = -p[2]

def p_error(p):
    if p:
        print(f"Syntax error at token '{p.value}'")
    else:
        print("Syntax error at end of input")

# Build the parser
parser = yacc.yacc()

def calculate(expr: str):
    return parser.parse(expr, lexer=lexer)

# Driver
if __name__ == "__main__":
    print("PLY Calculator. Ctrl-D (Unix) or Ctrl-Z (Win) to quit.\n")
    try:
        while True:
            line = input(">>> ")
            if not line.strip():
                continue
            result = calculate(line)
            print(result)
    except (EOFError, KeyboardInterrupt):
        print("\nGoodbye.")



# How to Run
# Install PLY (if you haven’t):

# bash
# Copy
# Edit
# pip install ply
# Save the two files in the same directory:

# lexer.py

# parser.py

# Run the parser (which pulls in the lexer):

# bash
# Copy
# Edit
# python parser.py
# Type any arithmetic expression at the >>> prompt:

# python-repl
# Copy
# Edit
# >>> 3 + 5 * (10 - 4)
# 33
# >>> -7 + 2 * (8 / 4)
# -3.0
