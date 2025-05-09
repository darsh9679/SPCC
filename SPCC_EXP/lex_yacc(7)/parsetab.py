
# parsetab.py
# This file is automatically generated. Do not edit.
# pylint: disable=W,C,R
_tabversion = '3.10'

_lr_method = 'LALR'

_lr_signature = 'leftPLUSMINUSleftTIMESDIVIDErightUMINUSDIVIDE LPAREN MINUS NUMBER PLUS RPAREN TIMESexpression : expression PLUS termexpression : expression MINUS termexpression : termterm : term TIMES factorterm : term DIVIDE factorterm : factorfactor : NUMBERfactor : LPAREN expression RPARENfactor : MINUS factor %prec UMINUS'
    
_lr_action_items = {'NUMBER':([0,3,6,7,8,9,10,],[5,5,5,5,5,5,5,]),'LPAREN':([0,3,6,7,8,9,10,],[6,6,6,6,6,6,6,]),'MINUS':([0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,],[3,8,-3,3,-6,-7,3,3,3,3,3,-9,8,-1,-2,-4,-5,-8,]),'$end':([1,2,4,5,11,13,14,15,16,17,],[0,-3,-6,-7,-9,-1,-2,-4,-5,-8,]),'PLUS':([1,2,4,5,11,12,13,14,15,16,17,],[7,-3,-6,-7,-9,7,-1,-2,-4,-5,-8,]),'RPAREN':([2,4,5,11,12,13,14,15,16,17,],[-3,-6,-7,-9,17,-1,-2,-4,-5,-8,]),'TIMES':([2,4,5,11,13,14,15,16,17,],[9,-6,-7,-9,9,9,-4,-5,-8,]),'DIVIDE':([2,4,5,11,13,14,15,16,17,],[10,-6,-7,-9,10,10,-4,-5,-8,]),}

_lr_action = {}
for _k, _v in _lr_action_items.items():
   for _x,_y in zip(_v[0],_v[1]):
      if not _x in _lr_action:  _lr_action[_x] = {}
      _lr_action[_x][_k] = _y
del _lr_action_items

_lr_goto_items = {'expression':([0,6,],[1,12,]),'term':([0,6,7,8,],[2,2,13,14,]),'factor':([0,3,6,7,8,9,10,],[4,11,4,4,4,15,16,]),}

_lr_goto = {}
for _k, _v in _lr_goto_items.items():
   for _x, _y in zip(_v[0], _v[1]):
       if not _x in _lr_goto: _lr_goto[_x] = {}
       _lr_goto[_x][_k] = _y
del _lr_goto_items
_lr_productions = [
  ("S' -> expression","S'",1,None,None,None),
  ('expression -> expression PLUS term','expression',3,'p_expression_plus','yacc.py',16),
  ('expression -> expression MINUS term','expression',3,'p_expression_minus','yacc.py',20),
  ('expression -> term','expression',1,'p_expression_term','yacc.py',24),
  ('term -> term TIMES factor','term',3,'p_term_times','yacc.py',28),
  ('term -> term DIVIDE factor','term',3,'p_term_divide','yacc.py',32),
  ('term -> factor','term',1,'p_term_factor','yacc.py',36),
  ('factor -> NUMBER','factor',1,'p_factor_number','yacc.py',40),
  ('factor -> LPAREN expression RPAREN','factor',3,'p_factor_group','yacc.py',44),
  ('factor -> MINUS factor','factor',2,'p_factor_uminus','yacc.py',48),
]
