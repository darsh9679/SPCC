import re

# Opcode and register tables
opcode_table = {
    "START": "01",
    "MOVER": "02",
    "MOVEM": "03",
    "ADD":   "04",
    "SUB":   "05",
    "MULT":  "06",
    "JUMP":  "07",
    "END":   "08"
}

register_table = {
    "AREG": "R1",
    "BREG": "R2",
    "CREG": "R3"
}

# Symbol & literal tables, intermediate & final code lists
symbol_table      = {}
literal_table     = {}
intermediate_code = []
machine_code      = []

# Starting location counter
memory_address = 100

# Your sample program
assembly_code = [
    "START 100",
    "MOVER AREG, X",
    "MOVEM AREG, Y",
    "ADD BREG, ='5'",
    "L1, SUB CREG, X",
    "MULT AREG, ='10'",
    "JUMP L1",
    "END"
]

#
# ─── PASS 1: Build Symbol & Literal Tables ─────────────────────────────────────
#
for line in assembly_code:
    line = line.strip()
    # Handle labels in Pass 1 too
    label_match = re.match(r'^([A-Za-z]\w*),\s*(.*)$', line)
    if label_match:
        lbl, rest = label_match.group(1), label_match.group(2)
        symbol_table[lbl] = memory_address
        line = rest

    tokens = re.split(r'[ ,]+', line)

    if tokens[0] == "START":
        memory_address = int(tokens[1])
        continue

    if tokens[0] == "END":
        break

    # Undefined symbols (variables)
    for operand in tokens[1:]:
        if (operand not in opcode_table and
            operand not in register_table and
            not operand.startswith("='")):
            symbol_table.setdefault(operand, None)

    # Literals
    if tokens[-1].startswith("='"):
        lit = tokens[-1][2:-1]
        literal_table.setdefault(lit, None)

    memory_address += 1

# Assign addresses to symbols (where None)
for sym, addr in list(symbol_table.items()):
    if addr is None:
        symbol_table[sym] = memory_address
        memory_address += 1

# Assign addresses to literals
for lit in literal_table:
    literal_table[lit] = memory_address
    memory_address += 1

#
# ─── PASS 2: Generate Intermediate & Machine Code ──────────────────────────────
#
memory_address = 100
for line in assembly_code:
    line = line.strip()

    # Strip labels (with or without comma) before tokenizing
    label_match = re.match(r'^([A-Za-z]\w*),\s*(.*)$', line)
    if label_match:
        line = label_match.group(2)

    tokens = re.split(r'[ ,]+', line)

    # Skip directives
    if tokens[0] in ("START", "END"):
        continue

    # Opcode lookup
    opc   = opcode_table[tokens[0]]
    op1   = register_table.get(tokens[1], symbol_table.get(tokens[1], ""))
    # Determine second operand (symbol or literal)
    if tokens[-1].startswith("='"):
        op2 = literal_table[tokens[-1][2:-1]]
    else:
        op2 = symbol_table.get(tokens[-1], "")

    # Emit intermediate and final machine code
    intermediate_code.append(f"{memory_address} ({opc}) {op1}, {op2}")
    machine_code.append(f"{memory_address} {opc} {op1} {op2}")

    memory_address += 1

#
# ─── OUTPUT ────────────────────────────────────────────────────────────────────
#
print("Symbol Table:")
for sym, addr in symbol_table.items():
    print(f"  {sym} -> {addr}")

print("\nLiteral Table:")
for lit, addr in literal_table.items():
    print(f"  ='{lit}' -> {addr}")

print("\nIntermediate Code:")
print("\n".join(intermediate_code))

print("\nMachine Code:")
print("\n".join(machine_code))
