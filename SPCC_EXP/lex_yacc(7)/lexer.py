# lexer.py

import ply.lex as lex

# --- Token Names ---
tokens = (
    'NUMBER',   # integer literal
    'PLUS',     # +
    'MINUS',    # -
    'TIMES',    # *
    'DIVIDE',   # /
    'LPAREN',   # (
    'RPAREN',   # )
)

# --- Regular Expressions ---
t_PLUS   = r'\+'
t_MINUS  = r'-'
t_TIMES  = r'\*'
t_DIVIDE = r'/'
t_LPAREN = r'\('
t_RPAREN = r'\)'

def t_NUMBER(t):
    r'\d+'
    t.value = int(t.value)
    return t

# Ignore spaces and tabs
t_ignore = ' \t'

# Track newlines for error reporting (optional)
def t_newline(t):
    r'\n+'
    t.lexer.lineno += len(t.value)

# Illegal character handler
def t_error(t):
    print(f"Illegal character '{t.value[0]}' at line {t.lexer.lineno}")
    t.lexer.skip(1)

# Build the lexer
lexer = lex.lex()

# Quick test when run directly
if __name__ == "__main__":
    data = input("Enter expression to tokenize> ")
    lexer.input(data)
    for tok in lexer:
        print(f"{tok.type:<7} {tok.value}")




# How to Run
# Install PLY (if you haven’t already):

# bash
# Copy
# Edit
# pip install ply
# Save the code above into a file named main.py.

# Run it in your terminal or PowerShell:

# bash
# Copy
# Edit
# python main.py
# Try entering expressions like:

# scss
# Copy
# Edit
# 3 + 5 * (10 - 4)
# -7 + 2 * (8 / 4)
# (1 + 2) * (3 + 4)
