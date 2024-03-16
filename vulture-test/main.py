def first() -> None:
    print('hi')

def second(recurse: bool = False) -> None:
    if recurse:
        second()