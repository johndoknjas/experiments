from rich.console import Console
from rich.style import Style

console = Console()

def print_colors(l: list[str], message: str) -> None:
    print(message)
    for c in l:
        console.print("not bold", style=Style(color=c, bold=False))
        console.print("bold", style=Style(color=c, bold=True))
        print('\n')

print_colors(['bright_red', 'grey100', 'grey39', 'bright_magenta', 'purple'], 
             "For these colors, the bold parameter seems to make no visual difference:\n")
print_colors(['white', 'red', 'magenta'], 
             "------------------------------\nFor these colors, the bold parameter does make a difference:\n")