# 🔍 Python Code Detective - Learn to Think Like Python!

import random
import time

# Color codes for pretty terminal output
class Colors:
    GREEN = '\033[92m'
    RED = '\033[91m'
    YELLOW = '\033[93m'
    BLUE = '\033[94m'
    PURPLE = '\033[95m'
    CYAN = '\033[96m'
    WHITE = '\033[97m'
    BOLD = '\033[1m'
    END = '\033[0m'

def print_header():
    """Display the fancy header"""
    print(f"\n{Colors.CYAN}{Colors.BOLD}{'='*60}")
    print("🔍 PYTHON CODE DETECTIVE")
    print("Learn to Think Through Code Step-by-Step!")
    print(f"{'='*60}{Colors.END}\n")

def print_thinking_steps():
    """Show the methodology for solving code puzzles"""
    print(f"{Colors.YELLOW}{Colors.BOLD}🧠 THE DETECTIVE METHOD:{Colors.END}")
    print(f"{Colors.WHITE}1. Read the code line by line")
    print("2. Track what each variable contains")
    print("3. Follow the execution order")
    print("4. Think about what each operation does")
    print("5. Predict the final result")
    print(f"6. Double-check your logic{Colors.END}\n")

# Quiz questions with educational focus
quiz_questions = [
    {
        "code": """x = 5
x = x + 3
print(x)""",
        "options": ["A) 5", "B) 8", "C) 53", "D) Error"],
        "correct": "B",
        "explanation": """🔍 Let's think through this step by step:
1. x = 5          → x now contains 5
2. x = x + 3      → x + 3 means 5 + 3 = 8, so x becomes 8
3. print(x)       → prints the current value of x, which is 8

💡 Key insight: x = x + 3 doesn't mean equality like in math - it means 
'calculate x + 3, then store that new value back in x'"""
    },
    
    {
        "code": """name = "Python"
print(name[0])""",
        "options": ["A) P", "B) Python", "C) 0", "D) Error"],
        "correct": "A",
        "explanation": """🔍 Let's trace this execution:
1. name = "Python"    → name contains the string "Python"
2. name[0]            → gets the character at position 0 (first character)
3. print(name[0])     → prints that character

💡 Key insight: String indexing starts at 0! 
P-y-t-h-o-n
0 1 2 3 4 5
So name[0] gives us 'P'"""
    },
    
    {
        "code": """numbers = [1, 2, 3]
numbers.append(4)
print(len(numbers))""",
        "options": ["A) 3", "B) 4", "C) [1, 2, 3, 4]", "D) 10"],
        "correct": "B",
        "explanation": """🔍 Following the execution:
1. numbers = [1, 2, 3]    → numbers contains a list with 3 items
2. numbers.append(4)      → adds 4 to the end, now [1, 2, 3, 4]
3. len(numbers)           → counts how many items: 4 items
4. print(len(numbers))    → prints the count: 4

💡 Key insight: append() modifies the original list, and len() counts items!"""
    },
    
    {
        "code": """result = "Hi" + "Bye"
print(result.lower())""",
        "options": ["A) HI BYE", "B) hibye", "C) Hi Bye", "D) HiBye"],
        "correct": "B",
        "explanation": """🔍 Step by step analysis:
1. "Hi" + "Bye"       → string concatenation gives "HiBye"
2. result = "HiBye"   → result contains "HiBye"
3. result.lower()     → converts ALL letters to lowercase
4. print(result.lower()) → prints "hibye"

💡 Key insight: .lower() converts the entire string to lowercase letters!"""
    },
    
    {
        "code": """x = 10
y = 3
print(x // y)""",
        "options": ["A) 3.333", "B) 3", "C) 4", "D) 30"],
        "correct": "B",
        "explanation": """🔍 Let's work through this:
1. x = 10             → x contains 10
2. y = 3              → y contains 3  
3. x // y             → 10 // 3 uses floor division (rounds down)
4. 10 ÷ 3 = 3.333...  → but // keeps only the whole number part
5. print(x // y)      → prints 3

💡 Key insight: // is floor division - it divides and rounds DOWN to nearest integer!"""
    },
    
    {
        "code": """numbers = [5, 2, 8, 1]
print(max(numbers))""",
        "options": ["A) 5", "B) 1", "C) 8", "D) 16"],
        "correct": "C",
        "explanation": """🔍 Breaking it down:
1. numbers = [5, 2, 8, 1]  → numbers contains a list of 4 integers
2. max(numbers)            → finds the largest value in the list
3. Looking at [5, 2, 8, 1] → 8 is the biggest number
4. print(max(numbers))     → prints 8

💡 Key insight: max() function finds the largest value in a collection!"""
    }
]

