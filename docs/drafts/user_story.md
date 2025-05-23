# User Story

### 🐚 **Epic: Shell Initialization**

#### **User Story 1.1: Display a Prompt**

**As a** user,
**I want** to see a prompt when I launch the shell,
**So that** I know the shell is ready to receive input.

**Acceptance Criteria:**

* When I start the shell, a prompt is displayed.
* The prompt appears again after I enter a command.
* The shell does not crash or leak memory.

---

#### **User Story 1.2: Read and Echo User Input**

**As a** user,
**I want** to type a command and see my input echoed back,
**So that** I can confirm the shell is correctly reading my input.

**Acceptance Criteria:**

* After typing a command and pressing enter, the command is echoed.
* Input reading works for empty lines, single words, and full commands.
* No memory leaks or crashes occur.

---

#### **User Story 1.3: Exit the Shell**

**As a** user,
**I want** to exit the shell using the `exit` command or `Ctrl+D`,
**So that** I can quit the shell cleanly when I’m done.

**Acceptance Criteria:**

* Typing `exit` terminates the shell.
* Pressing `Ctrl+D` (EOF) exits the shell if the input is empty.
* Shell exits cleanly without memory leaks.

---

#### **User Story 1.4: Command History**

**As a** user,
**I want** the shell to remember previously typed commands,
**So that** I can scroll through them with the arrow keys.

**Acceptance Criteria:**

* I can press ↑ and ↓ to scroll through input history.
* No history leaks memory.
* History works for multiple sessions (optional stretch goal).

---

### 🧱 **Epic: Lexing**

#### **User Story 2.1: Tokenize Simple Commands**

**As a** shell developer,
**I want** to convert raw user input into tokens (words, operators, etc.),
**So that** the parser can understand the command structure.

**Acceptance Criteria:**

* Given the input `ls -l /home`, it produces three tokens: `ls`, `-l`, `/home`.
* Handles simple separators like space and tab.
* Tokens are stored in a list/array structure.
* Memory is properly allocated and freed (no leaks).

---

#### **User Story 2.2: Handle Quotes and Escaping**

**As a** user,
**I want** the lexer to treat quoted strings as one token,
**So that** arguments with spaces are not split incorrectly.

**Acceptance Criteria:**

* Given `echo "hello world"`, it creates tokens: `echo`, `hello world`.
* Handles single `'` and double `"` quotes correctly.
* Escaped characters inside quotes are preserved.

### 🧠 **Epic: Parsing**

#### **User Story 3.1: Parse a Simple Command**

**As a** shell developer,
**I want** to convert a flat list of tokens into a simple command structure,
**So that** the shell can later execute it correctly.

**Acceptance Criteria:**

* Given tokens: `["ls", "-l", "/home"]`, the parser builds a structure with:

  * Command: `"ls"`
  * Arguments: `["-l", "/home"]`
* Command structure is consistent and memory-safe.
* Handles single commands with or without arguments.

---

#### **User Story 3.2: Parse Redirections**

**As a** user,
**I want** the shell to recognize input/output redirections,
**So that** I can redirect streams like stdin or stdout.

**Acceptance Criteria:**

* Recognizes and stores redirection operators (`>`, `<`, `>>`, `<<`)
* For `ls > out.txt`, the parser stores:

  * Command: `ls`
  * Redirection: stdout to `"out.txt"`
* No memory leaks or undefined behavior on malformed input.

---

#### **User Story 3.3: Parse Pipes**

**As a** user,
**I want** to use the pipe operator (`|`) to chain commands,
**So that** the output of one command becomes input to another.

**Acceptance Criteria:**

* Given `cat file | grep foo | wc -l`, builds a chain of command structures.
* Each command node knows its place in the pipeline.
* Parser correctly splits and links each command.
* No memory leaks.

---

#### **User Story 3.4: Parse Quoted and Escaped Strings**

**As a** user,
**I want** quoted and escaped tokens to remain grouped in the parse phase,
**So that** my arguments are preserved as intended.

**Acceptance Criteria:**

* `echo "hello world"` keeps `"hello world"` as a single argument.
* Escaped characters like `\"` are handled correctly.
* Malformed quotes are detected and reported.

---

#### **User Story 3.5: Syntax Error Detection**

**As a** user,
**I want** the shell to report syntax errors clearly,
**So that** I understand what went wrong with my command.

**Acceptance Criteria:**

* Detects cases like:

  * Unmatched quotes
  * Pipe with no command after (`ls |`)
  * Redirection with no target (`>`)
* Provides a clear error message.
* Shell does not crash or leak on bad input.

---

#### **User Story 3.6: Support Parentheses and Subshells (Optional)**

**As a** user,
**I want** to use parentheses for grouped commands,
**So that** I can execute compound expressions in a subshell.

**Acceptance Criteria:**

* `(ls && echo ok)` is parsed as a subshell with grouped logic.
* Grouped commands are kept together structurally.
* Nested parentheses are supported.
* Detects mismatched parentheses as syntax errors.