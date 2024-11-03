import sys
from typing import Optional
from copy import copy

def first(args: Optional[list[str]]) -> None:
    args = copy(sys.argv)
    print(sys.argv if args is None else args)

def second(args: Optional[list[str]]) -> None:
    print(sys.argv if sys.argv is None else args)