def ask_question(question_data, question_num, total_questions):
    """Display a question and get the user's answer"""
    print(f"{Colors.BLUE}{Colors.BOLD}Question {question_num}/{total_questions}:{Colors.END}")
    print(f"{Colors.WHITE}What will this code output?{Colors.END}\n")
    
    # Display the code in a nice box
    print(f"{Colors.PURPLE}┌{'─' * 30}┐")
    for line in question_data["code"].split('\n'):
        print(f"│ {line:<28} │")
    print(f"└{'─' * 30}┘{Colors.END}\n")
    
    # Display options
    for option in question_data["options"]:
        print(f"{Colors.CYAN}{option}{Colors.END}")
    
    print()
    while True:
        answer = input(f"{Colors.BOLD}Your answer (A, B, C, or D): {Colors.END}").upper().strip()
        if answer in ['A', 'B', 'C', 'D']:
            return answer
        print(f"{Colors.RED}Please enter A, B, C, or D{Colors.END}")

def show_result(user_answer, correct_answer, explanation):
    """Show whether the answer was correct and explain the reasoning"""
    print()
    if user_answer == correct_answer:
        print(f"{Colors.GREEN}{Colors.BOLD}🎉 CORRECT! Well done, detective!{Colors.END}\n")
    else:
        print(f"{Colors.RED}{Colors.BOLD}❌ Not quite right. The correct answer was {correct_answer}{Colors.END}\n")
    
    print(f"{Colors.YELLOW}{Colors.BOLD}🔍 DETECTIVE EXPLANATION:{Colors.END}")
    print(f"{Colors.WHITE}{explanation}{Colors.END}\n")
    
    input(f"{Colors.CYAN}Press Enter to continue...{Colors.END}")
    print()

def run_quiz():
    """Main quiz function"""
    print_header()
    print_thinking_steps()
    
    # Ask if they want to see the methodology
    show_method = input(f"{Colors.BOLD}Want to see the detective method before each question? (y/n): {Colors.END}").lower().strip()
    print()
    
    # Shuffle questions for variety
    questions = quiz_questions.copy()
    random.shuffle(questions)
    
    score = 0
    total_questions = len(questions)
    
    for i, question in enumerate(questions, 1):
        if show_method == 'y':
            print_thinking_steps()
        
        user_answer = ask_question(question, i, total_questions)
        correct = user_answer == question["correct"]
        
        if correct:
            score += 1
            
        show_result(user_answer, question["correct"], question["explanation"])
    
    # Final results
    print(f"{Colors.CYAN}{Colors.BOLD}{'='*60}")
    print(f"\n")
    print("🎯 FINAL DETECTIVE REPORT")
    print(f"\n")
    print(f"{'='*60}{Colors.END}")
    
    percentage = (score / total_questions) * 100
    print(f"{Colors.WHITE}Score: {Colors.BOLD}{score}/{total_questions} ({percentage:.1f}%){Colors.END}")
    
    if percentage >= 80:
        print(f"{Colors.GREEN}{Colors.BOLD}🏆 MASTER DETECTIVE! You've got great Python intuition!{Colors.END}")
    elif percentage >= 60:
        print(f"{Colors.YELLOW}{Colors.BOLD}🔍 GOOD DETECTIVE WORK! Keep practicing the method!{Colors.END}")
    else:
        print(f"{Colors.PURPLE}{Colors.BOLD}🎓 LEARNING DETECTIVE! The method takes practice - you've got this!{Colors.END}")
    
    print(f"\n{Colors.CYAN}Remember: The goal isn't to get everything right immediately.")
    print("It's to learn the thinking process that makes you a better programmer!")
    print(f"Keep practicing the detective method!{Colors.END}\n")

if __name__ == "__main__":
    run_quiz()