
# Grammar Transformation Programs

This repository contains programs for three different tasks related to context-free grammars: removing left-recursion, left-factoring, and implementing a recursive descent parser. Each program takes a specific type of grammar as input and provides the desired transformation or parsing functionality as output.

## Program 1: Remove Left-Recursion
### Description
This is a C++ program that implements an algorithm to remove left recursion from a context-free grammar. Left recursion can cause parsing conflicts and ambiguity in parsing techniques. The program reads input from a file named "input.txt," where each line represents a production rule in the form NonTerminal -> Production, and applies the left recursion removal algorithm to transform the grammar.

## How the Algorithm Works

The algorithm consists of the following steps:

1. **Read Input File**: The program reads the input grammar rules from the "input.txt" file, where each line represents a production rule for a non-terminal symbol.

2. **Preprocessing Functions**:

   - `removeWhiteSpace()`: Removes leading and trailing whitespaces from a string.
   - `getRules()`: Splits a rule into multiple sub-rules separated by the '|' symbol.

3. **Immediate Left Recursion Removal**:

   - If a production rule starts with the non-terminal symbol, it is considered left-recursive. The program separates such rules into two parts: rules that start with the non-terminal (alphas) and rules that do not (betas).
   - New non-terminal symbols are introduced for the immediate left-recursive rules. The original non-terminal is replaced with a non-terminal with a prime symbol (e.g., A' for A).
   - The new production rules are generated for the non-left-recursive rules by appending the new non-terminal with prime.
   - If there are no non-left-recursive rules (only immediate left-recursive rules), a new rule is added to generate ε (epsilon).

4. **Non-Immediate Left Recursion Removal**:

   - For each pair of non-terminals (A and B), the algorithm identifies whether A can derive B.
   - If a rule in A starts with B, the algorithm replaces that rule by generating rules with all possible combinations of B's rules and A's remaining part.

5. **Apply Algorithm**:

   - The algorithm is applied to all non-terminals. First, non-immediate left recursion is handled for each pair of non-terminals, and then immediate left recursion is resolved for each non-terminal.

6. **Print Results**:

   - The modified grammar rules are printed to the console.

## Usage

1. Create an "input.txt" file with the grammar rules following the format `NonTerminal -> Production | Production | ...`.
2. Compile and run the C++ program.
3. The modified grammar rules will be displayed on the console.

### Example
Input : 
```javascript
E->E+T|T
T->T*F|F
F->(E)|id
```

Output : 
```javascript
E -> T E'
T -> F T'
F -> (E) | id
E' -> +T E' | ε
T' -> *F T' | ε
```

# Program 2: Left Factoring Algorithm

This Markdown README provides an explanation for the C++ code that implements the left factoring algorithm. The code reads a set of context-free grammar rules from an "input.txt" file and applies the left factoring technique to remove ambiguity in parsing.

## Algorithm Overview

The left factoring algorithm is used to remove ambiguity that arises when multiple production rules for a non-terminal have the same prefix. The algorithm works as follows:

1. **Read Input File**: The program reads the grammar rules from the "input.txt" file. Each line represents a production rule for a non-terminal symbol.

2. **Preprocessing Functions**:
   - `removeWhiteSpace()`: Removes leading and trailing whitespaces from a string.
   - `getRules()`: Splits a rule into multiple sub-rules separated by the '|' symbol.

3. **Get Common Prefixes**:
   - `getCommonPrefixes()`: Finds the common prefix among multiple rules for a non-terminal.

4. **Apply Left Factoring**:
   - The algorithm iteratively searches for common prefixes among the rules for each non-terminal.
   - If a common prefix is found, the algorithm replaces the common prefix with a new non-terminal and generates new rules with the remaining suffixes.
   - The new non-terminal is named by adding a prime symbol (e.g., A' for A).

5. **Print Results**:
   - The modified grammar rules are printed to the console.

## Usage

1. Create an "input.txt" file with the grammar rules in the format `NonTerminal -> Production | Production | ...`.
2. Compile and run the C++ program.
3. The modified grammar rules will be displayed on the console.

Please ensure that you have a valid input file and that your grammar conforms to the expected format. The left factoring algorithm helps in eliminating ambiguity in parsing by transforming the grammar to a form that is easier to work with.

### Example
Input : 
```javascript
A->aAB|aBc|aAc
```

Output : 
```javascript
A -> aA'
A' -> AA'' | Bc
A'' -> B | c
```


# Program 3: Recursive Descent Parser with Derivation Tree Visualization

This document provides an explanation for the C++ code that implements a recursive descent parser for a context-free grammar. The parser validates input strings against the grammar and generates and visualizes derivation trees for valid strings.

## Code Explanation

The provided C++ code implements a recursive descent parser for a context-free grammar. The code is designed to achieve the following tasks:

1. **Parsing and Validation**:
   - The code reads grammar rules from an "input.txt" file. Each line in the file represents a production rule in the format `NonTerminal -> Production | Production | ...`.
   - The grammar rules are organized and stored for parsing purposes.
   - Users can input strings to be validated against the grammar.

2. **Derivation Tree Generation**:
   - For valid input strings, the code generates a derivation tree based on the parsed grammar rules.
   - The generated derivation tree is saved in a DOT file named "graph.dot" for visualization.

3. **Visualization**:
   - The code utilizes the Graphviz tool to convert the DOT file into an image format (PNG).
   - The generated derivation tree image ("graph.png") is displayed using the default image viewer on the system.

## Usage

1. Create an "input.txt" file containing grammar rules in the format `NonTerminal -> Production | Production | ...`.
2. Compile and run the C++ program.
3. The program will prompt for user input. Enter '1' to test strings or '0' to exit the program.
4. If you choose to test, input a word to validate against the grammar.
5. If the input word is valid, a derivation tree will be generated and displayed.

## Example
Input :
```javascript
   S
   S->idB
   B->idBAB|∈
   A->+|*

   Enter your word : nn\*nn+n+n+\*
   Enter your word : nn+

```
Output :
```javascript
   Word matches the grammar!
   Word matches the grammar!
```



## Screenshots
nn\*nn+n+n+\*
![App Screenshot](https://drive.google.com/uc?export=view&id=1W-NZKl5BBWN5h_eseg6WpQTtywKzBM7w)


nn+
![App Screenshot](https://drive.google.com/uc?export=view&id=1L5rJzLtWVP15YDEZy6V65mh9yLnWM2GM)
